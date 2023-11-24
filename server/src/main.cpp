#include "OrderBook.hpp"


int main(void) {
    OrderBook* orderBook = new OrderBook();
    Order* order = new Order("AAPL", "BID", 100.00);

    orderBook->addOrder(*order);
    orderBook->display();

    Order* order2 = new Order("AAPL", "BID", 200.00);
    orderBook->modifyOrder(*order2);
    orderBook->display();
    return 0;
}
