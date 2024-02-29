#include "Headers.hpp"

FixServer::FixServer() {
    initSocket();
    initMarket();
}

FixServer::~FixServer() {
    close(serverSocket);
}

void FixServer::run() {
    while (true) {
        int clientSocket = acceptConnection();
        if (clientSocket != -1) {
            handleClient(clientSocket);
        }
    }
}

void FixServer::initSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        perror("<Log>: Error creating socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(LISTEN_PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        perror("<Error>: Error binding socket");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) == -1) {
        perror("<Error>: Error listening on socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "<Log>: FIX server is listening on port " << LISTEN_PORT << std::endl;

    std::vector<std::thread> clientThreads;

    while (true) {
        int clientSocket = acceptConnection();
        if (clientSocket == -1) {
            std::cerr << "<Error>: Failed to accept client connection" << std::endl;
            close(serverSocket);
            exit(EXIT_FAILURE);
        }

        std::thread clientThread(&FixServer::handleClient, this, clientSocket);
        clientThread.detach();
    }

    close(serverSocket);
}

void FixServer::initMarket() {
    marketSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (marketSocket == -1) {
        perror("<Error>: Failed to create market socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(MARKET_PORT);

    if (bind(marketSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        perror("<Error>: Failed to bind market socket");
        close(marketSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "<Log>: Market server is listening on market port " << MARKET_PORT << std::endl;
}

int FixServer::acceptConnection() {
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);

    if (clientSocket == -1) {
        perror("<Error>: Failed to accept client connection");
        return -1;
    }

    std::cout << "<Log>: Accepted connection from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << std::endl;
    return clientSocket;
}

void FixServer::handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer))) > 0) {
        std::string receivedMessage(buffer, bytesRead);
        processMessage(receivedMessage, clientSocket);
    }

    std::cout << "<Log>: Connection closed with client" << std::endl;
    close(clientSocket);
}

void FixServer::processMessage(const std::string& receivedMessage, int clientSocket) {
    std::istringstream iss(receivedMessage);
    std::string fixMessage;

    while (std::getline(iss, fixMessage)) {
        if (fixMessage.empty()) {
            continue;
        }

        std::cout << "<Log>: Received FIX message: " << fixMessage << std::endl;

        FixMessage message("");
        std:: string msgType;

        message.deserialize(fixMessage);
        msgType = message.getField(35);

        std::cout << "<Log>: Message type: " << msgType << std::endl;

        if (msgType == "A") {
            write(clientSocket, "<Log>: Login successful.", 26);
        } else if (msgType == "F" || msgType == "D") {
            std::string symbol = message.getField(55);
            char side = message.getField(54)[0];
            int quantity = std::stoi(message.getField(38));
            double price = std::stoi(message.getField(44));
            market.receiveOrder(Order(atoi(message.getField(11).c_str()), side, symbol, quantity, price));
            std::cout << "<Log>: Order received and added to the order book." << std::endl;
        } else if (msgType == "U") {
            std::string symbol = message.getField(55);
            int quantity = std::stoi(message.getField(38));
            double price = std::stoi(message.getField(44));
            market.modifyOrder(atoi(message.getField(11).c_str()), symbol, price, quantity);
            std::cout << "<Log>: Order modified." << std::endl;
        } else if (msgType == "X") {
            market.cancelOrder(atoi(message.getField(11).c_str()), message.getField(55));
            std::cout << "<Log>: Order cancelled." << std::endl;
        } else if (msgType == "H") {
            std::string symbol = message.getField(55);
            std::string orderBook = market.getOrderBook(symbol);
            write(clientSocket, orderBook.c_str(), orderBook.length());
        } else {
            write(clientSocket, "<Error>: Invalid message type.", 27);
        }
    }
}
