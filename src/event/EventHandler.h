#pragma once

#include <ostream>

#include "Events.h"
#include "PrintHandler.h"
#include "../model/ComputerClub.h"


class EventHandler {

private:

    ComputerClub club;

    PrintHandler print;

public:

    EventHandler(const Time& time_open, const Time& time_close) :
        club(time_open, time_close),
        print(nullptr)
    {}

    EventHandler(const Time& time_open, const Time& time_close, std::ostream& os) :
        club(time_open, time_close),
        print(os)
    {}


    void operator()(const ClientArrivedEvent& event);
    
    void operator()(const ClientSatEvent& event);
    
    void operator()(const ClientWaitedEvent& event);
    
    void operator()(const ClientLeftEvent& event);
    
    void operator()(const ClientKickedEvent& event);
    
    void operator()(const QueuedClientSatEvent& event);
    
    void operator()(const ErrorEvent& event);

};
