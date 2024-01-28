#include "Headers.hpp"

UDPSocket::UDPSocket(int port)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        std::cerr << "Erreur lors de la création du socket UDP." << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockfd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
        std::cerr << "Erreur lors de la liaison du socket UDP." << std::endl;
        exit(EXIT_FAILURE);
    }
}
