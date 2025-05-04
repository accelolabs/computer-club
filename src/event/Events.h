#pragma once

#include <variant>

#include "../model/Time.h"


struct ClientArrivedEvent {
    
    Time time;

    int id = 1;

    std::string client_name;


    ClientArrivedEvent(const Time& time, const std::string& client_name) :
        time(time),
        client_name(client_name)
    {}

};


struct ClientSatEvent {
    
    Time time;

    int id = 1;

    std::string client_name;

    int table_id;


    ClientSatEvent(const Time& time, const std::string& client_name, int table_id) :
        time(time),
        client_name(client_name),
        table_id(table_id)
    {}

};


struct ClientWaitedEvent {
    
    Time time;

    int id = 3;

    std::string client_name;


    ClientWaitedEvent(const Time& time, const std::string& client_name) :
        time(time),
        client_name(client_name)
    {}

};


struct ClientLeftEvent {
    
    Time time;

    int id = 4;

    std::string client_name;


    ClientLeftEvent(const Time& time, const std::string& client_name) :
        time(time),
        client_name(client_name)
    {}

};


struct ClientKickedEvent {
    
    Time time;

    int id = 11;

    std::string client_name;


    ClientKickedEvent(const Time& time, const std::string& client_name) :
        time(time),
        client_name(client_name)
    {}

};


struct QueuedClientSatEvent {
    
    Time time;

    int id = 12;

    std::string client_name;

    int table_id;


    QueuedClientSatEvent(const Time& time, const std::string& client_name, int table_id) :
        time(time),
        client_name(client_name),
        table_id(table_id)
    {}

};


struct ErrorEvent {
    
    Time time;

    int id = 13;

    std::string error_name;


    ErrorEvent(const Time& time, const std::string& error_name) :
        time(time),
        error_name(error_name)
    {}

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
