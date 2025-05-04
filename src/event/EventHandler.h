#pragma once

#include "Events.h"
#include "PrintHandler.h"


class EventHandler {

private:

    PrintHandler print;

public:

    void operator()(const ClientArrivedEvent& event);
    
    void operator()(const ClientSatEvent& event);
    
    void operator()(const ClientWaitedEvent& event);
    
    void operator()(const ClientLeftEvent& event);
    
    void operator()(const ClientKickedEvent& event);
    
    void operator()(const QueuedClientSatEvent& event);
    
    void operator()(const ErrorEvent& event);

};
