#pragma once
#include <map>
#include <vector>
#include "order.h"

class OrderBook {
    std::map<double,std::vector<Order>,std::greater<double>> bids;
    std::map<double,std::vector<Order>> asks;

public:
    void add_order(Order o);
    void cancel_order(int id);
    void match_orders();
    void print_book();
};
