#include "order_book.h"
#include <iostream>

void OrderBook::add_order(const Order& o)
{
    if(o.side == "buy")
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
    
    for(auto it = asks.rbegin();it != asks.rend();++it)
    {
        std::cout<<"    "<<it->first<<" | ";
        for(auto& o : it->second)
        {
            if(cancel[o.id]) continue;
            std::cout<<"qty = "<<o.quantity<<"(id = "<<o.id<<") ";
        }
        std::cout<<'\n';
    }
    
    std::cout<<"\n─── SPREAD ───\n"<<'\n';
    std::cout<<"BIDS (buy side) : \n";
    
    for(auto& [price, orders] : bids)
    {
        std::cout<<"    "<<price<<" | ";
        for(auto& o : orders)
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
    while(!bids.empty() && !asks.empty())
    {
        auto bid_it = bids.begin();
        auto ask_it = asks.begin();

        while(!bid_it->second.empty() && cancel[bid_it->second.front().id])
            bid_it->second.erase(bid_it->second.begin());

        while(!ask_it->second.empty() && cancel[ask_it->second.front().id])
            ask_it->second.erase(ask_it->second.begin());

        if(bid_it->second.empty())
        {
            bids.erase(bid_it->first);
            continue;
        }

        if(ask_it->second.empty())
        {
            asks.erase(ask_it->first);
            continue;
        }

        double best_bid = bid_it->first;
        double best_ask = ask_it->first;

        if(best_bid < best_ask)
            break;

        Order& bid = bid_it->second.front();
        Order& ask = ask_it->second.front();

        int trade_qty = std::min(bid.quantity, ask.quantity);

        std::cout<<"TRADE :\n\tprice = "<<ask.price<<"\n\tqty = "<<trade_qty
            <<"\n\tbuyer_id = "<<bid.id<<"\n\tseller_id="<<ask.id<<'\n';

        bid.quantity -= trade_qty;
        ask.quantity -= trade_qty;

        if(bid.quantity == 0)
        {
            bid_it->second.erase(bid_it->second.begin());

            if(bid_it->second.empty())
                bids.erase(bid_it);
        }

        if(ask.quantity == 0)
        {
            ask_it->second.erase(ask_it->second.begin());

            if(ask_it->second.empty())
                asks.erase(ask_it);
        }
    }
}

std::pair<double,double> OrderBook::get_best_bid_ask()
{
    double best_bid = -1.0;
    double best_ask = -1.0;
    
    for(auto& [price, orders] : bids)
    {
        bool found = false;
        for(auto& o : orders)
        {
            if(!cancel[o.id])
            {
                found = true;
                break;
            }
        }
        if(found)
        {
            best_bid = price;
            break;
        }
    }
    
    for(auto& [price, orders] : asks)
    {
        bool found = false;
        for(auto& o : orders)
        {
            if(!cancel[o.id])
            {
                found = true;
                break;
            }
        }
        if(found)
        {
            best_ask = price;
            break;
        }
    }
    return {best_bid, best_ask};
}
