#include "Arithmetic.h"

//Accumualting values from the current timestamp
double Arithmetic::avg(const std::vector<double> &data) {
    return std::accumulate(data.begin(), data.end(), 0.0) / (double) data.size();
}

//Returning the minimum value
double Arithmetic::min(const std::vector<double> &data) {
    return *std::min_element(data.begin(), data.end());
}
//Returning the maximum value
double Arithmetic::max(const std::vector<double> &data) {
    return *std::max_element(data.begin(), data.end());
}
//Returning the spread
double Arithmetic::spread(const std::vector<double> &asks, const std::vector<double> &bids) {
    return min(asks) - max(bids);
}
//Returning the exponential moving average
double Arithmetic::ExpoMovAvg(int time, double data, double prevEMA) {
    if (time == 0) return data;

    const double a = 0.125;
    return a * data + (1 - a) * prevEMA;
}
