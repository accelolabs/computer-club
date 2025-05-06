#pragma once

#include <ostream>

#include "Events.h"
#include "PrintHandler.h"
#include "../model/ComputerClub.h"
#include "../model/HelperModels.h"


class EventHandler {

private:

    ComputerClub club;

    PrintHandler print;

public:

    EventHandler(const ComputerClubConfig& config) :
        club(config),
        print(nullptr)
    {}

    EventHandler(const ComputerClubConfig& config, std::ostream& os) :
        club(config),
        print(os)
    {}


    void operator()(const EmptyEvent& event);

    void operator()(const ClientArrivedEvent& event);
    
    void operator()(const ClientSatEvent& event);
    
    void operator()(const ClientWaitedEvent& event);
    
    void operator()(const ClientLeftEvent& event);
    
    void operator()(const ClientKickedEvent& event);
    
    void operator()(const ClientDequeuedEvent& event);
    
    void operator()(const ErrorEvent& event);

    void operator()(const OpenClubEvent& event);

    void operator()(const CloseClubEvent& event);

};
