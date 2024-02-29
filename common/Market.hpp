#include "Headers.hpp"


class Market {
    public:

        Market() {};
        ~Market() {};

        void receiveOrder(const Order& order) {
            orderBooks[order.symbol].addOrder(order);
        };

        std::string getOrderBook(const std::string& symbol) {
            return orderBooks[symbol].toString();
        };

        void modifyOrder(int orderId, std::string symbol, double newPrice, int newQuantity) {
            orderBooks[symbol].modifyOrder(orderId, newPrice, newQuantity);
        };

        void processOrders() {
            for (auto& pair : orderBooks) {
                OrderBook& orderBook = pair.second;
                orderBook.matchOrders();
            }
        };

        // void sendExecutionReport(const Order& order, const std::string& execType) {
        //     std::string execReport = "8=FIX.4.2|35=8|34=" + std::to_string(order.id) + "|49=Market|56=Client|55=" + order.symbol + "|39=" + execType + "|";
        //     std::cout << "<Log>: Sending execution report: " << execReport << std::endl;
        // };

        // void sendOrderBookImages() {
        //     // Parcourir les carnets d'ordres et envoyer l'image de chaque carnet aux clients
        //     for (const auto& pair : orderBooks) {
        //         const std::string& instrument = pair.first;
        //         const OrderBook& orderBook = pair.second;

        //         // Convertir l'image du carnet d'ordres en une chaîne de caractères (simulé)
        //         std::string orderBookImage = getOrderBookImageAsString(orderBook);

        //         // Envoyer l'image du carnet d'ordres au client
        //         sendOrderBookImageToClients(instrument, orderBookImage);
        //     }
        // }

        // std::string getOrderBookImageAsString(const OrderBook& orderBook) {
        //     // Convertir l'image du carnet d'ordres en une chaîne de caractères (simulé)
        //     // Ici, vous devez implémenter la logique pour convertir l'image du carnet d'ordres en une chaîne de caractères
        //     return "Order book image for instrument " + orderBook.getInstrument() + "\n" + orderBook.toString();
        // }

        // void sendOrderBookImageToClients(const std::string& instrument, const std::string& orderBookImage) {
        //     // Envoyer l'image du carnet d'ordres à tous les clients connectés
        //     // Ici, vous devez implémenter
        // }

        void cancelOrder(int orderId, const std::string& symbol) {
            orderBooks[symbol].cancelOrder(orderId);
        };

    private:
        std::map<std::string, OrderBook> orderBooks;
};
