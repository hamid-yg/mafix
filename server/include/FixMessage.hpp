#pragma once

#include "Headers.hpp"

class FixMessage
{
    public:
        FixMessage(const std::string& messageType);

        void setSenderCompID(const std::string& senderCompID) { setField(49, senderCompID); }
        std::string getSenderCompID() const { return getField(49); }
        void setTargetCompID(const std::string& targetCompID) { setField(56, targetCompID); }
        std::string getTargetCompID() const { return getField(56); }
        void setMsgSeqNum(int msgSeqNum) { setField(34, std::to_string(msgSeqNum)); }
        int getMsgSeqNum() const { return std::stoi(getField(34)); }

        const std::unordered_map<int, std::string>& getFields() const { return fields; }
        std::string serialize() const;
        void deserialize(const std::string& message);

    private:
        std::unordered_map<int, std::string> fields;

    protected:
        std::unordered_map<int, std::string> headerFields;
        std::unordered_map<int, std::string> trailerFields;

        std::string messageType;

        void setField(int tag, const std::string& value) {
            fields[tag] = value;
            headerFields[tag] = value;
            trailerFields[tag] = value;
        }

        std::string getField(int tag) const {
            auto it = fields.find(tag);
            return it != fields.end() ? it->second : "";
        }
};
