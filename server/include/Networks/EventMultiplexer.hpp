#pragma once

#include "Headers.hpp"

class EventMultiplexer {
    public:
        EventMultiplexer();
        ~EventMultiplexer();
        void addEventHandler(int socket, EventHandler* handler);
        void removeEventHandler(int socket);
        void waitForEvents();

    private:
        int kq;
        std::unordered_map<int, EventHandler*> eventHandlers;
};
