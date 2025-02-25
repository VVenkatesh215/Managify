#ifndef EMP_H
#define EMP_H

#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cstring>

class Emp {
    int eid;
    char name[20];
    float basic;
    char email[30];
    char contact[15];
    int leaves;

public:
    Emp();
    Emp(int d, const char *nm, float bs, const char *eml, const char *cnt, int lv);

    void display() const;
    int getid() const;
    const char *getname() const;
    float getbasic() const;
    const char *getemail() const;
    const char *getcontact() const;
    int getleaves() const;

    void setid(int d);
    void setename(const char *nm);
    void setbasic(float bs);
    void setemail(const char *eml);
    void setcontact(const char *cnt);
    void setleaves(int lv);

    void checkLeave() const;
    bool takeLeave(int days);
    std::string getFormattedSalary() const;
    std::string getLastLoginTime() const;
};

#endif // EMP_H