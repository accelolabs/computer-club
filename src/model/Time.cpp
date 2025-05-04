#include <stdexcept>

#include "Time.h"
#include "../parsing/ParseHelpers.h"


Time::Time(const std::string& str) {

    if (!is_time(str)) throw std::invalid_argument("Invalid time format.");

    time = str;
    minutes = std::stoi(str.substr(3, 2));
    hours = std::stoi(str.substr(0, 2));
}


uint Time::get_total_minutes() const {
    return hours * 60 + minutes;
}


uint Time::get_total_hours() const {
    return hours + !!minutes;
}


std::string Time::as_string() const {
    return time;
}
