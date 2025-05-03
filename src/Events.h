#pragma once

#include <variant>


struct ClientArrivedEvent {
    int id = 1;
};


struct ClientSatEvent {
    int id = 1;
};


struct ClientWaitedEvent {
    int id = 3;
};


struct ClientLeftEvent {
    int id = 4;
};


struct ClientKickedEvent {
    int id = 11;
};


struct QueuedClientSatEvent {
    int id = 12;
};


struct ErrorEvent {
    int id = 13;
};


using EVENTS = std::variant<
    ClientArrivedEvent,
    ClientSatEvent,
    ClientWaitedEvent,
    ClientLeftEvent,
    ClientKickedEvent,
    QueuedClientSatEvent,
    ErrorEvent
>;
