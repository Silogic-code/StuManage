// Stu_Manage.cpp - 数据加载模块实现：从标准输入读取学生数据并存入顺序表
#include "include/Stu_Manage.h"
#include "class/Stu_List.h"
#include <iostream>

Stu_List StuList;

void loadStudentData(){
    int id, total, idx = 1; std::string name; 
    int score_1, score_2, score_3, score_4, score_5, score_6;
    std::cout << "========================================" << std::endl;
    std::cout << "      学生成绩数据录入" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "【输入格式说明】" << std::endl;
    std::cout << "每行输入一名学生的信息，格式为：" << std::endl;
    std::cout << "  <学号> <姓名> <总分> <语文> <数学> <英语> <物理> <化学> <生物>" << std::endl;
    std::cout << std::endl;
    std::cout << "【示例】" << std::endl;
    std::cout << "  1 张三 650 120 135 128 92 88 87" << std::endl;
    std::cout << std::endl;
    std::cout << "【提示】" << std::endl;
    std::cout << "  - 输入完毕后按 Ctrl+D (Linux/Mac) 或 Ctrl+Z+回车 (Windows) 结束输入" << std::endl;
    std::cout << "  - 学号为正整数，姓名不包含空格" << std::endl;
    std::cout << "  - 六科成绩为整数" << std::endl;
    std::cout << std::endl;
    std::cout << "请开始输入学生数据：" << std::endl;
    while(std::cin >> id >> name >> total >> 
                     score_1 >> score_2 >> score_3 >>
                     score_4 >> score_5 >> score_6){
        Stu_List Student;
        Student.AddStudentId(id); Student.AddStudentName(name); Student.AddStudentTotal(total);
        Student.AddStudentScore("Chinese", score_1);
        Student.AddStudentScore("Math", score_2);
        Student.AddStudentScore("English", score_3);
        Student.AddStudentScore("Physics", score_4);
        Student.AddStudentScore("Chemistry", score_5);
        Student.AddStudentScore("Biology", score_6);
        StuList.AddStudent(Student);
        std::cout << "  [已录入] 学号 " << id << " " << name << " 总分 " << total << std::endl;
    }
    std::cin.clear();
    StuList.SortedByTotal();
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  录入完成！共 " << StuList.size() << " 名学生" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

// int main(){ return 0;}
