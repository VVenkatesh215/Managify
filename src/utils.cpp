#include "../include/utils.h"
#include <iostream>
#include <string>
#include <regex>
#include <conio.h>

// Implement all utility functions here
int getValidatedInt(const std::string& prompt) {
    std::string input;
    int value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (input.find_first_not_of("0123456789") == std::string::npos && !input.empty()) {
            try {
                value = std::stoi(input);
                if (value > 0) {
                    return value;
                }
            } catch (...) {
                // Handle conversion errors
            }
        }
        std::cout << "\nInvalid Input. Please enter a positive number.\n";
    }
}

float getValidatedFloat(const std::string& prompt) {
    std::string input;
    float value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        bool valid = true;
        int dotCount = 0;
        for (char c : input) {
            if (c == '.') {
                dotCount++;
                if (dotCount > 1) {
                    valid = false;
                    break;
                }
            } else if (!isdigit(c)) {
                valid = false;
                break;
            }
        }
        
        if (valid && !input.empty()) {
            try {
                value = std::stof(input);
                if (value > 0) {
                    return value;
                }
            } catch (...) {
                // Handle conversion errors
            }
        }
        std::cout << "\nInvalid Input. Please enter a positive number.\n";
    }
}

std::string getValidatedString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        
        bool valid = true;
        for (char c : value) {
            if (!isalpha(c) && !isspace(c)) {
                valid = false;
                break;
            }
        }
        
        if (!value.empty() && valid) {
            return value;
        }
        std::cout << "\nInvalid Name. Please use only letters and spaces.\n";
    }
}

bool isValidEmail(const std::string& email) {
    std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

bool isValidPhoneNumber(const std::string& phone) {
    if (phone.length() != 10 || phone.find_first_not_of("0123456789") != std::string::npos) {
        return false;
    }
    
    char firstDigit = phone[0];
    bool allSame = true;
    for (char digit : phone) {
        if (digit != firstDigit) {
            allSame = false;
            break;
        }
    }
    return !allSame;
}

std::string getValidatedEmail(const std::string& prompt) {
    std::string email;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, email);
        if (isValidEmail(email)) {
            return email;
        }
        std::cout << "\nInvalid email format. Please enter a valid email (e.g., user@domain.com)\n";
    }
}

std::string getValidatedPhone(const std::string& prompt) {
    std::string phone;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, phone);
        if (isValidPhoneNumber(phone)) {
            return phone;
        }
        std::cout << "\nInvalid phone number. Please enter a 10-digit number (not all same digits)\n";
    }
}

char getValidatedChar(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.length() == 1) {
            return toupper(input[0]);
        }
        std::cout << "\nInvalid input. Please enter a single character.\n";
    }
}

std::string getHiddenInput() {
    std::string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                std::cout << "\b \b";
                password.pop_back();
            }
        } else {
            password += ch;
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}