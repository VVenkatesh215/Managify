#ifndef COMPANY_H
#define COMPANY_H

#include "Emp.h"
#include <vector>
#include <set>
#include <fstream>
#include <sstream>

class Company {
    std::vector<Emp> employees;
    std::set<std::string> existingEmails;
    std::set<std::string> existingPhones;

public:
    Company();
    void loadEmployeesFromCSV();
    bool isEmailTaken(const std::string& email) const;
    bool isPhoneTaken(const std::string& phone) const;
    bool isEmployeeIdTaken(int id) const;
    void updateEmployeeLeaves(int empId, int newLeaves);
    Emp* getEmployeeById(int empId);
    void addemp(const Emp& e);
    void removeempById(int id);
    void editiEmp(int id, bool isAdmin = false);
    void searchEmpById(int id) const;
    void DisplayallEmp() const;
    void updateCSV() const;
    void searchEmployeeByName(const std::string& name) const;
    void generatePayrollReport() const;
    void generateLeaveReport() const;
};

#endif // COMPANY_H