#pragma once

#include "Headers.hpp"

class Socket {
    public:
        Socket() : sockfd(-1) {}
        virtual ~Socket() {
            if (sockfd != -1) {
                close(sockfd);
            }
        }

        int getSocket() const {
            return sockfd;
        }

    protected:
        int sockfd;
};
