#include "Headers.hpp"

int main() {
    // OrderBook orderBook;

    // orderBook.addOrder(Order(1, 'B', 100.0, 10));
    // orderBook.addOrder(Order(2, 'S', 105.0, 5));

    // orderBook.printOrderBook();

    // orderBook.modifyOrder(1, 101.0, 15);
    // orderBook.printOrderBook();
    // orderBook.cancelOrder(2);
    // orderBook.printOrderBook();


    // orderBook.printOrderBook();
    // orderBook.executePartialOrder(1, 5);
    // orderBook.executePartialOrder(1, 5);
    // orderBook.printOrderBook();

    // LogonMessage logonMessage;

    // std::string serializedLogon = logonMessage.serialize();
    // std::cout << "Serialized Logon Message: " << serializedLogon << std::endl;

    // FixMessage deserializedLogon = FixMessage::deserialize(serializedLogon);
    // std::cout << "Deserialized Logon Message: ";
    // for (const auto& field : deserializedLogon.getFields()) {
    //     std::cout << field.first << "=" << field.second << ", ";
    // }
    // std::cout << std::endl;

Logon logon;
    logon.setSenderCompID("Sender");
    logon.setTargetCompID("Target");
    logon.setMsgSeqNum(1);
    std::string serializedLogon = logon.serialize();
    std::cout << "Serialized Logon Message: " << serializedLogon << std::endl;

    NewOrder newOrder;
    newOrder.setSenderCompID("Sender");
    newOrder.setTargetCompID("Target");
    newOrder.setMsgSeqNum(2);
    std::string serializedNewOrder = newOrder.serialize();
    std::cout << "Serialized NewOrder Message: " << serializedNewOrder << std::endl;

    OrderCancelReplaceRequest cancelReplace;
    cancelReplace.setSenderCompID("Sender");
    cancelReplace.setTargetCompID("Target");
    cancelReplace.setMsgSeqNum(3);
    std::string serializedCancelReplace = cancelReplace.serialize();
    std::cout << "Serialized OrderCancelReplaceRequest Message: " << serializedCancelReplace << std::endl;

    OrderCancelRequest cancelRequest;
    cancelRequest.setSenderCompID("Sender");
    cancelRequest.setTargetCompID("Target");
    cancelRequest.setMsgSeqNum(4);
    std::string serializedCancelRequest = cancelRequest.serialize();
    std::cout << "Serialized OrderCancelRequest Message: " << serializedCancelRequest << std::endl;

    ExecutionReport executionReport;
    executionReport.setSenderCompID("Sender");
    executionReport.setTargetCompID("Target");
    executionReport.setMsgSeqNum(5);
    std::string serializedExecutionReport = executionReport.serialize();
    std::cout << "Serialized ExecutionReport Message: " << serializedExecutionReport << std::endl;

    MarketDataSnapshotFullRefresh snapshotRefresh;
    snapshotRefresh.setSenderCompID("Sender");
    snapshotRefresh.setTargetCompID("Target");
    snapshotRefresh.setMsgSeqNum(6);
    std::string serializedSnapshotRefresh = snapshotRefresh.serialize();
    std::cout << "Serialized MarketDataSnapshotFullRefresh Message: " << serializedSnapshotRefresh << std::endl;

    MarketDataIncrementalRefresh incrementalRefresh;
    incrementalRefresh.setSenderCompID("Sender");
    incrementalRefresh.setTargetCompID("Target");
    incrementalRefresh.setMsgSeqNum(7);
    std::string serializedIncrementalRefresh = incrementalRefresh.serialize();
    std::cout << "Serialized MarketDataIncrementalRefresh Message: " << serializedIncrementalRefresh << std::endl;

    return 0;
}
