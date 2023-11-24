#pragma once

#include <string>

class Order {
    public:
        Order(std::string symbol, std::string side, double price);
        ~Order();

        std::string getSymbol() const;
        std::string getSide() const;
        double getPrice() const;

    private:
        std::string symbol;
        std::string side;
        double price;
};
