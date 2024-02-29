#pragma once

// #include "Headers.hpp"
#include "Order.hpp"

class OrderBook {
    private:
        std::vector<Order> orders;

    public:
        OrderBook() {};
        ~OrderBook() {};

        void addOrder(Order order) {
            order.status = Order::NEW;
            orders.push_back(order);
        }

        void modifyOrder(int orderId, double newPrice, int newQuantity) {
            auto it = std::find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
                return order.id == orderId;
            });

            if (it != orders.end()) {
                it->price = newPrice;
                it->quantity = newQuantity;
            } else {
                std::cout << "<Log>: Order with ID " << orderId << " not found." << std::endl;
            }
        }

        void cancelOrder(int orderId) {
            auto it = std::find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
                return order.id == orderId;
            });

            if (it != orders.end()) {
                std::cout << "<Log>: Cancelling order ID " << orderId << "." << std::endl;
                it->status = Order::CANCELED;
                orders.erase(it);
            } else {
                std::cout << "<Log>: Order with ID " << orderId << " not found." << std::endl;
            }
        };

        void executeOrder(int orderId) {
            auto it = std::find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
                return order.id == orderId;
            });

            if (it != orders.end()) {
                std::cout << "<Log>: Executing order ID " << orderId << " completely." << std::endl;
                it->status = Order::FILLED;
                orders.erase(it);
            } else {
                std::cout << "<Log>: Order with ID " << orderId << " not found." << std::endl;
            }
        };

        void executePartialOrder(int orderId, int executedQuantity) {
            auto it = std::find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
                return order.id == orderId;
            });

            if (it == orders.end()) {
                throw std::runtime_error("<Log>: Order with ID " + std::to_string(orderId) + " not found.");
            }

            if (executedQuantity > it->quantity) {
                throw std::runtime_error("<Log>: Not enough quantity in order to execute.");
            }

            if (executedQuantity < it->quantity) {
                std::cout << "<Log>: Partially executing order ID " << orderId << " with quantity " << executedQuantity << "." << std::endl;
                it->status = Order::PARTIALLY_FILLED;
                it->quantity -= executedQuantity;
            } else {
                std::cout << "<Log>: Executing order ID " << orderId << " completely." << std::endl;
                it->status = Order::FILLED;
                orders.erase(it);
            }
        };

        void matchOrders() {
            std::sort(orders.begin(), orders.end(), [](const Order& a, const Order& b) {
                return a.price < b.price;
            });

            for (auto it = orders.begin(); it != orders.end(); ++it) {
                if (it->side == 'B') {
                    auto it2 = std::find_if(it + 1, orders.end(), [it](const Order& order) {
                        return order.side == 'S' && order.price <= it->price;
                    });

                    if (it2 != orders.end()) {
                        if (it2->quantity > it->quantity) {
                            executePartialOrder(it->id, it->quantity);
                            executePartialOrder(it2->id, it->quantity);
                        } else if (it2->quantity < it->quantity) {
                            executePartialOrder(it->id, it2->quantity);
                            executePartialOrder(it2->id, it2->quantity);
                        } else {
                            executeOrder(it->id);
                            executeOrder(it2->id);
                        }
                    }
                }
            }
        };

        void printOrderBook() const {
            std::cout << "<Display>: Order Book:" << std::endl;
            for (const auto& order : orders) {
                std::cout << "ID: " << order.id << ", Side: " << order.side << ", Price: " << order.price << ", Quantity: " << order.quantity << std::endl;
            }
        };

        std::string toString() {
            std::ostringstream oss;
            for (const auto& order : orders) {
                oss << "ID: " << order.id << ", Side: " << order.side << ", Price: " << order.price << ", Quantity: " << order.quantity << "\n";
            }
            return oss.str();
        }

};
