#pragma once

#include "Headers.hpp"

class OrderCancelRequest : public FixMessage {
    public:
        OrderCancelRequest() : FixMessage("9") {
            // Additional fields for OrderCancelRequest message
            setField(41, "55555");    // OrigClOrdID
            setField(37, "123456");   // OrderID
            setField(55, "AAPL");     // Symbol
            setField(54, "2");        // Side
            setField(38, "75");       // OrderQty
        }
};
