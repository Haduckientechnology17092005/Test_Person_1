#ifndef PERSON_H
#define PERSON_H
#define ull unsigned long long
#include <string>
#include "FileManage.h"

using namespace std;

class Person {
    protected:
        ull user_id;
        ull role_id;
        string name;
        string username;
        string password;
        string email;
        string phone;
        string village;
        string town;
        string province;
        string country;
        static ull next_id;
        bool isLoggedIn;
    public:
        Person() = default;  // Constructor mặc định
        Person(string name, string username, string password, string email, string phone, string village, string town, string province, string country);
        Person(const Person& person);  // Copy constructor
        virtual ~Person() = default;  // Destructor ảo để hỗ trợ tính đa hình
        ull getId() const;
        ull getRoleId() const;
        string getName() const;
        string getUsername() const;
        string getPassword() const;
        string getEmail() const;
        string getPhone() const;
        string getAddress() const;
        bool getIsLoggedIn();
        void setUserId(ull user_id);
        void setUsername(string username);	
        void setName(string name);
        void setEmail(string email);
        void setPassword(string password);
        void setPhone(string phone);
        void setVillage(string village);
        void setTown(string town);
        void setProvince(string province);
        void setCountry(string country);
        virtual void viewInformation();
        void changeUsername(const string& newUsername);
        void changeEmail(string& newEmail);
        void changePassword(string& password);
        static void initializeNextIdFromFile(const string& filename);
        bool isUniqueUser(const string& filename, const string& username, const string& email);
        virtual void changeInformation(string name, string phone, string village, string town, string province, string country);
        virtual bool loginUser(const string& filename, string username, string password) = 0;
        virtual void logoutUser() = 0;
};
#endif
