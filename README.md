# ACM 刷题知识库

[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE) ![Problems](https://img.shields.io/badge/problems-1209-blue) ![C++](https://img.shields.io/badge/C%2B%2B-20-blue) [![CI](https://github.com/ZFM-1208/ACM-Algorithm/actions/workflows/index-check.yml/badge.svg)](https://github.com/ZFM-1208/ACM-Algorithm/actions/workflows/index-check.yml)

> 自动生成时间：2026-10-11 00:35:22

这个 README 由 `tools/update_acm_index.ps1` 扫描代码和 CPH 记录生成。平时只需要改 `problem-notes.csv` 里的标签、状态、是否补题和错因，然后刷新索引。

## 目录

- [快速命令](#快速命令)
- [总览](#总览)
- [最近做题](#最近做题)
- [待补题 / 错因记录](#待补题--错因记录)
- [ACM Profile 环境](#acm-profile-环境)
- [记录字段](#记录字段)

## 快速命令

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\tools\update_acm_index.ps1
```

VSCode 里也可以运行任务：`ACM: update knowledge base`。

## 总览

| 平台/目录 | 题数 |
| --- | ---: |
| 原clion模板残留 | 327 |
| CodeForces | 292 |
| XCPC | 122 |
| 排位赛 | 94 |
| 牛客 | 67 |
| AtCoder | 58 |
| 杭电 | 55 |
| 马蹄杯 | 38 |
| 天梯赛 | 32 |
| 奶龙杯-可恶 | 29 |
| A组队赛 | 23 |
| 蓝桥杯 | 20 |
| DP专练 | 8 |
| 虚树 | 8 |
| A训练 | 8 |
| 好题 | 7 |
| 树上启发式合并 | 7 |
| 二分图 | 5 |
| 2.28训练赛 | 5 |
| 出题R | 2 |
| 第六届上海理工大学ACM程序设计全国挑战赛 | 2 |
| **Total** | **1209** |

## 最近做题

| 时间 | 平台 | 题目 | 标签 | 状态 | 错因/备注 | 路径 |
| --- | --- | --- | --- | --- | --- | --- |
| 2026-10-11 | CodeForces | [C. XOR Problem](https://codeforces.com/contest/2271/problem/C) |  |  |  | [code](CodeForces/2271/C.%20XOR%20Problem.cpp) |
| 2026-10-10 | CodeForces | [B. MEX Game](https://codeforces.com/contest/2271/problem/B) |  |  |  | [code](CodeForces/2271/B.%20MEX%20Game.cpp) |
| 2026-10-10 | CodeForces | [A. Robot Odd Moves](https://codeforces.com/contest/2271/problem/A) |  |  |  | [code](CodeForces/2271/A.%20Robot%20Odd%20Moves.cpp) |
| 2026-10-10 | XCPC | E |  |  |  | [code](XCPC/CCPC/2024CCPC重庆赛站/E.cpp) |
| 2026-10-10 | XCPC | I |  |  |  | [code](XCPC/CCPC/2024CCPC重庆赛站/I.cpp) |
| 2026-10-09 | XCPC | C |  |  |  | [code](XCPC/CCPC/2024CCPC重庆赛站/C.cpp) |
| 2026-10-09 | XCPC | B |  |  |  | [code](XCPC/CCPC/2024CCPC重庆赛站/B.cpp) |
| 2026-10-09 | XCPC | K |  |  |  | [code](XCPC/CCPC/2024CCPC重庆赛站/K.cpp) |
| 2026-10-09 | XCPC | J |  |  |  | [code](XCPC/CCPC/2024CCPC重庆赛站/J.cpp) |
| 2026-10-08 | XCPC | L - 树上游戏 |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/L%20-%20树上游戏.cpp) |
| 2026-10-08 | XCPC | A - 造计算机 |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/A%20-%20造计算机.cpp) |
| 2026-10-08 | XCPC | J - 新能源汽车 |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/J%20-%20新能源汽车.cpp) |
| 2026-10-08 | XCPC | C - 在哈尔滨指路 |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/C%20-%20在哈尔滨指路.cpp) |
| 2026-10-08 | CodeForces | [F](https://codeforces.com/contest/2275/problem/F) |  |  |  | [code](CodeForces/2275/F.cpp) |
| 2026-10-08 | XCPC | B - 凹包 |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/B%20-%20凹包.cpp) |
| 2026-10-08 | XCPC | M - 奇怪的上取整 |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/M%20-%20奇怪的上取整.cpp) |
| 2026-10-08 | XCPC | K - 农场经营 |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/K%20-%20农场经营.cpp) |
| 2026-10-08 | XCPC | G - 欢迎加入线上会议！ |  |  |  | [code](XCPC/CCPC/2024CCPC哈尔滨站/G%20-%20欢迎加入线上会议！.cpp) |
| 2026-10-08 | CodeForces | [E](https://codeforces.com/contest/2275/problem/E) |  |  |  | [code](CodeForces/2275/E.cpp) |
| 2026-10-07 | CodeForces | [D](https://codeforces.com/contest/2275/problem/D) |  |  |  | [code](CodeForces/2275/D.cpp) |
| 2026-10-07 | A训练 | b |  |  |  | [code](A训练/b.cpp) |
| 2026-10-07 | CodeForces | [B](https://codeforces.com/contest/2275/problem/B) |  |  |  | [code](CodeForces/2275/B.cpp) |
| 2026-10-07 | CodeForces | [C](https://codeforces.com/contest/2275/problem/C) |  |  |  | [code](CodeForces/2275/C.cpp) |
| 2026-10-07 | A训练 | a |  |  |  | [code](A训练/a.cpp) |
| 2026-10-04 | XCPC | G |  |  |  | [code](XCPC/ICPC/2024ICPC南京/G.cpp) |
| 2026-10-04 | XCPC | B |  |  |  | [code](XCPC/ICPC/2024ICPC南京/B.cpp) |
| 2026-10-04 | XCPC | K |  |  |  | [code](XCPC/ICPC/2024ICPC南京/K.cpp) |
| 2026-10-04 | XCPC | E |  |  |  | [code](XCPC/ICPC/2024ICPC南京/E.cpp) |
| 2026-09-29 | A训练 | c |  |  |  | [code](A训练/c.cpp) |
| 2026-09-27 | A训练 | e |  |  |  | [code](A训练/e.cpp) |
| 2026-09-22 | CodeForces | [D](https://codeforces.com/contest/2266/problem/D) |  |  |  | [code](CodeForces/2266/D.cpp) |
| 2026-09-22 | CodeForces | [E](https://codeforces.com/contest/2266/problem/E) |  |  |  | [code](CodeForces/2266/E.cpp) |
| 2026-09-21 | CodeForces | [C](https://codeforces.com/contest/2266/problem/C) |  |  |  | [code](CodeForces/2266/C.cpp) |
| 2026-09-11 | 牛客 | E |  |  |  | [code](牛客/小白月赛/小白月赛137/E.cpp) |
| 2026-09-11 | 牛客 | D |  |  |  | [code](牛客/小白月赛/小白月赛137/D.cpp) |
| 2026-09-09 | CodeForces | [D](https://codeforces.com/contest/2260/problem/D) |  |  |  | [code](CodeForces/2260/D.cpp) |
| 2026-09-08 | CodeForces | [C](https://codeforces.com/contest/2260/problem/C) |  |  |  | [code](CodeForces/2260/C.cpp) |
| 2026-09-08 | CodeForces | [B](https://codeforces.com/contest/2260/problem/B) |  |  |  | [code](CodeForces/2260/B.cpp) |
| 2026-09-08 | CodeForces | [A](https://codeforces.com/contest/2260/problem/A) |  |  |  | [code](CodeForces/2260/A.cpp) |
| 2026-09-06 | CodeForces | [F](https://codeforces.com/contest/2259/problem/F) |  |  |  | [code](CodeForces/2259/F.cpp) |

## 待补题 / 错因记录

_暂无。你可以在 `problem-notes.csv` 里把 `NeedReview` 填成 `是`，或者在 `Mistake` 写错因。_

## ACM Profile 环境

这个仓库带了一个独立的 VSCode ACM 环境，用户数据和扩展都放在 .acm-vscode/，不污染你日常的 VSCode。

- 首次安装扩展：双击 `scripts\setup-acm-profile.cmd`
- 启动 ACM 环境：双击 `scripts\open-acm-profile.cmd`
- 详细说明见 [ACM_PROFILE.md](ACM_PROFILE.md)

## 记录字段

- `Tags`：算法标签，比如 `dp;greedy;graph`。
- `Status`：建议填 `AC`、`WA后AC`、`待补`、`模板`。
- `NeedReview`：填 `是` 会进入待补题区。
- `Mistake`：写错因，比如 `边界没判 n=1`。
- `Note`：随手备注，比如做题思路或题解链接。
