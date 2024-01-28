#include "Headers.hpp"

EventMultiplexer::EventMultiplexer() {
    kq = kqueue();
    if (kq == -1) {
        std::cerr << "Error creating kqueue." << std::endl;
        exit(EXIT_FAILURE);
    }
}

EventMultiplexer::~EventMultiplexer() {
    close(kq);
}

void EventMultiplexer::addEventHandler(int socket, EventHandler* handler) {
    eventHandlers[socket] = handler;

    struct kevent ev;
    EV_SET(&ev, socket, EVFILT_READ, EV_ADD, 0, 0, nullptr);

    if (kevent(kq, &ev, 1, nullptr, 0, nullptr) == -1) {
        std::cerr << "Error adding socket to kqueue." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void EventMultiplexer::removeEventHandler(int socket) {
    struct kevent ev;
    EV_SET(&ev, socket, EVFILT_READ, EV_DELETE, 0, 0, nullptr);
    kevent(kq, &ev, 1, nullptr, 0, nullptr);

    eventHandlers.erase(socket);
}

void EventMultiplexer::waitForEvents() {
    constexpr int maxEvents = 10;
    struct kevent events[maxEvents];
    int numEvents = kevent(kq, nullptr, 0, events, maxEvents, nullptr);

    for (int i = 0; i < numEvents; ++i) {
        int socket = events[i].ident;
        eventHandlers[socket]->handleEvent(socket);
    }
}
