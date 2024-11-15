#include "authorize.h"
#include "admin.h"
#include "user.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Person* login(const string& username, const string& password) {
    Admin admin;
    User user;
    if (admin.loginUser("accounts.txt",username, password)) {
        cout << "Đăng nhập thành công dưới vai trò Admin." << endl;
        cout << "Thong tin User: ";
        admin.viewInformation("");
        return new Admin(admin);
    } else if (user.loginUser("accounts.txt",username, password)) {
        cout << "Đăng nhập thành công dưới vai trò User." << endl;
        cout << "Thong tin User: " << endl;
        user.viewInformation();
        user.changeUsername("hahaha");
        user.viewInformation();
        return new User(user);
    } else {
        cout << "Đăng nhập thất bại." << endl;
        return nullptr;
    }
}