# Order Book Recorder
Simple orderbook program to match order based on the price and quantity. 
Record the trades and print the snapshots

# Execute

## Compile
g++ -std=c++17 -Iinclude src/orderbook.cpp main.cpp -o orderbook.exe
## Run
orderbook.exe

# Tests

## Compile
 g++ -std=c++17 -Iinclude -O2 -Wall src/orderbook.cpp tests/test_orderbook.cpp -o orderbook_tests.exe
## Run
orderbook_tests.exe

