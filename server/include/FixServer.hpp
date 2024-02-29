#pragma once

#include "Headers.hpp"

constexpr int BUFFER_SIZE = 4096;
constexpr int LISTEN_PORT = 8000;
constexpr int MARKET_PORT = 8001;

class FixServer {
    public:
        FixServer();
        ~FixServer();

        void run();
        void stop();

    private:
        int serverSocket;
        int marketSocket;
        Market market;

        void initSocket();
        void initMarket();
        int acceptConnection();
        void handleClient(int clientSocket);
        void processMessage(const std::string& fixMessage, int clientSocket);
};
