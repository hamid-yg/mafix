#pragma once

#include "Headers.hpp"

constexpr int BUFFER_SIZE = 4096;
constexpr int LISTEN_PORT = 8000;

class FixServer {
    public:
        FixServer();
        ~FixServer();

        void run();
        void stop();

    private:
        int serverSocket;
        Market market;

        void initSocket();
        int acceptConnection();
        void handleClient(int clientSocket);
        void processMessage(const std::string& fixMessage, int clientSocket);
};
