#pragma once

#include "Headers.hpp"

class OrderCancelReplaceRequest : public FixMessage {
    public:
        OrderCancelReplaceRequest() : FixMessage("G") {
            setField(11, "67890");
            setField(41, "55555");
            setField(55, "AAPL");
            setField(54, "2");
            setField(38, "75");
            setField(44, "55.00");
        }
};
