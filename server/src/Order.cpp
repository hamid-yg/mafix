#include "Order.hpp"

Order::Order(std::string symbol, std::string side, double price) {
    this->symbol = symbol;
    this->side = side;
    this->price = price;
}

Order::~Order() {
}

std::string Order::getSymbol() const {
    return symbol;
}

std::string Order::getSide() const {
    return side;
}

double Order::getPrice() const {
    return price;
}
