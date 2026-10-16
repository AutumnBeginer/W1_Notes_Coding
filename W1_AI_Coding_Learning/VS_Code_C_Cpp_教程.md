# VS Code 编写 C/C++ 全流程教程：从零配置到语言精通

> 一份面向已掌握 C++ 的读者的实战手册。读完你能独立完成「安装配置 → 编写 → 编译调试 → 项目构建」，并快速补齐 C 语言的核心差异点。

---

## 目录

1. [前置认知：C、C++ 与 VS Code 的关系](#1-前置认知)
2. [环境安装与编译器配置](#2-环境安装与编译器配置)
3. [VS Code 界面全景导览](#3-vs-code-界面全景导览)
4. [必背快捷键清单](#4-必背快捷键清单)
5. [第一个程序：从 Hello World 到一键编译](#5-第一个程序)
6. [核心三件套：tasks.json / launch.json / c_cpp_properties.json](#6-核心三件套)
7. [调试（Debug）全流程](#7-调试全流程)
8. [C++ 快速复习（重温要点）](#8-c-快速复习)
9. [从 C++ 到 C：迁移指南](#9-从-c-到-c迁移指南)
10. [C 语言核心要点速览](#10-c-语言核心要点速览)
11. [多文件项目与 Makefile / CMake](#11-多文件项目与构建)
12. [实用插件与效率技巧](#12-实用插件与效率技巧)
13. [常见坑与排错速查表](#13-常见坑与排错速查表)

---

## 1. 前置认知

### 1.1 三个角色各司其职

很多初学者混淆了「编辑器」和「编译器」。务必分清：

| 角色 | 是什么 | 举例 | 本教程中的选择 |
|---|---|---|---|
| **编辑器 Editor** | 写代码、看代码的地方，本身不能编译 | VS Code、Vim、记事本 | **VS Code** |
| **编译器 Compiler** | 把源码翻译成机器码的工具 | GCC、Clang、MSVC | **GCC（Linux/macOS）/ MinGW-w64（Windows）** |
| **调试器 Debugger** | 逐行执行、看变量、找 bug | GDB、LLDB | **GDB** |

**一句话**：VS Code 负责"写"，GCC 负责"翻译"，GDB 负责"查"。三者通过配置文件串起来。

### 1.2 C 与 C++ 的关系

- C++ 是 C 的超集（大部分 C 代码能当 C++ 编译，反之不然）。
- 文件后缀：`C` 用 `.c`，`C++` 用 `.cpp` / `.cc` / `.cxx`。
- 编译命令区别：`gcc` 默认当 C 编译，`g++` 默认当 C++ 编译并自动链接 C++ 标准库。
- 本质差异：C 没有类、模板、引用、命名空间、函数重载；C 更贴近底层，头文件与内存管理要自己操心。

---

## 2. 环境安装与编译器配置

### 2.1 第一步：装 VS Code

官网下载安装包一路下一步即可：https://code.visualstudio.com/

### 2.2 第二步：装编译器

#### Windows（推荐 MSYS2 + MinGW-w64）

1. 安装 [MSYS2](https://www.msys2.org/)。
2. 打开 **MSYS2 UCRT64** 终端，依次执行：
   ```bash
   pacman -Syu                    # 更新包数据库
   pacman -S mingw-w64-ucrt-x86_64-gcc   # 安装 GCC
   pacman -S mingw-w64-ucrt-x86_64-gdb   # 安装 GDB
   ```
3. 把 `C:\msys64\ucrt64\bin` 加入系统环境变量 `PATH`，重启终端验证：
   ```bash
   gcc --version
   g++ --version
   gdb --version
   ```
   三条命令都能输出版本号即成功。

#### Linux（Ubuntu/Debian）

```bash
sudo apt update
sudo apt install build-essential gdb
```

#### macOS

先装 Xcode 命令行工具：
```bash
xcode-select --install
```

### 2.3 第三步：装 VS Code 插件

打开扩展面板（`Ctrl+Shift+X`），搜索安装：

| 插件 | 作用 |
|---|---|
| **C/C++**（Microsoft） | 智能提示、跳转、调试支持，必装 |
| **C/C++ CMake Tools** | CMake 项目集成（进阶） |
| **Code Runner** | 一键运行单文件，快速验证 |
| **GitLens** | Git 增强，看代码历史 |
| **Better Comments** | 让注释分色高亮 |

> 只装第一个也能完成所有工作，其余是效率加成。

---

## 3. VS Code 界面全景导览

启动后界面分五大区，记住它们的名字和位置：

```
┌──────────────────────────────────────────────────────────┐
│  菜单栏  文件(F) 编辑(E) 选择(S) 查看(V) 运行(R) 终端(T)   │ ← 菜单栏
├──────┬─────────────────────────────────────┬─────────────┤
│      │                                     │             │
│ 活动栏│          编辑器区域(可多标签页)       │   侧边栏     │
│ • 文件│  ┌───────────────────────────────┐  │ (资源管理器/ │
│ • 搜索│  │ main.cpp                      │  │  搜索/运行/  │
│ • Git │  │ #include <iostream>           │  │  扩展 随选中 │
│ • 运行│  │ int main() { ... }            │  │  活动栏变化) │
│ • 扩展│  └───────────────────────────────┘  │             │
│      │                                     │             │
├──────┴─────────────────────────────────────┴─────────────┤
│ 状态栏：分支 · 错误/警告数 · 语言模式 · 编码 · 行:列       │ ← 状态栏
├──────────────────────────────────────────────────────────┤
│ 面板（终端 / 调试控制台 / 问题 / 输出，按 Ctrl+` 切换）      │ ← 面板
└──────────────────────────────────────────────────────────┘
```

### 关键概念

- **活动栏**（最左侧竖条）：切换五大功能视图。
- **侧边栏**：跟随活动栏显示对应内容，资源管理器里能看到你的文件夹树。
- **面包屑**（编辑器顶部）：显示当前文件在目录中的路径，可点击跳转。
- **状态栏**（最底部）：最右端会显示当前文件语言，点它可切换；中间有错误和警告计数。
- **命令面板**（`Ctrl+Shift+P`）：VS Code 的"总控制台"，**任何操作都能在这里搜到**，记不住快捷键时它就是你最好的朋友。

---

## 4. 必背快捷键清单

> 不需要全背，先把「★核心」组练成肌肉记忆，其余用到再查。

### ★ 核心操作（最高频）

| 快捷键 | 功能 |
|---|---|
| `Ctrl+Shift+P` | 打开命令面板 |
| `Ctrl+P` | 快速打开文件（输入文件名跳转） |
| `Ctrl+Shift+N` | 新建 VS Code 窗口 |
| `Ctrl+W` | 关闭当前标签页 |
| `Ctrl+`` ` `` | 显示/隐藏终端 |
| `Ctrl+B` | 显示/隐藏侧边栏 |

### 编辑操作

| 快捷键 | 功能 |
|---|---|
| `Ctrl+C` / `Ctrl+V` / `Ctrl+X` | 复制 / 粘贴 / 剪切（**不选中时默认操作整行**） |
| `Ctrl+Z` / `Ctrl+Y` | 撤销 / 重做 |
| `Ctrl+/` | 单行注释 / 取消注释 |
| `Shift+Alt+A` | 块注释 `/* */` |
| `Alt+↑` / `Alt+↓` | 把当前行上移 / 下移 |
| `Shift+Alt+↑/↓` | 向上 / 向下复制当前行 |
| `Ctrl+D` | 选中下一个相同词（多光标神器） |
| `Alt+鼠标点击` | 多处插入光标 |
| `Ctrl+Shift+L` | 选中所有相同词并多光标编辑 |
| `Ctrl+F` / `Ctrl+H` | 查找 / 替换 |
| `Ctrl+Enter` | 在光标下方插入新行（不离开当前行） |

### 导航跳转

| 快捷键 | 功能 |
|---|---|
| `F12` | 跳转到定义 |
| `Alt+F12` | 查看定义（小窗预览，不跳转） |
| `Ctrl+Click` | 跳转到定义（鼠标版） |
| `Alt+←` / `Alt+→` | 后退 / 前进到上次光标位置 |
| `Ctrl+G` | 跳到指定行号 |
| `Ctrl+Shift+O` | 在当前文件内按符号（函数/类）跳转 |
| `Ctrl+T` | 在工作区内搜索符号 |

### 窗口与排版

| 快捷键 | 功能 |
|---|---|
| `Ctrl+\` | 拆分编辑器（左右分屏） |
| `Ctrl+1/2/3` | 聚焦到第 1/2/3 个编辑器组 |
| `Shift+Alt+F` | 格式化整个文档（需装 C/C++ 插件） |
| `Ctrl+K Ctrl+F` | 格式化选中代码 |
| `Ctrl+K Z` | 禅模式（全屏沉浸） |

### 编译运行与调试

| 快捷键 | 功能 |
|---|---|
| `F5` | 启动调试 |
| `Ctrl+F5` | 运行但不调试 |
| `F9` | 切换断点 |
| `F10` | 单步跳过（Step Over） |
| `F11` | 单步进入（Step Into） |
| `Shift+F11` | 单步跳出（Step Out） |
| `Ctrl+Shift+B` | 运行生成任务（编译） |

### 多选与块操作技巧

- **列选择（框选）**：按住 `Shift+Alt` 再拖动鼠标，可竖着选中一列，批量改多行缩进或多行前缀。
- **多光标** + 同时编辑：改一个变量名时比全局替换安全得多。

---

## 5. 第一个程序

### 5.1 命令行编译（理解本质）

新建文件夹 `hello`，在里面创建 `main.cpp`：

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello, VS Code!" << endl;
    return 0;
}
```

打开 VS Code 终端（`Ctrl+`` ` ``），输入：

```bash
g++ main.cpp -o hello      # 编译，生成可执行文件 hello
./hello                    # 运行（Windows 下是 hello.exe）
```

**推荐加上警告参数**，能抓出大量隐患：

```bash
g++ -Wall -Wextra -std=c++17 -g main.cpp -o hello
# -Wall -Wextra : 开启常用警告
# -std=c++17    : 指定 C++ 标准
# -g            : 加入调试信息（否则断点不生效）
```

### 5.2 Code Runner 一键运行

装了 Code Runner 后，右上角出现 ▶ 按钮，点击即可一键编译运行。本质是它在后台帮你拼好了 `g++` 命令。

> 小文件练习够用，正式项目和需要调试时还是推荐用下一节的 `tasks.json`。

---

## 6. 核心三件套

当你打开一个文件夹并第一次尝试编译/调试时，VS Code 会引导你生成 `.vscode` 文件夹，里面有三个关键配置文件。**理解它们，你就掌握了 VS Code 的精髓。**

```
你的项目/
├── main.cpp
├── math.cpp
├── math.h
└── .vscode/
    ├── tasks.json           ← 告诉 VS Code "怎么编译"
    ├── launch.json          ← 告诉 VS Code "怎么启动调试"
    └── c_cpp_properties.json← 告诉 IntelliSense "去哪找头文件、用什么标准"
```

### 6.1 tasks.json —— 编译任务

`Ctrl+Shift+P` → 输入 `Tasks: Configure Task` → `Create tasks.json from template` → `Others`，替换为：

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-Wall", "-Wextra", "-std=c++17", "-g",
                "${workspaceFolder}/*.cpp",
                "-o", "${workspaceFolder}/app"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        }
    ]
}
```

之后按 `Ctrl+Shift+B` 即可一键编译。

**变量说明**：

| 变量 | 含义 |
|---|---|
| `${workspaceFolder}` | 当前打开的项目根目录绝对路径 |
| `${file}` | 当前打开的文件 |
| `${fileDirname}` | 当前文件所在目录 |
| `${fileBasenameNoExtension}` | 当前文件名（不含扩展名） |

想只编译当前文件，把 `args` 里的 `*.cpp` 换成 `"${file}"` 和 `"-o", "${fileDirname}/${fileBasenameNoExtension}"`。

### 6.2 launch.json —— 调试配置

`Run` 视图 → `create a launch.json file` → `C++ (GDB/LLDB)`，替换为：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug app",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/app",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "build"
        }
    ]
}
```

`"preLaunchTask": "build"` 是关键：它让按 `F5` 时**先自动编译再启动调试**，保证你调试的是最新代码。

### 6.3 c_cpp_properties.json —— IntelliSense

`Ctrl+Shift+P` → `C/C++: Edit Configurations (UI)`，主要填两项：

- **Compiler path**：选你的 `g++` 路径（如 `/usr/bin/g++`）。
- **C++ standard**：选 `C++17` 或你项目用的标准。

它会自动生成：

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": ["${workspaceFolder}/**"],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```

> **为什么要这个文件？** 没有它，`#include` 会报红、跳转定义失效——因为 IntelliSense 不知道你的头文件在哪、用什么标准。

---

## 7. 调试全流程

### 7.1 打断点

在代码行号左侧点击，出现红点即为断点（`F9` 切换）。

### 7.2 启动调试

按 `F5`。程序会在断点处暂停，此时可用：

| 操作 | 快捷键 | 作用 |
|---|---|---|
| 单步跳过 | `F10` | 执行当前行，不进入函数内部 |
| 单步进入 | `F11` | 进入当前行调用的函数内部 |
| 单步跳出 | `Shift+F11` | 从当前函数返回到调用处 |
| 继续 | `F5` | 跑到下一个断点 |
| 重启 | `Ctrl+Shift+F5` | 重新启动调试 |
| 停止 | `Shift+F5` | 结束调试 |

### 7.3 观察变量

- **左侧"变量"面板**：自动显示当前作用域的所有变量。
- **悬停**：鼠标悬停在编辑器里的变量上，直接显示其值。
- **监视（Watch）**：把想持续观察的表达式拖进"监视"面板。
- **调试控制台**：可在暂停时执行表达式求值。

**调试的正确姿势**：先想"我怀疑哪一步算错了"，在那一行打断点，运行到那看变量，一步步缩小范围。比 `cout` 大法高效得多。

---

## 8. C++ 快速复习

> 这部分是速查式回顾，帮你快速唤起记忆。每个点给出核心语法和一句话要点。

### 8.1 程序骨架

```cpp
#include <iostream>      // 头文件
using namespace std;      // 使用标准命名空间

int main() {             // 程序入口，返回 int
    cout << "hi" << endl;
    return 0;            // 0 表示成功
}
```

### 8.2 基础类型与变量

| 类型 | 说明 | 大小（典型） |
|---|---|---|
| `bool` | 布尔 | 1 byte |
| `char` | 字符 | 1 byte |
| `int` | 整型 | 4 bytes |
| `long long` | 长整型 | 8 bytes |
| `float` | 单精度浮点 | 4 bytes |
| `double` | 双精度浮点 | 8 bytes |
| `auto` | 自动推导 | 由初始化值决定 |

```cpp
int a = 10;
double pi = 3.14159;
auto b = 3.14;        // b 是 double
const int N = 100;    // 常量，不可修改
```

### 8.3 流程控制

```cpp
if (x > 0) { ... } else if (x == 0) { ... } else { ... }
for (int i = 0; i < n; ++i) { ... }
while (cond) { ... }
do { ... } while (cond);
for (auto& x : container) { ... }   // 范围 for（C++11）
switch (val) { case 1: ...; break; default: ...; }
```

### 8.4 函数

```cpp
int add(int a, int b);                    // 声明
int add(int a, int b) { return a + b; }   // 定义
// 重载：同名不同参数
int add(int a, int b, int c) { return a + b + c; }
// 默认参数
void log(string msg, int level = 1);
// 引用传参（避免拷贝、可修改实参）
void swap(int& a, int& b);
```

### 8.5 数组与 STL 容器

```cpp
int arr[10];                 // 原生数组
#include <vector>
vector<int> v = {1, 2, 3};   // 动态数组
v.push_back(4);
// 常用容器
#include <string>    // string
#include <map>       // 有序映射
#include <unordered_map>  // 哈希映射
#include <set>       // 集合
```

### 8.6 类与面向对象

```cpp
class Person {
private:
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {}   // 构造函数初始化列表
    void say() const { cout << name << endl; }     // const 成员函数
    virtual ~Person() = default;                    // 虚析构
};
// 继承
class Student : public Person { ... };
// 多态：基类指针指向派生类，调用虚函数走派生类实现
```

**三大特性**：封装（访问控制）、继承（代码复用）、多态（接口统一）。

### 8.7 常用现代特性速览

| 特性 | 语法 | 一句话 |
|---|---|---|
| `auto` 推导 | `auto x = expr;` | 让编译器推断类型 |
| 范围 for | `for (auto& x : v)` | 遍历容器更简洁 |
| Lambda | `[capture](args){body}` | 就地写匿名函数 |
| `nullptr` | `int* p = nullptr;` | 类型安全的空指针 |
| 智能指针 | `shared_ptr<T>` / `unique_ptr<T>` | 自动管理内存 |
| 右值引用/移动 | `T&&` | 避免不必要拷贝 |

---

## 9. 从 C++ 到 C：迁移指南

> 这是你最关心的部分。C++ 能写的东西，在 C 里要换成对应的"底层做法"。

### 9.1 必须丢弃的 C++ 特性

| C++ 写法 | C 里的替代方案 |
|---|---|
| `//` 单行注释（C99 起支持） | C99 后可用；老标准用 `/* */` |
| `cout << x` | `printf("%d", x)` / `putchar` |
| `cin >> x` | `scanf("%d", &x)` / `fgets` + `sscanf` |
| `string` | 字符数组 `char str[100]` + `<string.h>` 函数 |
| `vector<T>` | 手动 `malloc`/`realloc` 的数组 |
| `new` / `delete` | `malloc()` / `free()` |
| `class` / 类 | `struct` + 函数指针，或分离结构体与函数 |
| 构造函数/析构函数 | 手写 `init_xxx()` / `destroy_xxx()` 函数 |
| 访问控制 `private/public` | **没有**，靠约定（命名加前缀 `_`） |
| 函数重载 | **没有**，靠不同函数名 |
| 默认参数 | **没有**，手写多个函数包装 |
| 引用 `int&` | 只用指针 `int*` |
| 命名空间 `namespace` | 无，靠函数名加前缀（如 `math_add`） |
| 模板 / 泛型 | 无类型安全方案，用 `void*` 或宏，或重复写 |
| 异常处理 `try/catch/throw` | 用返回值错误码 + `errno` + `goto cleanup` |
| `bool` 类型 | C99 有 `_Bool`，`<stdbool.h>` 提供 `bool/true/false` |
| `nullptr` | 用 `NULL`（本质是 `0`）或 C23 的 `nullptr` |
| `auto` 类型推导 | C23 才支持，旧标准需手写类型 |

### 9.2 编译差异

```bash
# C++ 用 g++
g++ main.cpp -o app

# C 用 gcc
gcc main.c -o app
```

### 9.3 头文件差异

| 功能 | C++ 头文件 | C 头文件 |
|---|---|---|
| 输入输出 | `<iostream>` | `<stdio.h>` |
| 字符串 | `<string>` | `<string.h>` |
| 内存 | `<new>` | `<stdlib.h>`（malloc/free） |
| 布尔 | 内置 | `<stdbool.h>` |
| 最大整数 | — | `<stdint.h>`（int32_t 等） |
| 变长数组参数 | `<cstdarg>` | `<stdarg.h>` |

> 在 C 中，`<stdio.h>` 和 `<string.h>` 等老式头文件仍有，C++ 里则是去掉 `.h` 加 `c` 前缀的 `<cstdio>`。

---

## 10. C 语言核心要点速览

### 10.1 Hello World in C

```c
#include <stdio.h>

int main(void) {                // C 推荐写 void 表示无参
    printf("Hello, C!\n");
    return 0;
}
```

### 10.2 输入输出

```c
int age;
char name[50];
printf("Enter name: ");
scanf("%s", name);          // 注意：不用 &，数组名会退化为指针
printf("Age: %d\n", age);   // %d 整数 %f 浮点 %c 字符 %s 字符串 %p 指针
```

**⚠️ 安全提示**：`scanf("%s", buf)` 容易溢出。生产代码推荐：
```c
fgets(buf, sizeof(buf), stdin);   // 指定缓冲区大小，安全
```

### 10.3 字符串

C 没有 `string` 类型，字符串是**以 `\0` 结尾的字符数组**。

```c
#include <string.h>
char s1[20] = "hello";
char s2[20];
strcpy(s2, s1);          // 复制
strcat(s2, " world");     // 拼接
int len = strlen(s2);     // 长度（不含 \0）
int cmp = strcmp(s1, s2); // 比较，0 表示相等
```

### 10.4 内存管理（C 的核心与难点）

```c
#include <stdlib.h>

int* p = (int*)malloc(10 * sizeof(int));  // 分配 10 个 int
if (p == NULL) {                          // 必须检查是否分配失败
    // 处理错误
}
// 使用 p[0] ... p[9]
free(p);    // 释放，p 成为悬空指针
p = NULL;   // 好习惯：释放后置空
```

**C 内存四区**：

| 区域 | 存放 | 生命周期 |
|---|---|---|
| 代码区 | 程序指令 | 程序运行期 |
| 全局/静态区 | 全局变量、static 变量 | 程序运行期 |
| 栈（stack） | 局部变量、函数参数 | 函数调用结束自动回收 |
| 堆（heap） | `malloc` 分配的内存 | 手动 `free` 前一直存在 |

**三大内存错误**：
1. **内存泄漏**：`malloc` 后忘了 `free`。
2. **悬空指针**：`free` 后继续用。
3. **越界访问**：数组下标超出范围，踩坏别的数据。

### 10.5 结构体与 typedef

```c
struct Point {
    int x;
    int y;
};

// 用 typedef 起别名，省去每次写 struct
typedef struct {
    int x;
    int y;
} Point;

Point p = {1, 2};
p.x = 10;
```

### 10.6 函数指针

C 没有类，但可以用函数指针实现"多态"和回调：

```c
int add(int a, int b) { return a + b; }
int (*op)(int, int) = &add;   // 函数指针
int result = op(3, 4);        // 调用，结果为 7
```

### 10.7 预处理

```c
#include <stdio.h>     // 包含头文件
#define MAX 100         // 宏常量
#define MAX(a,b) ((a) > (b) ? (a) : (b))   // 宏函数（多加括号！）
#undef MAX
#ifdef DEBUG
    printf("debug\n");
#endif
#ifndef HEADER_H
#define HEADER_H       // 头文件卫士，防止重复包含
// ... 头文件内容
#endif
```

**头文件卫士必须写**，否则多次 `#include` 同一头文件会报"重定义"。

### 10.8 错误处理惯例

C 没有异常，靠**返回值 + errno**：

```c
#include <errno.h>
FILE* f = fopen("a.txt", "r");
if (f == NULL) {
    perror("fopen");   // 自动打印错误原因
    return 1;
}
```

### 10.9 C 标准版本

| 标准 | 年份 | 关键特性 |
|---|---|---|
| C89 / ANSI C | 1989 | 经典 C，函数需先声明 |
| C99 | 1999 | 单行注释、`for` 内定义、`bool`、变长数组 |
| C11 | 2011 | 多线程、`_Generic`、匿名结构体 |
| C17 | 2017 | 缺陷修复 |
| C23 | 2023 | `nullptr`、auto、增强类型推导 |

编译时指定标准：`gcc -std=c11 -Wall main.c -o app`

---

## 11. 多文件项目与构建

### 11.1 头文件与源文件的分工

```
calculator/
├── main.c
├── math.h      ← 声明（函数原型、宏、类型定义）
├── math.c      ← 实现
└── .vscode/
```

**math.h**

```c
#ifndef MATH_H
#define MATH_H

int add(int a, int b);
int sub(int a, int b);

#endif
```

**math.c**

```c
#include "math.h"

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
```

**main.c**

```c
#include <stdio.h>
#include "math.h"

int main(void) {
    printf("%d\n", add(3, 4));
    return 0;
}
```

**编译**：`gcc main.c math.c -o calculator`

> 规则：系统头文件用 `<>`，自己的头文件用 `""`。

### 11.2 Makefile（推荐掌握）

当文件变多，手写编译命令太繁琐。Makefile 自动化：

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = app
OBJS = main.o math.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
```

终端执行 `make` 编译，`make clean` 清理。

### 11.3 CMake（大型项目）

CMake 是跨平台构建系统的"元构建工具"，生成 Makefile 或 VS 工程。

**CMakeLists.txt**：

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyApp C)
set(CMAKE_C_STANDARD 11)

add_executable(app main.c math.c)
```

构建：

```bash
mkdir build && cd build
cmake ..
make
```

VS Code 装了 CMake Tools 后可一键配置构建。

---

## 12. 实用插件与效率技巧

### 12.1 推荐插件组合

- **C/C++**（必装）：智能提示 + 调试。
- **CMake Tools** + **CMake**：CMake 项目必备。
- **GitLens**：每行代码后面标注是谁、什么时候改的。
- **Error Lens**：把错误和警告直接显示在代码行尾。
- **TODO Tree**：汇总所有 `TODO`/`FIXME` 注释。
- **Code Runner**：单文件一键运行。

### 12.2 代码片段（Snippets）

输入 `main` 按回车，C/C++ 插件会自动补全 `main` 函数骨架。你也可以自定义：

`File → Preferences → Configure User Snippets` → 选 `cpp.json`，加入：

```json
{
    "For Loop": {
        "prefix": "forr",
        "body": [
            "for (int ${1:i} = 0; ${1:i} < ${2:n}; ++${1:i}) {",
            "\t${0}",
            "}"
        ],
        "description": "快速生成 for 循环"
    }
}
```

### 12.3 settings.json 常用配置

`Ctrl+Shift+P` → `Preferences: Open Settings (JSON)`：

```json
{
    "editor.formatOnSave": true,
    "editor.tabSize": 4,
    "files.autoSave": "onFocusChange",
    "C_Cpp.clang_format_style": "{ BasedOnStyle: Google, IndentWidth: 4 }"
}
```

### 12.4 集成终端技巧

- 支持多终端标签，点 `+` 新建。
- 可选默认 Shell（PowerShell / Bash / WSL）。
- 可直接拖拽文件到终端得到完整路径。

---

## 13. 常见坑与排错速查表

| 现象 | 原因 | 解决 |
|---|---|---|
| `#include` 报红但能编译 | IntelliSense 找不到头文件 | 配 `c_cpp_properties.json` 的 `includePath` |
| 断点灰色/不命中 | 没加 `-g` 编译 | 在 tasks.json 的 args 加 `-g` |
| `F5` 提示找不到任务 | 未生成 tasks.json | 配置 `preLaunchTask` 对应的 build 任务 |
| `undefined reference` | 只编译了部分文件 | 把相关 `.c` 文件一起编译 |
| 多个 `main` 函数冲突 | 多文件里重复定义 | 一个项目只能有一个 `main` |
| 头文件重定义 | 缺头文件卫士 | 加 `#ifndef ... #define ... #endif` |
| `printf` 打印乱码 | 格式符与类型不匹配 | `%d` 配 `int`，`%f` 配 `double` |
| 段错误 Segmentation fault | 空指针/越界/已 free | 用 GDB 打断点定位 |
| `scanf` 读入失败 | 变量前漏写 `&` | `scanf("%d", &x)` 必须取地址 |
| 中文字符串乱码 | 文件编码问题 | 右下角切到 UTF-8 保存 |
| 修改代码后运行没变化 | 忘了重新编译 | `Ctrl+Shift+B` 重新构建 |

### 调试段错误的经典流程

```bash
gcc -g main.c -o app       # 带调试信息编译
gdb ./app                  # 启动 gdb
(gdb) run                  # 重现段错误
(gdb) bt                   # backtrace 看调用栈，定位出错行
```

---

## 学习路径建议

如果你时间有限，按这个顺序推进，每天 1–2 小时，两周可形成完整能力：

1. **Day 1–2**：装环境、跑通 Hello World，练熟 `Ctrl+Shift+B` 和 `F5`。
2. **Day 3–4**：写几个单文件小程序（计算器、猜数字），熟练快捷键。
3. **Day 5–6**：拆成多文件项目，学会头文件 + 源文件分工。
4. **Day 7–8**：用 GDB 调试一个带 bug 的程序，掌握断点/单步/变量观察。
5. **Day 9–10**：用 C 重写之前写的 C++ 小程序（把 `vector` 换成数组 + `malloc`），体会差异。
6. **Day 11–12**：学 Makefile，把项目自动化构建。
7. **Day 13+**：挑战一个小项目（如通讯录、简易 shell），综合运用。

---

## 附录：速查卡片

### 编译命令模板

```bash
gcc -Wall -Wextra -std=c11 -g main.c math.c -o app    # C 项目
g++ -Wall -Wextra -std=c++17 -g main.cpp -o app        # C++ 项目
./app                                                   # 运行
```

### 调试命令模板

```bash
gdb ./app
(gdb) break main        # 在 main 设断点
(gdb) run               # 运行
(gdb) next              # 单步跳过（= F10）
(gdb) step              # 单步进入（= F11）
(gdb) print x           # 打印变量
(gdb) bt                # 调用栈
(gdb) continue          # 继续（= F5）
(gdb) quit              # 退出
```

### 文件模板（C）

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    return 0;
}
```

### 文件模板（C++）

```cpp
#include <iostream>
using namespace std;

int main() {
    return 0;
}
```

---

*祝编码愉快。记住：编辑器是工具，语言是手段，解决问题才是目的。遇到问题先读报错、再看文档、最后再问人。*
