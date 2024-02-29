#pragma once

#include "Headers.hpp"

class FixMessage
{
    protected:
        std::unordered_map<int, std::string> headerFields;
        std::unordered_map<int, std::string> trailerFields;

        std::string messageType;

        void setField(int tag, const std::string& value) {
            if (tag == 8 || tag == 9 || tag == 35 || tag == 49 || tag == 56 || tag == 34)
                headerFields[tag] = value;
            else if (tag == 10)
                trailerFields[tag] = value;
            else
                fields[tag] = value;
        }

    public:
        FixMessage(const std::string& messageType) : messageType(messageType) {
            setField(8, "FIX.4.2");
            setField(35, messageType);
        }

        void setSenderCompID(const std::string& senderCompID) { setField(49, senderCompID); }
        std::string getSenderCompID() const { return getField(49); }
        void setTargetCompID(const std::string& targetCompID) { setField(56, targetCompID); }
        std::string getTargetCompID() const { return getField(56); }
        void setMsgSeqNum(int msgSeqNum) { setField(34, std::to_string(msgSeqNum)); }
        int getMsgSeqNum() const { return std::stoi(getField(34)); }
        void setSendingTime(const std::string& sendingTime) { setField(52, sendingTime); }

        std::string getMessageType() const { return messageType; }

        const std::unordered_map<int, std::string>& getFields() const { return fields; }

        std::string serialize() {
            std::ostringstream oss;

            for (const auto& field : headerFields) {
                oss << field.first << "=" << field.second << '\x01';
            }

            std::string messageWithoutChecksum = oss.str();

            // Calculate body length and checksum
            int bodyLength = messageWithoutChecksum.length();
            headerFields[9] = std::to_string(bodyLength);

            int checksum = std::accumulate(messageWithoutChecksum.begin(), messageWithoutChecksum.end(), 0) % 256;
            trailerFields[10] = std::to_string(checksum);

            headerFields[34] = "1";

            headerFields[52] = "20210901-00:00:00";

            // Rebuild the message with the correct body length and checksum
            oss.str("");
            oss.clear();

            std::map<int, std::string> allFields;

            allFields.insert(headerFields.begin(), headerFields.end());
            allFields.insert(fields.begin(), fields.end());
            allFields.insert(trailerFields.begin(), trailerFields.end());

            for (const auto& field : allFields) {
                oss << field.first << "=" << field.second << '|' << '\x01';
            }

            return oss.str();
        }

        void deserialize(const std::string& message) {
            std::istringstream iss(message);
            std::string field;

            while (std::getline(iss, field, '\x01')) {
                size_t pos = field.find('=');
                if (pos != std::string::npos) {
                    int tag = std::stoi(field.substr(0, pos));
                    std::string value = field.substr(pos + 1);

                    if (tag == 8 || tag == 9 || tag == 35 || tag == 49 || tag == 56 || tag == 34)
                        headerFields[tag] = value;
                    else if (tag == 10)
                        trailerFields[tag] = value;
                    else
                        fields[tag] = value;
                }
            }
        }

        std::string getField(int tag) const {
            auto it = fields.find(tag);
            return it != fields.end() ? it->second : "";
        }

    private:
        std::unordered_map<int, std::string> fields;
};
