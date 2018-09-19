//
// Created by yang on 18-9-12.
//

#ifndef DAZUOYE_TEACHER_H
#define DAZUOYE_TEACHER_H

#include <string>
#include <vector>
#include "TestPaper.h"

class Teacher {
public:
    Teacher(int i, std::string n, std::string un, std::string pass) : id(i), name(n), username(un), password(pass) {};

    int getId() const;

    void setId(int id);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    std::vector<TestPaper> &getTestPapers();

    void setTestPapers(const std::vector<TestPaper> &testPapers);

    std::vector<TestPaper> &getNote();

    void setNote(const std::vector<TestPaper> &note);
//id, name, username, password, testPapers
private:
    int id;
    std::string name;
    std::string username;
    std::string password;
    std::vector<TestPaper> note;
    std::vector<TestPaper> testPapers;
};


#endif //DAZUOYE_TEACHER_H
