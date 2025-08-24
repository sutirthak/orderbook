#pragma once
#include <iostream>
#include <map>
#include <deque>
#include <list>
#include <queue>
#include <vector>
#include <iomanip>

struct Order {
    int id;
    bool isBuy;
    double price;
    int quantity;
};

struct Trade {
    int buyOrderId;
    int sellOrderId;
    double price;
    int quantity;
};

class OrderBook {
    std::list<Order> allOrders;
    std::map<double, std::deque<std::list<Order>::iterator>> buyLevels;
    std::map<double, std::deque<std::list<Order>::iterator>> sellLevels;
    std::priority_queue<double> buyPrices;
    std::priority_queue<double, std::vector<double>, std::greater<double>> sellPrices;
public:
    std::vector<Trade> trades;

    void addOrder(const Order& o);
    void printOrderBook();
    void printTrades();

private:
    void matchBuy(std::list<Order>::iterator it);
    void matchSell(std::list<Order>::iterator it);
};
