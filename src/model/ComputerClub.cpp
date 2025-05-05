#include "ComputerClub.h"


bool ComputerClub::open_at(const Time& time) const {
    return
        time.get_total_minutes() > minutes_open &&
        time.get_total_minutes() < minutes_close;
}

bool ComputerClub::at_tables(const std::string client_name) const {
    for (const Table& table : tables) {
        if (table.occupied_by() == client_name) return true;
    }

    return false;
}

bool ComputerClub::at_queue(const std::string client_name) const {
    for (const std::string& name : queue) {
        if (name == client_name) return true;
    }

    return false;
}

bool ComputerClub::at_club(const std::string client_name) const {
    return at_tables(client_name) || at_queue(client_name);
}

bool ComputerClub::has_tables() const {
    for (const Table& table : tables) {
        if (!table.is_occupied()) return true;
    }

    return false;
}

int ComputerClub::tables_count() const {
    return tables.size();
}

int ComputerClub::queue_count() const {
    return queue.size();
}
