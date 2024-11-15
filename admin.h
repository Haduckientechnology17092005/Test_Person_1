#ifndef ADMIN_H
#define ADMIN_H
#define ull unsigned long long
#include <string>
#include <iostream>
#include "person.h"
#include "user.h"
#include "product.h"
#include "cart.h"
#include "invoice.h"
#include "FileManage.h"
#include "productmanager.h"
#include "order.h"
#include "usermanager.h"

using namespace std;

class Admin : public Person {
    private:
    UserManager userManager;
    public:
    // hàm dựng của Admin và hàm hủy
        Admin() = default;
        Admin(string name, string username, string password, string email, string phone, string village, string town, string province, string country);
        ~Admin() = default;
    // hàm thay đổi các role_id của Admin và User
        void setAdminRoleId(Admin& admin, ull role_id);
        void setUserRoleId(User& user, ull role_id);
    // hàm thay đổi các thống tin cơ bản của Admin và User
        void resetPassword(int userId);
        void addUser(const string& filename, const string& name, const string& username, 
                          const string& password, const string& email, const string& phone,
                          const string& village, const string& town, const string& province, 
                          const string& country);
        void deleteUser(int userId);
    // hàm riêng của admin
        void viewInformation(const string& username);
        void changeInformation(string &name, string &username, string &phone, string &village, string &town, string &province, string &country);
        void searchUser(const vector<Person*> &persons, const string& keyword);
    // Thao tac voi san pham 
        void addProduct(ProductManager& pm, const Product& product);
        void updateProduct(ProductManager& pm, const char* breed, double price);
        void deleteProduct(ProductManager& pm, int productId);
        void viewStock(ProductManager& pm);
        void viewPurchaseHistory(User& user);
        void processPayment(User& user, const char* paymentMethod, const char* shippingAddress);
        Invoice generateInvoice(User& user, const char* paymentMethod, const char* shippingAddress);
        void generateReport();
        void approveCancellation(Order& order);
        void denyCancellation(Order& order);
        bool loginUser(const string& filename, string username, string password) override;
        void logoutUser() override;
};

#endif