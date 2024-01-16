#include <criterion/criterion.h>
#include "Headers.hpp"

Test(orderbook_tests, add_order_test) {
    OrderBook ob;
    Order order1 = {1, 100.0, 10};
    ob.addOrder(order1);
    cr_assert_eq(ob.orders.size(), 1, "OrderBook should contain 1 order after adding an order");
}

Test(orderbook_tests, modify_order_test) {
    OrderBook ob;
    Order order1 = {1, 100.0, 10};
    ob.addOrder(order1);
    ob.modifyOrder(1, 200.0, 20);
    cr_assert_eq(ob.orders[0].price, 200.0, "Order price should be updated to 200.0");
    cr_assert_eq(ob.orders[0].quantity, 20, "Order quantity should be updated to 20");
}

Test(orderbook_tests, modify_nonexistent_order_test) {
    OrderBook ob;
    Order order1 = {1, 100.0, 10};
    ob.addOrder(order1);
    ob.modifyOrder(2, 200.0, 20);
    cr_assert_eq(ob.orders[0].price, 100.0, "Order price should remain 100.0 when trying to modify a non-existent order");
    cr_assert_eq(ob.orders[0].quantity, 10, "Order quantity should remain 10 when trying to modify a non-existent order");
}
