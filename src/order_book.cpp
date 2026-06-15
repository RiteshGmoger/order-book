#include "order_book.h"
#include <iostream>

void OrderBook::add_order(const Order& o)
{
    if (o.side == "buy")
        bids[o.price].push_back(o);
    else
        asks[o.price].push_back(o);
        
    cancel[o.id] = false; 
    std::cout<<"Added "<<o.side<<" order : "<<o.quantity<<" @ "<<o.price<<" ( id = " <<o.id<< " )\n";
}

void OrderBook::print_book()
{
    std::cout<< "\n─── ORDER BOOK ─── \n";
    std::cout<< "ASKS (sell side) :\n";
    
    for (auto it = asks.rbegin();it != asks.rend();++it)
    {
        std::cout<<"    "<<it->first<<" | ";
        for (auto& o : it->second)
        {
            if(cancel[o.id]) continue;
            std::cout<<"qty = "<<o.quantity<<"(id = "<<o.id<<") ";
        }
        std::cout<<'\n';
    }

    std::cout<<"\n─── SPREAD ───\n"<<'\n';
    std::cout<<"BIDS (buy side) : \n";
    
    for (auto& [price, orders] : bids)
    {
        std::cout<<"    "<<price<<" | ";
        for (auto& o : orders)
        {
            if(cancel[o.id]) continue;
            std::cout<<"qty = "<<o.quantity<<"(id = "<<o.id<<") ";
        }
        std::cout<<'\n';
    }
    std::cout<<"\n";
}

void OrderBook::cancel_order(int id)
{
    cancel[id] = true;
    std::cout<<"cancel_order called for id = "<<id<<'\n';
}

void OrderBook::match_orders()
{
    std::cout<<"match_orders called"<<'\n';
}
