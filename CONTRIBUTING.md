# Contributing / 贡献指南

感谢你对本项目的关注！目前我还是一名高二学生，编程经验有限，非常欢迎各路开发者一起改进这个项目。

## 特别欢迎的方向

### 1. 交互体验优化（最优先）

当前交互逻辑使用多层 `if-else` 嵌套实现，虽然功能完整，但用户体验还有很大提升空间。如果你有想法让操作更流畅、提示更清晰、路径更短，**非常欢迎提交 PR**！

参考方向：
- 压缩菜单层级（如三层入口合并为一层）
- 输入容错处理（大小写不敏感、模糊匹配）
- 增加操作历史/撤销功能
- 引入更直观的命令行界面库（如 ncurses）

### 2. 数据结构拓展

当前仅支持单个班级的顺序表存储。可拓展方向：
- 引入树形结构搭建「学生-班级-学校」多层架构
- 将手动管理的动态数组替换为 `std::vector`
- 增加数据持久化（文件读写 / 简单数据库）

### 3. 评分规则动态化

当前成绩评判函数为固定阈值。可改造为：
- `unordered_map<std::string, pair<int, int>>` 维护分数区间与等级
- 支持自定义科目和满分值
- 支持不同评分标准（如百分制 vs 等级制）

### 4. 其他改进

- 代码健壮性（异常安全、边界检查）
- 单元测试
- 更多统计分析维度（标准差、方差、相关性分析）

## 如何提交

1. Fork 本仓库
2. 创建你的功能分支 (`git checkout -b feature/xxx`)
3. 提交更改 (`git commit -am 'Add xxx'`)
4. Push 到分支 (`git push origin feature/xxx`)
5. 创建 Pull Request

## 注意事项

- 本项目为学习用途，代码风格保持简洁直观
- 提交前请确保能通过 `g++ -std=c++17` 编译
- README 中的运行示例如发生变更，请同步更新

---

Thank you for your interest in this project! I am a high school student with limited programming experience, and I warmly welcome contributions from developers of all backgrounds.

### Priority Areas

1. **UX improvement** - The current nested `if-else` interaction works but is clunky. Help make it smoother!
2. **Data structure extension** - Tree-based multi-layer architecture, `std::vector` migration, persistence
3. **Dynamic grading rules** - Configurable scoring thresholds via `unordered_map`
4. **General robustness** - Exception safety, unit tests, additional statistics

See the Chinese section above for full details.
