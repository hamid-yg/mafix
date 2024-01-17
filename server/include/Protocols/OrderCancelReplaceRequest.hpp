#pragma once

#include "Headers.hpp"

class OrderCancelReplaceRequest : public FixMessage {
    public:
        OrderCancelReplaceRequest() : FixMessage("G") {
            // Additional fields for OrderCancelReplaceRequest message
            setField(11, "67890");    // ClOrdID
            setField(41, "55555");    // OrigClOrdID
            setField(55, "AAPL");     // Symbol
            setField(54, "2");        // Side
            setField(38, "75");       // OrderQty
            setField(44, "55.00");    // Price
        }
};
