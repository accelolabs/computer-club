#include "EventHandler.h"
#include "Events.h"
#include <variant>


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


void EventHandler::operator()(const QueuedClientSatEvent& event) {
    print(event);
}


void EventHandler::operator()(const ErrorEvent& event) {
    print(event);
}
