// main.cpp - 程序入口 + 状态机交互框架：实现完整的用户交互流程与功能调度
#include <iostream>
#include <iomanip>
#include <cmath>
#include "class/Stu_List.h"
#include "include/Stu_Manage.h"
#include "include/System_Items.h"
#include <cstdlib>
#include <string>

template<typename T>
// 消息结构体
struct Message{
    T get_Msg;

    std::istream &input_Msg(std::istream& is, Message& Msg){
        is >> Msg.get_Msg;
        return is;
    }

    void handle_Msg(){ 
        std::cout << "好!(Ok!)" << std::endl;
    }

    // 版本1：检查整数返回值是否为 -1（用于 FindStudentID 等）
    bool handle_error(int function){
        if (function == -1){
            std::cout << "[!] 查找失败：该编号不存在或已越界" << std::endl;
            std::cout << "    请确认编号在 0 ~ " << (StuList.size() - 1) << " 范围内" << std::endl;
            return true; 
        } 
        else return false;
    }

    // 版本2：检查字符串返回值是否为空（用于 FindStudentName）
    bool handle_error(const std::string& result){
        if (result.empty()){
            std::cout << "[!] 查找失败：该编号不存在或已越界" << std::endl;
            std::cout << "    请确认编号在 0 ~ " << (StuList.size() - 1) << " 范围内" << std::endl;
            return true;
        }
        else return false;
    }

    // 版本3：无参版本，用于索引越界、操作失败等场景
    bool handle_error(){
        std::cout << "[!] 操作失败！" << std::endl;
        std::cout << "    可能原因：编号越界（有效范围 0 ~ " << (StuList.size() - 1) << "）" << std::endl;
        std::cout << "    或学号/姓名不存在，请检查后重新输入" << std::endl;
        return false;
    }
};

Message<std::string>MsgType_1;
Message<std::string>Msg_Subject;
Message<int>MsgType_2;
bool is_used = false;
int expect;

