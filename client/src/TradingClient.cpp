#include "Headers.hpp"

TradingClient::TradingClient() : orderId(1) {
    initSocket();
}

TradingClient::~TradingClient() {
    close(clientSocket);
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
    serverAddress.sin_port = htons(8000);

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error: Could not connect to server." << std::endl;
        exit(1);
    }

    std::cout << "Connected to server." << std::endl;
}

void TradingClient::run() {
    std::cout << "Usage: Price Quantity Symbol (B or S)" << std::endl;
    std::cout << "Enter 'exit' to close the connection." << std::endl;

    while (true) {
        std::string response;
        std::cout << "<client> ";
        std::getline(std::cin, response);

        if (response == "exit") {
            write(clientSocket, response.c_str(), response.size());
            break;
        }
        response = std::to_string(orderId) + " " + response;
        orderId++;
        write(clientSocket, response.c_str(), response.size());
    }
}
