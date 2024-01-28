#pragma once

#include "Headers.hpp"

class ExecutionReport : public FixMessage {
    public:
        ExecutionReport() : FixMessage("8") {
            setField(11, "99999");
            setField(37, "123456");
            setField(150, "0");
            setField(39, "2");
            setField(55, "AAPL");
            setField(54, "1");
            setField(38, "50");
            setField(14, "25");
            setField(6, "50.00");
        }
};
