#include "EventHandler.h"
#include "Events.h"
#include <variant>


void EventHandler::operator()(const EmptyEvent& event) {}

void EventHandler::operator()(const ClientArrivedEvent& event) {
    print(event);

    std::visit(*this, club.handle_arrive(event));
}


void EventHandler::operator()(const ClientSatEvent& event) {
    print(event);

    std::visit(*this, club.handle_sit(event));
}


void EventHandler::operator()(const ClientWaitedEvent& event) {
    print(event);

    std::visit(*this, club.handle_wait(event));
}


void EventHandler::operator()(const ClientLeftEvent& event) {
    print(event);

    std::visit(*this, club.handle_leave(event));
}


void EventHandler::operator()(const ClientKickedEvent& event) {
    print(event);

    std::visit(*this, club.handle_kick(event));
}


void EventHandler::operator()(const ClientDequeuedEvent& event) {
    print(event);

    std::visit(*this, club.handle_dequeue(event));
}


void EventHandler::operator()(const ErrorEvent& event) {
    print(event);
}

void EventHandler::operator()(const OpenClubEvent& event) {
    print(event);
}

void EventHandler::operator()(const CloseClubEvent& event) {
    print(event);

    // std::visit(*this, for in club.handle_close(event));
}

void EventHandler::operator()(const TableLogEvent& event) {
    print(event);
}
