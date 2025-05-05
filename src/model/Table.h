#pragma once

#include "Time.h"
#include <string>


class Table {

    private:

    int id;

    std::string occupier;

    int revenue = 0;

    int minutes = 0;

    Time session_start {"00:00"};

    bool occupied = false;


    public:

    Table(int id) : id(id) {}


    bool is_occupied() const;

    std::string occupied_by() const;

    void occupy(const Time& time, const std::string& client_name);
    
    void free(const Time& time, int price);

};
