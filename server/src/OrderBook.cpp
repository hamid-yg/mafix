#include "OrderBook.hpp"

OrderBook::OrderBook() {
    orderBook = std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Order> > >();
}

OrderBook::~OrderBook() {
    orderBook.clear();
}

void OrderBook::addOrder(Order order) {
    std::string symbol = order.getSymbol();
    std::string side = order.getSide();
    std::vector<Order> orders = orderBook[symbol][side];
    orders.push_back(order);
    orderBook[symbol][side] = orders;
}

void OrderBook::modifyOrder(Order order) {
    std::string symbol = order.getSymbol();
    std::string side = order.getSide();
    std::vector<Order> orders = orderBook[symbol][side];

    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].getPrice() == order.getPrice()) {
            orders[i] = order;
            break;
        }
    }
    orderBook[symbol][side] = orders;
}

void OrderBook::removeOrder(Order order) {
    std::string symbol = order.getSymbol();
    std::string side = order.getSide();
    std::vector<Order> orders = orderBook[symbol][side];

    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].getPrice() == order.getPrice()) {
            orders.erase(orders.begin() + i);
            break;
        }
    }
    orderBook[symbol][side] = orders;
    orderBook[symbol].erase(side);
    if (orderBook[symbol].empty()) {
        orderBook.erase(symbol);
    }
}

void OrderBook::cancelOrder(Order order) {
    std::string symbol = order.getSymbol();
    std::string side = order.getSide();
    std::vector<Order> orders = orderBook[symbol][side];

    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].getPrice() == order.getPrice()) {
            orders[i].setQuantity(0);
            break;
        }
    }
    orderBook[symbol][side] = orders;
}

void OrderBook::partialFillOrder(Order order) {
    std::string symbol = order.getSymbol();
    std::string side = order.getSide();
    std::vector<Order> orders = orderBook[symbol][side];

    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].getPrice() == order.getPrice()) {
            orders[i].setQuantity(orders[i].getQuantity() - order.getQuantity());
            break;
        }
    }
    orderBook[symbol][side] = orders;
}

void OrderBook::fullFillOrder(Order order) {
    std::string symbol = order.getSymbol();
    std::string side = order.getSide();
    std::vector<Order> orders = orderBook[symbol][side];

    for (size_t i = 0; i < orders.size(); i++) {
        if (orders[i].getPrice() == order.getPrice()) {
            orders[i].setQuantity(0);
            break;
        }
    }
    orderBook[symbol][side] = orders;
}

void OrderBook::display() {
    if (orderBook.empty()) {
        std::cout << "Order Book is empty." << std::endl;
        return;
    } else {
        std::cout << "Order Book:" << std::endl;
        for (auto const& symbol : orderBook) {
            std::cout << "Symbol: " << symbol.first << std::endl;
            for (auto const& side : symbol.second) {
                std::cout << "Side: " << side.first << std::endl;
                for (auto const& order : side.second) {
                    std::cout << "Price: " << order.getPrice() << std::endl;
                }
            }
        }
    }
}
