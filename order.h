#pragma once
#include <iostream>
#include <vector>
#include "product.h"
#include "user.h"
#include "FileManage.h"

using namespace std;
enum OrderStatus {
    PENDING,    // Đơn hàng đang chờ xử lý
    SHIPPED,    // Đơn hàng đã giao
    CANCEL_REQUESTED, // Người dùng đã gửi yêu cầu hủy đơn hàng
    CANCELLED   // Đơn hàng đã hủy (sau khi admin chấp nhận)
};

class Order {
    int orderId;
    User user;  // User đã đặt đơn hàng
    vector<Product> orderedItems;
    double totalAmount;
    OrderStatus status;  // Trạng thái đơn hàng
public:
    Order(int id, User user, vector<Product> items, double amount);
    // Các phương thức thay đổi trạng thái đơn hàng
    void requestCancellation();     // Người dùng yêu cầu hủy đơn hàng
    void approveCancellation();     // Admin chấp nhận hủy
    void denyCancellation();        // Admin từ chối hủy
    OrderStatus getStatus() const;  // Lấy trạng thái hiện tại của đơn hàng
};
