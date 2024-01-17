#pragma once

#include "Headers.hpp"

class MarketDataIncrementalRefresh : public FixMessage {
    public:
        MarketDataIncrementalRefresh() : FixMessage("X") {
            // Additional fields for MarketDataIncrementalRefresh message
            setField(55, "AAPL");     // Symbol
            setField(270, "1");       // NoMDEntries
            setField(279, "1");       // MDUpdateAction
            setField(269, "0");       // MDEntryType
            setField(278, "101.00");  // MDEntryPx
            setField(271, "50");      // MDEntrySize
        }
};
