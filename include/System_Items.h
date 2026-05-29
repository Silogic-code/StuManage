// System_Items.h - 统计与评价模块接口：成绩分级、线性回归等功能的声明
#pragma once
#include "class/Stu_List.h"
#include <vector>

extern int avg_Total;

typedef enum{
    OPERATION,
    EVALUATION,
    STATISTIC,
}Scenario;

// 向上判定
typedef enum{
    MAJOR_FULLMARK = 150,
    MAJOR_EXCELLENT = 120,
    MAJOR_GOOD = 90,
    MAJOR_PASS = 90,
    MAJOR_POOR = 60,
    MAJOR_FAIL = 0,
}MajorSubjectLevel;

typedef enum{
    MINOR_FULLMARK = 100,
    MINOR_EXCELLENT = 90,
    MINOR_GOOD = 75,
    MINOR_PASS = 60,
    MINOR_POOR = 35,
    MINOR_FAIL = 0,
}MinorSubjectLevel;

// 判优函数
void JudgeTotal(Stu_List& StuList);
void JudgeMajorSubject(Stu_List& StuList);
void JudgeMinorSubject(Stu_List& StuList);

// 计算线性回归方程
double Calculate(std::vector<int> x, std::vector<int> y, int x_1);
