#pragma once

#include <vector>
#include <string>
#include <cstring>

class Tokeniser {
public:
    /**
     * Tokeniser function to split an input string separated by seperators into tokens 
     * @param csvline Input String
     * @param seperator String Seperator
    */
    static std::vector<std::string> tokenise(std::string csvline, const std::string &seperator);
};

