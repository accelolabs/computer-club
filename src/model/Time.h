#pragma once

#include <string>


class Time {
private:

    std::string time;

    int minutes;

    int hours;

public:

    explicit Time(const std::string& str);

    // Return minutes starting from 00:00
    uint get_total_minutes() const;

    // Return hours starting from 00:00, rounding up minutes
    // Example: 00:01 should return 1
    uint get_total_hours() const;

    std::string as_string() const;

};
