#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
#include "person.h"
#include "admin.h"
#include "product.h"
#include "cart.h"
#include "invoice.h"
#include "order.h"
#include "FileManage.h"

#define ull unsigned long long

using namespace std;

class User : public Person {
    private:
        Cart cart;
        vector<Invoice> pushchaseHistory;
    public:
        User() = default;
        User(string name, string username, string password, string email, string phone, string village, string town, string province, string country);
        User(const User& user);
        ~User() = default;
        void resetPassword();
        void changeInformation(string name, string phone, string village, string town, string province, string country);
        void registerUser(const string& filename, string name, string username, string password, string email, string phone, string village, string town, string province, string country);
        bool loginUser(const string& filename, string username, string password) override;
        void logoutUser() override;
        void viewProducts(const vector<Product*> &products) const;
        void searchProduct(const char* keyword) const;
        void addToCart(Product& product, int quantity);
        void removeFromCart(Product& product);
        void checkout(const char* paymentMethod, const char* shippingAddress);
        void requestOrderCancellation(Order& order);
        void reviewProduct(Product& product, int rating);
        void viewOrderHistory();
        void viewCart();
        friend class Admin;
};

#endif