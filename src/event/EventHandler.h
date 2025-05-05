#pragma once

#include "Events.h"
#include "PrintHandler.h"
#include <fstream>
#include <ostream>


class EventHandler {

private:

    PrintHandler print;

public:

    EventHandler() : print(nullptr) {}

    EventHandler(std::ostream& os) : print(os) {}


    void operator()(const ClientArrivedEvent& event);
    
    void operator()(const ClientSatEvent& event);
    
    void operator()(const ClientWaitedEvent& event);
    
    void operator()(const ClientLeftEvent& event);
    
    void operator()(const ClientKickedEvent& event);
    
    void operator()(const QueuedClientSatEvent& event);
    
    void operator()(const ErrorEvent& event);

};
