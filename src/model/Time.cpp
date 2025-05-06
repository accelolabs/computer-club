#include <stdexcept>
#include <iomanip>
#include <sstream>

#include "Time.h"
#include "../parsing/ParseHelpers.h"


Time::Time(const std::string& str) {

    if (!is_time(str)) throw std::invalid_argument("Invalid time format.");


    minutes = std::stoi(str.substr(3, 2));
    hours = std::stoi(str.substr(0, 2));

    time = str;
}


Time::Time(int mins) {

    if (mins < 0 || mins >= 1440) throw std::invalid_argument("Invalid time format.");

    int hours = mins / 60;
    int minutes = mins % 60;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":" 
       << std::setw(2) << std::setfill('0') << mins;
    
    time = ss.str();
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
