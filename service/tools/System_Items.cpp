// System_Items.cpp - 统计与评价模块实现：成绩分级统计 + 最小二乘法线性回归
#include "include/System_Items.h"
#include <vector>
#include <iostream>

int avg_Total;

void JudgeTotal(Stu_List& StuList){
    int sum_Total = 0;
    for (int i = 0; i < StuList.size(); i++){
        sum_Total += StuList.FindStudentTotal(i);
    }
    avg_Total = sum_Total / StuList.size();

    StuList.SortedByTotal();
    int upper_Total = 0, low_Total = 0;
    for (int i = 0; i < StuList.size(); i++){
        if (StuList.FindStudentTotal(i) >= avg_Total) upper_Total++;
        else low_Total++;
    }
    if ((double)upper_Total / StuList.size() >= 0.65f){
        std::cout << "本次考试总体成绩不错" << std::endl;
    }
    else if ((double) low_Total / StuList.size() >+ 0.4f){
        std::cout << "本次考试总体成绩较差" << std::endl;
    }
    
    std::cout << "本次考试平均分为：" << avg_Total << "\n" 
              << "超过平均分得有" << upper_Total << "人" << "平均分以下的有" << low_Total << "人" << std::endl;


    if (StuList.FindStudentTotal(0) - StuList.FindStudentTotal(StuList.size() - 1) >= 200){
        std::cout << "本次极差较大！请注意！极差为" << StuList.FindStudentTotal(0) - StuList.FindStudentTotal(StuList.size() - 1) << std::endl;
    } 
    else {
        std::cout << "本次极差为" << StuList.FindStudentTotal(0) - StuList.FindStudentTotal(StuList.size() - 1) << std::endl;
    }
}

