//
// Created by yang on 18-9-12.
//

#include "Student.h"

int Student::getId() const
{
    return id;
}

void Student::setId(int id)
{
    Student::id = id;
}

const std::string &Student::getName() const
{
    return name;
}

void Student::setName(const std::string &name)
{
    Student::name = name;
}

const std::string &Student::getUsername() const
{
    return username;
}

void Student::setUsername(const std::string &username)
{
    Student::username = username;
}

const std::string &Student::getPassword() const
{
    return password;
}

void Student::setPassword(const std::string &password)
{
    Student::password = password;
}

std::vector<TestPaper> &Student::getTestPapers()
{
    return testPapers;
}

void Student::setTestPapers(const std::vector<TestPaper> &testPapers)
{
    Student::testPapers = testPapers;
}
