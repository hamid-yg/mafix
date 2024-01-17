#pragma once

#include "Headers.hpp"

class ExecutionReport : public FixMessage {
    public:
        ExecutionReport() : FixMessage("8") {
            // Additional fields for ExecutionReport message
            setField(11, "99999");    // ClOrdID
            setField(37, "123456");   // OrderID
            setField(150, "0");       // ExecType
            setField(39, "2");        // OrdStatus
            setField(55, "AAPL");     // Symbol
            setField(54, "1");        // Side
            setField(38, "50");       // OrderQty
            setField(14, "25");       // CumQty
            setField(6, "50.00");     // AvgPx
        }
};