void JudgeMinorSubject(Stu_List& StuList){
    // -------------------- 物理评价 --------------------
    StuList.SortedByPhysicsScore();
    std::vector<int> person_1, person_2, person_3, person_4, person_5, person_6;
    int levelTotal_1 = 0, levelTotal_2 = 0, levelTotal_3 = 0, levelTotal_4 = 0, levelTotal_5 = 0, levelTotal_6 = 0;

    for (int i = 0; i < StuList.size(); i++){
        if (StuList.FindStudentScore(i, "Physics") <= MINOR_FULLMARK
            && StuList.FindStudentScore(i, "Physics") >= MINOR_EXCELLENT){
            levelTotal_1++;
            person_1.push_back(StuList.FindStudentScore(i, "Physics"));
        }
        else if (StuList.FindStudentScore(i, "Physics") < MINOR_EXCELLENT
            && StuList.FindStudentScore(i, "Physics") >= MINOR_GOOD){
            levelTotal_2++;
            person_2.push_back(StuList.FindStudentScore(i, "Physics"));
        }
        else if (StuList.FindStudentScore(i, "Physics") < MINOR_GOOD
            && StuList.FindStudentScore(i, "Physics") >= MINOR_PASS){
            levelTotal_3++;
            person_3.push_back(StuList.FindStudentScore(i, "Physics"));
        }
        else if (StuList.FindStudentScore(i, "Physics") < MINOR_PASS
            && StuList.FindStudentScore(i, "Physics") >= MINOR_POOR){
            levelTotal_4++;
            person_4.push_back(StuList.FindStudentScore(i, "Physics"));
        }
        else if (StuList.FindStudentScore(i, "Physics") < MINOR_POOR
            && StuList.FindStudentScore(i, "Physics") > MINOR_FAIL)
        {
            levelTotal_5++;
            person_5.push_back(StuList.FindStudentScore(i, "Physics"));
        }
        else{
            levelTotal_6++;
            person_6.push_back(StuList.FindStudentScore(i, "Physics"));
        }
    }

    // 输出物理评价结果
    std::cout << "\n===== 物理成绩评价 =====\n";
    std::cout << "优秀（90-100）人数：" << levelTotal_1 << " 人\n";
    std::cout << "良好（75-89）人数：" << levelTotal_2 << " 人\n";
    std::cout << "及格（60-74）人数：" << levelTotal_3 << " 人\n";
    std::cout << "较差（35-59）人数：" << levelTotal_4 << " 人\n";
    std::cout << "差（1-34）人数：" << levelTotal_5 << " 人\n";
    std::cout << "不及格（0分）人数：" << levelTotal_6 << " 人\n";
    
    if ((double)(levelTotal_1 + levelTotal_2) / StuList.size() > 0.3f){
        std::cout << "物理成绩总体优秀！" << std::endl;
    } 
    else if ((double)(levelTotal_1 + levelTotal_2 + levelTotal_3) / StuList.size() > 0.5f){
        std::cout << "物理成绩总体不错！" << std::endl;
    }
    else if((double)(levelTotal_5 + levelTotal_6) / StuList.size() > 0.35f){
        std::cout << "物理成绩分数价低者较多！" << std::endl;
    }

    // 重置
    person_1.clear();
    person_2.clear();
    person_3.clear();
    person_4.clear();
    person_5.clear();
    person_6.clear();
    levelTotal_1 = levelTotal_2 = levelTotal_3 = levelTotal_4 = levelTotal_5 = levelTotal_6 = 0;

    // -------------------- 化学评价 --------------------
    StuList.SortedByChemistryScore();

    for (int i = 0; i < StuList.size(); i++){
        if (StuList.FindStudentScore(i, "Chemistry") <= MINOR_FULLMARK
            && StuList.FindStudentScore(i, "Chemistry") >= MINOR_EXCELLENT){
            levelTotal_1++;
            person_1.push_back(StuList.FindStudentScore(i, "Chemistry"));
        }
        else if (StuList.FindStudentScore(i, "Chemistry") < MINOR_EXCELLENT
            && StuList.FindStudentScore(i, "Chemistry") >= MINOR_GOOD){
            levelTotal_2++;
            person_2.push_back(StuList.FindStudentScore(i, "Chemistry"));
        }
        else if (StuList.FindStudentScore(i, "Chemistry") < MINOR_GOOD
            && StuList.FindStudentScore(i, "Chemistry") >= MINOR_PASS){
            levelTotal_3++;
            person_3.push_back(StuList.FindStudentScore(i, "Chemistry"));
        }
        else if (StuList.FindStudentScore(i, "Chemistry") < MINOR_PASS
            && StuList.FindStudentScore(i, "Chemistry") >= MINOR_POOR){
            levelTotal_4++;
            person_4.push_back(StuList.FindStudentScore(i, "Chemistry"));
        }
        else if (StuList.FindStudentScore(i, "Chemistry") < MINOR_POOR
            && StuList.FindStudentScore(i, "Chemistry") > MINOR_FAIL){
            levelTotal_5++;
            person_5.push_back(StuList.FindStudentScore(i, "Chemistry"));
        }
        else{
            levelTotal_6++;
            person_6.push_back(StuList.FindStudentScore(i, "Chemistry"));
        }
    }

    // 输出化学评价结果
    std::cout << "\n===== 化学成绩评价 =====\n";
    std::cout << "优秀（90-100）人数：" << levelTotal_1 << " 人\n";
    std::cout << "良好（75-89）人数：" << levelTotal_2 << " 人\n";
    std::cout << "及格（60-74）人数：" << levelTotal_3 << " 人\n";
    std::cout << "较差（35-59）人数：" << levelTotal_4 << " 人\n";
    std::cout << "差（1-34）人数：" << levelTotal_5 << " 人\n";
    std::cout << "不及格（0分）人数：" << levelTotal_6 << " 人\n";

    if ((double)(levelTotal_1 + levelTotal_2) / StuList.size() > 0.3f){
        std::cout << "化学成绩总体优秀！" << std::endl;
    } 
    else if ((double)(levelTotal_1 + levelTotal_2 + levelTotal_3) / StuList.size() > 0.5f){
        std::cout << "化学成绩总体不错！" << std::endl;
    }
    else if((double)(levelTotal_5 + levelTotal_6) / StuList.size() > 0.35f){
        std::cout << "化学成绩分数价低者较多！" << std::endl;
    }

    // 重置
    person_1.clear();
    person_2.clear();
    person_3.clear();
    person_4.clear();
    person_5.clear();
    person_6.clear();
    levelTotal_1 = levelTotal_2 = levelTotal_3 = levelTotal_4 = levelTotal_5 = levelTotal_6 = 0;

    // -------------------- 生物评价 --------------------
    StuList.SortedByBiologyScore();

    for (int i = 0; i < StuList.size(); i++){
        if (StuList.FindStudentScore(i, "Biology") <= MINOR_FULLMARK
            && StuList.FindStudentScore(i, "Biology") >= MINOR_EXCELLENT){
            levelTotal_1++;
            person_1.push_back(StuList.FindStudentScore(i, "Biology"));
        }
        else if (StuList.FindStudentScore(i, "Biology") < MINOR_EXCELLENT
            && StuList.FindStudentScore(i, "Biology") >= MINOR_GOOD){
            levelTotal_2++;
            person_2.push_back(StuList.FindStudentScore(i, "Biology"));
        }
        else if (StuList.FindStudentScore(i, "Biology") < MINOR_GOOD
            && StuList.FindStudentScore(i, "Biology") >= MINOR_PASS){
            levelTotal_3++;
            person_3.push_back(StuList.FindStudentScore(i, "Biology"));
        }
        else if (StuList.FindStudentScore(i, "Biology") < MINOR_PASS
            && StuList.FindStudentScore(i, "Biology") >= MINOR_POOR){
            levelTotal_4++;
            person_4.push_back(StuList.FindStudentScore(i, "Biology"));
        }
        else if (StuList.FindStudentScore(i, "Biology") < MINOR_POOR
            && StuList.FindStudentScore(i, "Biology") > MINOR_FAIL){
            levelTotal_5++;
            person_5.push_back(StuList.FindStudentScore(i, "Biology"));
        }
        else{
            levelTotal_6++;
            person_6.push_back(StuList.FindStudentScore(i, "Biology"));
        }
    }

    // 输出生物评价结果
    std::cout << "\n===== 生物成绩评价 =====\n";
    std::cout << "优秀（90-100）人数：" << levelTotal_1 << " 人\n";
    std::cout << "良好（75-89）人数：" << levelTotal_2 << " 人\n";
    std::cout << "及格（60-74）人数：" << levelTotal_3 << " 人\n";
    std::cout << "较差（35-59）人数：" << levelTotal_4 << " 人\n";
    std::cout << "差（1-34）人数：" << levelTotal_5 << " 人\n";
    std::cout << "不及格（0分）人数：" << levelTotal_6 << " 人\n";

    if ((double)(levelTotal_1 + levelTotal_2) / StuList.size() > 0.3f){
        std::cout << "生物成绩总体优秀！" << std::endl;
    } 
    else if ((double)(levelTotal_1 + levelTotal_2 + levelTotal_3) / StuList.size() > 0.5f){
        std::cout << "生物成绩总体不错！" << std::endl;
    }
    else if((double)(levelTotal_5 + levelTotal_6) / StuList.size() > 0.35f){
        std::cout << "生物成绩分数价低者较多！" << std::endl;
    }

    // 最终重置
    person_1.clear();
    person_2.clear();
    person_3.clear();
    person_4.clear();
    person_5.clear();
    person_6.clear();
}

