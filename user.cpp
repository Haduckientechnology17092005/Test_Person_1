#include "user.h"
#include "FileManage.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define ull unsigned long long
using namespace std;

User::User(string name, string username, string password, string email, string phone, string village, string town, string province, string country) : Person(name, username, password, email, phone, village, town, province, country) {
    this->role_id = 2;
}

User::User(const User& user) : Person(user) {
    this->role_id = 2;
}

void User::resetPassword() {
    this->password = "DHBK@2024";
}
void User::changeInformation(string name, string phone, string village, string town, string province, string country) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user && user->username == this->username) {
            if(name != "") user->name = name;
            if(phone != "") user->phone = phone;
            if(village != "") user->village = village;
            if(town != "") user->town = town;
            if(province != "") user->province = province;
            if(country != "") user->country = country;
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
    cout << "Thay doi thong tin thanh cong" << endl;
    for(Person* person : persons) {
        delete person;
    }
}

void User::registerUser(const string& filename, string name, string username, string password, string email, string phone, string village, string town, string province, string country) {
    if(name == "" || username == "" || password == "" || email == "" || phone == "" || village == "" || town == "" || province == "" || country == ""){
        cout << "Vui long nhap day du thong tin" << endl;
        throw invalid_argument("Vui long nhap day du thong tin");
    }
    if(!Person::isUniqueUser(filename, username, email)) {
        cout << "Tai khoan hoac email da ton tai" << endl;
        throw invalid_argument("Tai khoan hoac email da ton tai");
    }
    this->user_id = next_id++;
    this->role_id = 2;
    this->name = name;
    this->username = username;
    this->password = password;
    this->email = email;
    this->phone = phone;
    this->village = village;
    this->town = town;
    this->province = province;
    this->country = country;    
    cout<<"Dang ky thanh cong"<<endl;
    ofstream file(filename, ios::app);
    if(!file) {
        cerr << "Khong the mo file " << filename << endl;
        throw invalid_argument("Khong the mo file " + filename);
    }
    file << user_id << ",2,"<< name << "," << username << "," << password << "," << email << "," << phone << "," << village << "," << town << "," << province << "," << country << endl;
    file.close();
    cout << "Dang ky thanh cong" << endl;
}

bool User::loginUser(const string& filename, string username, string password) {
    ifstream file(filename);
    if(!file) {
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
        if(file_username == username && file_password == password){
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
            this->isLoggedIn = true;
            cout<<"Dang nhap thanh cong"<<endl;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void User::logoutUser() {
    if(isLoggedIn) {
        isLoggedIn = false;
        cout<<"Dang xuat thanh cong"<<endl;
    } else {
        cout<<"Chua dang nhap"<<endl;
    }
}

