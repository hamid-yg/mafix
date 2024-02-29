#pragma once

#include "Headers.hpp"

class OrderCancelRequest : public FixMessage {
    public:
        OrderCancelRequest() : FixMessage("9") {
            setField(41, "55555");
            setField(37, "123456");
            setField(55, "AAPL");
            setField(54, "2");
            setField(38, "75");
        }
};
