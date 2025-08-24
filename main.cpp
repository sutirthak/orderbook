#include "orderbook.h"

int main() {
    OrderBook ob;

    std::cout << "=== Test 1: Simple Buy/Sell ===\n";
    ob.addOrder({1, true, 100.0, 10});   // Buy 10 @ 100
    ob.addOrder({2, false, 105.0, 5});   // Sell 5 @ 105 (no match, goes to book)
    ob.addOrder({3, false, 99.0, 5});    // Sell 5 @ 99 (matches with Buy 10 @ 100)

    std::cout << "\n=== Test 2: Market Buy ===\n";
    ob.addOrder({4, false, 101.0, 5});   // Sell 5 @ 101 (goes to book)
    ob.addOrder({5, true, 0.0, 8});      // Market Buy 8 (should take 5 @ 101, 3 @ 105)

    std::cout << "\n=== Test 3: Market Sell ===\n";
    ob.addOrder({6, true, 102.0, 6});    // Buy 6 @ 102
    ob.addOrder({7, true, 101.0, 4});    // Buy 4 @ 101
    ob.addOrder({8, false, 0.0, 8});     // Market Sell 8 (should hit 6 @ 102, 2 @ 101)

    std::cout << "\n=== Test 4: Partial Fills ===\n";
    ob.addOrder({9, true, 100.0, 10});   // Buy 10 @ 100
    ob.addOrder({10, false, 100.0, 15}); // Sell 15 @ 100 (fills Buy 10, leaves 5 in book)

    std::cout << "\n=== Test 5: No Match ===\n";
    ob.addOrder({11, true, 90.0, 10});   // Buy 10 @ 90 (too low, sits in book)
    ob.addOrder({12, false, 110.0, 5});  // Sell 5 @ 110 (too high, sits in book)

    return 0;
}