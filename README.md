# 学生成绩管理系统 / Student Grade Management System

> **High School Student Project** | C++17 | 1000+ Lines | 分层架构 | 简易状态机
>
> **🇨🇳 中文** | [**English**](#english-version)

---

## 🇨🇳 中文版本

## 运行示例

### 数据录入

```
========================================
      学生成绩数据录入
========================================

【输入格式说明】
每行输入一名学生的信息，格式为：
  <学号> <姓名> <总分> <语文> <数学> <英语> <物理> <化学> <生物>

【示例】
  1 张三 650 120 135 128 92 88 87

【提示】
  - 输入完毕后按 Ctrl+D (Linux/Mac) 或 Ctrl+Z+回车 (Windows) 结束输入

请开始输入学生数据：
  [已录入] 学号 1 张三 总分 650
  [已录入] 学号 2 李四 总分 580
  [已录入] 学号 3 王五 总分 720

========================================
  录入完成！共 3 名学生
========================================
```

### 主界面与操作模式

```
========================================
      欢迎使用学生成绩管理系统
========================================

本次考试成绩（已按总分降序排列）：

姓名(Name)：王五   学号(ID)：3   总分(Total)：720
  语文:138  数学:145  英语:142  物理:95  化学:98  生物:102
...

========================================
          第一步：选择操作
========================================
【当前状态】主入口

操作指引：
  quit     - 直接退出程序
  continue - 进入功能菜单

请输入：continue
好!(Ok!)

========================================
          第三步：功能模式
========================================
【当前状态】模式选择

操作指引：
  0 - Operation  操作模式（查找/修改/添加/删除学生）
  1 - Evaluation 评价模式（线性回归预测下次成绩）
  2 - Statistic  统计模式（成绩分级统计报告）
  end - 退出，查看最终评价
```

### 线性回归预测（Evaluation 模式）

```
========================================
      Evaluation 评价模式
      线性回归成绩预测
========================================

请输入考试次数（至少2次）：5

请依次输入每次考试的班级总分平均分：
  第 1 次考试平均分：580
  第 2 次考试平均分：600
  第 3 次考试平均分：620
  第 4 次考试平均分：610
  第 5 次考试平均分：640

          历史成绩趋势图
   分
   数
 662 |
 655 |
 634 |                                       -*
 628 |                                   ----
 614 |                    *   -----
 600 |             ------
 580 |---
 573 |*
     +-----------------------------------------
       1           2           3           4           5  P

  回归方程: y = 13.0x + 571.0
  趋势方向: 明显上升 ▲▲
  下次预测: 649 分
  (* = 历史数据  P = 预测  - = 趋势线)
```

### 成绩统计报告（Statistic 模式）

```
===== 语文成绩评价 =====
优秀(120-150)人数：3 人
良好(90-119)  人数：2 人
及格(70-89)   人数：0 人
...
语文成绩总体优秀！
```

### 最终评价

```
========================================
          最终评价报告
========================================
本次考试平均分为：628
超过平均分得有3人  平均分以下的有2人
本次极差较大！请注意！极差为210

【线性回归预测结论】
  经模拟，下次考试全班平均分预计还能上升！
  预测分数：649 分（当前平均：628 分）
  >> 建议：多奖励学生们，保持良好势头！

========================================
    感谢使用学生成绩管理系统，再见！
========================================
```

---

### 快速开始

#### 编译

```bash
g++ -std=c++17 -I. service/core/main.cpp service/utils/Stu_List.cpp \
    service/data/Stu_Manage.cpp service/tools/System_Items.cpp -o stu_manage
```

#### 运行

```bash
./stu_manage
```

输入完毕后按 `Ctrl+D` (Linux/Mac) 或 `Ctrl+Z+回车` (Windows) 结束输入。

#### 输入格式

每行一名学生：`<学号> <姓名> <总分> <语文> <数学> <英语> <物理> <化学> <生物>`

---

### 介绍

本项目是一款学生成绩管理系统，代码分层最深为2层，总代码量1000余行。

> **关于作者**：目前我还是一名高二学生，编程能力与项目设计经验尚有不足。本项目从架构设计到代码实现均为独立完成，状态机交互框架更是在尚未了解"状态机"这一概念前凭直觉设计，事后才知其名。文中若有表述不当、设计不合理的地方，欢迎各位指正。

---

### 数据结构选择

结合本项目面向对象的设计思路，核心需要统一维护全体学生信息。首先排除访问存在限制的数据结构，例如栈、队列；其次排除存在层级从属关系的树形结构。原因在于：所有学生信息属于平级关系，不存在上下级、主次之分。

因此本项目底层选用**顺序表**作为核心数据结构。所有学生数据统一存放于顺序表中，彼此地位平等，可通过下标直接访问；所有数据同属一张表，天然代表同一个班级的学生群体，贴合业务场景。

---

### 类设计

基于选定的顺序表结构，设计 `Stu_List` 类作为底层容器。本类并未参照标准容器 `vector` 实现完整功能，仅根据项目实际需求，基于顺序表完成数据存储核心逻辑。

`Stu_List` 仅负责容器层面的数据存放，学生具体信息则由 `Stu_Info` 类维护。`Stu_Info` 仅对 `Stu_List` 内部开放接口与数据，不对外暴露，严格遵循封装原则。

| 类名 | 职责 |
|------|------|
| `Stu_Info` | 维护单个学生的姓名、学号、总分及六科成绩 |
| `Stu_List` | 顺序表容器，负责学生对象的存储、排序、增删改查 |

---

### 状态机设计

项目交互模块采用简易状态机实现：以 `while` 循环作为程序主交互框架，搭配 `switch` 完成功能场景选择，结合 `if-else` 分支处理用户具体操作。

```
[数据录入] → [continue/next] → [模式选择 0/1/2/end]
                                     |
          +------------------+------------------+
          |                  |                  |
       OPERATION        EVALUATION         STATISTIC
       find/revise      线性回归预测        六科分级统计
       add/remove
          |
          +------------------+------------------+
                                     |
                              [最终评价报告]
```

| 模式 | 功能 |
|------|------|
| **Operation** | `find` 查找、`revise` 修改、`add` 添加、`remove` 删除 |
| **Evaluation** | 输入历次班级平均分，线性回归分析趋势并预测下次成绩 |
| **Statistic** | 六科成绩分级统计，输出各等级人数分布及总体评价 |

---

### 项目文件结构

```
Manage/
├── README.md               # 项目说明文档（首页自动渲染）
├── CONTRIBUTING.md         # 贡献指南
├── CHANGELOG.md            # 开发日志
├── run.sh                  # 编译运行脚本（build / run / clean / help）
├── class/                  # 数据模型层
│   ├── Stu_Info.h         # 学生信息类
│   └── Stu_List.h         # 学生顺序表容器类
├── include/                # 接口声明层
│   ├── Stu_Manage.h       # 数据加载模块接口
│   └── System_Items.h     # 统计/评价模块接口
├── service/                # 业务逻辑层
│   ├── core/
│   │   └── main.cpp        # 程序入口 + 状态机交互框架
│   ├── data/
│   │   └── Stu_Manage.cpp  # 学生数据加载实现
│   ├── tools/
│   │   └── System_Items.cpp # 统计评价 + 线性回归实现
│   └── utils/
│       └── Stu_List.cpp    # 顺序表核心操作实现
└── test/                   # 测试目录（预留，欢迎补充单元测试）
    └── .gitkeep
```

该分层设计并非冗余，一方面延续了全栈项目开发中的架构习惯；另一方面为项目后续迭代拓展预留空间。

---

### 可拓展设计

1. **数据结构拓展**：引入树形结构，搭建「学生-班级-学校」多层架构，适配更大规模场景；
2. **交互逻辑拓展**：当前使用多层 `if-else` 嵌套，后续可解耦交互模块，优化代码结构。欢迎对交互体验进行优化！
3. **评分规则拓展**：目前评判函数为固定规则，可改造为动态规则，参考 `unordered_map<std::string, pair<int, int>>` 实现。

---

### 致谢

感谢您阅读本项目文档。目前我还是一名高二学生，编程能力与项目设计经验尚有不足。也希望这份代码与设计思路，能够给有需要的人带来参考。

一名高中生  
2026.5.28

---

## English Version

## Demo

### Data Entry

```
========================================
      Student Grade Data Entry
========================================

[Format]
  <ID> <Name> <Total> <Chinese> <Math> <English> <Physics> <Chemistry> <Biology>

[Example]
  1 Alice 650 120 135 128 92 88 87

[Hint] Press Ctrl+D (Linux/Mac) or Ctrl+Z+Enter (Windows) after input

Enter student data:
  [Recorded] ID 1 Alice Total 650
  [Recorded] ID 2 Bob Total 580

========================================
  Entry complete! 2 students in total.
========================================
```

### Linear Regression Prediction (Evaluation Mode)

```
          Grade Trend Chart
  662 |
  634 |                                       -*
  614 |                    *   -----
  580 |---
  573 |*
     +-----------------------------------------
       1           2           3           4           5  P

  Regression: y = 13.0x + 571.0
  Trend: Strong upward ▲▲
  Next prediction: 649 pts
  (* = history  P = prediction  - = trend line)
```

### Final Report

```
========================================
          Final Evaluation Report
========================================
Class average: 628
Above average: 3 students  Below average: 2 students
Range: 210 (significant gap)

[Prediction Conclusion]
  Predicted next exam average: 649 (current: 628)
  >> Keep up the good work!

========================================
  Thank you for using the system!
========================================
```

---

### Quick Start

```bash
# Compile
g++ -std=c++17 -I. service/core/main.cpp service/utils/Stu_List.cpp \
    service/data/Stu_Manage.cpp service/tools/System_Items.cpp -o stu_manage

# Run
./stu_manage
```

---

### Introduction

This project is a student grade management system with over 1000 lines of code and a maximum nesting depth of 2 layers.

> **About the author**: I am currently a high school sophomore. This project was independently designed and implemented from architecture to code. The state machine interaction framework was designed intuitively before I even knew the term "state machine" — I only learned the name afterward.

---

### Data Structure Selection

All student information is **flat** — there is no superior-subordinate relationship. Therefore, a **sequential list (dynamic array)** is chosen as the underlying data structure. Each entry is equal and directly accessible by index. The entire list naturally represents a class of students.

---

### Class Design

| Class | Responsibility |
|-------|---------------|
| `Stu_Info` | Maintains name, ID, total score, and 6 subject scores for a single student |
| `Stu_List` | Sequential list container: storage, sorting, CRUD operations |

`Stu_List` only handles container-level storage; actual student data is maintained by `Stu_Info`, which exposes its interface only to `Stu_List`, strictly following encapsulation.

---

### State Machine Design

The interaction module uses a simple state machine: a `while` loop as the main framework, `switch` for scenario selection, and `if-else` chains for specific operations.

| Mode | Function |
|------|----------|
| **Operation** | `find`, `revise`, `add`, `remove` |
| **Evaluation** | Linear regression trend analysis and prediction |
| **Statistic** | Six-subject grade distribution report |

---

### Extensibility

1. **Data structure**: Introduce tree structures for "student → class → school" multi-layer hierarchy;
2. **Interaction logic**: Currently nested `if-else`; can be decoupled into a modular interaction system. **Contributions to improve UX are welcome!**
3. **Grading rules**: Currently hard-coded; can be made dynamic using `unordered_map<string, pair<int, int>>`.

---

### Acknowledgements

Thank you for reading this document. I am still a high school student with much to learn. I hope my code and design ideas can be helpful to those who need them.

**A High School Student**  
2026.5.28
