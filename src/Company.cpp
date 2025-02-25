#include "../include/Company.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <sys/stat.h> // For mkdir on Windows and Linux
#include <io.h>

Company::Company() {
    loadEmployeesFromCSV();
}

void Company::loadEmployeesFromCSV() {
    // Ensure the data directory exists
    std::string directory = "../data";
#ifdef _WIN32
    mkdir(directory.c_str()); // Create directory on Windows
#else
    mkdir(directory.c_str(), 0777); // Create directory on Linux/macOS
#endif

    std::ifstream file("../data/employee.csv"); // Updated path
    if (!file) {
        // Create the file if it doesn't exist
        std::ofstream newFile("../data/employee.csv"); // Updated path
        newFile << "ID,Name,Salary,Email,Contact,Leaves\n"; // Add header
        newFile.close();
        file.open("../data/employee.csv"); // Updated path
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> row;
        while (std::getline(ss, item, ',')) {
            row.push_back(item);
        }
        if (row.size() == 6) {
            existingEmails.insert(row[3]);
            existingPhones.insert(row[4]);
            Emp e(std::stoi(row[0]), row[1].c_str(), std::stof(row[2]), row[3].c_str(), row[4].c_str(), std::stoi(row[5]));
            employees.push_back(e);
        }
    }
    file.close();
}

bool Company::isEmailTaken(const std::string& email) const {
    return existingEmails.find(email) != existingEmails.end();
}

bool Company::isPhoneTaken(const std::string& phone) const {
    return existingPhones.find(phone) != existingPhones.end();
}

bool Company::isEmployeeIdTaken(int id) const {
    for (const auto& e : employees) {
        if (e.getid() == id) {
            return true;
        }
    }
    return false;
}

void Company::updateEmployeeLeaves(int empId, int newLeaves) {
    for (auto& e : employees) {
        if (e.getid() == empId) {
            e.setleaves(newLeaves);
            updateCSV();
            return;
        }
    }
    std::cout << "\nEmployee not found.";
}

Emp* Company::getEmployeeById(int empId) {
    for (auto& e : employees) {
        if (e.getid() == empId) {
            return &e;
        }
    }
    return nullptr;
}

void Company::addemp(const Emp& e) {
    std::string email = e.getemail();
    std::string phone = e.getcontact();
    
    if (isEmployeeIdTaken(e.getid())) {
        std::cout << "\nEmployee with ID " << e.getid() << " already exists.";
        return;
    }
    
    if (isEmailTaken(email)) {
        std::cout << "\nEmail address " << email << " is already in use.";
        return;
    }
    
    if (isPhoneTaken(phone)) {
        std::cout << "\nPhone number " << phone << " is already in use.";
        return;
    }
    
    employees.push_back(e);
    existingEmails.insert(email);
    existingPhones.insert(phone);
    updateCSV();
    std::cout << "\nEmployee added successfully!";
}

void Company::removeempById(int id) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->getid() == id) {
            existingEmails.erase(it->getemail());
            existingPhones.erase(it->getcontact());
            it->display();
            std::cout << "\nThis employee is deleted ...";
            employees.erase(it);
            updateCSV();
            return;
        }
    }
    std::cout << "\nNot Found ";
}

void Company::editiEmp(int id, bool isAdmin) {
    for (auto& e : employees) {
        if (e.getid() == id) {
            char ans;
            std::string name, email, contact;
            float sal;
            
            ans = getValidatedChar("\nDo you want to change name? (Y/N): ");
            if (ans == 'Y') {
                name = getValidatedString("\nEnter New Name: ");
                e.setename(name.c_str());
            }

            ans = getValidatedChar("\nDo you want to change Email? (Y/N): ");
            if (ans == 'Y') {
                do {
                    email = getValidatedEmail("\nEnter New Email: ");
                    if (email != e.getemail() && isEmailTaken(email)) {
                        std::cout << "\nThis email is already in use. Please try another.";
                        continue;
                    }
                    break;
                } while (true);
                existingEmails.erase(e.getemail());
                existingEmails.insert(email);
                e.setemail(email.c_str());
            }

            ans = getValidatedChar("\nDo you want to change Contact? (Y/N): ");
            if (ans == 'Y') {
                do {
                    contact = getValidatedPhone("\nEnter New Contact: ");
                    if (contact != e.getcontact() && isPhoneTaken(contact)) {
                        std::cout << "\nThis phone number is already in use. Please try another.";
                        continue;
                    }
                    break;
                } while (true);
                existingPhones.erase(e.getcontact());
                existingPhones.insert(contact);
                e.setcontact(contact.c_str());
            }

            if (isAdmin) {
                ans = getValidatedChar("\nDo you want to change Salary? (Y/N): ");
                if (ans == 'Y') {
                    sal = getValidatedFloat("\nEnter new salary: ");
                    e.setbasic(sal);
                }
            }
            
            updateCSV();
            return;
        }
    }
    std::cout << "\nRecord not Found ";
}

void Company::searchEmpById(int id) const {
    for (const auto& e : employees) {
        if (e.getid() == id) {
            std::cout << "\nEmployee Found ...";
            e.display();
            return;
        }
    }
    std::cout << "\nEmployee is not Found";
}

void Company::DisplayallEmp() const {
    if (employees.empty()) {
        std::cout << "\n\nNo employee data here ";
        return;
    }
    for (const auto& e : employees) {
        e.display();
    }
}

void Company::updateCSV() const {
    std::ofstream file("../data/employee.csv"); // Updated path
    for (const auto& e : employees) {
        file << e.getid() << "," << e.getname() << "," << e.getbasic() << ","
             << e.getemail() << "," << e.getcontact() << "," << e.getleaves() << "\n";
    }
    file.close();
}

void Company::searchEmployeeByName(const std::string& name) const {
    bool found = false;
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    for (const auto& e : employees) {
        std::string lowerEmpName = e.getname();
        std::transform(lowerEmpName.begin(), lowerEmpName.end(), lowerEmpName.begin(), ::tolower);
        if (lowerEmpName.find(lowerName) != std::string::npos) {
            e.display();
            found = true;
        }
    }
    if (!found) {
        std::cout << "\nNo employees found with the given name.";
    }
}

void Company::generatePayrollReport() const {
    std::ofstream report("../data/payroll_report.csv"); // Updated path
    report << "ID,Name,Salary\n";
    for (const auto& e : employees) {
        report << e.getid() << "," << e.getname() << "," << e.getFormattedSalary() << "\n";
    }
    report.close();
    std::cout << "\nPayroll report generated successfully in CSV format.";
}

void Company::generateLeaveReport() const {
    std::ofstream report("../data/leave_report.csv"); // Updated path
    report << "ID,Name,Leaves Remaining\n";
    for (const auto& e : employees) {
        report << e.getid() << "," << e.getname() << "," << e.getleaves() << "\n";
    }
    report.close();
    std::cout << "\nLeave report generated successfully in CSV format.";
}