#pragma once

#include <string>


class Time {
private:

    int minutes;

    int hours;

public:

    explicit Time(const std::string& str);

    // Return minutes starting from 00:00
    uint get_total_minutes();

    // Return hours starting from 00:00, rounding up minutes
    // Example: 00:01 should return 1
    uint get_total_hours();

    uint parse_minutes();

    uint parse_hours();

};
