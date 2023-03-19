#include <sstream>
#include "Tokeniser.h"

//Tokenising the inputs into seperate strings
std::vector<std::string> Tokeniser::tokenise(std::string csvline, const std::string &seperator) {
    std::vector<std::string> tokens;

    for (char *token = strtok(std::data(csvline), std::data(seperator));
         token != nullptr; token = strtok(nullptr, std::data(seperator))) {
         tokens.emplace_back(token);
    }

    return tokens;
}
