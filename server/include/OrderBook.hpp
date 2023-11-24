#pragma once

#include "Order.hpp"

#include <map>
#include <string>
#include <vector>
#include <iostream>


class OrderBook {
    public:
        OrderBook();
        ~OrderBook();

        void addOrder(Order order);
        void modifyOrder(Order order);
        void removeOrder(Order order);
        void cancelOrder(Order order);
        void partialFillOrder(Order order);
        void fullFillOrder(Order order);
        void display();

    private:
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Order> > > orderBook;
};
