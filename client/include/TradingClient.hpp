#pragma once

#include "Headers.hpp"

class TradingClient {
    public:
        TradingClient();
        ~TradingClient();

        void run();

    private:
        int clientSocket;
        int orderId = 0;

        void initSocket();
        void sendMessage(const std::string& message);
};
