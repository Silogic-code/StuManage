// Stu_Info.h - 学生信息类：封装单个学生的姓名、学号、总分及六科成绩
#pragma once

#include <string>
#include <unordered_map>
class Stu_Info{
private:
    std::string name;
    int id;
    int total;
    std::unordered_map<std::string, int>score;

    // 对象内部接口
    bool check(const std::string& Subject) const{
        return score.find(Subject) == score.end();
    }    
public:

    Stu_Info():name(""), id(0), total(0){
        score["Chinese"] = 0;
        score["Math"] = 0;
        score["English"] = 0;
        score["Physics"] = 0;
        score["Chemistry"] = 0;
        score["Biology"] = 0;
    }

    std::string getName() const{ return name;}
    int getId() const{ return id;}
    int getTotal() const{ return total;}
    int getScore(const std::string& Subject) const{
        if (check(Subject)) return -1; 
        return score.at(Subject);
    }

    std::string setName(const std::string& newName) { name = newName; return name;}
    void setId(int newId){ id = newId;}
    void setTotal(int newTotal){ total = newTotal;}
    void setScore(const std::string& Subject, int newScore){
        if (check(Subject)) return;
        score[Subject] = newScore;
    }

};
