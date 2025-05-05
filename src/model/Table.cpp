#include "Table.h"


bool Table::is_occupied() const {
    return occupied;
}


std::string Table::occupied_by() const {
    return occupier;
}

void Table::occupy(const Time& time, const std::string& client_name) {
    if (occupied) return;

    occupied = true;
    occupier = client_name;
    session_start = time;
}

void Table::free(const Time& time, int price) {
    if (!occupied) return;

    occupied = false;

    int minutes_occupied = time.get_total_minutes() - session_start.get_total_minutes();
    revenue += (minutes_occupied / 60) * price;
    minutes += minutes_occupied;
}
