//
// Created by yang on 18-9-12.
//

#include "Teacher.h"

int Teacher::getId() const {
    return id;
}

void Teacher::setId(int id) {
    Teacher::id = id;
}

const std::string &Teacher::getName() const {
    return name;
}

void Teacher::setName(const std::string &name) {
    Teacher::name = name;
}

const std::string &Teacher::getUsername() const {
    return username;
}

void Teacher::setUsername(const std::string &username) {
    Teacher::username = username;
}

const std::string &Teacher::getPassword() const {
    return password;
}

void Teacher::setPassword(const std::string &password) {
    Teacher::password = password;
}

std::vector<TestPaper> &Teacher::getTestPapers(){
    return testPapers;
}

void Teacher::setTestPapers(const std::vector<TestPaper> &testPapers) {
    Teacher::testPapers = testPapers;
}

std::vector<TestPaper> &Teacher::getNote()
{
    return note;
}

void Teacher::setNote(const std::vector<TestPaper> &note)
{
    Teacher::note = note;
}
