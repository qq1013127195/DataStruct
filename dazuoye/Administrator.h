//
// Created by yang on 18-9-12.
//

#ifndef DAZUOYE_ADMINISTRATOR_H
#define DAZUOYE_ADMINISTRATOR_H

#include <string>
#include <vector>

#include "Teacher.h"
#include "Student.h"

class Administrator {
public:
    Administrator(int i, std::string un, std::string pass) : id(i), username(un), password(pass) {};
    int getId() const;
    void setId(int id);
    const std::string &getUsername() const;
    void setUsername(const std::string &username);
    const std::string &getPassword() const;
    void setPassword(const std::string &password);
    const std::vector<Teacher> &getTeachers() const;
    void setTeachers(const std::vector<Teacher> &teachers);
    const std::vector<Student> &getStudents() const;
    void setStudents(const std::vector<Student> &students);
    void addTeacher(const Teacher &teacher);
    void addStudent(const Student &student);

private:
    int id;
    std::string username;
    std::string password;
    std::vector<Teacher> teachers;
    std::vector<Student> students;

};


#endif //DAZUOYE_ADMINISTRATOR_H
