#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product(int id, string name, double price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void setQuantity(int qty) {
        quantity = qty;
    }

    bool purchase(int qty) {
        if (qty <= quantity) {
            quantity -= qty;
            return true;
        }
        return false; 
    }
};

class Cart {
private:
    unordered_map<int, int> cartItems;

public:
    void addToCart(shared_ptr<Product> product, int qty) {
        if (qty <= 0) {
            cout << "Số lượng phải lớn hơn 0." << endl;
            return;
        }
        if (product->getQuantity() < qty) {
            cout << "Số lượng yêu cầu vượt quá số lượng trong kho của sản phẩm " << product->getName() << endl;
            return; 
        }
        cartItems[product->getId()] += qty; 
        cout << "Đã thêm " << qty << " sản phẩm " << product->getName() << " vào giỏ hàng." << endl;
    }

    void removeFromCart(int productId) {
        cartItems.erase(productId); 
    }

    void viewCart(const unordered_map<int, shared_ptr<Product>>& productCatalog) const {
        if (cartItems.empty()) {
            cout << "Giỏ hàng trống." << endl;
            return;
        }
        cout << "Giỏ hàng:" << endl;
        for (const auto& item : cartItems) {
            auto product = productCatalog.at(item.first);
            cout << "ID: " << product->getId() << ", Tên: " << product->getName()
                 << ", Giá: " << product->getPrice() << ", Số lượng: " << item.second << endl;
        }
    }

    double getTotalPrice(const unordered_map<int, shared_ptr<Product>>& productCatalog) const {
        double total = 0;
        for (const auto& item : cartItems) {
            auto product = productCatalog.at(item.first);
            total += product->getPrice() * item.second;
        }
        return total;
    }

    const unordered_map<int, int>& getCartItems() const {
        return cartItems;
    }

    void clearCart() {
        cartItems.clear();
    }
};

class CartManager {
private:
    unordered_map<int, shared_ptr<Cart>> userCarts;
    unordered_map<int, shared_ptr<Product>> productCatalog;

    bool checkAvailability(const shared_ptr<Cart>& cart) {
        for (const auto& item : cart->getCartItems()) {
            auto product = productCatalog.at(item.first);
            if (product->getQuantity() < item.second) {
                cout << "Không thể thanh toán. Sản phẩm " << product->getName() << " chỉ còn " 
                     << product->getQuantity() << " trong kho, trong khi yêu cầu " 
                     << item.second << "." << endl;
                return false;
            }
        }
        return true;
    }

public:
    void addProductToCatalog(shared_ptr<Product> product) {
        productCatalog[product->getId()] = product;
    }

    void addProductToCart(int userId, shared_ptr<Product> product, int qty) {
        if (productCatalog.find(product->getId()) == productCatalog.end()) {
            cout << "Sản phẩm không tồn tại trong danh mục." << endl;
            return;
        }
        if (userCarts.find(userId) == userCarts.end()) {
            userCarts[userId] = make_shared<Cart>();
        }
        userCarts[userId]->addToCart(product, qty);
    }

    shared_ptr<Cart> getCartByUserId(int userId) {
        if (userCarts.find(userId) != userCarts.end()) {
            return userCarts[userId];
        }
        return nullptr;
    }

    bool purchaseCart(int userId) {
        auto cart = getCartByUserId(userId);
        if (!cart) {
            cout << "Không tìm thấy giỏ hàng của người dùng " << userId << endl;
            return false;
        }

        if (!checkAvailability(cart)) {
            return false;
        }

        double totalPrice = 0;
        for (const auto& item : cart->getCartItems()) {
            auto product = productCatalog[item.first];
            product->purchase(item.second);
            totalPrice += product->getPrice() * item.second;
        }

        cart->clearCart();
        cout << "Thanh toán thành công! Tổng tiền: " << totalPrice << endl;

        return true;
    }

    void viewProductCatalog() const {
        if (productCatalog.empty()) {
            cout << "Danh mục sản phẩm trống." << endl;
            return;
        }
        cout << "Danh mục sản phẩm:" << endl;
        for (const auto& productPair : productCatalog) {
            const auto& product = productPair.second;
            cout << "ID: " << product->getId() << ", Tên: " << product->getName()
                 << ", Giá: " << product->getPrice() << ", Số lượng trong kho: " << product->getQuantity() << endl;
        }
    }
    unordered_map<int, shared_ptr<Product>> getProductCatalog() const { return productCatalog; }
};

class User {
private:
    int userId;
    string name;
    string email;
    string password;

public:
    User(int id, const string& name, const string& email, const string& password)
        : userId(id), name(name), email(email), password(password) {}

    int getUserId() const { return userId; }
    string getName() const { return name; }
};

int main() {
    User user1(1, "John Doe", "john@example.com", "password123");
    User user2(2, "Jane Doe", "jane@example.com", "password456");
    CartManager cartManager;

    auto product1 = make_shared<Product>(101, "ProductA", 10.0, 50);
    auto product2 = make_shared<Product>(102, "ProductB", 20.0, 30);
    auto product3 = make_shared<Product>(103, "ProductC", 15.0, 20);
    cartManager.addProductToCatalog(product1);
    cartManager.addProductToCatalog(product2);
    cartManager.addProductToCatalog(product3);

    cartManager.addProductToCart(user1.getUserId(), product1, 2); 
    cartManager.addProductToCart(user1.getUserId(), product2, 1); 
    cartManager.addProductToCart(user1.getUserId(), product1, 1);   
    cartManager.addProductToCart(user2.getUserId(), product3, 1);   
    cartManager.addProductToCart(user2.getUserId(), product1, 1);   

    cout << "Giỏ hàng của người dùng 1:" << endl;
    auto cart1 = cartManager.getCartByUserId(user1.getUserId());
    if (cart1) cart1->viewCart(cartManager.getProductCatalog());

    cout << endl << "Giỏ hàng của người dùng 2:" << endl;
    auto cart2 = cartManager.getCartByUserId(user2.getUserId());
    if (cart2) cart2->viewCart(cartManager.getProductCatalog());

    cout << endl << "Thực hiện thanh toán cho giỏ hàng của người dùng 1..." << endl;
    cartManager.purchaseCart(user1.getUserId());

    cout << endl << "Thực hiện thanh toán cho giỏ hàng của người dùng 2..." << endl;
    cartManager.purchaseCart(user2.getUserId());

    return 0;
}
