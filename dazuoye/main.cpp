#include <iostream>
#include <vector>
#include "Teacher.h"
#include "Student.h"
#include "TestPaper.h"
#include "Administrator.h"
#include <iomanip>

void init(std::vector<Teacher> &, std::vector<Student> &, Administrator &);//初始化
void toMain(std::vector<Teacher> &, std::vector<Student> &, Administrator &);//跳转到主页面
void toStu(std::vector<Teacher> &, std::vector<Student> &, Administrator &);
void toTech(std::vector<Teacher> &, std::vector<Student> &, Administrator &);
void toAdmin(std::vector<Teacher> &, std::vector<Student> &, Administrator &);
void toEditStuPass(std::vector<Student>::iterator &);
void toSubTestPaper(std::vector<Student>::iterator &, std::vector<Teacher> &);
void toViewScore(std::vector<Student>::iterator &);
void toViewTask(std::vector<Student>::iterator &, std::vector<Teacher> &);
void toEditTechPass(std::vector<Teacher>::iterator &);
void toSubNote(std::vector<Teacher>::iterator &);
void toViewNote(std::vector<Teacher>::iterator &);
void toEditAdminPass(Administrator &);
void addTeacher(std::vector<Teacher> &);
void addStu(std::vector<Student> &);
void toEditScore(std::vector<Teacher>::iterator &, std::vector<Student> &);

int main() {
    std::vector<Teacher> teachers;
    std::vector<Student> students;
    Administrator admin(0, "null", "null");
    init(teachers, students, admin);
    toMain(teachers, students, admin);
    return 0;
}

void init(std::vector<Teacher> &teachers, std::vector<Student> &students, Administrator &admin)
{
    Teacher t1(1, "yzy", "yyy", "yyy");
    Teacher t2(2, "zzz", "zzz", "zzz");
    teachers.push_back(t1);
    teachers.push_back(t2);

    Student s1(1, "www", "www", "www");
    Student s2(2, "xxx", "xxx", "xxx");
    students.push_back(s1);
    students.push_back(s2);

    admin.setUsername("admin");
    admin.setPassword("admin");
}

void toMain(std::vector<Teacher> &teachers, std::vector<Student> &students, Administrator &admin)
{
    std::cout << "欢迎使用学生作业管理系统" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "1.学生" << std::endl;
    std::cout << "2.管理员" << std::endl;
    std::cout << "3.教师" << std::endl;
    std::cout << "4.退出" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "清选择：";
    int a;
    std::cin >> a;
    switch (a)
    {
        case 1:
            toStu(teachers, students, admin);
            break;
        case 2:
            toAdmin(teachers, students, admin);
            break;
        case 3:
            toTech(teachers, students, admin);
            break;
        case 4:
            return;

    }

}

void toStu(std::vector<Teacher> &teachers, std::vector<Student> &students, Administrator &admin)
{
    std::cout << "请输入账号： ";
    std::string username;
    std::cin >> username;
    std::cout << "请输入密码： ";
    std::string password;
    std::cin >> password;
    for (auto itr = students.begin(); itr != students.end(); itr++)
    {
        if (!(itr->getUsername().compare(username)) && !(itr->getPassword().compare(password)))
        {
            r:
            std::cout << "--------------------------------" << std::endl;
            std::cout << "---->学生：" << std::endl;
            std::cout << "1.修改密码" << std::endl;
            std::cout << "2.上传作业" << std::endl;
            std::cout << "3.查看成绩" << std::endl;
            std::cout << "4.查看作业任务" << std::endl;
            std::cout << "5.返回主菜单" << std::endl;
            std::cout << "清选择：";
            int a;
            std::cin >> a;
            switch (a)
            {
                case 1:
                    toEditStuPass(itr);
                    std::cout << "是否继续<Y/N>: ";
                    char b;
                    std::cin >> b;
                    if (b == 'Y')
                        goto r;
                    else
                        toMain(teachers, students, admin);
                    break;
                case 2:
                    toSubTestPaper(itr, teachers);
                    std::cout << "是否返回主菜单<Y/N>: ";
                    char z;
                    std::cin >> z;
                    if (z == 'Y')
                        toMain(teachers, students, admin);
                    else
                        goto r;
                    break;
                case 3:
                    toViewScore(itr);
                    std::cout << "是否继续<Y/N>: ";
                    char c;
                    std::cin >> c;
                    if (c == 'Y')
                        goto r;
                    else
                        toMain(teachers, students, admin);
                    break;
                case 4:
                    toViewTask(itr, teachers);
                    std::cout << "是否返回主菜单<Y/N>: ";
                    char d;
                    std::cin >> d;
                    if (d == 'Y')
                        toMain(teachers, students, admin);
                    else
                        goto r;
                    break;
                case 5:
                    std::cout << "是否返回主菜单<Y/N>: ";
                    char f;
                    std::cin >> f;
                    if (f == 'Y')
                        toMain(teachers, students, admin);
                    else
                        goto r;
                    break;
            }
            break;
        }
    }

}

