#pragma once

#include "Headers.hpp"

class NewOrder : public FixMessage {
    public:
        NewOrder(int orderId, std::string symbol, std::string side,
                 std::string price, std::string quantity) : FixMessage("D")
        {
            setField(11, std::to_string(orderId));
            setField(55, symbol);
            setField(54, side);
            setField(44, price);
            setField(38, quantity);
        }
};
