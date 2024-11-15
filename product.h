#pragma once
#include "FileManage.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iterator>

using namespace std;

class Product {
    protected:
        int id;
        char *type;
        char *breed;
        int quantity;
        double price;
    public:
        Product() = default;
        Product(int id, const char *type, const char *breed, int quantity, double price);
        virtual ~Product();
        void setId(int newId);
        int getId() const;
        void updateQuantity(int quantity);
        void updatePrice(double price);
        void updateType(const char *newType);
        void updateBreed(const char *newBreed);
        void updateProductInfor(const char *type,const char *breed, int quantity, double price);
        int getQuantity() const;
        double getPrice() const;
        const char* getType() const;
        const char* getBreed() const;
        int getId() const;
        string getProductInfo() const;
        void displayProductInfo() const;
        bool checkStock(int amount) const;
        bool decreaseStock(int amount);
        bool operator<(const Product& other) const;
        bool operator==(const Product& other) const;
};