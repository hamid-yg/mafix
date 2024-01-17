#pragma once

#include "Headers.hpp"

class MarketDataSnapshotFullRefresh : public FixMessage {
    public:
        MarketDataSnapshotFullRefresh() : FixMessage("W") {
            // Additional fields for MarketDataSnapshotFullRefresh message
            setField(55, "AAPL");     // Symbol
            setField(270, "1");       // NoMDEntries
            setField(279, "0");       // MDUpdateAction
            setField(269, "0");       // MDEntryType
            setField(278, "100.00");  // MDEntryPx
            setField(271, "100");     // MDEntrySize
        }
};
