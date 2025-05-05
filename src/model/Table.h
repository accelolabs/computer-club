#pragma once

#include "Time.h"
#include <string>


class Table {

    private:

    int id;

    bool occupied = false;
    std::string occupier;
    Time session_start {"00:00"};

    int price_rate;
    int revenue = 0;
    int minutes = 0;

    public:

    Table(int id, int price_rate) : id(id), price_rate(price_rate) {}


    bool is_occupied() const;

    std::string occupied_by() const;

    void occupy(const Time& time, const std::string& client_name);
    
    void free(const Time& time);

};
