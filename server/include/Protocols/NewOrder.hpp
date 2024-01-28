#pragma once

#include "Headers.hpp"

class NewOrder : public FixMessage {
    public:
        NewOrder() : FixMessage("D") {
            setField(11, "12345");
            setField(55, "AAPL");
            setField(54, "1");
            setField(38, "100");
            setField(44, "50.00");
        }
};
