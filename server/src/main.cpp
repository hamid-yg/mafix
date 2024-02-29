#include "Headers.hpp"

int main() {
    try {
        FixServer fixServer;
        fixServer.run();
    } catch (const std::exception& e) {
        std::cerr << "<Error>: " << e.what() << std::endl;
    }
    return 0;
}
