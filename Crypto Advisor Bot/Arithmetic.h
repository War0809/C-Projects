#pragma once

#include <vector>
#include <algorithm>
#include <numeric>

class Arithmetic {
public:
    /**
    * Function to calculate the Exponential Moving Average
    * @param time The time at which the EMA is calculated
    * @param data Value at time t
    * @param prevEMA The previous value of the EMA
    * @return The Exponential Moving Average
    */
    static double ExpoMovAvg(int time, double data, double prevEMA);

    /**
     * Function to calculate the average
     * @param data A vector of values
     * @return The average value
     */
    static double avg(const std::vector<double> &data);

    /**
     * Function to return the minimum value
     * @param data A vector of values
     * @return The minimum value
     */
    static double min(const std::vector<double> &data);

    /**
     * Function to return the maximum
     * @param data A vector of values
     * @return The maximum value
     */
    static double max(const std::vector<double> &data);

    /**
    * Function to calculate the spread
    * @param asks A vector of ask prices
    * @param bids A vector of bid prices
    * @return The spread value
    */
    static double spread(const std::vector<double> &asks, const std::vector<double> &bids);

};