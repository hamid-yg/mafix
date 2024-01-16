#pragma once

#include "Headers.hpp"

class Order {
    public:
        int id;
        char side;  // 'B' for Bid, 'S' for Sell
        double price;
        int quantity;

        Order(int orderId, char orderSide, double orderPrice, int orderQuantity)
            : id(orderId), side(orderSide), price(orderPrice), quantity(orderQuantity) {}
};
