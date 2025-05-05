#include "EventHandler.h"
#include "Events.h"


void EventHandler::operator()(const ClientArrivedEvent& event) {
    print(event);
}


void EventHandler::operator()(const ClientSatEvent& event) {
    print(event);
}


void EventHandler::operator()(const ClientWaitedEvent& event) {
    print(event);
}


void EventHandler::operator()(const ClientLeftEvent& event) {
    print(event);
}


void EventHandler::operator()(const ClientKickedEvent& event) {
    print(event);
}


void EventHandler::operator()(const QueuedClientSatEvent& event) {
    print(event);
}


void EventHandler::operator()(const ErrorEvent& event) {
    print(event);
}