// 线性回归趋势图打印
void PrintTrendChart(const std::vector<int>& x, const std::vector<int>& y, int predict_x, double predict_y) {
    int n = x.size();
    if (n == 0) return;
    
    // 找出 y 的范围（留出上下边距）
    int y_max = y[0], y_min = y[0];
    for (int yi : y) { if (yi > y_max) y_max = yi; if (yi < y_min) y_min = yi; }
    if ((int)predict_y > y_max) y_max = (int)predict_y;
    if ((int)predict_y < y_min) y_min = (int)predict_y;
    int y_margin = (y_max - y_min) / 8 + 5;
    y_max += y_margin;
    y_min = (y_min > y_margin) ? y_min - y_margin : 0;
    
    int y_range = y_max - y_min;
    if (y_range == 0) y_range = 1;
    
    const int CHART_HEIGHT = 14;
    const int CHART_WIDTH = 40;
    
    // 预计算每个数据点的列位置
    int* point_col = new int[n];
    int* point_row = new int[n];
    for (int i = 0; i < n; i++) {
        point_col[i] = (CHART_WIDTH * i) / (n > 1 ? n - 1 : 1);
        point_row[i] = (CHART_HEIGHT * (y[i] - y_min)) / y_range;
    }
    int predict_col = (CHART_WIDTH * (predict_x - 1)) / (n > 1 ? n - 1 : 1);
    int predict_row = (CHART_HEIGHT * ((int)predict_y - y_min)) / y_range;
    
    // 计算回归直线上的所有 (col, row) 点
    double sum_x = 0, sum_y_val = 0;
    for (int xi : x) sum_x += xi;
    for (int yi : y) sum_y_val += yi;
    double avg_x = sum_x / n;
    double avg_y = sum_y_val / n;
    double numerator = 0, denominator = 0;
    for (int i = 0; i < n; i++) {
        numerator += (x[i] - avg_x) * (y[i] - avg_y);
        denominator += (x[i] - avg_x) * (x[i] - avg_x);
    }
    double b = (denominator == 0) ? 0 : numerator / denominator;
    double a_val = avg_y - b * avg_x;
    
    std::cout << std::endl;
    std::cout << "          历史成绩趋势图" << std::endl;
    std::cout << "   分" << std::endl;
    std::cout << "   数" << std::endl;
    
    for (int row = CHART_HEIGHT; row >= 0; row--) {
        int row_y = y_min + (y_range * row) / CHART_HEIGHT;
        std::cout << std::setw(4) << row_y << " |";
        
        for (int col = 0; col <= CHART_WIDTH; col++) {
            // 优先级：历史点 > 预测点 > 趋势线 > 空格
            bool printed = false;
            
            // 1. 检查历史数据点
            for (int i = 0; i < n; i++) {
                if (point_col[i] == col && point_row[i] == row) {
                    std::cout << "*";
                    printed = true;
                    break;
                }
            }
            if (printed) continue;
            
            // 2. 检查预测点
            if (predict_col == col && predict_row == row) {
                std::cout << "P";
                continue;
            }
            
            // 3. 检查趋势线（回归直线）
            double col_x_val = 1.0 + (n - 1.0) * col / CHART_WIDTH;
            double line_y = a_val + b * col_x_val;
            int line_row = (CHART_HEIGHT * ((int)(line_y + 0.5) - y_min)) / y_range;
            if (line_row == row) {
                std::cout << "-";
                continue;
            }
            
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "     +";
    for (int i = 0; i <= CHART_WIDTH; i++) std::cout << "-";
    std::cout << std::endl;
    
    std::cout << "      ";
    for (int i = 0; i < n; i++) {
        int pos = (CHART_WIDTH * i) / (n > 1 ? n - 1 : 1);
        std::cout << std::string(pos - (i > 0 ? (CHART_WIDTH * (i-1)) / (n > 1 ? n - 1 : 1) : 0), ' ');
        std::cout << std::setw(2) << (i + 1);
    }
    std::cout << "  P" << std::endl;
    
    delete[] point_col;
    delete[] point_row;
    
    std::cout << std::endl;
    std::cout << "  回归方程: y = " << std::fixed << std::setprecision(1) << b << "x + " << a_val << std::endl;
    std::cout << "  趋势方向: ";
    if (b > 5) std::cout << "明显上升 ▲▲" << std::endl;
    else if (b > 0) std::cout << "缓慢上升 ▲" << std::endl;
    else if (b > -5) std::cout << "缓慢下降 ▼" << std::endl;
    else std::cout << "明显下降 ▼▼" << std::endl;
    std::cout << "  下次预测: " << (int)predict_y << " 分" << std::endl;
    std::cout << "  (* = 历史数据  P = 预测  - = 趋势线)" << std::endl;
}

void PrintSeparator(){
    std::cout << "========================================" << std::endl;
}

void PrintStatus(const std::string& status){
    std::cout << "【当前状态】" << status << std::endl;
    std::cout << std::endl;
}

void RunInteraction(){
    PrintSeparator();
    std::cout << "      欢迎使用学生成绩管理系统" << std::endl;
    PrintSeparator();
    std::cout << std::endl;
    
    std::cout << "本次考试成绩（已按总分降序排列）：" << std::endl;
    std::cout << std::endl;
    StuList.print();
    std::cout << std::endl;
    
    PrintSeparator();
    std::cout << "          第一步：选择操作" << std::endl;
    PrintSeparator();
    PrintStatus("主入口");
    std::cout << "操作指引：" << std::endl;
    std::cout << "  quit     - 直接退出程序" << std::endl;
    std::cout << "  continue - 进入功能菜单" << std::endl;
    std::cout << std::endl;
    std::cout << "请输入：" << std::endl;
    
    MsgType_1.input_Msg(std::cin, MsgType_1);
    if (MsgType_1.get_Msg == "quit"){
        std::cout << std::endl;
        std::cout << "感谢使用学生成绩管理系统，再见！" << std::endl;
        Stu_List();
        exit(0);
    } 
    else {
        MsgType_1.handle_Msg();
        std::cout << std::endl;
        PrintSeparator();
        std::cout << "          第二步：模式选择" << std::endl;
        PrintSeparator();
        PrintStatus("主菜单");
        std::cout << "操作指引：" << std::endl;
        std::cout << "  next - 进入操作/评价/统计模式" << std::endl;
        std::cout << "  end  - 跳过操作，直接查看最终评价" << std::endl;
        std::cout << std::endl;
        std::cout << "请输入：" << std::endl;
        
        MsgType_1.input_Msg(std::cin, MsgType_1);
        if (MsgType_1.get_Msg == "next") {
            std::cout << std::endl;
            PrintSeparator();
            std::cout << "          第三步：功能模式" << std::endl;
            PrintSeparator();
            PrintStatus("模式选择");
            std::cout << "操作指引：" << std::endl;
            std::cout << "  0 - Operation  操作模式（查找/修改/添加/删除学生）" << std::endl;
            std::cout << "  1 - Evaluation 评价模式（线性回归预测下次成绩）" << std::endl;
            std::cout << "  2 - Statistic  统计模式（成绩分级统计报告）" << std::endl;
            std::cout << "  end - 退出，查看最终评价" << std::endl;
            std::cout << std::endl;
            std::cout << "请输入：" << std::endl;
            
            MsgType_1.input_Msg(std::cin, MsgType_1);
            while (MsgType_1.get_Msg != "end") {
                int scenario = atoi(MsgType_1.get_Msg.c_str());
                switch (scenario){
                case OPERATION:{
                    std::cout << std::endl;
                    MsgType_1.handle_Msg();
                    PrintSeparator();
                    std::cout << "        Operation 操作模式" << std::endl;
                    PrintSeparator();
                    PrintStatus("操作菜单");
                    std::cout << "操作指引：" << std::endl;
                    std::cout << "  find   - 查找学生信息" << std::endl;
                    std::cout << "  revise - 修改学生信息" << std::endl;
                    std::cout << "  add    - 添加新学生" << std::endl;
                    std::cout << "  remove - 删除学生" << std::endl;
                    std::cout << std::endl;
                    std::cout << "请输入：" << std::endl;
                    
                    MsgType_1.input_Msg(std::cin, MsgType_1);
                    if (MsgType_1.get_Msg == "find"){
                        std::cout << std::endl;
                        MsgType_1.handle_Msg();
                        PrintSeparator();
                        std::cout << "        查找学生信息" << std::endl;
                        PrintSeparator();
                        PrintStatus("查找菜单");
                        std::cout << "【方式一】按排序后编号查找（编号对应上方打印列表的顺序）" << std::endl;
                        std::cout << "  Id    - 按编号查学号   （输入编号如 0, 1, 2...）" << std::endl;
                        std::cout << "  Name  - 按编号查姓名   （输入编号如 0, 1, 2...）" << std::endl;
                        std::cout << "  Total - 按编号查总分   （输入编号如 0, 1, 2...）" << std::endl;
                        std::cout << "  Score - 按编号查单科   （先输入学科名，再输入编号）" << std::endl;
                        std::cout << std::endl;
                        std::cout << "【方式二】直接查找" << std::endl;
                        std::cout << "  0 - 输入学号直接查找" << std::endl;
                        std::cout << "  1 - 输入姓名直接查找" << std::endl;
                        std::cout << std::endl;
                        std::cout << "请输入：" << std::endl;
                        
                        MsgType_1.input_Msg(std::cin, MsgType_1);
                        if (MsgType_1.get_Msg == "Id"){
                            std::cout << std::endl;
                            MsgType_1.handle_Msg();
                            std::cout << "请输入排序编号（0 ~ " << (StuList.size() - 1) << "）：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int order = MsgType_2.get_Msg;
                            if (!MsgType_2.handle_error(StuList.FindStudentID(order))){
                                std::cout << "  [结果] 编号 " << order << " 的学号为：" << StuList.FindStudentID(order) << std::endl;
                            }
                        }
                        else if (MsgType_1.get_Msg == "Name"){
                            std::cout << std::endl;
                            MsgType_1.handle_Msg();
                            std::cout << "请输入排序编号（0 ~ " << (StuList.size() - 1) << "）：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int order = MsgType_2.get_Msg;
                            std::string name_result = StuList.FindStudentName(order);
                            if (!MsgType_1.handle_error(name_result)){
                                std::cout << "  [结果] 编号 " << order << " 的姓名为：" << name_result << std::endl;
                            }
                        }
                        else if (MsgType_1.get_Msg == "Total"){
                            std::cout << std::endl;
                            MsgType_1.handle_Msg();
                            std::cout << "请输入排序编号（0 ~ " << (StuList.size() - 1) << "）：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int order = MsgType_2.get_Msg;
                            if (!MsgType_2.handle_error(StuList.FindStudentTotal(order))){
                                std::cout << "  [结果] 编号 " << order << " 的总分为：" << StuList.FindStudentTotal(order) << std::endl;
                            }
                        }
                        else if (MsgType_1.get_Msg == "Score"){
                            std::cout << std::endl;
                            MsgType_1.handle_Msg();
                            std::cout << "请输入学科名称（Chinese/Math/English/Physics/Chemistry/Biology）：" << std::endl;
                            Msg_Subject.input_Msg(std::cin, Msg_Subject);
                            std::cout << "请输入排序编号（0 ~ " << (StuList.size() - 1) << "）：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int order = MsgType_2.get_Msg;
                            std::string subject = Msg_Subject.get_Msg;
                            if (!MsgType_2.handle_error(StuList.FindStudentScore(order, subject))){
                                std::cout << "  [结果] 编号 " << order << " 的 " << subject << " 成绩为：" << StuList.FindStudentScore(order, subject) << std::endl;
                            }
                        } else {
                            int choice = atoi(MsgType_1.get_Msg.c_str());
                            if (choice == 0){
                                std::cout << std::endl;
                                std::cout << "请输入要查找的学号：" << std::endl;
                                MsgType_2.input_Msg(std::cin, MsgType_2);
                                int search_id = MsgType_2.get_Msg;
                                int order = StuList.FindById(search_id);
                                if (order < 0 || order >= StuList.size()) {
                                    MsgType_2.handle_error();
                                } else {
                                    std::cout << std::endl;
                                    std::cout << std::endl << "  ---- 学生详细信息 ----" << std::endl;
                                    std::cout << "    学号：" << StuList.FindStudentID(order) << std::endl;
                                    std::cout << "    姓名：" << StuList.FindStudentName(order) << std::endl;
                                    std::cout << "    总分：" << StuList.FindStudentTotal(order) << std::endl;
                                    std::string name_check = StuList.FindStudentName(order);
                                    if (MsgType_1.handle_error(name_check)) break;
                                    std::cout << std::endl;
                                    std::cout << "是否需要打印该学生的六科成绩？（yes / no）" << std::endl;
                                    MsgType_1.input_Msg(std::cin, MsgType_1);
                                    if (MsgType_1.get_Msg == "yes"){
                                        std::cout << std::endl;
                                        std::cout << "    语文：" << StuList.FindStudentScore(order, "Chinese") << std::endl;
                                        std::cout << "    数学：" << StuList.FindStudentScore(order, "Math") << std::endl;
                                        std::cout << "    英语：" << StuList.FindStudentScore(order, "English") << std::endl;
                                        std::cout << "    物理：" << StuList.FindStudentScore(order, "Physics") << std::endl;
                                        std::cout << "    化学：" << StuList.FindStudentScore(order, "Chemistry") << std::endl;
                                        std::cout << "    生物：" << StuList.FindStudentScore(order, "Biology") << std::endl;
                                    }
                                }
                            } else if (choice == 1){
                                std::cout << std::endl;
                                std::cout << "请输入要查找的姓名：" << std::endl;
                                MsgType_1.input_Msg(std::cin, MsgType_1);
                                std::string search_name = MsgType_1.get_Msg;
                                int order = StuList.FindById(search_name);
                                if (order < 0 || order >= StuList.size()) {
                                    MsgType_2.handle_error();
                                } else {
                                    std::cout << std::endl;
                                    std::cout << std::endl << "  ---- 学生详细信息 ----" << std::endl;
                                    std::cout << "    学号：" << StuList.FindStudentID(order) << std::endl;
                                    std::cout << "    姓名：" << StuList.FindStudentName(order) << std::endl;
                                    std::cout << "    总分：" << StuList.FindStudentTotal(order) << std::endl;
                                    std::string name_check = StuList.FindStudentName(order);
                                    if (MsgType_1.handle_error(name_check)) break;
                                    std::cout << std::endl;
                                    std::cout << "是否需要打印该学生的六科成绩？（yes / no）" << std::endl;
                                    MsgType_1.input_Msg(std::cin, MsgType_1);
                                    if (MsgType_1.get_Msg == "yes"){
                                        std::cout << std::endl;
                                        std::cout << "    语文：" << StuList.FindStudentScore(order, "Chinese") << std::endl;
                                        std::cout << "    数学：" << StuList.FindStudentScore(order, "Math") << std::endl;
                                        std::cout << "    英语：" << StuList.FindStudentScore(order, "English") << std::endl;
                                        std::cout << "    物理：" << StuList.FindStudentScore(order, "Physics") << std::endl;
                                        std::cout << "    化学：" << StuList.FindStudentScore(order, "Chemistry") << std::endl;
                                        std::cout << "    生物：" << StuList.FindStudentScore(order, "Biology") << std::endl;
                                    }
                                }
                            }
                        }

                    }
                    else if (MsgType_1.get_Msg == "revise"){
                        std::cout << std::endl;
                        PrintSeparator();
                        std::cout << "        修改学生信息" << std::endl;
                        PrintSeparator();
                        PrintStatus("修改菜单");
                        std::cout << "操作指引：" << std::endl;
                        std::cout << "  Id    - 修改学号   （先输入编号，再输入新学号）" << std::endl;
                        std::cout << "  Name  - 修改姓名   （先输入编号，再输入新姓名）" << std::endl;
                        std::cout << "  Total - 修改总分   （先输入编号，再输入新总分）" << std::endl;
                        std::cout << "  Score - 修改单科   （先输入编号，再输入新分数，最后输入学科）" << std::endl;
                        std::cout << std::endl;
                        std::cout << "【提示】编号为排序后的序号，范围 0 ~ " << (StuList.size() - 1) << std::endl;
                        std::cout << std::endl;
                        std::cout << "请输入：" << std::endl;
                        
                        MsgType_1.input_Msg(std::cin, MsgType_1);
                        if (MsgType_1.get_Msg == "Id"){
                            std::cout << "请输入要修改的学生编号：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int id = MsgType_2.get_Msg;
                            std::cout << "请输入新的学号：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int news = MsgType_2.get_Msg; 
                            if (id < 0 || id >= StuList.size()) {
                                MsgType_2.handle_error();
                            } else {
                                StuList.ReviseStudentID(id, news);
                                std::cout << "  [成功] 编号 " << id << " 的学号已修改为 " << news << std::endl;
                            }
                        } 
                        else if (MsgType_1.get_Msg == "Name"){
                            std::cout << "请输入要修改的学生编号：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int id = MsgType_2.get_Msg;
                            std::cout << "请输入新的姓名：" << std::endl;
                            MsgType_1.input_Msg(std::cin, MsgType_1);
                            std::string news = MsgType_1.get_Msg; 
                            if (id < 0 || id >= StuList.size()) {
                                MsgType_2.handle_error();
                            } else {
                                StuList.ReviseStudentName(id, news);
                                std::cout << "  [成功] 编号 " << id << " 的姓名已修改为 " << news << std::endl;
                            }
                        } 
                        else if (MsgType_1.get_Msg == "Total"){
                            std::cout << "请输入要修改的学生编号：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int id = MsgType_2.get_Msg;
                            std::cout << "请输入新的总分：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int news = MsgType_2.get_Msg; 
                            if (id < 0 || id >= StuList.size()) {
                                MsgType_2.handle_error();
                            } else {
                                StuList.ReviseStudentTotal(id, news);
                                std::cout << "  [成功] 编号 " << id << " 的总分已修改为 " << news << std::endl;
                            }
                        } 
                        else if (MsgType_1.get_Msg == "Score"){
                            std::cout << "请输入要修改的学生编号：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int id = MsgType_2.get_Msg;
                            std::cout << "请输入新的分数：" << std::endl;
                            MsgType_2.input_Msg(std::cin, MsgType_2);
                            int news = MsgType_2.get_Msg; 
                            std::cout << "请输入学科名称（Chinese/Math/English/Physics/Chemistry/Biology）：" << std::endl;
                            Msg_Subject.input_Msg(std::cin, Msg_Subject);
                            std::string Subject = Msg_Subject.get_Msg;
                            if (id < 0 || id >= StuList.size()) {
                                MsgType_2.handle_error();
                            } else {
                                StuList.ReviseStudentScore(id, Subject, news);
                                std::cout << "  [成功] 编号 " << id << " 的 " << Subject << " 已修改为 " << news << std::endl;
                            }
                        } 
                    } else if (MsgType_1.get_Msg == "add"){
                        std::cout << std::endl;
                        PrintSeparator();
                        std::cout << "        添加新学生" << std::endl;
                        PrintSeparator();
                        PrintStatus("添加学生");
                        std::cout << "【输入格式】" << std::endl;
                        std::cout << "  <学号> <姓名> <总分> <语文> <数学> <英语> <物理> <化学> <生物>" << std::endl;
                        std::cout << std::endl;
                        std::cout << "【示例】1 张三 650 120 135 128 92 88 87" << std::endl;
                        std::cout << std::endl;
                        std::cout << "请依次输入：" << std::endl;
                        
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_1 = MsgType_2.get_Msg;
                        MsgType_1.input_Msg(std::cin, MsgType_1);
                        std::string order_2 = MsgType_1.get_Msg;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_3 = MsgType_2.get_Msg;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_4 = MsgType_2.get_Msg;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_5 = MsgType_2.get_Msg;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_6 = MsgType_2.get_Msg;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_7 = MsgType_2.get_Msg;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_8 = MsgType_2.get_Msg;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order_9 = MsgType_2.get_Msg;

                        Stu_List Student;
                        Student.AddStudentId(order_1);
                        Student.AddStudentName(order_2);
                        Student.AddStudentTotal(order_3);
                        Student.AddStudentScore("Chinese", order_4);
                        Student.AddStudentScore("Math", order_5);
                        Student.AddStudentScore("English", order_6);
                        Student.AddStudentScore("Physics", order_7);
                        Student.AddStudentScore("Chemistry", order_8);
                        Student.AddStudentScore("Biology", order_9);
                        StuList.AddStudent(Student);
                        std::cout << "  [成功] 学生 " << order_2 << " 已添加！" << std::endl;

                    } else if (MsgType_1.get_Msg == "remove"){
                        std::cout << std::endl;
                        PrintSeparator();
                        std::cout << "        删除学生" << std::endl;
                        PrintSeparator();
                        PrintStatus("删除学生");
                        std::cout << "【提示】编号为排序后的序号，范围 0 ~ " << (StuList.size() - 1) << std::endl;
                        std::cout << std::endl;
                        std::cout << "请输入要删除的学生编号：" << std::endl;
                        
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        int order = MsgType_2.get_Msg;
                        if (order < 0 || order >= StuList.size()) {
                            MsgType_2.handle_error();
                        } else {
                            std::string removed_name = StuList.FindStudentName(order);
                            StuList.RemoveStudent(order);
                            std::cout << "  [成功] 学生 " << removed_name << " 已删除！" << std::endl;
                        }
                    }
                    break;
                }
                case EVALUATION:{
                    std::cout << std::endl;
                    MsgType_1.handle_Msg();
                    PrintSeparator();
                    std::cout << "      Evaluation 评价模式" << std::endl;
                    std::cout << "      线性回归成绩预测" << std::endl;
                    PrintSeparator();
                    PrintStatus("线性回归");
                    
                    std::cout << "【功能说明】" << std::endl;
            std::cout << "  输入历次考试的班级平均分，系统将用线性回归" << std::endl;
                    std::cout << "  分析趋势并预测下次考试的班级平均分。" << std::endl;
                    std::cout << std::endl;
                    
                    std::cout << "请输入考试次数（至少2次）：" << std::endl;
                    MsgType_2.input_Msg(std::cin, MsgType_2);
                    int order = MsgType_2.get_Msg;
                    if (order < 2) {
                        std::cout << "[!] 考试次数至少为2次才能进行回归分析" << std::endl;
                        break;
                    }

                    std::vector<int> x;
                    std::vector<int> y;
                    std::cout << std::endl;
                    std::cout << "请依次输入每次考试的班级总分平均分：" << std::endl;
                    for (int i = 1; i <= order; i++){
                        std::cout << "  第 " << i << " 次考试平均分：" << std::endl;
                        MsgType_2.input_Msg(std::cin, MsgType_2);
                        x.push_back(i);
                        y.push_back(MsgType_2.get_Msg);
                    } 
                    
                    expect = Calculate(x, y, order + 1);
                    std::cout << std::endl;
                    
                    // 打印趋势图
                    PrintTrendChart(x, y, order + 1, expect);
                    
                    is_used = true;
                    break;
                }
                case STATISTIC:{
                    std::cout << std::endl;
                    MsgType_1.handle_Msg();
                    PrintSeparator();
                    std::cout << "      Statistic 统计模式" << std::endl;
                    PrintSeparator();
                    PrintStatus("成绩统计");
                    std::cout << "正在生成六科成绩分级统计报告..." << std::endl;
                    std::cout << std::endl;
                    JudgeMajorSubject(StuList);
                    JudgeMinorSubject(StuList);
                    break;
                }
                default:
                    std::cout << "[!] 无效指令！" << std::endl;
                    std::cout << "    请输入 0, 1, 2 或 end" << std::endl;
                    break;
                }
                std::cout << std::endl;
                PrintSeparator();
                std::cout << "        功能模式" << std::endl;
                PrintSeparator();
                PrintStatus("模式选择");
                std::cout << "操作指引：" << std::endl;
                std::cout << "  0 - Operation  操作模式（查找/修改/添加/删除学生）" << std::endl;
                std::cout << "  1 - Evaluation 评价模式（线性回归预测下次成绩）" << std::endl;
                std::cout << "  2 - Statistic  统计模式（成绩分级统计报告）" << std::endl;
                std::cout << "  end - 退出，查看最终评价" << std::endl;
                std::cout << std::endl;
                std::cout << "请输入：" << std::endl;
                MsgType_1.input_Msg(std::cin, MsgType_1);
            }
            std::cout << std::endl;
            PrintSeparator();
            std::cout << "          最终评价报告" << std::endl;
            PrintSeparator();
            JudgeTotal(StuList);
            if (is_used){
                std::cout << std::endl;
                std::cout << "【线性回归预测结论】" << std::endl;
                if (expect > avg_Total){
                    std::cout << "  经模拟，下次考试全班平均分预计还能上升！" << std::endl;
                    std::cout << "  预测分数：" << expect << " 分（当前平均：" << avg_Total << " 分）" << std::endl;
                    std::cout << "  >> 建议：多奖励学生们，保持良好势头！" << std::endl;
                } 
                else {
                    std::cout << "  经模拟，下次考试全班平均分可能会下降。" << std::endl;
                    std::cout << "  预测分数：" << expect << " 分（当前平均：" << avg_Total << " 分）" << std::endl;
                    std::cout << "  >> 建议：多鼓励学生们，关注薄弱环节！" << std::endl;
                }
            }
        }
    }
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "    感谢使用学生成绩管理系统，再见！" << std::endl;
    std::cout << "========================================" << std::endl;
}


int main(){
    loadStudentData();
    RunInteraction();
    Stu_List();
    return 0;
}
