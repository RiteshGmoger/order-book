#pragma once
#include<map>
#include<vector>
#include<unordered_map>
#include"order.h"
#include<utility>

class OrderBook
{
private:
    std::map<double,std::vector<Order>,std::greater<double>> bids{};
    std::map<double,std::vector<Order>> asks{};
    std::unordered_map<int,bool> cancel{};

public:
    void add_order(const Order& o);
    void cancel_order(int id);
    void match_orders();
    void print_book();
    std::pair<double,double> get_best_bid_ask();
};
