#include "orderbook.h"
#include <cassert>
#include <iostream>

void testBasicMatch() {
    OrderBook ob;
    ob.addOrder({1, true, 100.0, 10});
    ob.addOrder({2, false, 99.0, 5});

    assert(ob.trades.size() == 1);
    auto t = ob.trades[0];
    assert(t.buyOrderId == 1);
    assert(t.sellOrderId == 2);
    assert(t.price == 99.0);
    assert(t.quantity == 5);

    std::cout << "testBasicMatch Passed ✅\n";
}

int main() {
    testBasicMatch();
    std::cout << "All tests passed ✅\n";
    return 0;
}
