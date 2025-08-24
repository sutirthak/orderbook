#pragma once
#include <iostream>
#include <map>
#include <deque>
#include <list>
#include <queue>
#include <vector>
#include <iomanip>

// Order structure to hold order details
struct Order {
    int id;         // Unique order ID  
    bool isBuy;     // true for buy, false for sell
    double price;   // Price per unit
    int quantity;   // Quantity of units
};

// Trade structure to hold trade details
struct Trade {
    int buyOrderId;     // ID of the buy order
    int sellOrderId;    // ID of the sell order
    double price;       // Trade price
    int quantity;       // Quantity traded
};

// OrderBook class to manage orders and trades
// In real exachnges the trade happens when buy order price >= sell order price
// So highest buy order price is matched with lowest sell order price
class OrderBook {
    std::list<Order> allOrders; // List to hold all orders
    std::map<double, std::deque<std::list<Order>::iterator>> buyLevels;                 // Map price to deque of order iterators for buy orders
    std::map<double, std::deque<std::list<Order>::iterator>> sellLevels;                // Map price to deque of order iterators for sell orders
    std::priority_queue<double> buyPrices;                                              // Max-heap for buy prices
    std::priority_queue<double, std::vector<double>, std::greater<double>> sellPrices;  // Min-heap for sell prices
    public:
        std::vector<Trade> trades;      // Vector to hold executed trades
        void addOrder(const Order& o);  // Add a new order to the order book
        void printOrderBook();          // Print the current state of the order book
        void printTrades();             // Print all executed trades

    private:
        void matchBuy(std::list<Order>::iterator it);   // Match a buy order
        void matchSell(std::list<Order>::iterator it);  // Match a sell order
};
