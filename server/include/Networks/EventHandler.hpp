#pragma once

#include "Headers.hpp"

class EventHandler {
    public:
        virtual void handleEvent(int socket) = 0;
        virtual ~EventHandler() = default;
};
