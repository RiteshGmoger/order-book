#pragma once
#include <string>

struct Order
{
    int id;
    std::string side;
    double price;
    int quantity;
    long long timestamp;
};