void toEditStuPass(std::vector<Student>::iterator &itr)
{
    std::string oldPass;
    std::string newPass1;
    std::string newPass2;
    r1:
    std::cout  << "请输入密码： ";
    std::cin >> oldPass;
    if (!(itr->getPassword().compare(oldPass)))
    {
        r2:
        std::cout << "请输入新密码： ";
        std::cin >> newPass1;
        std::cout << "请再次输入新密码： ";
        std::cin >> newPass2;
        if (!newPass1.compare(newPass2))
        {
            itr->setPassword(newPass1);
            std::cout << "修改成功" << std::endl;
        }
        else
        {
            goto r2;
        }

    }
    else
    {
        std::cout << "密码错误" << std::endl;
        goto r1;
    }
}

void toSubTestPaper(std::vector<Student>::iterator &itr, std::vector<Teacher> &teachers)
{
    stp:
    std::string teacher;
    std::cout << "请输入你要提交作业老师的名字: " << std::endl;
    std::cin >> teacher;
    for (auto itrT = teachers.begin(); itrT != teachers.end(); itrT++)
    {
        if (!(itrT->getName().compare(teacher)))
        {
            std::cout.width(8);
            std::cout << "序号" << "科目" << "要求" << std::endl;
            int i = 1;
            std::vector<TestPaper> t;
            for (auto itrTP = itrT->getNote().begin(); itrTP != itrT->getNote().end(); itrTP++)
            {
                bool b = true;
                for (auto itrSP = itr->getTestPapers().begin(); itrSP != itr->getTestPapers().end(); itrSP++)
                {
                    if (!(itrSP->getName().compare(itrTP->getName())))
                    {
                        b = false;
                        break;
                    }

                }
                if (b)
                {
                    TestPaper tt(i, itrTP->getName(), itrTP->getTeacherName());
                    tt.setRequire(itrTP->getRequire());
                    tt.setStuName(itr->getName());
                    t.push_back(tt);
                    std::cout << i << itrTP->getName() << itrTP->getRequire() << std::endl;
                    i++;
                }

            }
            std::cout << "请输入你要做的题的序号: ";
            int z;
            std::cin >> z;
            std::cout << "请输入你的答案: ";
            std::string area;
            std::cin >> area;
            t[--z].setArea(area);
            t[z].setStuName(itr->getName());
            itr->getTestPapers().push_back(t[z]);
            itrT->getTestPapers().push_back(t[z]);
            std::cout << "是否继续<Y/N>: ";
            char a;
            std::cin >> a;
            if (a == 'Y')
                goto stp;
            break;
        }
    }
}

void toViewScore(std::vector<Student>::iterator &itr)
{
    std::cout.width(8);
    int i = 1;
    std::cout << "序号" << "要求" << "科目" << "分数" << std::endl;
    for (auto itrSP = itr->getTestPapers().begin(); itrSP != itr->getTestPapers().end(); itrSP++)
    {
        std::cout << i << itrSP->getRequire() << itrSP->getName() << itrSP->getScore() << std::endl;
    }
}

void toViewTask(std::vector<Student>::iterator &itr, std::vector<Teacher> &teachers)
{
    std::cout << "请输入你要提交作业的老师的名字: ";
    std::string teacher;
    std::cin >> teacher;
    for (auto itrT = teachers.begin(); itrT != teachers.end(); itrT++)
    {
        if (!(itrT->getName().compare(teacher)))
        {
            std::cout.width(8);
            std::cout << "序号" << "科目" << "要求" << std::endl;
            int i = 1;
            std::vector<TestPaper> t;
            for (auto itrTN = itrT->getNote().begin(); itrTN != itrT->getNote().end(); itrTN++)
            {
                bool b = true;
                for (auto itrSP = itr->getTestPapers().begin(); itrSP != itr->getTestPapers().end(); itrSP++)
                {
                    if (!(itrSP->getName().compare(itrTN->getName())))
                    {
                        b = false;
                        break;
                    }

                }
                if (b)
                {
                    TestPaper tt(i, itrTN->getName(), itrTN->getTeacherName());
                    tt.setRequire(itrTN->getRequire());
                    tt.setStuName(itr->getName());
                    t.push_back(tt);
                    std::cout << i << itrTN->getName() << itrTN->getRequire() << std::endl;
                    i++;
                }
            }

            std::cout << "是否去完成作业<Y/N>:";
            char aaa;
            std::cin >> aaa;
            if (aaa == 'Y')
            {
                rrrr:
                std::cout << "请输入你要做的题的序号: ";
                int z;
                std::cin >> z;
                std::cout << "请输入你的答案: ";
                std::string area;
                std::cin >> area;
                t[--z].setArea(area);
                t[z].setStuName(itr->getName());
                itr->getTestPapers().push_back(t[z]);
                itrT->getTestPapers().push_back(t[z]);
                std::cout << "作业完成!" << std::endl;

                std:: cout << "是否继续<Y/N>: ";
                char bbb;
                std::cin >> bbb;
                if (bbb == 'Y')
                {
                    goto rrrr;
                }

            }
            else
            {
                break;
            }

        }
    }
}

