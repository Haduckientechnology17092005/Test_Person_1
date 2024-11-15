#pragma once
#include "order.h"
#include "user.h"
#include <vector>
#include "FileManage.h"

using namespace std;

class OrderManager {
    vector<Order> orders;
public:
    void addOrder(const Order& order);
    vector<Order> getPendingCancellations() const;  // Lấy danh sách các đơn hàng yêu cầu hủy
};
