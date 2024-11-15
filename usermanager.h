#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <vector>
#include <string>
#include "user.h"
#include "FileManage.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class UserManager {
public:
    UserManager() = default;
    UserManager(const string& filename);
    ~UserManager() = default;
    void addUser(const string& filename, const string& name, const string& username, 
                 const string& password, const string& email, const string& phone,
                 const string& village, const string& town, const string& province, 
                 const string& country);
    void deleteUser(int userId);
    void resetPassword(int userId, const Person& person);
    void updateUserInformation(int userId, const string& name, const string& phone, 
                               const string& village, const string& town, 
                               const string& province, const string& country);
    User* searchUser(const string& keyword);
    vector<User> getAllUsers() const;
private:
    vector<User> users; // Danh sách người dùng
    FileManager fileManager; // Quản lý file
};

#endif
