#include "Order.h"

//Components which make up an order
Order::Order(std::string _timestamp, std::string _product, OrderType _orderType, double _price, double _amount) :
        timestamp(_timestamp), product(_product), orderType(_orderType), price(_price), amount(_amount) {}

//Error handling for the inserted order type
OrderType Order::strToOrderType(const std::string &type) {
    if (type == "ask")
        return OrderType::ask;
    if (type == "bid")
        return OrderType::bid;

    throw std::invalid_argument("Error: The entered order type \"" + type + "\" does not exist! Please enter a valid order type.");
}

//Creating and validating tokenized strings to an order entry
Order Order::tknToOrderEntry(std::vector<std::string> tokens) {
    OrderType orderType;
    double price;
    double amount;

    try {
        orderType = strToOrderType(tokens[2]);
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch (const std::exception &e) {
        throw std::runtime_error("Error: Tokens couldn't be converted to double.");
    }

    return {tokens[0], tokens[1], orderType, price, amount};
}
