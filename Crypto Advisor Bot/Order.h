#pragma once

#include <string>
#include <vector>
#include <iostream>

enum class OrderType {
    bid, 
    ask,
};

class Order {
public:
    /**
     * A constructor that creates an Order
     * @param _timestamp A string that represents the timestamp
     * @param _product A string that represents a product type
     * @param _orderType An OrderType which represents the type of the order being done
     * @param _price The price of the order
     * @param _amount The amount of the order
     */
    Order(
            std::string _timestamp,
            std::string _product,
            OrderType _orderType,
            double _price,
            double _amount);

    /**
     * Converting a string to an OrderType
     * @param type A string containing the name of an order type
    */
    static OrderType strToOrderType(const std::string &type);

    /**
     * Converting a vector of tokens to an Order entry
     * @param tokens A vector of strings containing a timestamp, product, order type, price and amount
    */
    static Order tknToOrderEntry(std::vector<std::string> tokens);

    std::string timestamp;
    std::string product;
    OrderType orderType;
    double price;
    double amount;
};