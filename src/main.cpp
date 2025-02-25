#include "../include/Emp.h"
#include "../include/Company.h"
#include "../include/User.h"
#include "../include/utils.h"
#include <iostream>

// Implement the main function and menu functions here
void employeeMenu(Company &company, int empId) {
    while (true) {
        std::cout << "\n\n================================";
        std::cout << "\n   Employee Menu";
        std::cout << "\n================================";
        std::cout << "\n  1. View My Details";
        std::cout << "\n  2. Edit My Details";
        std::cout << "\n  3. Check Leave";
        std::cout << "\n  4. Take Leave";
        std::cout << "\n  5. Logout";
        std::cout << "\n================================\n";
        
        int ch = getValidatedInt("\nEnter your choice: ");

        switch (ch) {
            case 1: {
                company.searchEmpById(empId);
                break;
            }
            case 2: {
                company.editiEmp(empId, false);
                break;
            }
            case 3: {
                Emp* emp = company.getEmployeeById(empId);
                if (emp) {
                    emp->checkLeave();
                } else {
                    std::cout << "\nEmployee not found.";
                }
                break;
            }
            case 4: {
                Emp* emp = company.getEmployeeById(empId);
                if (emp) {
                    emp->checkLeave();
                    char choice = getValidatedChar("\nDo you want to take leave? (Y/N): ");
                    if (choice == 'Y') {
                        int days = getValidatedInt("\nEnter the number of days: ");
                        if (emp->takeLeave(days)) {
                            company.updateCSV();
                        }
                    }
                } else {
                    std::cout << "\nEmployee not found.";
                }
                break;
            }
            case 5: {
                std::cout << "\nLogging out...";
                return;
            }
            default: {
                std::cout << "\nInvalid choice. Please try again.";
                break;
            }
        }
    }
}

void adminMenu(Company &company) {
    while (true) {
        std::cout << "\n\n================================";
        std::cout << "\n   Admin Menu";
        std::cout << "\n================================";
        std::cout << "\n  1. Add Employee";
        std::cout << "\n  2. Remove Employee";
        std::cout << "\n  3. Edit Employee";
        std::cout << "\n  4. Search Employee by ID";
        std::cout << "\n  5. Search Employee by Name";
        std::cout << "\n  6. Display All Employees";
        std::cout << "\n  7. Generate Payroll Report";
        std::cout << "\n  8. Generate Leave Report";
        std::cout << "\n  9. Logout";
        std::cout << "\n================================\n";
        
        int ch = getValidatedInt("\nEnter your choice: ");

        switch (ch) {
            case 1: {
                int id, leaves;
                std::string name, email, contact;
                float sal;
                
                do {
                    id = getValidatedInt("\nEnter Employee ID: ");
                    if (company.isEmployeeIdTaken(id)) {
                        std::cout << "\nEmployee with this ID already exists. Please enter a different ID.\n";
                    }
                } while (company.isEmployeeIdTaken(id));
                
                name = getValidatedString("Enter Employee Name: ");
                
                do {
                    email = getValidatedEmail("Enter Employee Email: ");
                    if (company.isEmailTaken(email)) {
                        std::cout << "\nThis email is already registered. Please use a different email.\n";
                    }
                } while (company.isEmailTaken(email));
                
                do {
                    contact = getValidatedPhone("Enter Employee Contact: ");
                    if (company.isPhoneTaken(contact)) {
                        std::cout << "\nThis phone number is already registered. Please use a different number.\n";
                    }
                } while (company.isPhoneTaken(contact));
                
                sal = getValidatedFloat("Enter Salary: ");
                leaves = getValidatedInt("Enter Leaves: ");
                
                Emp e(id, name.c_str(), sal, email.c_str(), contact.c_str(), leaves);
                company.addemp(e);
                break;
            }
            case 2: {
                int id = getValidatedInt("\nEnter Employee ID to remove: ");
                company.removeempById(id);
                break;
            }
            case 3: {
                int id = getValidatedInt("\nEnter Employee ID to edit: ");
                company.editiEmp(id, true);
                break;
            }
            case 4: {
                int id = getValidatedInt("\nEnter Employee ID to search: ");
                company.searchEmpById(id);
                break;
            }
            case 5: {
                std::string name = getValidatedString("\nEnter employee name to search: ");
                company.searchEmployeeByName(name);
                break;
            }
            case 6: {
                company.DisplayallEmp();
                break;
            }
            case 7: {
                company.generatePayrollReport();
                break;
            }
            case 8: {
                company.generateLeaveReport();
                break;
            }
            case 9: {
                std::cout << "\nLogging out...";
                return;
            }
            default: {
                std::cout << "\nInvalid choice. Please try again.";
                break;
            }
        }
    }
}

int main() {
    Company company;
    User admin, employee;
    std::cout << "Welcome to" <<"\033[1m MANAGIFY \033[0m";
    std::cout << "\nAn Employee management system";

    while (true) {
        std::cout << "\n\n================================";
        std::cout << "\n   Main Menu";
        std::cout << "\n================================";
        std::cout << "\n  1. Admin";
        std::cout << "\n  2. Employee";
        std::cout << "\n  3. Exit";
        std::cout << "\n================================\n";
        
        int choice = getValidatedInt("\nEnter your choice: ");

        switch (choice) {
            case 1: {
                int opt = getValidatedInt("\n1. Signup\n2. Login\nEnter your choice: ");
                bool loginSuccess = false;
                if (opt == 1) {
                    admin.signup("../data/admin_credentials.csv"); // Updated path
                    loginSuccess = true;
                } else if (opt == 2) {
                    loginSuccess = admin.login("../data/admin_credentials.csv"); // Updated path
                }
                
                if (loginSuccess) {
                    adminMenu(company);
                }
                break;
            }
            case 2: {
                int opt = getValidatedInt("\n1. Signup\n2. Login\nEnter your choice: ");
                bool loginSuccess = false;
                if (opt == 1) {
                    employee.signup("../data/employee_credentials.csv"); // Updated path
                    loginSuccess = true;
                } else if (opt == 2) {
                    loginSuccess = employee.login("../data/employee_credentials.csv"); // Updated path
                }
                
                if (loginSuccess) {
                    int empId = getValidatedInt("\nEnter your employee ID: ");
                    employeeMenu(company, empId);
                }
                break;
            }
            case 3: {
                std::cout << "\nExiting... Thank you for using MANAGIFY!";
                return 0;
            }
            default: {
                std::cout << "\nInvalid choice. Please try again.";
                break;
            }
        }
    }
    return 0;
}