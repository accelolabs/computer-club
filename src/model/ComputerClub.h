#pragma once

#include <map>
#include <string>
#include <vector>
#include <deque>

#include "Table.h"
#include "HelperModels.h"
#include "../event/Events.h"


class ComputerClub {

private:

    int minutes_open;
    int minutes_close;

    std::vector<Table> tables;
    std::deque<std::string> queue;
    std::map<std::string, ClientStatus> clients;

public:

    ComputerClub(const ComputerClubConfig& config);


    EventVariants handle_arrive(const ClientArrivedEvent& event);

    EventVariants handle_sit(const ClientSatEvent& event);

    EventVariants handle_wait(const ClientWaitedEvent& event);

    EventVariants handle_leave(const ClientLeftEvent& event);

    EventVariants handle_kick(const ClientKickedEvent& event);

    EventVariants handle_dequeue(const ClientDequeuedEvent& event);

    std::vector<EventVariants> handle_close(const CloseClubEvent& event);

    std::vector<EventVariants> handle_tables_log();

private:

    bool remove_gaming_client(const Time& time, const std::string& client_name);

    bool remove_waiting_client(const std::string& client_name);

};
