// Stu_List.h - 学生顺序表容器类：动态数组管理多个 Stu_Info 对象，提供增删改查和排序
#pragma once
#include "Stu_Info.h"
#include <cassert>
class Stu_List{
private:
    Stu_Info* a;
    int capacity;
    int len;

    void allocate();
public:

    Stu_List():a(nullptr), capacity(0), len(0){}


    int FindStudentID(int idx) const;
    std::string FindStudentName(int idx) const;
    int FindStudentTotal(int idx) const;
    int FindStudentScore(int idx,const std::string& Subject) const;
    // 函数重载
    int FindById(int id) const;
    int FindById(const std::string& name) const;

    void AddStudent(const Stu_List& List);
    void AddStudentId(int id);
    void AddStudentName(const std::string& name);
    void AddStudentTotal(int total);
    void AddStudentScore(const std::string& Subject, int Score);

    void ReviseStudentID(int idx,int newId);
    void ReviseStudentTotal(int idx, int newTotal);
    void ReviseStudentName(int idx, const std::string& newName); 
    void ReviseStudentScore(int idx, std::string& Subject, int newScore);

    void SortedByTotal();
    void SortedById();
    void SortedByChineseScore();
    void SortedByMathScore();
    void SortedByEnglishScore();
    void SortedByPhysicsScore();
    void SortedByChemistryScore();
    void SortedByBiologyScore();

    int size() const;
    void print() const;
    void RemoveStudent(int idx);
    ~Stu_List();
    bool empty() const;

};
