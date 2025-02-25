#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <conio.h>

int getValidatedInt(const std::string& prompt);
float getValidatedFloat(const std::string& prompt);
std::string getValidatedString(const std::string& prompt);
bool isValidEmail(const std::string& email);
bool isValidPhoneNumber(const std::string& phone);
std::string getValidatedEmail(const std::string& prompt);
std::string getValidatedPhone(const std::string& prompt);
char getValidatedChar(const std::string& prompt);
std::string getHiddenInput();

#endif // UTILS_H