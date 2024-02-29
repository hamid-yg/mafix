#include "../include/Headers.hpp"

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
    std::cout << "Usage: Symbol Side(B|S) Price Quantity" << std::endl;
    std::cout << "Enter 'exit' to close the connection." << std::endl;

    while (true) {
        std::string response;
        std::vector<std::string> tokens;

        std::cout << "<client> ";

        std::getline(std::cin, response);
        std::istringstream iss(response);

        for (std::string s; iss >> s;) {
            tokens.push_back(s);
        }

        if (tokens[0] == "logon") {
            Logon logon(tokens[1], tokens[2], tokens[3], tokens[4]);
            std::string logonMsg = logon.serialize();
            std::cout << "Message: " << logonMsg << std::endl;
            write(clientSocket, logonMsg.c_str(), logonMsg.size());
        } else if (tokens[0] == "add") {
            NewOrder newOrder(orderId, tokens[1], tokens[2], tokens[3], tokens[4]);
            orderId++;
            std::string orderMsg = newOrder.serialize();
            write(clientSocket, orderMsg.c_str(), orderMsg.size());
        } else if (tokens[0] == "modify") {
            // OrderCancelReplaceRequest modifyOrder;
            // modifyOrder.setField(11, std::to_string(orderId));
            // modifyOrder.setField(41, std::to_string(orderId));
            // modifyOrder.setField(55, "MSFT");
            // modifyOrder.setField(54, "1");
            // modifyOrder.setField(38, "100");
            // modifyOrder.setField(44, "50.00");
            // std::string modifyMsg = modifyOrder.serialize();
            // write(clientSocket, modifyMsg.c_str(), modifyMsg.size());
        } else if (tokens[0] == "report") {
            // ExecutionReport report(std::to_string(orderId), "MSFT", "2", "2");
            // std::string reportMsg = report.serialize();
            // write(clientSocket, reportMsg.c_str(), reportMsg.size());
        } else if (tokens[0] == "cancel") {
            // OrderCancelRequest cancelOrder;
            // cancelOrder.setField(11, std::to_string(orderId));
            // cancelOrder.setField(41, std::to_string(orderId));
            // cancelOrder.setField(55, "MSFT");
            // std::string cancelMsg = cancelOrder.serialize();
            // write(clientSocket, cancelMsg.c_str(), cancelMsg.size());
        } else if (response == "exit") {
            write(clientSocket, response.c_str(), response.size());
            break;
        } else {
            std::cerr << "Error: Invalid action." << std::endl;
            return;
        }
    }
}
