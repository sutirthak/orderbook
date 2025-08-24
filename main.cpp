#include "orderbook.h"

int main() {
    OrderBook ob;
    ob.addOrder({1, true, 100.0, 10});
    ob.addOrder({2, false, 99.0, 5});
    ob.addOrder({3, false, 101.0, 5});
    ob.addOrder({4, true, 101.0, 3});
    ob.addOrder({5, true, 102.0, 7});
    ob.addOrder({6, false, 101.0, 10});
    ob.addOrder({7, true, 99.0, 4});
    ob.addOrder({8, false, 98.0, 6});
}