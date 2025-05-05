#include "ComputerClub.h"
#include <string>


EventVariants ComputerClub::handle_arrive(const ClientArrivedEvent& event) {
    if (clients.contains(event.client_name)) return ErrorEvent(event.time, "YouShallNotPass");
    if (event.time.get_total_minutes() < minutes_open) return ErrorEvent(event.time, "NotOpenYet");
    if (event.time.get_total_minutes() > minutes_close) return ErrorEvent(event.time, "NotOpenYet");

    clients.emplace(event.client_name, WAITING);
    queue.emplace_back(event.client_name);

    return EmptyEvent();
}


EventVariants ComputerClub::handle_sit(const ClientSatEvent& event) {
    if (!clients.contains(event.client_name)) return ErrorEvent(event.time, "ClientUnknown");
    if (tables.at(event.table_id - 1).is_occupied()) return ErrorEvent(event.time, "PlaceIsBusy");

    ClientStatus status = clients.at(event.client_name);

    if (status == GAMING) {
        for (Table& table : tables) {
            if (table.occupied_by() == event.client_name) table.free(event.time);
        }
    }

    tables.at(event.table_id - 1).occupy(event.time, event.client_name);

    return EmptyEvent();
}


EventVariants ComputerClub::handle_wait(const ClientWaitedEvent& event) {
    if (!clients.contains(event.client_name)) return ErrorEvent(event.time, "ClientUnknown");
    
    for (const Table& table : tables) {
        if (!table.is_occupied()) return ErrorEvent(event.time, "ICanWaitNoLonger!");
    }

    if (tables.size() < queue.size()) return ClientKickedEvent(event.time, event.client_name);

    return EmptyEvent();
}


EventVariants ComputerClub::handle_leave(const ClientLeftEvent& event) {
    if (!clients.contains(event.client_name)) return ErrorEvent(event.time, "ClientUnknown");

    ClientStatus status = clients.at(event.client_name);
    clients.erase(event.client_name);

    if (status == GAMING) {
        for (Table& table : tables) {
            if (table.occupied_by() == event.client_name) {

                table.free(event.time);
                return ClientDequeuedEvent(event.time, event.client_name, event.id);
            }
        }
    }

    if (status == WAITING) {
        for (std::deque<std::string>::iterator i = queue.begin(); i != queue.end();) {
            if (*i == event.client_name) queue.erase(i);
            i++;
        }
    }

    return EmptyEvent();
}


EventVariants ComputerClub::handle_kick(const ClientKickedEvent& event) {
    if (!clients.contains(event.client_name)) return ErrorEvent(event.time, "ClientUnknown");

    ClientStatus status = clients.at(event.client_name);
    clients.erase(event.client_name);

    if (status == GAMING) {
        for (Table& table : tables) {
            if (table.occupied_by() == event.client_name) table.free(event.time);
        }
    }

    if (status == WAITING) {
        for (std::deque<std::string>::iterator i = queue.begin(); i != queue.end();) {
            if (*i == event.client_name) queue.erase(i);
            i++;
        }
    }

    return EmptyEvent();
}


EventVariants ComputerClub::handle_dequeue(const ClientDequeuedEvent& event) {
    if (!clients.contains(event.client_name)) return ErrorEvent(event.time, "ClientUnknown");

    std::string name = queue.front();
    queue.pop_front();

    tables.at(event.table_id - 1).occupy(event.time, event.client_name);

    return EmptyEvent();
}
