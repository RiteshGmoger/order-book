#include "src/order_book.h"
#include <iostream>
using namespace std;

int main()
{
    OrderBook book;

    book.add_order({1, "buy",  100.5, 10, 1});
    book.add_order({2, "buy",  100.0, 5,  2});
    book.add_order({3, "sell", 101.0, 15, 3});
    book.add_order({4, "sell", 100.5, 8,  4});
    
    book.cancel_order(1);
    book.match_orders();
    book.print_book();
    
    auto [bid, ask] = book.get_best_bid_ask();
    std::cout << "Best bid: " << bid << " | Best ask: " << ask << "\n";

    return 0;
}
