#include "../include/User.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <sys/stat.h> 
#include <io.h>

void User::signup(const std::string& filename) {
    // Ensure the data directory exists
    std::string directory = "../data"; // Updated path
#ifdef _WIN32
    mkdir(directory.c_str()); // Create directory on Windows
#else
    mkdir(directory.c_str(), 0777); // Create directory on Linux/macOS
#endif

    // Check if the file exists, and create it if it doesn't
    std::ifstream checkFile(filename);
    if (!checkFile) {
        std::ofstream newFile(filename);
        if (!newFile) {
            std::cout << "\nError: Unable to create file. Check permissions or directory path.";
            return;
        }
        newFile << "LoginID,Password\n"; // Add header
        newFile.close();
    }

    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cout << "\nError: Unable to open file for writing. Check permissions or directory path.";
        return;
    }

    std::cout << "\nEnter Login ID: ";
    std::getline(std::cin, login_id);
    
    if (isLoginIdTaken(filename, login_id)) {
        std::cout << "\nThis Login ID is already taken. Please choose another.";
        file.close();
        return;
    }
    
    std::cout << "Enter Password: ";
    password = getHiddenInput();
    file << login_id << "," << password << "\n";
    file.close();
    std::cout << "\nSignup Successful!";
}

bool User::isLoginIdTaken(const std::string& filename, const std::string& id) {
    std::ifstream file(filename);
    if (!file) {
        return false; // File doesn't exist, so the ID is not taken
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string stored_id;
        std::getline(ss, stored_id, ',');
        if (stored_id == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool User::login(const std::string& filename) {
    std::string entered_id;
    std::ifstream file(filename);
    if (!file) {
        std::cout << "\nNo user found. Please signup first!";
        return false;
    }

    std::cout << "\nEnter Login ID: ";
    std::getline(std::cin, entered_id);
    std::cout << "Enter Password: ";
    std::string entered_pass = getHiddenInput();
    
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string stored_id, stored_pass;
        std::getline(ss, stored_id, ',');
        std::getline(ss, stored_pass);
        if (stored_id == entered_id && stored_pass == entered_pass) {
            std::cout << "\nLogin Successful!";
            logLoginAttempt(true);
            return true;
        }
    }
    std::cout << "\nInvalid credentials!";
    logLoginAttempt(false);
    return false;
}

void User::logLoginAttempt(bool success) {
    std::ofstream logfile("../data/login_attempts.log", std::ios::app); // Updated path
    auto now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    logfile << ctime(&tt) << " Login " << (success ? "successful" : "failed") 
            << " for user: " << login_id << "\n";
    logfile.close();
}
