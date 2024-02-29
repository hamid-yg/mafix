#pragma once

#include "Headers.hpp"

class Logon : public FixMessage {
    public:
        Logon(std::string senderCompID, std::string targetCompID, std::string username, std::string password) : FixMessage("A") {
            setField(49, senderCompID);
            setField(56, targetCompID);
            setField(98, "0");
            setField(553, username);
            setField(554, password);
        }
};
