#include "Headers.hpp"

FixServer::FixServer() {
    initSocket();
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
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(LISTEN_PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "FIX server is listening on port " << LISTEN_PORT << std::endl;
}

int FixServer::acceptConnection() {
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);

    if (clientSocket == -1) {
        perror("Error accepting connection");
        return -1;
    }

    std::cout << "Accepted connection from " << inet_ntoa(clientAddress.sin_addr) << ":" << ntohs(clientAddress.sin_port) << std::endl;
    return clientSocket;
}

void FixServer::handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(clientSocket, buffer, sizeof(buffer))) > 0) {
        std::string fixMessage(buffer, bytesRead);

        FixMessage receivedFixMessage("UnknownMessageType");

        receivedFixMessage.deserialize(fixMessage);

        std::string msgType = receivedFixMessage.getField(35);

        processFixMessage(receivedFixMessage.serialize(), msgType, clientSocket);
    }

    std::cout << "Connection closed with client" << std::endl;
    close(clientSocket);
}

void FixServer::processFixMessage(const std::string& fixMessage, const std::string& messageType, int clientSocket) {
    FixMessage receivedFixMessage(messageType);
    receivedFixMessage.deserialize(fixMessage);

    std::string msgType = receivedFixMessage.getField(35);

    if (msgType == "A") {
        std::cout << "Received Logon message" << std::endl;
    } else if (msgType == "5") {
        std::cout << "Received Logout message" << std::endl;
    } else if (msgType == "D") {
        std::cout << "Received New Order - Single message" << std::endl;
    } else if (msgType == "F") {
        std::cout << "Received Order - Cancel/Replace Request message" << std::endl;
    } else if (msgType == "8") {
        std::cout << "Received Execution Report message" << std::endl;
    } else {
        std::cerr << "Unknown MsgType received: " << msgType << std::endl;
    }
    write(clientSocket, fixMessage.c_str(), fixMessage.size());
}
