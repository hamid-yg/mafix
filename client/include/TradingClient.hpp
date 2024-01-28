#pragma once

#include "Headers.hpp"

class TradingClient {
    public:
        TradingClient();
        ~TradingClient();

        // void sendOrder(Order order);
        // void sendCancel(const std::string& orderId);
        // void modifyOrder(const std::string& orderId, double newPrice, int newQuantity);
        void run();

    private:
        int clientSocket;

        void initSocket();
        void sendMessage(const std::string& message);
        // std::string createNewOrderMessage(Order order);
        // std::string createCancelOrderMessage(const std::string& orderId);
        // std::string createModifyOrderMessage(const std::string& orderId, double newPrice, int newQuantity);
};
