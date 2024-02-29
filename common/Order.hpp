#pragma once

#include "Headers.hpp"

class Order {

    public:
        enum Status {
            NEW,
            PARTIALLY_FILLED,
            FILLED,
            CANCELED,
            REJECTED
        };

        int id;
        char side;
        std::string symbol;
        double price;
        int quantity;
        Status status;

        Order(int orderId, char orderSide, std::string orderSymbol, double orderPrice, int orderQuantity)
            : id(orderId), side(orderSide), symbol(orderSymbol), price(orderPrice), quantity(orderQuantity) {}
};
