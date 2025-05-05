#pragma once

#include <memory>
#include "Events.h"


class PrintHandler {

private:

    std::ostream* output;

public:

    PrintHandler(std::nullptr_t) : output(nullptr) {}

    PrintHandler(std::ostream& os) : output(&os) {}


    void operator()(const ClientArrivedEvent& event);
    
    void operator()(const ClientSatEvent& event);
    
    void operator()(const ClientWaitedEvent& event);
    
    void operator()(const ClientLeftEvent& event);
    
    void operator()(const ClientKickedEvent& event);
    
    void operator()(const QueuedClientSatEvent& event);

    void operator()(const ErrorEvent& event);

};
