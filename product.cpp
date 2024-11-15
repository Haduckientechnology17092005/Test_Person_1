#include"product.h"

using namespace std;

Product::Product(int id, const char *type,const char *breed, int quantity, double price):quantity(quantity),price(price){
    this->id = id;
    this->type = new char[strlen(type)+1];
    strcpy(this->type,type);
    this->breed = new char[strlen(breed)+1];
    strcpy(this->breed,breed);
}

Product::~Product(){
    delete[] type;
    delete[] breed;
}

void Product::setId(int newId){
    this->id = newId;
}

int Product::getId() const{
    return id;
}

void Product::updateQuantity(int quantity){
    this->quantity = quantity;
}

void Product::updatePrice(double price){
    this->price = price;
}

void Product::updateType(const char *newType){
    delete[] type;
    type = new char[strlen(newType)+1];
    strcpy(type,newType);
}

void Product::updateBreed(const char *newBreed){
    delete[] breed;
    breed = new char[strlen(newBreed)+1];
    strcpy(breed,newBreed);
}

void Product::updateProductInfor(const char *type, const char *breed, int quantity, double price){
    updateType(type);
    updateBreed(breed);
    updateQuantity(quantity);
    updatePrice(price);
}

int Product::getQuantity() const{
    return quantity;
}

double Product::getPrice() const{
    return price;
}

const char* Product::getType() const{
    return type;
}

const char* Product::getBreed() const{
    return breed;
}

int Product::getId() const{
    return id;
}

string Product::getProductInfo() const{
    return to_string(id)+","+type+","+breed+","+to_string(quantity)+","+to_string(price);
}

void Product::displayProductInfo() const{
    cout<<"ID: "<<id<<endl;
    cout<<"Type: "<<type<<endl;
    cout<<"Breed: "<<breed<<endl;
    cout<<"Quantity: "<<quantity<<endl;
    cout<<"Price: "<<price<<endl;
}

bool Product::checkStock(int amount) const{
    return quantity >= amount;
}

bool Product::decreaseStock(int amount){
    if(quantity >= amount){
        quantity -= amount;
        return true;
    }
    return false;
}

bool Product::operator<(const Product& other) const{
    return price < other.price;
}

bool Product::operator==(const Product& other) const{
    return (strcmp(type,other.type) == 0 && strcmp(breed,other.breed) == 0 && quantity == other.quantity && price == other.price);
}  
