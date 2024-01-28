#include "Headers.hpp"

TradingClient::TradingClient() {
    initSocket();
}

TradingClient::~TradingClient() {
    close(clientSocket);
}

void TradingClient::run() {
    std::string message;

    while (true) {
        std::cout << "Enter FIX message: ";
        std::getline(std::cin, message);
        sendMessage(message);
    }
}

void TradingClient::initSocket() {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error: Could not create socket." << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(9876);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error: Could not connect to server." << std::endl;
        exit(1);
    }

    std::cout << "Connected to server." << std::endl;
}

void TradingClient::sendMessage(const std::string& message) {
    write(clientSocket, message.c_str(), message.size());
    std::cout << "Sent FIX message: " << message << std::endl;
}

// std::string TradingClient::createNewOrderMessage(const std::string& symbol, double price, int quantity) {
//     return "8=FIX.4.2|35=D|55=" + symbol + "|44=" + std::to_string(price) + "|38=" + std::to_string(quantity);
// }

// std::string TradingClient::createCancelOrderMessage(const std::string& orderId) {
//     return "8=FIX.4.2|35=F|41=" + orderId;
// }

// std::string TradingClient::createModifyOrderMessage(const std::string& orderId, double newPrice, int newQuantity) {
//     return "8=FIX.4.2|35=G|41=" + orderId + "|44=" + std::to_string(newPrice) + "|38=" + std::to_string(newQuantity);
// }
