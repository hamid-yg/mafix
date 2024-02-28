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
        perror("<Log>: Error creating socket");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(LISTEN_PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        perror("<Log>: Error binding socket");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 10) == -1) {
        perror("<Log>: Error listening on socket");
        exit(EXIT_FAILURE);
    }

    std::cout << "<Log>: FIX server is listening on port " << LISTEN_PORT << std::endl;
}

int FixServer::acceptConnection() {
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);

    if (clientSocket == -1) {
        perror("<Log>: Error accepting connection");
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
    std::vector<std::string> words;
    std::string word;

    while (std::getline(iss, word, ' ')) {
        words.push_back(word);
    }
    char side = words[3][0];

    if (side == 'B') {
        market.receiveOrder(Order(atoi(words[0].c_str()), side, atoi(words[1].c_str()), atoi(words[2].c_str())));
        std::cout << "<Log>: Order received and added to the order book." << std::endl;
        write(clientSocket, "Order placed successfully.", 26);
    } else if (side == 'S') {
        market.receiveOrder(Order(atoi(words[0].c_str()), side, atoi(words[1].c_str()), atoi(words[2].c_str())));
        std::cout << "<Log>: Order received and added to the order book." << std::endl;
        write(clientSocket, "Order placed successfully.", 26);
    }
}
