#include "Headers.hpp"


class Market {
    public:

        Market() {};
        ~Market() {};

        void receiveOrder(const Order& order) {
            orderBook.addOrder(order);
            orderBook.executeOrder(order.id);
        };

        void cancelOrder(int orderId) {
            orderBook.cancelOrder(orderId);
        };

        void modifyOrder(int orderId, double newPrice, int newQuantity) {
            orderBook.modifyOrder(orderId, newPrice, newQuantity);
            orderBook.executeOrder(orderId);
        };

    private:
        OrderBook orderBook;
};
