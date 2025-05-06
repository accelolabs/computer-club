#include "EventHandler.h"
#include "Events.h"
#include <variant>
#include <vector>


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
    std::vector<EventVariants> events = club.handle_close(event);

    for (const auto& event : events) std::visit(*this, event);

    print(event);
    
    events.clear();
    events = club.handle_tables_log();

    for (const auto& event : events) std::visit(*this, event);
}


void EventHandler::operator()(const TableLogEvent& event) {
    print(event);
}
