#pragma once

#include <vector>
#include "Table.h"


class ComputerClub {
private:

    int minutes_open;

    int minutes_close;

    std::vector<Table> tables;
    
    std::vector<std::string> queue;

public:

    ComputerClub(const Time& time_open, const Time& time_close) :
        minutes_open(time_open.get_total_minutes()),
        minutes_close(time_close.get_total_minutes())
    {}


    bool open_at(const Time& time) const;

    bool at_tables(const std::string client_name) const;

    bool at_queue(const std::string client_name) const;

    bool at_club(const std::string client_name) const;

    bool has_tables() const;

    int tables_count() const;

    int queue_count() const;

};
