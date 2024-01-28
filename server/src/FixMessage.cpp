#include "Headers.hpp"


FixMessage::FixMessage(const std::string& messageType) : messageType(messageType) {
    setField(8, "FIX.4.2");
    setField(35, messageType);
}

std::string FixMessage::serialize() const {
    std::ostringstream oss;
    for (const auto& field : headerFields)
        oss << field.first << "=" << field.second << '\x01';
    for (const auto& field : fields)
        oss << field.first << "=" << field.second << '\x01';
    for (const auto& field : trailerFields)
        oss << field.first << "=" << field.second << '\x01';
    return oss.str();
}

void FixMessage::deserialize(const std::string& message) {
    std::istringstream iss(message);
    std::string field;
    while (std::getline(iss, field, '\x01')) {
        size_t pos = field.find('=');
        if (pos != std::string::npos) {
            int tag = std::stoi(field.substr(0, pos));
            std::string value = field.substr(pos + 1);
            setField(tag, value);
        }
    }
}
