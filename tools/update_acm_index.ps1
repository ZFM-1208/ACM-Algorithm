param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path,
    [int]$Recent = 40
)

$ErrorActionPreference = "Stop"

function Normalize-RelativePath {
    param(
        [Parameter(Mandatory = $true)][string]$Path,
        [Parameter(Mandatory = $true)][string]$Base
    )

    $fullPath = [System.IO.Path]::GetFullPath($Path)
    $fullBase = [System.IO.Path]::GetFullPath($Base).TrimEnd('\') + '\'
    return $fullPath.Substring($fullBase.Length).Replace('\', '/')
}

function Normalize-FullPath {
    param([Parameter(Mandatory = $true)][string]$Path)
    return [System.IO.Path]::GetFullPath($Path)
}

function Test-WebUrl {
    param([string]$Url)
    return $Url -match '^https?://'
}

function Get-ProblemFiles {
    param([Parameter(Mandatory = $true)][string]$Root)

    Get-ChildItem -LiteralPath $Root -Recurse -File -ErrorAction SilentlyContinue |
        Where-Object {
            $_.Extension -in @(".cpp", ".cc", ".cxx") -and
            $_.Length -gt 0 -and
            (Normalize-RelativePath $_.FullName $Root) -notmatch '(^|/)(\.git|\.cph|\.vscode|\.acm-vscode)(/|$)'
        }
}

function Get-CphProblemMap {
    param([Parameter(Mandatory = $true)][string]$Root)

    $map = @{}
    $invalidCount = 0
    Get-ChildItem -LiteralPath $Root -Recurse -File -Filter "*.prob" -ErrorAction SilentlyContinue |
        ForEach-Object {
            $filePath = $_.FullName
            try {
                $problem = Get-Content -LiteralPath $filePath -Raw | ConvertFrom-Json
                if ($problem.srcPath) {
                    $map[(Normalize-FullPath $problem.srcPath)] = $problem
                }
            } catch {
                $invalidCount++
            }
        }
    if ($invalidCount -gt 0) {
        Write-Warning "Skipped $invalidCount invalid CPH records."
    }
    return $map
}

function Get-Platform {
    param([Parameter(Mandatory = $true)][string]$RelativePath)

    $parts = $RelativePath -split '/'
    if ($parts.Count -le 1) { return "Root" }
    return $parts[0]
}

function Get-InferredUrl {
    param(
        [Parameter(Mandatory = $true)][string]$RelativePath,
        [Parameter(Mandatory = $true)][string]$Title
    )

    $path = $RelativePath.Replace('\', '/')
    $base = [System.IO.Path]::GetFileNameWithoutExtension($path)

    if ($path -match '^CodeForces/([^/]+)/(.+)\.(cpp|cc|cxx)$') {
        $contest = $matches[1]
        $index = $null
        if ($base -match '^([A-Za-z][0-9]?)(\.|_| |-|\b)') {
            $index = $matches[1]
        }
        if ($index) {
            $contestNumber = 0
            if ([int]::TryParse($contest, [ref]$contestNumber) -and $contestNumber -ge 100000) {
                return "https://codeforces.com/gym/$contest/problem/$index"
            }
            return "https://codeforces.com/contest/$contest/problem/$index"
        }
    }

    if ($path -match '^AtCoder/([^/]+)/(.+)\.(cpp|cc|cxx)$') {
        $contest = $matches[1].ToLowerInvariant()
        $index = $null
        if ($base -match '^([A-Za-z])(\s*-\s*|\.|_|$)') {
            $index = $matches[1].ToLowerInvariant()
        }
        if ($index) {
            return "https://atcoder.jp/contests/$contest/tasks/${contest}_$index"
        }
    }

    if ($base -match '^(P\d+|B\d+)') {
        return "https://www.luogu.com.cn/problem/$($matches[1])"
    }

    return ""
}

function Read-Notes {
    param([Parameter(Mandatory = $true)][string]$NotesPath)

    $notes = @{}
    if (Test-Path -LiteralPath $NotesPath) {
        Import-Csv -LiteralPath $NotesPath | ForEach-Object {
            if ($_.Path) {
                $notes[$_.Path] = $_
            }
        }
    }
    return $notes
}

function New-NoteRow {
    param(
        [Parameter(Mandatory = $true)]$Problem,
        $Existing
    )

    [PSCustomObject]@{
        Path       = $Problem.Path
        Title      = $Problem.Title
        Platform   = $Problem.Platform
        Url        = $(if ($Existing -and $Existing.Url) { $Existing.Url } else { $Problem.Url })
        Tags       = $(if ($Existing) { $Existing.Tags } else { "" })
        Status     = $(if ($Existing) { $Existing.Status } else { "" })
        NeedReview = $(if ($Existing) { $Existing.NeedReview } else { "" })
        Mistake    = $(if ($Existing) { $Existing.Mistake } else { "" })
        Note       = $(if ($Existing) { $Existing.Note } else { "" })
    }
}

function Escape-Md {
    param([string]$Text)
    if ($null -eq $Text) { return "" }
    return ($Text -replace '\|', '\|') -replace "`r?`n", " "
}

function Link-Or-Dash {
    param(
        [string]$Text,
        [string]$Url
    )

    if (Test-WebUrl $Url) {
        return "[$(Escape-Md $Text)]($Url)"
    }
    return Escape-Md $Text
}

$root = (Resolve-Path -LiteralPath $Root).Path
$notesPath = Join-Path $root "problem-notes.csv"
$readmePath = Join-Path $root "README.md"
$cphMap = Get-CphProblemMap -Root $root

$problems = Get-ProblemFiles -Root $root | ForEach-Object {
    $relative = Normalize-RelativePath $_.FullName $root
    $title = [System.IO.Path]::GetFileNameWithoutExtension($_.Name)
    $platform = Get-Platform -RelativePath $relative
    $cph = $cphMap[(Normalize-FullPath $_.FullName)]
    $url = ""
    if ($cph -and (Test-WebUrl $cph.url)) {
        $url = $cph.url
    } else {
        $url = Get-InferredUrl -RelativePath $relative -Title $title
    }

    [PSCustomObject]@{
        Path          = $relative
        Title         = $title
        Platform      = $platform
        Url           = $url
        LastWriteTime = $_.LastWriteTime
    }
} | Sort-Object Path

$existingNotes = Read-Notes -NotesPath $notesPath
$noteRows = foreach ($problem in $problems) {
    New-NoteRow -Problem $problem -Existing $existingNotes[$problem.Path]
}
$noteRows | Sort-Object Path | Export-Csv -LiteralPath $notesPath -NoTypeInformation -Encoding UTF8

$notesByPath = @{}
$noteRows | ForEach-Object { $notesByPath[$_.Path] = $_ }

$enriched = foreach ($problem in $problems) {
    $note = $notesByPath[$problem.Path]
    [PSCustomObject]@{
        Path          = $problem.Path
        Title         = $problem.Title
        Platform      = $problem.Platform
        Url           = $(if ($note.Url) { $note.Url } else { $problem.Url })
        Tags          = $note.Tags
        Status        = $note.Status
        NeedReview    = $note.NeedReview
        Mistake       = $note.Mistake
        Note          = $note.Note
        LastWriteTime = $problem.LastWriteTime
    }
}

$stats = $enriched | Group-Object Platform | Sort-Object Count -Descending
$recentProblems = $enriched | Sort-Object LastWriteTime -Descending | Select-Object -First $Recent
$reviewProblems = $enriched | Where-Object {
    ($_.NeedReview -match '^(1|yes|y|true|是|补|待)$') -or
    ($_.Status -match '(补|待|review|todo|错|WA|wa)') -or
    ($_.Mistake -and $_.Mistake.Trim().Length -gt 0)
} | Sort-Object LastWriteTime -Descending

$now = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
$lines = New-Object System.Collections.Generic.List[string]
$lines.Add("# ACM 刷题知识库")
$lines.Add("")
$lines.Add("> 自动生成时间：$now")
$lines.Add("")
$lines.Add('这个 README 由 `tools/update_acm_index.ps1` 扫描代码和 CPH 记录生成。平时只需要改 `problem-notes.csv` 里的标签、状态、是否补题和错因，然后刷新索引。')
$lines.Add("")
$lines.Add("## 快速命令")
$lines.Add("")
$lines.Add('```powershell')
$lines.Add("powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\update_acm_index.ps1")
$lines.Add('```')
$lines.Add("")
$lines.Add('VSCode 里也可以运行任务：`ACM: update knowledge base`。')
$lines.Add("")
$lines.Add("## 总览")
$lines.Add("")
$lines.Add("| 平台/目录 | 题数 |")
$lines.Add("| --- | ---: |")
foreach ($item in $stats) {
    $lines.Add("| $(Escape-Md $item.Name) | $($item.Count) |")
}
$lines.Add("| **Total** | **$($enriched.Count)** |")
$lines.Add("")
$lines.Add("## 最近做题")
$lines.Add("")
$lines.Add("| 时间 | 平台 | 题目 | 标签 | 状态 | 错因/备注 | 路径 |")
$lines.Add("| --- | --- | --- | --- | --- | --- | --- |")
foreach ($p in $recentProblems) {
    $date = $p.LastWriteTime.ToString("yyyy-MM-dd")
    $title = Link-Or-Dash -Text $p.Title -Url $p.Url
    $path = "[code]($($p.Path -replace ' ', '%20'))"
    $remark = if ($p.Mistake) { $p.Mistake } else { $p.Note }
    $lines.Add("| $date | $(Escape-Md $p.Platform) | $title | $(Escape-Md $p.Tags) | $(Escape-Md $p.Status) | $(Escape-Md $remark) | $path |")
}
$lines.Add("")
$lines.Add("## 待补题 / 错因记录")
$lines.Add("")
if ($reviewProblems.Count -eq 0) {
    $lines.Add('_暂无。你可以在 `problem-notes.csv` 里把 `NeedReview` 填成 `是`，或者在 `Mistake` 写错因。_')
} else {
    $lines.Add("| 题目 | 状态 | 错因 | 标签 | 路径 |")
    $lines.Add("| --- | --- | --- | --- | --- |")
    foreach ($p in $reviewProblems) {
        $title = Link-Or-Dash -Text $p.Title -Url $p.Url
        $path = "[code]($($p.Path -replace ' ', '%20'))"
        $lines.Add("| $title | $(Escape-Md $p.Status) | $(Escape-Md $p.Mistake) | $(Escape-Md $p.Tags) | $path |")
    }
}
$lines.Add("")
$lines.Add("## 记录字段")
$lines.Add("")
$lines.Add('- `Tags`：算法标签，比如 `dp;greedy;graph`。')
$lines.Add('- `Status`：建议填 `AC`、`WA后AC`、`待补`、`模板`。')
$lines.Add('- `NeedReview`：填 `是` 会进入待补题区。')
$lines.Add('- `Mistake`：写错因，比如 `边界没判 n=1`。')
$lines.Add('- `Note`：随手备注，比如做题思路或题解链接。')

Set-Content -LiteralPath $readmePath -Value $lines -Encoding UTF8

Write-Host "Updated $readmePath"
Write-Host "Updated $notesPath"
Write-Host "Problems indexed: $($enriched.Count)"
