#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "Tokeniser.h"
#include "Order.h"
#include "Arithmetic.h"

class Stat {
public:
    double EMAminbid;
    double EMAmaxbid;
    double EMAminask;
    double EMAmaxask;
};

class OrderBook {
public:
    /**
     * Function to load the CSV file
     * @param filename The filename from which to load the data
     */
    void load(const std::string &filename);

    // Function to process the loaded data from the CSV file
    void process();

    /**
     * Function to calculate the average over a given number of timestamps
     * @param timeStampPos Position of the current timestamp
     * @param product The product for example "ETH/BTC"
     * @param orderType An order type of order which can be "bid" or "ask"
     * @param steps The number of time steps
     * @return The average over the given number of timestamps
     */
    double avgTimeSteps(int timeStampPos, const std::string &product, const OrderType &orderType, int steps);

    /**
     * Function which returns a statistic based on the given parameters
     * @param minmax A string which can be "min" or "max"
     * @param product The product for example "ETH/BTC"
     * @param orderType An order type of order which can be "bid" or "ask"
     * @return A value of a statistic which is an EMA value
     */
    double pricePred(const std::string &minmax, const std::string &product, const OrderType &orderType);

    /**
     * Function to update the statistics for each product with values at the given timeStampPos
     * @param timeStampPos Position of the current timestamp
     */
    void updSts(int timeStampPos);

     /**
     * Function to checks if the given string is a valid product
     * @param product The product for example "ETH/BTC"
     * @return The product if it's a valid string
     * @throw A runtime_error if the product inserted is not valid
     */
    std::string checkProductValid(const std::string &product);

    /**
     * Function to get all prices from a vector of orders
     * @param orders The orders from which to retrieve the prices
     * @return A vector of values
     */
    static std::vector<double> retPri(const std::vector<Order> &orders);

     /**
     * Function to get all orders that match the specified parameters
     * @param timestamp The current timestamp
     * @param product The product for example "ETH/BTC"
     * @param orderType An order type of order which can be "bid" or "ask"
     * @return A vector with the orders
     */
    std::vector<Order> retOrd(const std::string &timestamp, const std::string &product, const OrderType &orderType);

    /**
     * A joint function of getOrders and getPrices for simplification
     * @param timestamp The current timestamp
     * @param product The product for example "ETH/BTC"
     * @param orderType An order type of order which can be "bid" or "ask"
     * @return A vector of values
     */
    std::vector<double>
    retPriFromOrd(const std::string &timestamp, const std::string &product, const OrderType &orderType);

    /**
     * Function to return all the available products
     * @return The vector of all available products
     */
    std::vector<std::string> retProds();

    /**
     * Function to return all available timestamps
     * @return The vector of all available timestamps
     */
    std::vector<std::string> retTimestamps();

private:
    // A vector of all the available timestamps
    std::vector<std::string> timestamps;

    // Map which assigns each timestamp a vector of orders
    std::map<std::string, std::vector<Order>> entries;

    // Map which assigns each product a statistic
    std::map<std::string, Stat> stats;

    // Vector of all the available products
    std::vector<std::string> products;
};