#include "OrderBook.h"

//Displaying error message to user if CSV file cannot be opened
void OrderBook::load(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: File cannot be opened. Please use a different file.");
    }

    int lineNumber = 1;
    std::string line;

//Checking for bad data in the CSV file
    while (std::getline(file, line)) {
        try {
            Order entry = Order::tknToOrderEntry(Tokeniser::tokenise(line, ","));
            entries[entry.timestamp].push_back(entry);
        } catch (const std::exception &e) {
            throw std::runtime_error("Error: Found bad data in the CSV file at line: " + std::to_string(lineNumber));
        }
        lineNumber++;
    }

    process();
}

//Processing the data
void OrderBook::process() {
    std::set<std::string> processProducts;

    for (const auto &[timestamp, orders]: entries) {
        timestamps.push_back(timestamp);

        if (processProducts.empty())
            for (const auto &order: orders) {
                processProducts.insert((order.product));
            }
    }

    products.assign(processProducts.begin(), processProducts.end());

    for (const auto &product: products) {
        stats[product] = {0, 0, 0, 0};
    }
}

//Returning the price prediction value for the predict command
double OrderBook::pricePred(const std::string &minmax, const std::string &product, const OrderType &orderType) {
    if (minmax == "min") {
        return (orderType == OrderType::ask ? stats[product].EMAminask : stats[product].EMAminbid);
    } else {
        return (orderType == OrderType::ask ? stats[product].EMAmaxask : stats[product].EMAmaxbid);
    }
}

//Checking the number of steps inserted by the user in the specific timestamp. 
//If the inserted number of steps is more than there the user moved, a message is displayed to the user
double OrderBook::avgTimeSteps(int timeStampPos, const std::string &product, const OrderType &orderType, int steps) {
    if (steps > timeStampPos) throw std::runtime_error("Currently you are at timestamp position " + std::to_string(timeStampPos)+"." + " The entered number of steps is too big. Please use the step command to move to the next timestamp and try again.");

    double sum = 0;
    for (int i = timeStampPos - 1; i >= timeStampPos - steps; --i) {
        sum += Arithmetic::avg(retPriFromOrd(timestamps[i], product, orderType));
    }

    return sum / steps;
}

//Updating the order statistics for the specific timestamp
void OrderBook::updSts(int timeStampPos) {
    const auto &currentTime = timestamps[timeStampPos];

    for (auto &[product, stat]: stats) {
        const auto bids = retPriFromOrd(currentTime, product, OrderType::bid);
        const auto asks = retPriFromOrd(currentTime, product, OrderType::ask);
        stat.EMAminbid = Arithmetic::ExpoMovAvg(timeStampPos, Arithmetic::min(bids), stat.EMAminbid);
        stat.EMAmaxbid = Arithmetic::ExpoMovAvg(timeStampPos, Arithmetic::max(bids), stat.EMAmaxbid);
        stat.EMAminask = Arithmetic::ExpoMovAvg(timeStampPos, Arithmetic::min(asks), stat.EMAminask);
        stat.EMAmaxask = Arithmetic::ExpoMovAvg(timeStampPos, Arithmetic::max(asks), stat.EMAmaxask);
    }
}

//Validating the entered product. If it doesn't exist a message is displayed to the user
std::string OrderBook::checkProductValid(const std::string &product) {
    if (std::find(products.begin(), products.end(), product) == products.end()) {
        throw std::runtime_error("Error: The entered product \"" + product + "\" does not exist! Please enter a valid product.");
    }
    return product;
}

//Returning the products read from the CSV file
std::vector<std::string> OrderBook::retProds() {
    return products;
}

//Returning the timestamps read from the CSV file
std::vector<std::string> OrderBook::retTimestamps() {
    return timestamps;
}

//Returning the orders 
std::vector<Order>
OrderBook::retOrd(const std::string &timestamp, const std::string &product, const OrderType &orderType) {
    std::vector<Order> orders;

    for (const auto &order: entries[timestamp]) {
        if (order.product == product && order.orderType == orderType) {
            orders.push_back(order);
        }
    }

    return orders;
}

//Returning the order prices
std::vector<double> OrderBook::retPri(const std::vector<Order> &orders) {
    std::vector<double> prices;

    for (const auto &order: orders) {
        prices.push_back(order.price);
    }
    return prices;
}

//Returning the prices for a specific product and order type
std::vector<double>
OrderBook::retPriFromOrd(const std::string &timestamp, const std::string &product, const OrderType &orderType) {
    return retPri(retOrd(timestamp, product, orderType));
}
