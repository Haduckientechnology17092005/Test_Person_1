#include"FileManage.h"

using namespace std;

vector<Person*> FileManager::loadFromFile(const string& filename) {
    vector<Person*> persons;
    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Khong the mo file " << filename << endl;
        return persons;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        ull user_id, role_id;
        string name, username, password, email, phone, village, town, province, country;
        getline(ss, line, ',');
        user_id = stoull(line);
        getline(ss, line, ',');
        role_id = stoull(line);
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        getline(ss, phone, ',');
        getline(ss, village, ',');
        getline(ss, town, ',');
        getline(ss, province, ',');
        getline(ss, country, ',');
        Person* person = nullptr;
        if(role_id == 1) {
            person = new Admin(name, username, password, email, phone, village, town, province, country);
        } else if(role_id == 2) {
            person = new User(name, username, password, email, phone, village, town, province, country);
        }
        if(person != nullptr) {
            person->setUserId(user_id);
            persons.push_back(person);
        }
    }
    file.close();
    return persons;
}

void FileManager::saveToFile(const string& filename, const vector<Person*>& persons) {
    ofstream file(filename);
    if(!file) {
        cerr << "Khong the mo file " << filename << endl;
        return;
    }
    for(Person* person : persons) {
        file << person->getId() <<","<<person->getRoleId() <<","<<person->getName() <<","<<person->getUsername() <<","<<person->getPassword() <<","<<person->getEmail() <<","<<person->getPhone() <<","<<person->getAddress() << endl;
    }
    file.close();
}

vector<Product*> FileManager::loadProductFromFile(const string& filename) {
    vector<Product*> products;
    ifstream file(filename);
    if(!file.is_open()) {
        cerr << "Khong the mo file " << filename << endl;
        return products;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        int product_id, product_quantity;
        double product_price;
        string product_type, product_breed;
        getline(ss, line, ',');
        product_id = stoi(line);
        getline(ss, product_type, ',');
        getline(ss, product_breed, ',');
        getline(ss, line, ',');
        product_quantity = stoi(line);
        getline(ss, line, ',');
        product_price = stod(line);
        Product* product = new Product(product_id, product_type.c_str(), product_breed.c_str(), product_quantity, product_price);
        products.push_back(product);
    }
    file.close();
    return products;
}

void FileManager::saveProductToFile(const string& filename, const vector<Product*>& products) {
    ofstream file(filename);
    if(!file) {
        cerr << "Khong the mo file " << filename << endl;
        return;
    }
    for(Product* product : products) {
        file << product->getId() <<","<<product->getType() <<","<<product->getBreed() <<","<<product->getQuantity() <<","<<product->getPrice() << endl;
    }
    file.close();
}