void JudgeMajorSubject(Stu_List& StuList){
    // -------------------- 语文评价 --------------------
    StuList.SortedByChineseScore();
    std::vector<int> person_1, person_2, person_3, person_4, person_5, person_6;
    int levelTotal_1 = 0, levelTotal_2 = 0, levelTotal_3 = 0, levelTotal_4 = 0, levelTotal_5 = 0, levelTotal_6 = 0;

    for (int i = 0; i < StuList.size(); i++){
        if (StuList.FindStudentScore(i, "Chinese") <= MAJOR_FULLMARK
            && StuList.FindStudentScore(i, "Chinese") >= MAJOR_EXCELLENT){
            levelTotal_1++;
            person_1.push_back(StuList.FindStudentScore(i, "Chinese"));
        }
        else if (StuList.FindStudentScore(i, "Chinese") < MAJOR_EXCELLENT
            && StuList.FindStudentScore(i, "Chinese") >= MAJOR_GOOD){
            levelTotal_2++;
            person_2.push_back(StuList.FindStudentScore(i, "Chinese"));
        }
        else if (StuList.FindStudentScore(i, "Chinese") < MAJOR_GOOD
            && StuList.FindStudentScore(i, "Chinese") >= MAJOR_PASS){
            levelTotal_3++;
            person_3.push_back(StuList.FindStudentScore(i, "Chinese"));
        }
        else if (StuList.FindStudentScore(i, "Chinese") < MAJOR_PASS
            && StuList.FindStudentScore(i, "Chinese") >= MAJOR_POOR){
            levelTotal_4++;
            person_4.push_back(StuList.FindStudentScore(i, "Chinese"));
        }
        else if (StuList.FindStudentScore(i, "Chinese") < MAJOR_POOR
            && StuList.FindStudentScore(i, "Chinese") > MAJOR_FAIL){
            levelTotal_5++;
            person_5.push_back(StuList.FindStudentScore(i, "Chinese"));
        }
        else{
            levelTotal_6++;
            person_6.push_back(StuList.FindStudentScore(i, "Chinese"));
        }
    }

    // 输出语文评价结果
    std::cout << "\n===== 语文成绩评价 =====\n";
    std::cout << "优秀（120-150）人数：" << levelTotal_1 << " 人\n";
    std::cout << "良好（90-119）人数：" << levelTotal_2 << " 人\n";
    std::cout << "及格（70-89）人数：" << levelTotal_3 << " 人\n";
    std::cout << "较差（40-69）人数：" << levelTotal_4 << " 人\n";
    std::cout << "差（1-39）人数：" << levelTotal_5 << " 人\n";
    std::cout << "不及格（0分）人数：" << levelTotal_6 << " 人\n";

    if ((double)(levelTotal_1 + levelTotal_2) / StuList.size() > 0.3f){
        std::cout << "语文成绩总体优秀！" << std::endl;
    } 
    else if ((double)(levelTotal_1 + levelTotal_2 + levelTotal_3) / StuList.size() > 0.5f){
        std::cout << "语文成绩总体不错！" << std::endl;
    }
    else if((double)(levelTotal_5 + levelTotal_6) / StuList.size() > 0.35f){
        std::cout << "语文成绩分数价低者较多！" << std::endl;
    }

    // 重置
    person_1.clear();
    person_2.clear();
    person_3.clear();
    person_4.clear();
    person_5.clear();
    person_6.clear();
    levelTotal_1 = levelTotal_2 = levelTotal_3 = levelTotal_4 = levelTotal_5 = levelTotal_6 = 0;

    // -------------------- 数学评价 --------------------
    StuList.SortedByMathScore();

    for (int i = 0; i < StuList.size(); i++){
        if (StuList.FindStudentScore(i, "Math") <= MAJOR_FULLMARK
            && StuList.FindStudentScore(i, "Math") >= MAJOR_EXCELLENT){
            levelTotal_1++;
            person_1.push_back(StuList.FindStudentScore(i, "Math"));
        }
        else if (StuList.FindStudentScore(i, "Math") < MAJOR_EXCELLENT
            && StuList.FindStudentScore(i, "Math") >= MAJOR_GOOD){
            levelTotal_2++;
            person_2.push_back(StuList.FindStudentScore(i, "Math"));
        }
        else if (StuList.FindStudentScore(i, "Math") < MAJOR_GOOD
            && StuList.FindStudentScore(i, "Math") >= MAJOR_PASS){
            levelTotal_3++;
            person_3.push_back(StuList.FindStudentScore(i, "Math"));
        }
        else if (StuList.FindStudentScore(i, "Math") < MAJOR_PASS
            && StuList.FindStudentScore(i, "Math") >= MAJOR_POOR){
            levelTotal_4++;
            person_4.push_back(StuList.FindStudentScore(i, "Math"));
        }
        else if (StuList.FindStudentScore(i, "Math") < MAJOR_POOR
            && StuList.FindStudentScore(i, "Math") > MAJOR_FAIL){
            levelTotal_5++;
            person_5.push_back(StuList.FindStudentScore(i, "Math"));
        }
        else{
            levelTotal_6++;
            person_6.push_back(StuList.FindStudentScore(i, "Math"));
        }
    }

    // 输出数学评价结果
    std::cout << "\n===== 数学成绩评价 =====\n";
    std::cout << "优秀（120-150）人数：" << levelTotal_1 << " 人\n";
    std::cout << "良好（90-119）人数：" << levelTotal_2 << " 人\n";
    std::cout << "及格（70-89）人数：" << levelTotal_3 << " 人\n";
    std::cout << "较差（40-69）人数：" << levelTotal_4 << " 人\n";
    std::cout << "差（1-39）人数：" << levelTotal_5 << " 人\n";
    std::cout << "不及格（0分）人数：" << levelTotal_6 << " 人\n";

    if ((double)(levelTotal_1 + levelTotal_2) / StuList.size() > 0.3f){
        std::cout << "数学成绩总体优秀！" << std::endl;
    } 
    else if ((double)(levelTotal_1 + levelTotal_2 + levelTotal_3) / StuList.size() > 0.5f){
        std::cout << "数学成绩总体不错！" << std::endl;
    }
    else if((double)(levelTotal_5 + levelTotal_6) / StuList.size() > 0.35f){
        std::cout << "数学成绩分数价低者较多！" << std::endl;
    }

    // 重置
    person_1.clear();
    person_2.clear();
    person_3.clear();
    person_4.clear();
    person_5.clear();
    person_6.clear();
    levelTotal_1 = levelTotal_2 = levelTotal_3 = levelTotal_4 = levelTotal_5 = levelTotal_6 = 0;

    // -------------------- 英语评价 --------------------
    StuList.SortedByEnglishScore();

    for (int i = 0; i < StuList.size(); i++){
        if (StuList.FindStudentScore(i, "English") <= MAJOR_FULLMARK
            && StuList.FindStudentScore(i, "English") >= MAJOR_EXCELLENT){
            levelTotal_1++;
            person_1.push_back(StuList.FindStudentScore(i, "English"));
        }
        else if (StuList.FindStudentScore(i, "English") < MAJOR_EXCELLENT
            && StuList.FindStudentScore(i, "English") >= MAJOR_GOOD){
            levelTotal_2++;
            person_2.push_back(StuList.FindStudentScore(i, "English"));
        }
        else if (StuList.FindStudentScore(i, "English") < MAJOR_GOOD
            && StuList.FindStudentScore(i, "English") >= MAJOR_PASS){
            levelTotal_3++;
            person_3.push_back(StuList.FindStudentScore(i, "English"));
        }
        else if (StuList.FindStudentScore(i, "English") < MAJOR_PASS
            && StuList.FindStudentScore(i, "English") >= MAJOR_POOR){
            levelTotal_4++;
            person_4.push_back(StuList.FindStudentScore(i, "English"));
        }
        else if (StuList.FindStudentScore(i, "English") < MAJOR_POOR
            && StuList.FindStudentScore(i, "English") > MAJOR_FAIL){
            levelTotal_5++;
            person_5.push_back(StuList.FindStudentScore(i, "English"));
        }
        else{
            levelTotal_6++;
            person_6.push_back(StuList.FindStudentScore(i, "English"));
        }
    }

    // 输出英语评价结果
    std::cout << "\n===== 英语成绩评价 =====\n";
    std::cout << "优秀（120-150）人数：" << levelTotal_1 << " 人\n";
    std::cout << "良好（90-119）人数：" << levelTotal_2 << " 人\n";
    std::cout << "及格（70-89）人数：" << levelTotal_3 << " 人\n";
    std::cout << "较差（40-69）人数：" << levelTotal_4 << " 人\n";
    std::cout << "差（1-39）人数：" << levelTotal_5 << " 人\n";
    std::cout << "不及格（0分）人数：" << levelTotal_6 << " 人\n";

    if ((double)(levelTotal_1 + levelTotal_2) / StuList.size() > 0.3f){
        std::cout << "英语成绩总体优秀！" << std::endl;
    } 
    else if ((double)(levelTotal_1 + levelTotal_2 + levelTotal_3) / StuList.size() > 0.5f){
        std::cout << "英语成绩总体不错！" << std::endl;
    }
    else if((double)(levelTotal_5 + levelTotal_6) / StuList.size() > 0.35f){
        std::cout << "英语成绩分数价低者较多！" << std::endl;
    }

    // 最终重置
    person_1.clear();
    person_2.clear();
    person_3.clear();
    person_4.clear();
    person_5.clear();
    person_6.clear();
}

double Calculate(std::vector<int> x, std::vector<int> y, int x_1) {
    int n = x.size();
    if (n == 0 || n != y.size()) {
        return 0; // 防止空数据或长度不一致
    }

    // 1. 计算平均值
    double sum_x = 0, sum_y = 0;
    for (int xi : x) sum_x += xi;
    for (int yi : y) sum_y += yi;
    double avg_x = sum_x / n;
    double avg_y = sum_y / n;

    // 2. 计算分子分母
    double numerator = 0; // sum((xi - avg_x)(yi - avg_y))
    double denominator = 0; // sum((xi - avg_x)^2)
    for (int i = 0; i < n; i++) {
        double dx = x[i] - avg_x;
        double dy = y[i] - avg_y;
        numerator += dx * dy;
        denominator += dx * dx;
    }

    if (denominator == 0) {
        return avg_y; // 防止除以0，此时所有x都相同，预测值就是平均值
    }

    // 3. 计算回归系数
    double b = numerator / denominator;
    double a = avg_y - b * avg_x;

    // 4. 预测 x1 对应的 y 值
    return a + b * x_1;
}

// int main(){ return 0;}
