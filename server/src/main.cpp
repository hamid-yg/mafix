#include "Headers.hpp"

int main() {
    OrderBook orderBook;

    orderBook.addOrder(Order(1, 'B', 100.0, 10));
    orderBook.addOrder(Order(2, 'S', 105.0, 5));

    orderBook.printOrderBook();

    orderBook.modifyOrder(1, 101.0, 15);
    orderBook.printOrderBook();
    orderBook.cancelOrder(2);
    orderBook.printOrderBook();


    orderBook.printOrderBook();
    orderBook.executePartialOrder(1, 5);
    orderBook.executePartialOrder(1, 5);
    orderBook.printOrderBook();

    return 0;
}
