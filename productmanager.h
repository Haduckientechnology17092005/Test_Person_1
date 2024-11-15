#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "product.h"
#include "FileManage.h"

using namespace std;

class ProductManager {
    private:
    vector<Product*> products;
    FileManager file_manager;
    public:
        ProductManager(const string& filename);
        ~ProductManager();
        void addProduct(Product* product, 
        const string &filename);
        void updateProduct(int productId, const char* breed, double price, const string& filename);
        void deleteProduct(int productId, const string& filename);
        Product* getProduct(int productId, const string& filename);
        vector<Product*> searchProduct(double price, const string& filename);
        void checkStock(int productId, const string& filename);
        void viewStock(const string &filename);
        void displayAllProducts(const string &filename);
        void displayProductInfo(const char* criteria);
        void displayInstockProducts(const ProductManager& manager);
        vector<Product*> filterProducts(const char* criteria);
        void displaySearchResults(const char* criteria, const string& filename);
        void displaySearchResults(double price, const string& filename);
        int getMaxProductId();
};
