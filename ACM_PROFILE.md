# VSCode ACM Profile

这个目录带了一个独立的 ACM 启动环境，用户数据和扩展都放在 `.acm-vscode/`，不会污染你默认 VSCode。

## 首次安装扩展

双击：

```bat
scripts\setup-acm-profile.cmd
```

它只会给 ACM 环境安装这些扩展：

- Competitive Programming Helper
- C/C++
- Error Lens
- CodeSnap
- Background
- Chinese Language Pack

## 启动

双击：

```bat
scripts\open-acm-profile.cmd
```

等价命令：

```bat
code --new-window --user-data-dir D:\VSC\code_ex\.acm-vscode\user-data --extensions-dir D:\VSC\code_ex\.acm-vscode\extensions D:\VSC\code_ex
```

## 配置同步

`scripts\open-acm-profile.cmd` 每次启动前会同步你的 C++ snippets 和快捷键到 ACM 环境；扩展只需要首次用 `scripts\setup-acm-profile.cmd` 安装。
