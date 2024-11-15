#pragma once

#include "product.h"
#include <vector>
#include <iostream>
#include <memory>
#include "FileManage.h"

using namespace std;

class Cart {
    int CartId;
    vector <shared_ptr<Product>> cartItmes;
    public:
    void addToCart (shared_ptr<Product> product);
    void removeFromCart (shared_ptr<Product> product);
    void viewCart() const;
    void updateQuantity(int productId, int quantity);
    double getTotalPrice() const;
};