// Stu_List.cpp - 顺序表核心操作实现：排序、查找、增删改、动态扩容及内存管理
#include "class/Stu_List.h"
#include <cstring>
#include <iostream>
#include <algorithm>

void Stu_List::SortedByTotal(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getTotal() > y.getTotal();
    });
}

void Stu_List::SortedById(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getId() > y.getId();
    });
}

void Stu_List::SortedByChineseScore(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getScore("Chinese") > y.getScore("Chinese");
    });
}

void Stu_List::SortedByMathScore(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getScore("Math") > y.getScore("Math");
    });
}

void Stu_List::SortedByEnglishScore(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getScore("English") > y.getScore("English");
    });
}

void Stu_List::SortedByPhysicsScore(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getScore("Physics") > y.getScore("Physics");
    });
}

void Stu_List::SortedByChemistryScore(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getScore("Chemistry") > y.getScore("Chemistry");
    });
}

void Stu_List::SortedByBiologyScore(){
    std::sort(a, a + len, [](const Stu_Info& x, const Stu_Info y){
        return x.getScore("Biology") > y.getScore("Biology");
    });
}


void Stu_List::AddStudentId(int id) {
    allocate();
    a->setId(id); 
}

void Stu_List::AddStudentName(const std::string& name){
    a->setName(name);
}

void Stu_List::AddStudentTotal(int total){
    a->setTotal(total);
}

void Stu_List::AddStudentScore(const std::string& Subject, int Score){
    a->setScore(Subject, Score);
}

int Stu_List::size() const{
    return len;
}

int Stu_List::FindById(const std::string& name) const{
    if (empty()) return -1;
    for (int i = 0; i < len; i++)
        if (a[i].getName() == name) return i;
    return -1;
}

int Stu_List::FindById(int id) const{
    if (id < 0) return -1;
    for (int i = 0; i < len; i++)
        if (a[i].getId() == id) return i;
    return -1;
}

bool Stu_List::empty() const{
    return len == 0;
}

void Stu_List::print() const{
    if (empty()) return;
    for (int i = 0; i < len; i++){
        std::cout << "姓名（Name）："     << a[i].getName()
                  << "学号（ID）："       << a[i].getId()
                  << "总分（Total）："    << a[i].getTotal()
                  << "语文（Chinese）："  << a[i].getScore("Chinese")
                  << "数学（Math）："     << a[i].getScore("Math")
                  << "英语（English）："   << a[i].getScore("English")
                  << "物理（Physics）："  << a[i].getScore("Physics")
                  << "化学（Chemistry）："<< a[i].getScore("Chemistry")
                  << "生物（Biology）："  << a[i].getScore("Biology") << "\n";
    }
    
}

void Stu_List::ReviseStudentID(int idx, int newId){
    if (idx < 0 || idx >= len) return;
    a[idx].setId(newId);
    
}

void Stu_List::ReviseStudentTotal(int idx, int newTotal){
    if (idx < 0 || idx >= len) return;
    a[idx].setTotal(newTotal);
}

void Stu_List::ReviseStudentName(int idx, const std::string& newName){
    if (idx < 0 || idx >= len) return;
    a[idx].setName(newName);
}

void Stu_List::ReviseStudentScore(int idx, std::string& Subject, int newScore){
    if (idx < 0 || idx >= len) return;
    a[idx].setScore(Subject, newScore);
}

void Stu_List::RemoveStudent(int idx){
    if (empty()) return;
    for (int i = idx; i < len - 1; i++) a[i] = a[i + 1];
    len--;
}

void Stu_List::AddStudent(const Stu_List& List){
    allocate();
    a[len] = *List.a;
    len++;
}


int Stu_List::FindStudentID(int idx) const{
    if (idx < 0 || idx >= len) return -1;
    return a[idx].getId();
}

std::string Stu_List::FindStudentName(int idx) const{
    if (idx < 0 || idx >= len) return "";
    return a[idx].getName();
}

int Stu_List::FindStudentTotal(int idx) const{
    if (idx < 0 || idx >= len) return -1;
    return a[idx].getTotal();
}

int Stu_List::FindStudentScore(int idx, const std::string& Subject) const{
    if (idx < 0 || idx >= len) return -1;
    return a[idx].getScore(Subject);
}

void Stu_List::allocate(){
    if (capacity == 0){
        a = new Stu_Info[4];
        capacity = 4;
    }
    else if(len >= capacity){
        Stu_Info* newarr = new Stu_Info[capacity * 2];
        for (int i = 0; i < len; ++i) newarr[i] = a[i];
        delete[] a;
        a = newarr;
        capacity *= 2;
    } else return;
}

Stu_List::~Stu_List(){
    delete[] a;
    a = nullptr;
    capacity = 0;
    len = 0;
    
}

// int main(){  return 0;}
