#include "PrintHandler.h"


void PrintHandler::operator()(const ClientArrivedEvent& event) {
    *output
        << event.time.as_string() << " "
        << event.id << " "
        << event.client_name << "\n";
}

void PrintHandler::operator()(const ClientSatEvent& event) {
    *output
        << event.time.as_string() << " "
        << event.id << " "
        << event.client_name << " "
        << event.table_id << "\n";
}

void PrintHandler::operator()(const ClientWaitedEvent& event) {
    *output
        << event.time.as_string() << " "
        << event.id << " "
        << event.client_name << "\n";
}

void PrintHandler::operator()(const ClientLeftEvent& event) {
    *output
        << event.time.as_string() << " "
        << event.id << " "
        << event.client_name << "\n";
}

void PrintHandler::operator()(const ClientKickedEvent& event) {
    *output
        << event.time.as_string() << " "
        << event.id << " "
        << event.client_name << "\n";
}

void PrintHandler::operator()(const QueuedClientSatEvent& event) {
    *output
        << event.time.as_string() << " "
        << event.id << " "
        << event.client_name << " "
        << event.table_id << "\n";
}

void PrintHandler::operator()(const ErrorEvent& event) {
    *output
        << event.time.as_string() << " "
        << event.id << " "
        << event.error_name << "\n";
}
