# C++ Limit Order Book
A limit order book implementation in C++ 
with price-time priority.

## What is a Limit Order Book?
The matching engine at the core of every 
financial exchange. Buyers place bids. 
Sellers place asks. When best bid meets 
best ask, a trade executes.

## Why std::map?
std::map keeps prices sorted automatically 
in O(log n). Bids use greater<double> for 
highest-first. Asks use default ascending 
for lowest-first. O(1) access to best price.

## Methods
- add_order() - adds limit order to book
- cancel_order() - removes order by id
- match_orders() - executes crossing orders
- print_book() - displays current state

## Compile and Run
make
./order_book

## Clean
make clean

## Status
Week 1 complete - skeleton compiling
Week 2 - cancel_order + match_orders (June 11)
