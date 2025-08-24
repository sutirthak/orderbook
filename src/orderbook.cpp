#include "orderbook.h"

// ------------------ addOrder ------------------
void OrderBook::addOrder(const Order& o) {
    allOrders.push_back(o);
    auto it = std::prev(allOrders.end());

    if (o.isBuy) matchBuy(it);
    else matchSell(it);

    printOrderBook();
    std::cout << "-----------------------------------\n";
    printTrades();
    std::cout << "-----------------------------------\n";
    std::cout << "-----------------------------------\n";
}

// ------------------ matchBuy ------------------
void OrderBook::matchBuy(std::list<Order>::iterator it) {
    while (it->quantity > 0 && !sellPrices.empty()) {
        double bestSellPrice = sellPrices.top();

        // Market buy: price == 0 means accept any sell price
        if (it->price != 0 && bestSellPrice > it->price) break;

        auto sellLevelIt = sellLevels.find(bestSellPrice);
        if (sellLevelIt == sellLevels.end() || sellLevelIt->second.empty()) {
            sellLevels.erase(bestSellPrice);
            sellPrices.pop();
            continue;
        }

        auto& level = sellLevelIt->second;
        auto sellIt = level.front();

        int tradedQty = std::min(it->quantity, sellIt->quantity);
        trades.push_back({it->id, sellIt->id, bestSellPrice, tradedQty});

        it->quantity -= tradedQty;
        sellIt->quantity -= tradedQty;

        if (sellIt->quantity == 0) {
            level.pop_front();
        }
        if (level.empty()) {
            sellLevels.erase(bestSellPrice);
            sellPrices.pop();
        }
    }

    // For market buy (price=0), do NOT put into book
    if (it->quantity > 0 && it->price > 0) {
        buyLevels[it->price].push_back(it);
        buyPrices.push(it->price);
    }
}

// ------------------ matchSell ------------------
void OrderBook::matchSell(std::list<Order>::iterator it) {
    while (it->quantity > 0 && !buyPrices.empty()) {
        double bestBuyPrice = buyPrices.top();

        // Market sell: price == 0 means accept any buy price
        if (it->price != 0 && bestBuyPrice < it->price) break;

        auto buyLevelIt = buyLevels.find(bestBuyPrice);
        if (buyLevelIt == buyLevels.end() || buyLevelIt->second.empty()) {
            buyLevels.erase(bestBuyPrice);
            buyPrices.pop();
            continue;
        }

        auto& level = buyLevelIt->second;
        auto buyIt = level.front();

        int tradedQty = std::min(it->quantity, buyIt->quantity);
        trades.push_back({buyIt->id, it->id, bestBuyPrice, tradedQty});

        it->quantity -= tradedQty;
        buyIt->quantity -= tradedQty;

        if (buyIt->quantity == 0) {
            level.pop_front();
        }
        if (level.empty()) {
            buyLevels.erase(bestBuyPrice);
            buyPrices.pop();
        }
    }

    // For market sell (price=0), do NOT put into book
    if (it->quantity > 0 && it->price > 0) {
        sellLevels[it->price].push_back(it);
        sellPrices.push(it->price);
    }
}

// ------------------ printOrderBook ------------------
void OrderBook::printOrderBook() {
    std::cout << "Order Book:\n";
    std::cout << std::left
              << std::setw(10) << "BuyPrice"
              << std::setw(12) << "| BuyQty"
              << " || "
              << std::setw(11) << "SellPrice"
              << std::setw(10) << "| SellQty"
              << "\n";

    auto buyIt = buyLevels.rbegin();
    auto sellIt = sellLevels.begin();
    while (buyIt != buyLevels.rend() || sellIt != sellLevels.end()) {
        int buyQty = 0;
        double buyPrice = 0;
        if (buyIt != buyLevels.rend()) {
            buyPrice = buyIt->first;
            for (auto& o : buyIt->second) buyQty += o->quantity;
        }

        int sellQty = 0;
        double sellPrice = 0;
        if (sellIt != sellLevels.end()) {
            sellPrice = sellIt->first;
            for (auto& o : sellIt->second) sellQty += o->quantity;
        }

        std::cout << std::left
                  << std::setw(10) << (buyIt != buyLevels.rend() ? buyPrice : 0)
                  << "| " << std::setw(10) << (buyIt != buyLevels.rend() ? buyQty : 0)
                  << " || "
                  << std::setw(10) << (sellIt != sellLevels.end() ? sellPrice : 0)
                  << "| " << std::setw(10) << (sellIt != sellLevels.end() ? sellQty : 0)
                  << "\n";

        if (buyIt != buyLevels.rend()) ++buyIt;
        if (sellIt != sellLevels.end()) ++sellIt;
    }
}

// ------------------ printTrades ------------------
void OrderBook::printTrades() {
    std::cout << "Trade Book:\n";
    if (trades.empty()) {
        std::cout << "  (No trades yet)\n";
        return;
    }

    std::cout << std::left
              << std::setw(8) << "BuyID"
              << std::setw(8) << "SellID"
              << std::setw(10) << "Price"
              << std::setw(8) << "Qty"
              << "\n";

    for (auto& t : trades) {
        std::cout << std::left
                  << std::setw(8) << t.buyOrderId
                  << std::setw(8) << t.sellOrderId
                  << std::setw(10) << std::fixed << std::setprecision(2) << t.price
                  << std::setw(8) << t.quantity
                  << "\n";
    }
}
