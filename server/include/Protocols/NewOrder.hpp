#pragma once

#include "Headers.hpp"

class NewOrder : public FixMessage {
    public:
        NewOrder() : FixMessage("D") {
            // Additional fields for NewOrder message
            setField(11, "12345");    // ClOrdID
            setField(55, "AAPL");     // Symbol
            setField(54, "1");        // Side
            setField(38, "100");      // OrderQty
            setField(44, "50.00");    // Price
        }
};
