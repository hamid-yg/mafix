#include "Serializer.hpp"


std::string Serializer::serialize(std::map<int, std::string> message_map) {
    std::stringstream fix_message;
    char SOH = 0x01;  // Start of Header character

    for (auto const& pair: message_map) {
        fix_message << pair.first << '=' << pair.second << SOH;
    }

    return fix_message.str();
}
