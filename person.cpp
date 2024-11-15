#include"person.h"
#include "FileManage.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

Person::Person(string name, string username, string password, string email, string phone, string village, string town, string province, string country) {
    this->user_id = next_id;
    next_id++;
    this->name = name;
    this->username = username;
    this->password = password;
    this->email = email;
    this->phone = phone;
    this->village = village;
    this->town = town;
    this->province = province;
    this->country = country;
}

Person::Person(const Person& person) {
    this->user_id = person.user_id;
    this->name = person.name;
    this->username = person.username;
    this->password = person.password;
    this->email = person.email;
    this->phone = person.phone;
    this->village = person.village;
    this->town = person.town;
    this->province = person.province;
    this->country = person.country;
}

ull Person::getId() const {
    return this->user_id;
}

ull Person::getRoleId() const {
    return this->role_id;
}

string Person::getName() const {
    return this->name;
}

string Person::getUsername() const {
    return this->username;
}

string Person::getPassword() const {
    return this->password;
}

string Person::getEmail() const {
    return this->email;
}

string Person::getPhone() const {
    return this->phone;
}

string Person::getAddress() const {
    return this->village + "," + this->town + "," + this->province + "," + this->country;
}

bool Person::getIsLoggedIn() {
    return this->isLoggedIn;
}

void Person::setUserId(ull user_id) {
    this->user_id = user_id;
}

void Person::setUsername(string username) {
    this->username = username;
}

void Person::setName(string name) {
    this->name = name;
}
void Person::setEmail(string email) {
    this->email = email;
}

void Person::setPassword(string password) {
    this->password = password;
}

void Person::setPhone(string phone) {
    this->phone = phone;
}

void Person::setVillage(string village) {
    this->village = village;
}

void Person::setTown(string town) {
    this->town = town;
}

void Person::setProvince(string province) {
    this->province = province;
}

void Person::setCountry(string country) {
    this->country = country;
}

void Person::viewInformation() {
    if(this->getId() == 0){
        cout <<"Error: ID is 0" << endl;
        throw invalid_argument("Error: ID is 0");
    }
    cout << "ID: " << this->getId() << endl;
    ull role_id = this->getRoleId();
    if(role_id == 1) cout << "Role: Admin" << endl;
    else cout << "Role: User" << endl;
    cout << "Name: " << this->getName() << endl;
    cout << "Username: " << this->getUsername() << endl;
    cout << "Password: " << this->getPassword() << endl;
    cout << "Email: " << this->getEmail() << endl;
    cout << "Phone: " << this->getPhone() << endl;
    cout << "Address: " << this->getAddress() << endl;
}

void Person::changeUsername(const string& newUsername) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    
    // Kiểm tra nếu username mới đã tồn tại
    for(Person* person : persons) {
        if(person->getUsername() == newUsername) {
            cout << "Username is exist. Please try again" << endl;
            return;
        }
    }
    
    // Thay đổi username của người dùng hiện tại
    for(Person* person : persons) {
        if(person->getId() == this->getId()) {
            person->setUsername(newUsername);
            this -> setUsername(newUsername);
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
    
    // Giải phóng bộ nhớ
    for(Person* person : persons) {
        delete person;
    }
    
    cout << "Username đã thay đổi!" << endl;
}

void Person::changeEmail(string& newEmail) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        if(person->getEmail() == email) {
            cerr << "Email is exist. Please try again" << endl;
            return;
        }
    }
    for(Person* person : persons) {
        if(person->getId() == this->getId()) {
            person->setEmail(newEmail);
            this -> setEmail(newEmail);
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
    for(Person* person : persons) {
        delete person;
    }
}

void Person::changePassword(string& password) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        if(person->getId() == this->getId()) {
            person->setPassword(password);
            this -> setPassword(password);
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
    for(Person* person : persons) {
        delete person;
    }
}

void Person::initializeNextIdFromFile(const string& filename) {
    ifstream file(filename);
    if(!file){
        cerr << "Khong the mo file " << filename << endl;
        return;
    }
    ull max_id = 0;
    string line;
    while(getline(file, line)){
        istringstream iss(line);
        ull user_id;
        if(iss >> user_id){
            max_id = max(max_id, user_id);
        }
    }
    next_id = max_id + 1; //dam bao id khong bi trung
    file.close();
}

bool Person::isUniqueUser(const string& filename, const string& username, const string& email) {
    ifstream file(filename);
    if(!file){
        cerr << "Khong the mo file " << filename << endl;
        return false;
    }
    string line;
    while(getline(file, line)){
        istringstream iss(line);
        string user_id, role_id, name, username2, password, email2, phone, village, town, province, country;
        getline(iss, user_id, ',');
        getline(iss, role_id, ',');
        getline(iss, name, ',');
        getline(iss, username2, ',');
        getline(iss, password, ',');
        getline(iss, email2, ',');
        getline(iss, phone, ',');
        getline(iss, village, ',');
        getline(iss, town, ',');
        getline(iss, province, ',');
        getline(iss, country, ',');
        if(username2 == username || email2 == email){
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}
void Person::changeInformation(string name, string phone, string village, string town, string province, string country){
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        if(person->getId() == this->getId()) {
            if(name != ""){
                person->setName(name);
                this -> setName(name);
            }
            if(phone != ""){
                person->setPhone(phone);
                this -> setPhone(phone);
            }
            if(village != ""){
                person->setVillage(village);
                this -> setVillage(village);
            }
            if(town != ""){
                person->setTown(town);
                this -> setTown(town);
            }
            if(province != ""){
                person->setProvince(province);
                this -> setProvince(province);
            }
            if(country != ""){
                person->setCountry(country);
                this -> setCountry(country);
            }  
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
    for(Person* person : persons) {
        delete person;
    }
}