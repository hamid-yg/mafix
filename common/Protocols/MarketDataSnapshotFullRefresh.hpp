#pragma once

#include "Headers.hpp"

class MarketDataSnapshotFullRefresh : public FixMessage {
    public:
        MarketDataSnapshotFullRefresh() : FixMessage("W") {
            setField(55, "AAPL");
            setField(270, "1");
            setField(279, "0");
            setField(269, "0");
            setField(278, "100.00");
            setField(271, "100");
        }
};