void toTech(std::vector<Teacher> &teachers, std::vector<Student> &students, Administrator &admin)
{
    std::cout << "清输入账号: ";
    std::string username;
    std::cin >> username;
    std::cout << "清输入密码: ";
    std::string password;
    std::cin >>password;
    for (auto itr = teachers.begin(); itr != teachers.end(); itr++)
    {
        if (!(itr->getUsername().compare(username)) && !(itr->getPassword().compare(password)))
        {
            rtech:
            std::cout << "***********************************" << std::endl;
            std::cout << "--------->教师: " << std::endl;
            std::cout << "1.修改密码" << std::endl;
            std::cout << "2.批改作业" << std::endl;
            std::cout << "3.发布作业任务" << std::endl;
            std::cout << "4.查看以发布作业任务" << std::endl;
            std::cout << "5.返回主菜单" << std::endl;
            std::cout << "清选择：";
            int a;
            std::cin >> a;
            switch (a)
            {
                case 1:
                    toEditTechPass(itr);
                    std::cout << "是否继续<Y/N>: ";
                    char b;
                    std::cin >> b;
                    if (b == 'Y')
                        goto rtech;
                    else
                        toMain(teachers, students, admin);
                    break;
                case 2:
                    toEditScore(itr, students);
                    goto rtech;
                    break;
                case 3:
                    toSubNote(itr);
                    goto rtech;
                    break;
                case 4:
                    toViewNote(itr);
                    std::cout << "是否继续<Y/N>: ";
                    char c;
                    std::cin >> c;
                    if (c == 'Y')
                        goto rtech;
                    else
                        toMain(teachers, students, admin);
                    break;
                case 5:
                    std::cout << "是否返回主菜单<Y/N>: ";
                    char f;
                    std::cin >> f;
                    if (f == 'Y')
                        toMain(teachers, students, admin);
                    else
                        goto rtech;
                    break;
            }
        }
    }
}

void toEditTechPass(std::vector<Teacher>::iterator &itr)
{
    std::string oldPass;
    std::string newPass1;
    std::string newPass2;
    r1:
    std::cout  << "请输入密码： ";
    std::cin >> oldPass;
    if (!(itr->getPassword().compare(oldPass)))
    {
        r2:
        std::cout << "请输入新密码： ";
        std::cin >> newPass1;
        std::cout << "请再次输入新密码： ";
        std::cin >> newPass2;
        if (!newPass1.compare(newPass2))
        {
            itr->setPassword(newPass1);
            std::cout << "修改成功" << std::endl;
        }
        else
        {
            goto r2;
        }

    }
    else
    {
        std::cout << "密码错误" << std::endl;
        goto r1;
    }
}

void toSubNote(std::vector<Teacher>::iterator &itr)
{
    tsn:
    std::cout << "请输入课程名称: ";
    std::string name;
    std::cin >> name;
    std::cout << "请输入作业要求: ";
    std::string require;
    std::cin >> require;
    std::cout << "请输入截止日期: ";
    std::string data;
    std::cin >> data;
    TestPaper tt(0, name, itr->getName());
    tt.setRequire(require);
    tt.setData(data);
    itr->getNote().push_back(tt);

    char aaa;
    std::cout << "是否继续发布<Y/N>: ";
    std::cin >> aaa;
    if (aaa == 'Y')
    {
        goto tsn;
    }

}

void toViewNote(std::vector<Teacher>::iterator &itr)
{
    std::cout.width(8);
    std::cout << "序号" << "课程名" << "要求" << "截止日期" << std::endl;
    int i = 1;
    for (auto itrN = itr->getNote().begin(); itrN != itr->getNote().end(); itrN++)
    {
        std::cout << i << itrN->getName() << itrN->getRequire() << itrN->getData() << std::endl;
        i++;
    }
}

