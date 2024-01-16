#pragma once

#include "Headers.hpp"

class OrderBook {
    private:
        std::vector<Order> orders;

    public:
        OrderBook();
        ~OrderBook();

        void addOrder(const Order& order);
        void modifyOrder(int orderId, double newPrice, int newQuantity);
        void cancelOrder(int orderId);
        void executeOrder(int orderId);
        void executePartialOrder(int orderId, int executedQuantity);
        void printOrderBook() const;
};
