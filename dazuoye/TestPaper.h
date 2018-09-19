//
// Created by yang on 18-9-12.
//



#ifndef DAZUOYE_TESTPAPER_H
#define DAZUOYE_TESTPAPER_H

#include <vector>
#include <string>

class Teacher;
class Student;

class TestPaper {
public:
    TestPaper(int i, std::string n, std::string tn) : id(i), name(n), teacherName(tn), score(0) {};

    int getId() const;

    void setId(int id);

    const std::string &getTeacherName() const;

    void setTeacherName(const std::string &teacherName);

    const std::string &getStuName() const;

    void setStuName(const std::string &stuName);

    unsigned int getScore() const;

    void setScore(unsigned int score);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getArea() const;

    void setArea(const std::string &area);

    const std::string &getRequire() const;

    void setRequire(const std::string &require);

    const std::string &getData() const;

    void setData(const std::string &data);
//id， stuName， teacherName， score
private:
    int id;
    std::string name;
    std::string stuName;
    std::string teacherName;
    unsigned int score;
    std::string area;
    std::string require;
    std::string data;

};


#endif //DAZUOYE_TESTPAPER_H
