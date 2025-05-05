#pragma once

#include <map>
#include <string>
#include <vector>
#include <deque>

#include "Table.h"
#include "ClientStatus.h"
#include "../event/Events.h"


class ComputerClub {

private:

    int minutes_open;
    int minutes_close;

    std::vector<Table> tables;
    std::deque<std::string> queue;
    std::map<std::string, ClientStatus> clients;

public:

    ComputerClub(const Time& time_open, const Time& time_close) :
        minutes_open(time_open.get_total_minutes()),
        minutes_close(time_close.get_total_minutes())
    {}


    EventVariants handle_arrive(const ClientArrivedEvent& event);

    EventVariants handle_sit(const ClientSatEvent& event);

    EventVariants handle_wait(const ClientWaitedEvent& event);

    EventVariants handle_leave(const ClientLeftEvent& event);

    EventVariants handle_kick(const ClientKickedEvent& event);

    EventVariants handle_dequeue(const ClientDequeuedEvent& event);

};
