#include "order_book.h"
#include <iostream>
using namespace std;

void OrderBook::add_order(Order o)
{
    if (o.side == "buy")
        bids[o.price].push_back(o);
    else
        asks[o.price].push_back(o);
        
    cout<<"Added "<< o.side<<" order: "<< o.quantity<<" @ "<< o.price<<" (id=" <<o.id<< ")"<<endl;
}

void OrderBook::print_book()
{
    cout << "\n─── ORDER BOOK ───" << endl;
    cout << "ASKS (sell side):" << endl;
    
    for (auto it = asks.rbegin();it != asks.rend();++it)
    {
        cout<<"  "<<it->first<<" | ";
        for (auto& o : it->second)
            cout<<"qty = "<<o.quantity<<"(id = "<<o.id<<") ";
        cout << endl;
    }

    cout<<"  ───SPREAD───  "<<endl;
    cout<<"BIDS (buy side):"<<endl;
    
    for (auto& [price, orders] : bids)
    {
        cout<<"  "<<price<<" | ";
        for (auto& o : orders)
            cout<<"qty = "<<o.quantity<<"(id = "<<o.id<<") ";
        cout<<endl;
    }
    cout << "─────────────────\n" << endl;
}

void OrderBook::cancel_order(int id) {
    cout<<"cancel_order called for id = "<<id<<endl;
}

void OrderBook::match_orders() {
    cout<<"match_orders called"<< endl;
}
