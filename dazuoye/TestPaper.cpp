//
// Created by yang on 18-9-12.
//

#include "TestPaper.h"

int TestPaper::getId() const
{
    return id;
}

void TestPaper::setId(int id)
{
    TestPaper::id = id;
}

const std::string &TestPaper::getTeacherName() const
{
    return teacherName;
}

void TestPaper::setTeacherName(const std::string &teacherName)
{
    TestPaper::teacherName = teacherName;
}

const std::string &TestPaper::getStuName() const
{
    return stuName;
}

void TestPaper::setStuName(const std::string &stuName)
{
    TestPaper::stuName = stuName;
}

unsigned int TestPaper::getScore() const
{
    return score;
}

void TestPaper::setScore(unsigned int score)
{
    TestPaper::score = score;
}

const std::string &TestPaper::getName() const
{
    return name;
}

void TestPaper::setName(const std::string &name)
{
    TestPaper::name = name;
}

const std::string &TestPaper::getArea() const
{
    return area;
}

void TestPaper::setArea(const std::string &area)
{
    TestPaper::area = area;
}

const std::string &TestPaper::getRequire() const
{
    return require;
}

void TestPaper::setRequire(const std::string &require)
{
    TestPaper::require = require;
}

const std::string &TestPaper::getData() const
{
    return data;
}

void TestPaper::setData(const std::string &data)
{
    TestPaper::data = data;
}
