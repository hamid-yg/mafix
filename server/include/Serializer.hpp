#pragma once

#include <string>
#include <map>
#include <sstream>

class Serializer {
    public:
        std::string serialize(std::map<int, std::string> message_map);
};
