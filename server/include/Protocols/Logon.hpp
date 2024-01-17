#pragma once

#include "Headers.hpp"

class Logon : public FixMessage {
    public:
        Logon() : FixMessage("A") {
            // Additional fields for Logon message
            setField(98, "0");       // EncryptMethod
            setField(108, "30");      // HeartBtInt
        }
};
