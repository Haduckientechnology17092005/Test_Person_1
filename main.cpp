#include "person.cpp"
#include "admin.cpp"
#include "user.cpp"
#include "authorize.cpp"
#include "FileManage.cpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

ull Person::next_id = 1;
// int main() {
//     User* user1 = new User();
//     User* user2 = new User();
//     User* user3 = new User();
//     Admin* admin1 = new Admin();
    
//     try {
//         user1->registerUser("user1", "user1", "password1", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         (user1->loginUser("user1", "password1")) == true ? cout << "Login success\n" : cout << "Login failed\n";
//         user1->logoutUser();
        
//         admin1->registerAdmin("Admin1", "admin1", "password1", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         (admin1->loginUser("admin1", "password1")) == true ? cout << "Login success\n" : cout << "Login failed\n";
        
//         admin1->viewInformation(*admin1);
//         admin1->viewInformation(*user1);
//         admin1->changeInformation(*admin1, "Admin1", "admin1", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         admin1->resetPassword(*user1);
//         admin1->viewInformation(*user1);
//         admin1->changeInformation(*user1, "User1", "user1", "0123456789", "Quang Nam", "Quang Nam", "Viet Nam", "Viet Nam");
//         admin1->viewInformation(*user1);
//         admin1->addUser(*user2, "User2", "user2", "password2", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         admin1->addUser(*user3, "User3", "user3", "password3", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
        
//         admin1->viewInformation(*user2);
//         admin1->viewInformation(*user3);
//         admin1->deleteUser(user2);
//         admin1->viewInformation(*user3);
//         if (admin1->getIsLoggedIn()) {
//             admin1->viewInformation(*admin1);
//         } else {
//             cout << "Admin is not logged in" << endl;
//         }
//         cout << admin1->getIsLoggedIn() << endl;
//     } catch (invalid_argument e) {
//         cout << e.what() << endl;
//     }
//     delete user1;
//     delete user3;
//     delete admin1;

//     return 0;
// }
// int main() {
//     User user1, user2, user3;
//     Admin admin1;
//     try {
//         user1.registerUser("User1", "user1", "password1", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         (user1.loginUser("user1", "password1")) == true ? cout << "Login success\n" : cout << "Login failed\n";
//         // user1.viewInformation();
//         user1.logoutUser();
//         // if(user1.getIsLoggedIn()) {
//         //     user1.viewInformation();
//         // } else {
//         //     cout << "User is not logged in" << endl;
//         // }
//         admin1.registerAdmin("Admin1", "admin1", "password1", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         (admin1.loginUser("admin1", "password1")) == true ? cout << "Login success\n" : cout << "Login failed\n";
//         cout<<"View Information: \n";
//         admin1.viewInformation(admin1);
//         cout<<"View Information: \n";
//         admin1.viewInformation(user1);
//         admin1.changeInformation(admin1, "Admin1", "admin1", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         admin1.resetPassword(user1);
//         cout<<"View Information: \n";
//         admin1.viewInformation(user1);
//         admin1.changeInformation(user1, "User1", "user1", "0123456789", "Quang Nam", "Quang Nam", "Viet Nam", "Viet Nam");
//         cout<<"View Information: \n";
//         admin1.viewInformation(user1);
//         admin1.addUser(user2, "User2", "user2", "password2", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         admin1.addUser(user3, "User3", "user3", "password3", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//         cout<<"View information after addUser: \n";
//         admin1.viewInformation(user2);
//         cout<<"View information after addUser: \n";
//         admin1.viewInformation(user3);
//         admin1.deleteUser(user2);
//         admin1.viewInformation(user2);
//         admin1.logoutUser();
//         if(admin1.getIsLoggedIn()) {
//             admin1.viewInformation(admin1);
//         } else {
//             cout << "Admin is not logged in" << endl;
//         }
//         //user1.loginUser("user1", "DHBK@2024") == true ? cout << "Login success\n" : cout << "Login failed\n";
//         cout <<user1.getIsLoggedIn() << endl;   
//     } catch (invalid_argument e) {
//         cout << e.what() << endl;
//     }
//     return 0;
// }
// int main(){
//     Person::initializeNextIdFromFile("accounts.txt");
//     User* user1 = new User();
//     user1->registerUser("accounts.txt","user1", "Nguyen_Van_A", "password1", "Xwqo0@example.com", "0123456789", "Vung Tau", "Vung Tau", "Viet Nam", "Viet Nam");
//     user1->viewInformation();
//     delete user1;
//     return 0;
// }
int main() {
    Person* currentUser = nullptr;
    ifstream file("accounts.txt");

    if (file.is_open()) {
        cout << "File is open" << endl;
    } else {
        cout << "Unable to open file." << endl;
    }

    int loginAttempts = 0;
    const int maxAttempts = 3;

    while (true) {
        if (!currentUser) {
            if (loginAttempts >= maxAttempts) {
                cout << "Exceeded maximum login attempts. Exiting program.\n";
                break;
            }

            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (username == "0" || password == "0") { // Cho phép người dùng thoát
                cout << "Exiting to main screen.\n";
                break;
            }
            currentUser = login(username, password);
            if (!currentUser) {
                cout << "Incorrect username or password. Please try again.\n";
                ++loginAttempts;
            }
        }
        if (currentUser) {
            char choice;
            cout << "\nSelect an action: \n";
            cout << "1. Logout\n";
            cout << "2. Exit program\n";
            cout << "Enter choice: ";
            cin >> choice;
            if (choice == '1') {
                currentUser->logoutUser();
                delete currentUser;
                currentUser = nullptr;
                loginAttempts = 0; 
            } else if (choice == '2') {
                break;
            }
        } else {
            cout << "Please try logging in again.\n";
        }
    }
    delete currentUser;
    return 0;
}
// vector<Person*> loadFromFile(const string& filename) {
//     vector<Person*> persons;
//     ifstream file(filename);
//     if(!file.is_open()) {
//         cerr << "Khong the mo file " << filename << endl;
//         return persons;
//     }
//     string line;
//     while(getline(file, line)){
//         stringstream ss(line);
//         ull user_id, role_id;
//         string name, username, password, email, phone, village, town, province, country;
//         getline(ss, line, ',');
//         user_id = stoull(line);
//         getline(ss, line, ',');
//         role_id = stoull(line);
//         getline(ss, name, ',');
//         getline(ss, username, ',');
//         getline(ss, password, ',');
//         getline(ss, email, ',');
//         getline(ss, phone, ',');
//         getline(ss, village, ',');
//         getline(ss, town, ',');
//         getline(ss, province, ',');
//         getline(ss, country, ',');
//         Person* person = nullptr;
//         if(role_id == 1) {
//             person = new Admin(name, username, password, email, phone, village, town, province, country);
//         } else if(role_id == 2) {
//             person = new User(name, username, password, email, phone, village, town, province, country);
//         }
//         if(person != nullptr) {
//             person->setUserId(user_id);
//             persons.push_back(person);
//         }
//     }
//     file.close();
//     return persons;
// }
// int main(){
//     vector<Person*> persons = loadFromFile("accounts.txt");
//     Admin admin;
//     string keyword;
//     cout << "Enter keyword: ";
//     getline(cin, keyword);
//     admin.searchUser(persons, keyword);
//     for(Person* person : persons) {
//         person->viewInformation();
//         delete person;
//     }
//     return 0;
// }