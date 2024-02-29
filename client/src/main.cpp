#include "Headers.hpp"

int main() {
    try {
        TradingClient client;
        client.run();
    }
    catch(const std::exception& e) {
        std::cerr << "<Error>: " << e.what() << "\n";
    }
    return 0;
}
