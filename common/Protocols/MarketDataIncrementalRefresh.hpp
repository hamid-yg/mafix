#pragma once

#include "Headers.hpp"

class MarketDataIncrementalRefresh : public FixMessage {
    public:
        MarketDataIncrementalRefresh() : FixMessage("X") {
            setField(55, "AAPL");
            setField(270, "1");
            setField(279, "1");
            setField(269, "0");
            setField(278, "101.00");
            setField(271, "50");
        }
};
