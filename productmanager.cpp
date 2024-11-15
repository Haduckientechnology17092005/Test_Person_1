#include"productmanager.h"
using namespace std;

ProductManager::ProductManager(const string& filename){
    products = file_manager.loadProductFromFile(filename);
}

ProductManager::~ProductManager(){
    file_manager.saveProductToFile("products.txt", products);
    for(Product* product : products){
        delete product;
    }
}

void ProductManager::addProduct(Product* product, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    int newId = getMaxProductId() + 1;
    product->setId(newId);
    products.push_back(product);
    file_manager.saveProductToFile(filename, products);
}

void ProductManager::updateProduct(int productId, const char* breed, double price, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    for(auto& product : products){
        if(product->getId() == productId){
            product->updateBreed(breed);
            product->updatePrice(price);
            file_manager.saveProductToFile(filename, products);
            return;
        }
    }
    cout<<"Khong tim thay san pham co id "<<productId<<endl;
}

void ProductManager::deleteProduct(int productId, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    auto it = remove_if(products.begin(), products.end(), [productId](Product* product){
        return product->getId() == productId;
    });
    if(it != products.end()){
        products.erase(it, products.end());
        file_manager.saveProductToFile(filename, products);
    } else {
        cout<<"Khong tim thay san pham co id "<<productId<<endl;
    }
}

Product* ProductManager::getProduct(int productId, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    for(Product* product : products){
        if(product->getId() == productId){
            return product;
        }
    }
    cerr << "Khong tim thay san pham co id " << productId << endl;
    return nullptr;
}   

vector<Product*> ProductManager::searchProduct(double price, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    vector<Product*> foundProducts;
    for(Product* product : products){
        if(product->getPrice() <= price){
            foundProducts.push_back(product);
        }
    }
    return foundProducts;
}

void ProductManager::checkStock(int productId, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    for(auto& product : products){
        if(product->getId() == productId && product->getQuantity() > 0){
            cout<<"San pham co id "<<productId<<" co trong kho"<<endl;
            return;
        }
    }
    cout<<"San pham co id "<<productId<<" khong co trong kho"<<endl;
}

void ProductManager::viewStock(const string &filename){
    products = file_manager.loadProductFromFile(filename);
    for(auto& product : products){
        cout<<"ID: "<<product->getId()<<endl;
        cout<<"Type: "<<product->getType()<<endl;
        cout<<"Breed: "<<product->getBreed()<<endl;
        cout<<"Quantity: "<<product->getQuantity()<<endl;
        cout<<"Price: "<<product->getPrice()<<endl;
    }
}

void ProductManager::displayAllProducts(const string &filename){
    products = file_manager.loadProductFromFile(filename);
    for(auto& product : products){
        product->displayProductInfo();
    }
}

void ProductManager::displayProductInfo(const char* criteria){
    products = file_manager.loadProductFromFile("products.txt");
    for(auto& product : products){
        if(strstr(product->getType(), criteria) != nullptr || strstr(product->getBreed(), criteria) != nullptr){
            product->displayProductInfo();
        }
    }
}

void ProductManager::displayInstockProducts(const ProductManager& manager){
    for(auto& product : manager.products){
        if(product->getQuantity() > 0){
            cout<<"ID: "<<product->getId()<<endl;
            cout<<"Type: "<<product->getType()<<endl;
            cout<<"Breed: "<<product->getBreed()<<endl;
            cout<<"Quantity: "<<product->getQuantity()<<endl;
            cout<<"Price: "<<product->getPrice()<<endl;
        }
    }
}

vector<Product*> ProductManager::filterProducts(const char* criteria){
    products = file_manager.loadProductFromFile("products.txt");
    vector<Product*> filteredProducts;
    for(auto& product : products){
        if(strstr(product->getType(), criteria) != nullptr || strstr(product->getBreed(), criteria) != nullptr){
            filteredProducts.push_back(product);
        }
    }
    return filteredProducts;
}

void ProductManager::displaySearchResults(const char* criteria, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    vector<Product*> filteredProducts = filterProducts(criteria);
    if(filteredProducts.empty()){
        cout<<"Khong tim thay san pham phu hop"<<endl;
        return;
    } else {
        for(auto& product : filteredProducts){
            cout<<"ID: "<<product->getId()<<endl;
            cout<<"Type: "<<product->getType()<<endl;
            cout<<"Breed: "<<product->getBreed()<<endl;
            cout<<"Quantity: "<<product->getQuantity()<<endl;
            cout<<"Price: "<<product->getPrice()<<endl;
        }
    }
}

void ProductManager::displaySearchResults(double price, const string& filename){
    products = file_manager.loadProductFromFile(filename);
    vector<Product*> filteredProducts;
    for(auto& product : products){
        if(product->getPrice() <= price){
            filteredProducts.push_back(product);
        }
    }
    if(filteredProducts.empty()){
        cout<<"Khong tim thay san pham phu hop"<<endl;
        return;
    } else {
        for(auto& product : filteredProducts){
            cout<<"ID: "<<product->getId()<<endl;
            cout<<"Type: "<<product->getType()<<endl;
            cout<<"Breed: "<<product->getBreed()<<endl;
            cout<<"Quantity: "<<product->getQuantity()<<endl;
            cout<<"Price: "<<product->getPrice()<<endl;
        }
    }
}

int ProductManager::getMaxProductId(){
    products = file_manager.loadProductFromFile("products.txt");
    int maxId = 0;
    for(auto& product : products){
        if(product->getId() > maxId){
            maxId = product->getId();
        }
    }
    return maxId;
}