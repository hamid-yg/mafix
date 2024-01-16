#include "Headers.hpp"

OrderBook::OrderBook() {
}

OrderBook::~OrderBook() {
}

void OrderBook::addOrder(const Order& order) {
    orders.push_back(order);
}

void OrderBook::modifyOrder(int orderId, double newPrice, int newQuantity) {
    auto it = std::find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
        return order.id == orderId;
    });

    if (it != orders.end()) {
        it->price = newPrice;
        it->quantity = newQuantity;
    } else {
        std::cout << "Order with ID " << orderId << " not found." << std::endl;
    }
}

void OrderBook::cancelOrder(int orderId) {
    orders.erase(std::remove_if(orders.begin(), orders.end(), [orderId](const Order& order) {
        return order.id == orderId;
    }), orders.end());
}

void OrderBook::executeOrder(int orderId) {
    auto it = std::find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
        return order.id == orderId;
    });

    if (it != orders.end()) {
        std::cout << "Executing order ID " << orderId << " completely." << std::endl;
        orders.erase(it);
    } else {
        std::cout << "Order with ID " << orderId << " not found." << std::endl;
    }
}

void OrderBook::executePartialOrder(int orderId, int executedQuantity) {
    auto it = std::find_if(orders.begin(), orders.end(), [orderId](const Order& order) {
        return order.id == orderId;
    });

    if (it == orders.end()) {
        throw std::runtime_error("Order with ID " + std::to_string(orderId) + " not found.");
    }

    if (executedQuantity > it->quantity) {
        throw std::runtime_error("Not enough quantity in order to execute.");
    }

    if (executedQuantity < it->quantity) {
        std::cout << "Partially executing order ID " << orderId << " with quantity " << executedQuantity << "." << std::endl;
        it->quantity -= executedQuantity;
    } else {
        std::cout << "Executing order ID " << orderId << " completely." << std::endl;
        orders.erase(it);
    }
}

void OrderBook::printOrderBook() const {
    std::cout << "Order Book:" << std::endl;
    for (const auto& order : orders) {
        std::cout << "ID: " << order.id << ", Side: " << order.side << ", Price: " << order.price << ", Quantity: " << order.quantity << std::endl;
    }
}
