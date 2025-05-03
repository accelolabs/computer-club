#include <cstddef>
#include <regex>
#include <sstream>
#include <string>

#include "ParseHelpers.h"


std::size_t get_args(const std::string& str, std::vector<std::string>& args) {
    std::istringstream iss(str);
    std::string current;
    
    while (iss >> current) args.push_back(current);

    return args.size();
}


bool is_time(const std::string& str) {
    const std::regex pattern("^([0-1][0-9]|2[0-3]):([0-5][0-9])$");

    return std::regex_match(str, pattern);
}


bool is_int(const std::string& str) {
    try {
        size_t pos;
        std::stoi(str, &pos);
        return pos == str.length();
    
    } catch (...) {
        return false;
    }
}

