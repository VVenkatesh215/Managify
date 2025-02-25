#include "../include/Emp.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Implement all methods of Emp class here
Emp::Emp() {
    eid = 0;
    strcpy(name, "Not Given");
    basic = 0;
    strcpy(email, "Not Given");
    strcpy(contact, "Not Given");
    leaves = 0;
}

Emp::Emp(int d, const char *nm, float bs, const char *eml, const char *cnt, int lv) {
    eid = d;
    strncpy(name, nm, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
    basic = bs;
    strncpy(email, eml, sizeof(email) - 1);
    email[sizeof(email) - 1] = '\0';
    strncpy(contact, cnt, sizeof(contact) - 1);
    contact[sizeof(contact) - 1] = '\0';
    leaves = lv;
}

void Emp::display() const {
    std::cout << "\n*******************************";
    std::cout << "\nEmployee Id: " << eid;
    std::cout << "\nName: " << name;
    std::cout << "\nSalary: " << getFormattedSalary();
    std::cout << "\nEmail: " << email;
    std::cout << "\nContact: " << contact;
    std::cout << "\nLeaves Remaining: " << leaves;
    std::cout << "\n*******************************";
}

int Emp::getid() const { return eid; }
const char *Emp::getname() const { return name; }
float Emp::getbasic() const { return basic; }
const char *Emp::getemail() const { return email; }
const char *Emp::getcontact() const { return contact; }
int Emp::getleaves() const { return leaves; }

void Emp::setid(int d) { this->eid = d; }
void Emp::setename(const char *nm) { strncpy(this->name, nm, sizeof(this->name) - 1); this->name[sizeof(this->name) - 1] = '\0'; }
void Emp::setbasic(float bs) { this->basic = bs; }
void Emp::setemail(const char *eml) { strncpy(this->email, eml, sizeof(this->email) - 1); this->email[sizeof(this->email) - 1] = '\0'; }
void Emp::setcontact(const char *cnt) { strncpy(this->contact, cnt, sizeof(this->contact) - 1); this->contact[sizeof(this->contact) - 1] = '\0'; }
void Emp::setleaves(int lv) { this->leaves = lv; }

void Emp::checkLeave() const {
    std::cout << "\nYou have " << leaves << " leaves remaining.";
}

bool Emp::takeLeave(int days) {
    if (days <= leaves) {
        leaves -= days;
        std::cout << "\nLeave granted. You now have " << leaves << " leaves remaining.";
        return true;
    } else {
        std::cout << "\nInsufficient leaves. You only have " << leaves << " leaves available.";
        return false;
    }
}

std::string Emp::getFormattedSalary() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << basic;
    return ss.str();
}

std::string Emp::getLastLoginTime() const {
    auto now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    return ctime(&tt);
}