#include <algorithm>
#include <string>
#include <vector>

#include "ComputerClub.h"
#include "HelperModels.h"


ComputerClub::ComputerClub(const ComputerClubConfig& config) {
    for (int id = 1; id <= config.table_count; ++id) tables.emplace_back(id, config.price_rate);

    minutes_open = config.time_open.get_total_minutes();
    minutes_close = config.time_close.get_total_minutes();
}


EventVariants ComputerClub::handle_arrive(const ClientArrivedEvent& event) {
    if (clients.contains(event.client_name)) return ErrorEvent(event.time, "YouShallNotPass");
    if (event.time.get_total_minutes() < minutes_open) return ErrorEvent(event.time, "NotOpenYet");
    if (event.time.get_total_minutes() > minutes_close) return ErrorEvent(event.time, "NotOpenYet");

    clients.insert_or_assign(event.client_name, ClientStatus::WAITING);
    queue.emplace_back(event.client_name);

    return EmptyEvent();
}


EventVariants ComputerClub::handle_sit(const ClientSatEvent& event) {
    if (!clients.contains(event.client_name)) return ErrorEvent(event.time, "ClientUnknown");
    if (tables.at(event.table_id - 1).is_occupied()) return ErrorEvent(event.time, "PlaceIsBusy");

    ClientStatus status = clients.at(event.client_name);

    if (status == ClientStatus::GAMING) {
        for (Table& table : tables) {
            if (table.occupied_by() == event.client_name) table.free(event.time);
        }
    }

    clients.insert_or_assign(event.client_name, ClientStatus::GAMING);
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

    if (status == ClientStatus::GAMING) {
        for (Table& table : tables) {
            if (table.occupied_by() == event.client_name) {

                table.free(event.time);
                return ClientDequeuedEvent(event.time, event.client_name, event.id);
            }
        }
    }

    if (status == ClientStatus::WAITING) {
        for (std::deque<std::string>::iterator it = queue.begin(); it != queue.end();) {
            if (*it == event.client_name) {
                queue.erase(it);
                break;
            }

            it++;
        }
    }

    return EmptyEvent();
}


EventVariants ComputerClub::handle_kick(const ClientKickedEvent& event) {
    if (!clients.contains(event.client_name)) return ErrorEvent(event.time, "ClientUnknown");

    ClientStatus status = clients.at(event.client_name);
    clients.erase(event.client_name);

    if (status == ClientStatus::GAMING) {
        for (Table& table : tables) {
            if (table.occupied_by() == event.client_name) table.free(event.time);
        }
    }

    if (status == ClientStatus::WAITING) {
        for (std::deque<std::string>::iterator it = queue.begin(); it != queue.end();) {
            if (*it == event.client_name) {
                queue.erase(it);
                break;
            }

            it++;
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


std::vector<EventVariants> ComputerClub::handle_close(const CloseClubEvent& event) {
    std::vector<std::string> clients_sorted;
    clients_sorted.reserve(clients.size());

    for (std::map<std::string, ClientStatus>::iterator it = clients.begin(); it != clients.end(); ++it) {
        clients_sorted.push_back(it -> first);
    }

    std::sort(
        clients_sorted.begin(),
        clients_sorted.end(),
        [](const std::string& a, const std::string& b){ return a > b; }
    );

    std::vector<EventVariants> result;

    for (const std::string& client_name: clients_sorted) {
        result.emplace_back(ClientKickedEvent(event.time, client_name));
    }

    return result;
}


std::vector<EventVariants> ComputerClub::handle_tables_log() {
    std::vector<EventVariants> result;

    for (const Table& table: tables) {
        result.emplace_back(TableLogEvent(Time(table.get_total_minutes()), table.get_id(), table.get_revenue()));
    }

    return result;
}

