#include "usermanager.h"
#include "FileManage.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

using namespace std;

UserManager::UserManager(const string& filename) {
    vector<Person*> persons = FileManager::loadFromFile(filename);
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user){
            users.push_back(*user);
        }
    }
}

void UserManager::addUser(const string& filename, const string& name, const string& username, 
                          const string& password, const string& email, const string& phone,
                          const string& village, const string& town, const string& province, 
                          const string& country) {
    try {
        User newUser;
        newUser.registerUser(filename, name, username, password, email, phone, village, town, province, country);
        users.push_back(newUser);
        cout << "User added successfully." << endl;
    } catch (const exception& e){
        cerr << "Add User failed";
    }
}

void UserManager::deleteUser(int userId){
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user && user->getId() == userId) {
            persons.erase(persons.begin() + persons.size() - 1);
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
}

void UserManager::resetPassword(int userId, const Person& person) {
    if(person.getRoleId()==1){
        vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
        for(Person* person: persons){
            User* user = dynamic_cast<User*>(person);
            if(user && user->getId()==userId){
                user->resetPassword();
                break;
            }
        }
        FileManager::saveToFile("accounts.txt", persons);
    } else if(person.getRoleId()==2 && person.getId()==userId){
        vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
        for(Person* person : persons){
            User* user = dynamic_cast<User*>(person);
            if(user && user->getId() == userId){
                user->resetPassword();
                break;
            }
        }
        FileManager::saveToFile("accounts.txt", persons);
    } else {
        cout <<"No reset Password !\n";
    }
}

void UserManager::updateUserInformation(int userId, const string& name, const string& phone, 
                                         const string& village, const string& town, 
                                         const string& province, const string& country) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user && user->getId() == userId) {
            user->changeInformation(name, phone, village, town, province, country);
            break;
        }
    }
    FileManager::saveToFile("accounts.txt", persons);
}

User* UserManager::searchUser(const string& keyword) {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user && user->getEmail().find(keyword) != string::npos) {
            return user;
        }
    }
    return nullptr;
}

vector<User> UserManager::getAllUsers() const {
    vector<Person*> persons = FileManager::loadFromFile("accounts.txt");
    vector<User> users;
    for(Person* person : persons) {
        User* user = dynamic_cast<User*>(person);
        if(user) {
            users.push_back(*user);
        }
    }
    return users;
}