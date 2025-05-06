#pragma once

#include <variant>

#include "../model/Time.h"


struct EmptyEvent {

    int id = 0;


    EmptyEvent() {}

};


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


struct ClientDequeuedEvent {

    Time time;
    int id = 12;
    std::string client_name;
    int table_id;


    ClientDequeuedEvent(const Time& time, const std::string& client_name, int table_id) :
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


struct OpenClubEvent {

    Time time;
    int id = -1;


    OpenClubEvent(const Time& time) :
        time(time)
    {}

};


struct CloseClubEvent {

    Time time;
    int id = -2;


    CloseClubEvent(const Time& time) :
        time(time)
    {}

};


using EventVariants = std::variant<
    EmptyEvent,
    ClientArrivedEvent,
    ClientSatEvent,
    ClientWaitedEvent,
    ClientLeftEvent,
    ClientKickedEvent,
    ClientDequeuedEvent,
    ErrorEvent,
    OpenClubEvent,
    CloseClubEvent
>;
