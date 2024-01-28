#pragma once

#include "Headers.hpp"

class Logon : public FixMessage {
    public:
        Logon() : FixMessage("A") {
            setField(98, "0");
            setField(108, "30");
        }
};
