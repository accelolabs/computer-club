#include <iostream>

#include "EventHandler.h"


void EventHandler::operator()(const ClientArrivedEvent& event) {
    std::cout << event.id << std::endl;
}


void EventHandler::operator()(const ClientSatEvent& event) {
    std::cout << event.id << std::endl;
}


void EventHandler::operator()(const ClientWaitedEvent& event) {
    std::cout << event.id << std::endl;
}


void EventHandler::operator()(const ClientLeftEvent& event) {
    std::cout << event.id << std::endl;
}


void EventHandler::operator()(const ClientKickedEvent& event) {
    std::cout << event.id << std::endl;
}


void EventHandler::operator()(const QueuedClientSatEvent& event) {
    std::cout << event.id << std::endl;
}


void EventHandler::operator()(const ErrorEvent& event) {
    std::cout << event.id << std::endl;
}
