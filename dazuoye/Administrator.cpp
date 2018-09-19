//
// Created by yang on 18-9-12.
//

#include "Administrator.h"

int Administrator::getId() const
{
    return id;
}

void Administrator::setId(int id)
{
    Administrator::id = id;
}

const std::string &Administrator::getUsername() const
{
    return username;
}

void Administrator::setUsername(const std::string &username)
{
    Administrator::username = username;
}

const std::string &Administrator::getPassword() const
{
    return password;
}

void Administrator::setPassword(const std::string &password)
{
    Administrator::password = password;
}

const std::vector<Teacher> &Administrator::getTeachers() const
{
    return teachers;
}

void Administrator::setTeachers(const std::vector<Teacher> &teachers)
{
    Administrator::teachers = teachers;
}

const std::vector<Student> &Administrator::getStudents() const
{
    return students;
}

void Administrator::setStudents(const std::vector<Student> &students)
{
    Administrator::students = students;
}

void Administrator::addTeacher(const Teacher &teacher)
{
    Administrator::teachers.push_back(teacher);
}

void Administrator::addStudent(const Student &student)
{
    Administrator::students.push_back(student);
}