void toAdmin(std::vector<Teacher> &teachers, std::vector<Student> &students, Administrator &admin)
{
    std::cout << "清输入账号: ";
    std::string username;
    std::cin >> username;
    std::cout << "清输入密码: ";
    std::string password;
    std::cin >> password;

    if (!(username.compare(admin.getUsername())) && !(password.compare(admin.getPassword())))
    {
        ta:
        std::cout << "*********************************" << std::endl;
        std::cout << "-------->管理员:" << std::endl;
        std::cout << "1.修改密码" << std::endl;
        std::cout << "2.添加学生" << std::endl;
        std::cout << "3.添加教师" << std::endl;
        std::cout << "4.返回主菜单" << std::endl;
        std::cout << "清选择：";
        int a;
        std::cin >> a;
        switch (a)
        {
            case 1:
                toEditAdminPass(admin);
                std::cout << "是否继续<Y/N>: ";
                char b;
                std::cin >> b;
                if (b == 'Y')
                    goto ta;
                else
                    toMain(teachers, students, admin);
                break;
            case 2:
                addStu(students);
                std::cout << "是否继续<Y/N>: ";
                char d;
                std::cin >> d;
                if (d == 'Y')
                    goto ta;
                else
                    toMain(teachers, students, admin);
                break;
            case 3:
                addTeacher(teachers);
                std::cout << "是否继续<Y/N>: ";
                char c;
                std::cin >> c;
                if (b == 'Y')
                    goto ta;
                else
                    toMain(teachers, students, admin);
                break;
            case 4:
                std::cout << "是否返回主菜单<Y/N>: ";
                char f;
                std::cin >> f;
                if (f == 'Y')
                    toMain(teachers, students, admin);
                else
                    goto ta;
                break;
        }
    }
}

void toEditAdminPass(Administrator &admin)
{
    std::string oldPass;
    std::string newPass1;
    std::string newPass2;
    r1:
    std::cout  << "请输入密码： ";
    std::cin >> oldPass;
    if (!(admin.getPassword().compare(oldPass)))
    {
        r2:
        std::cout << "请输入新密码： ";
        std::cin >> newPass1;
        std::cout << "请再次输入新密码： ";
        std::cin >> newPass2;
        if (!newPass1.compare(newPass2))
        {
            admin.setPassword(newPass1);
            std::cout << "修改成功" << std::endl;
        }
        else
        {
            goto r2;
        }

    }
    else
    {
        std::cout << "密码错误" << std::endl;
        goto r1;
    }
}

void addTeacher(std::vector<Teacher> &teachers)
{
    std::cout << "请输入你要添加的教师的个数: ";
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <=n; i++)
    {
        std::cout << "请输入第" << i << "个教师的姓名: ";
        std::string name;
        std::cin >> name;
        std::cout << "请输入第" << i << "个教师的账号: ";
        std::string username;
        std::cin >> username;
        std::cout << "请输入第" << i << "个教师的密码: ";
        std::string password;
        std::cin >> password;
        Teacher tt((teachers.end() - 1)->getId() + 1, name, username, password);
        teachers.push_back(tt);
    }
}

void addStu(std::vector<Student> &students)
{
    std::cout << "请输入你要添加的学生的个数: ";
    int n = 0;
    std::cin >> n;
    for (int i = 1; i <=n; i++)
    {
        std::cout << "请输入第" << i << "个学生的姓名: ";
        std::string name;
        std::cin >> name;
        std::cout << "请输入第" << i << "个学生的账号: ";
        std::string username;
        std::cin >> username;
        std::cout << "请输入第" << i << "个学生的密码: ";
        std::string password;
        std::cin >> password;
        Student s((students.end() - 1)->getId() + 1, name, username, password);
        students.push_back(s);
    }
}

void toEditScore(std::vector<Teacher>::iterator &itr, std::vector<Student> &students)
{
    tes:
    std::cout << "序号" << "名字" << "要求" << "答案" << std::endl;
    int i = 1;
    for (auto itrTP = itr->getTestPapers().begin(); itrTP != itr->getTestPapers().end(); itrTP++)
    {
        std::cout << i << itrTP->getName() << itrTP->getRequire() << itrTP->getArea() << std::endl;

    }

    std::cout << "请选择你要打分的序号: ";
    int a;
    std::cin >> a;
    std::cout << "请输入你要打的分数: ";
    int b;
    std::cin >> b;
    itr->getTestPapers()[--a].setScore(b);
    for (auto itrS = students.begin(); itrS != students.end(); itrS++)
    {
        if (!(itrS->getName().compare(itr->getTestPapers()[a].getStuName())))
        {
            for (auto itrSP = itrS->getTestPapers().begin(); itrSP != itrS->getTestPapers().end(); itrSP++)
            {
                if (!(itr->getTestPapers()[a].getName().compare(itrSP->getName())))
                {
                    itrSP->setScore(b);
                }
            }
        }
    }
    char aaa;
    std::cout << "是否继续<Y/N>: ";
    std::cin >> aaa;
    if (aaa == 'Y')
    {
        goto tes;
    }
}