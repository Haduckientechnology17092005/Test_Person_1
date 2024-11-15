#include "admin.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "user.h"
#include "person.h"

using namespace std;

Admin::Admin(string name, string username, string password, string email, string phone, string village, string town, string province, string country) : Person(name, username, password, email, phone, village, town, province, country) {
    this->role_id = 1;
}

void Admin::setAdminRoleId(Admin& admin, ull new_role_id) {
    if(new_role_id == 1 || new_role_id == 2) admin.role_id = new_role_id;
    else admin.role_id = 1;
}

void Admin::setUserRoleId(User& user, ull new_role_id) {
    if(new_role_id == 1 || new_role_id == 2) user.role_id = new_role_id;
    else user.role_id = 2;
}

void Admin::resetPassword(int userId) {
    userManager.resetPassword(userId, *this);
}

void Admin::addUser(const string& filename, const string& name, const string& username, 
                          const string& password, const string& email, const string& phone,
                          const string& village, const string& town, const string& province, 
                          const string& country) {
    userManager.addUser(filename, name, username, password, email, phone, village, town, province, country);
}

void Admin::deleteUser(int userId) {
    userManager.deleteUser(userId);
}
void Admin::viewInformation(const string& username) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    bool found = false;
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user && (user->getUsername() == username || username.empty())) {
            cout << "Name: " << user->getName() << endl;
            cout << "Username: " << user->getUsername() << endl;
            cout << "Phone: " << user->getPhone() << endl;
            cout << "Address: " << user->getAddress() << endl;
            cout << "Email: " << user->getEmail() << endl;
            found = true;
            break;
        }
    }
    if(!found && !username.empty()) {
        cout << "User not found" << endl;
    }
}

void Admin::changeInformation(string &name, string &username, string &phone, string &village, string &town, string &province, string &country) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user && user->getUsername() == username) {
            user->changeInformation(name, phone, village, town, province, country);
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
}

void Admin::searchUser(const vector<Person*> &persons, const string& keyword){
    bool found = false;
    for(const auto& person : persons){
        const Admin* admin = dynamic_cast<const Admin*>(person);
        if(admin){
            if(admin->getName().find(keyword) != string::npos || admin->getUsername().find(keyword) != string::npos || admin->getEmail().find(keyword) != string::npos){
                cout << "ID: " << admin->getId() << endl;
                cout << "Ho ten: " << admin->getName() << endl;
                cout << "Username: " << admin->getUsername() << endl;
                cout << "Email: " << admin->getEmail() << endl;
                cout << "So dien thoai: " << admin->getPhone() << endl;
                cout << endl;
                found = true;
            }
        }
        const User* user = dynamic_cast<const User*>(person);
        if(user){
            if(user->getName().find(keyword) != string::npos || user->getUsername().find(keyword) != string::npos || user->getEmail().find(keyword) != string::npos){
                cout << "ID: " << user->getId() << endl;
                cout << "Ho ten: " << user->getName() << endl;
                cout << "Username: " << user->getUsername() << endl;
                cout << "Email: " << user->getEmail() << endl;
                cout << "So dien thoai: " << user->getPhone() << endl;
                cout << endl;
                found = true;
            }
        }
    }
    if(!found) cout<<"Khong tim thay nguoi dung"<<endl;
}

bool Admin::loginUser(const string& filename, string username, string password) {
    ifstream file(filename);
    if(!file){
        cerr << "Khong the mo file " << filename << endl;
        throw invalid_argument("Khong the mo file " + filename);
        return false;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string item;
        ull file_user_id, file_role_id;
        string file_name, file_username, file_password, file_email, file_phone, file_village, file_town, file_province, file_country;
        getline(ss, item, ',');
        file_user_id = stoull(item);
        getline(ss, item, ',');
        file_role_id = stoull(item);
        getline(ss, file_name, ',');
        getline(ss, file_username, ',');
        getline(ss, file_password, ',');
        getline(ss, file_email, ',');
        getline(ss, file_phone, ',');
        getline(ss, file_village, ',');
        getline(ss, file_town, ',');
        getline(ss, file_province, ',');
        getline(ss, file_country, ',');
        if(file_username == username && file_password == password && file_role_id == 1){
            this->user_id = file_user_id;
            this->role_id = file_role_id;
            this->name = file_name;
            this->username = file_username;
            this->password = file_password;
            this->email = file_email;
            this->phone = file_phone;
            this->village = file_village;
            this->town = file_town;
            this->province = file_province;
            this->country = file_country;
            isLoggedIn = true;
            cout<<"Dang nhap thanh cong"<<endl;
            file.close();
            return true;
        }
    }
    file.close();
    cout<<"Dang nhap that bai"<<endl;
    return false;
}

void Admin::logoutUser() {
    if(isLoggedIn) {
        isLoggedIn = false;
        cout<<"Dang xuat thanh cong"<<endl;
    } else {
        cout<<"Chua dang nhap"<<endl;
    }
}