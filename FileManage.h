#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "person.h"
#include "admin.h"
#include "user.h"
#include "product.h"
#include "order.h"
#include "ordermanager.h"
#include "usermanager.h"
#include "productmanager.h"
#include "invoice.h"
#include "cart.h"
#include "authorize.h"
#include "summaryinvoice.h"

using namespace std;

class FileManager {
public:
    static vector<Person*> loadFromFile(const string& filename);
    static void saveToFile(const string& filename, const vector<Person*>& persons);
    static vector<Product*> loadProductFromFile(const string& filename);
    static void saveProductToFile(const string& filename, const vector<Product*>& products);
    static vector<Cart*> loadCartFromFile(const string& filename);
    static void saveCartToFile(const string& filename, const vector<Cart*>& carts);
};

#endif
