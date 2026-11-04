# ACM 刷题知识库

[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE) ![Problems](https://img.shields.io/badge/problems-1253-blue) ![C++](https://img.shields.io/badge/C%2B%2B-20-blue) [![CI](https://github.com/ZFM-1208/ACM-Algorithm/actions/workflows/index-check.yml/badge.svg)](https://github.com/ZFM-1208/ACM-Algorithm/actions/workflows/index-check.yml)

> 自动生成时间：2026-11-04 21:13:31

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
| CodeForces | 302 |
| XCPC | 133 |
| 排位赛 | 94 |
| 牛客 | 67 |
| AtCoder | 64 |
| 杭电 | 55 |
| 马蹄杯 | 38 |
| 天梯赛 | 32 |
| 奶龙杯-可恶 | 29 |
| A组队赛 | 23 |
| 蓝桥杯 | 20 |
| 有人天生为王，有人落草为寇 | 14 |
| 虚树 | 8 |
| A训练 | 8 |
| DP专练 | 8 |
| 树上启发式合并 | 7 |
| 好题 | 7 |
| 二分图 | 5 |
| 2.28训练赛 | 5 |
| Tarjan | 3 |
| 出题R | 2 |
| 第六届上海理工大学ACM程序设计全国挑战赛 | 2 |
| **Total** | **1253** |

## 最近做题

| 时间 | 平台 | 题目 | 标签 | 状态 | 错因/备注 | 路径 |
| --- | --- | --- | --- | --- | --- | --- |
| 2026-11-04 | XCPC | I - Barkley II |  |  |  | [code](XCPC/CCPC/2023CCPC桂林站/I%20-%20Barkley%20II.cpp) |
| 2026-11-04 | XCPC | K - Randias Permutation Task |  |  |  | [code](XCPC/CCPC/2023CCPC桂林站/K%20-%20Randias%20Permutation%20Task.cpp) |
| 2026-11-04 | XCPC | M - Flipping Cards  |  |  |  | [code](XCPC/CCPC/2023CCPC桂林站/M%20-%20Flipping%20Cards%20.cpp) |
| 2026-11-04 | XCPC | G - Hard Brackets Problem  |  |  |  | [code](XCPC/CCPC/2023CCPC桂林站/G%20-%20Hard%20Brackets%20Problem%20.cpp) |
| 2026-11-02 | CodeForces | [F. Modulo and Counting](https://codeforces.com/contest/2278/problem/F) |  |  |  | [code](CodeForces/2278/F.%20Modulo%20and%20Counting.cpp) |
| 2026-11-02 | CodeForces | [E. Swap and Negate](https://codeforces.com/contest/2278/problem/E) |  |  |  | [code](CodeForces/2278/E.%20Swap%20and%20Negate.cpp) |
| 2026-11-02 | CodeForces | [D. Lock and Unlock](https://codeforces.com/contest/2278/problem/D) |  |  |  | [code](CodeForces/2278/D.%20Lock%20and%20Unlock.cpp) |
| 2026-11-02 | CodeForces | [C. Math and Physics](https://codeforces.com/contest/2278/problem/C) |  |  |  | [code](CodeForces/2278/C.%20Math%20and%20Physics.cpp) |
| 2026-11-02 | CodeForces | [B. Stakes and Shapes](https://codeforces.com/contest/2278/problem/B) |  |  |  | [code](CodeForces/2278/B.%20Stakes%20and%20Shapes.cpp) |
| 2026-11-02 | A训练 | b |  |  |  | [code](A训练/b.cpp) |
| 2026-11-02 | A训练 | a |  |  |  | [code](A训练/a.cpp) |
| 2026-11-02 | CodeForces | [A. Fraction and Six](https://codeforces.com/contest/2278/problem/A) |  |  |  | [code](CodeForces/2278/A.%20Fraction%20and%20Six.cpp) |
| 2026-10-27 | CodeForces | [C](https://codeforces.com/contest/2272/problem/C) |  |  |  | [code](CodeForces/2272/C.cpp) |
| 2026-10-27 | CodeForces | [D](https://codeforces.com/contest/2272/problem/D) |  |  |  | [code](CodeForces/2272/D.cpp) |
| 2026-10-26 | CodeForces | [B](https://codeforces.com/contest/2272/problem/B) |  |  |  | [code](CodeForces/2272/B.cpp) |
| 2026-10-26 | CodeForces | [A](https://codeforces.com/contest/2272/problem/A) |  |  |  | [code](CodeForces/2272/A.cpp) |
| 2026-10-26 | AtCoder | [A](https://atcoder.jp/contests/abc481/tasks/abc481_a) |  |  |  | [code](AtCoder/ABC481/A.cpp) |
| 2026-10-24 | AtCoder | [F - Evil Shortest Path](https://atcoder.jp/contests/abc481/tasks/abc481_f) |  |  |  | [code](AtCoder/ABC481/F%20-%20Evil%20Shortest%20Path.cpp) |
| 2026-10-24 | AtCoder | [E](https://atcoder.jp/contests/abc481/tasks/abc481_e) |  |  |  | [code](AtCoder/ABC481/E.cpp) |
| 2026-10-24 | AtCoder | [D](https://atcoder.jp/contests/abc481/tasks/abc481_d) |  |  |  | [code](AtCoder/ABC481/D.cpp) |
| 2026-10-24 | AtCoder | [C](https://atcoder.jp/contests/abc481/tasks/abc481_c) |  |  |  | [code](AtCoder/ABC481/C.cpp) |
| 2026-10-24 | AtCoder | [B](https://atcoder.jp/contests/abc481/tasks/abc481_b) |  |  |  | [code](AtCoder/ABC481/B.cpp) |
| 2026-10-21 | XCPC | K. 纸带染色 |  |  |  | [code](XCPC/CCPC/2026CCPC长春站/K.%20纸带染色.cpp) |
| 2026-10-21 | XCPC | M. 余镜 |  |  |  | [code](XCPC/CCPC/2026CCPC长春站/M.%20余镜.cpp) |
| 2026-10-21 | XCPC | C. 无忧旋律 |  |  |  | [code](XCPC/CCPC/2026CCPC长春站/C.%20无忧旋律.cpp) |
| 2026-10-21 | XCPC | J. 送给好友的惊喜 |  |  |  | [code](XCPC/CCPC/2026CCPC长春站/J.%20送给好友的惊喜.cpp) |
| 2026-10-21 | XCPC | A. 又一道纸笔问题 |  |  |  | [code](XCPC/CCPC/2026CCPC长春站/A.%20又一道纸笔问题.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | AG |  |  |  | [code](有人天生为王，有人落草为寇/AG.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | AF |  |  |  | [code](有人天生为王，有人落草为寇/AF.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | AE |  |  |  | [code](有人天生为王，有人落草为寇/AE.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | AD |  |  |  | [code](有人天生为王，有人落草为寇/AD.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | AC |  |  |  | [code](有人天生为王，有人落草为寇/AC.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | AB |  |  |  | [code](有人天生为王，有人落草为寇/AB.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | AA |  |  |  | [code](有人天生为王，有人落草为寇/AA.cpp) |
| 2026-10-13 | Tarjan | (e-BCC) |  |  |  | [code](Tarjan/(e-BCC).cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | Z |  |  |  | [code](有人天生为王，有人落草为寇/Z.cpp) |
| 2026-10-13 | Tarjan | SCC |  |  |  | [code](Tarjan/SCC.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | U |  |  |  | [code](有人天生为王，有人落草为寇/U.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | T |  |  |  | [code](有人天生为王，有人落草为寇/T.cpp) |
| 2026-10-13 | 有人天生为王，有人落草为寇 | S |  |  |  | [code](有人天生为王，有人落草为寇/S.cpp) |

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
