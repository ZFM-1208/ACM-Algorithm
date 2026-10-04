param(
    [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
)

$ErrorActionPreference = "Stop"
$root = (Resolve-Path -LiteralPath $Root).Path
$notesPath = Join-Path $root "problem-notes.csv"

# 目录关键词 -> 算法标签：路径中包含该关键词就追加标签（可自由扩展）。
# 平台/赛事目录（CodeForces、XCPC、排位赛等）不是算法，不在这里标注。
$tagMap = [ordered]@{
    "虚树"           = "虚树"
    "DP专练"         = "dp"
    "二分图"         = "二分图"
    "树上启发式合并" = "dsu-on-tree"
}

$rows = Import-Csv -LiteralPath $notesPath
$updated = 0

foreach ($row in $rows) {
    $tags = @()
    if ($row.Tags -and $row.Tags.Trim().Length -gt 0) {
        $tags += ($row.Tags -split ';' | ForEach-Object { $_.Trim() } | Where-Object { $_ })
    }

    foreach ($key in $tagMap.Keys) {
        if ($row.Path -like "*$key*") {
            $t = $tagMap[$key]
            if ($tags -notcontains $t) { $tags += $t }
        }
    }

    $newTags = ($tags -join ';')
    if ($newTags -ne $row.Tags) {
        $row.Tags = $newTags
        $updated++
    }
}

$rows | Export-Csv -LiteralPath $notesPath -NoTypeInformation -Encoding UTF8
Write-Host "Tags applied to $updated rows."
