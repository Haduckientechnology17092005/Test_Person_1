#pragma once

#include "product.h"
#include <vector>
#include <iostream>
#include <memory>
#include "FileManage.h"

using namespace std;

class Invoice {
    private:
        char* customerName;
        char* shippingAddress;
        char* paymentMethod;
        vector<shared_ptr<Product>> pushchasedItems;
        double totalAmount;
    public:
        Invoice(char* customerName, char* shippingAddress, char* paymentMethod);
        ~Invoice();
        void viewInvoice() const;
        void clearInvoice();
};