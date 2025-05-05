#include <iostream>
#include <vector>
#include "src/event/EventHandler.h"
#include "src/event/Events.h"




int main(int, char**){
    std::vector<EVENTS> events;
    events.emplace_back(ClientArrivedEvent(Time("01:44"), "Linus"));
    events.emplace_back(ClientArrivedEvent(Time("01:45"), "Marvin"));
    events.emplace_back(ClientArrivedEvent(Time("02:39"), "Terry"));
    events.emplace_back(ClientArrivedEvent(Time("04:04"), "Garry"));
    events.emplace_back(ClientArrivedEvent(Time("05:59"), "Daniel"));

    EventHandler handler(std::cout);
    for (const auto& event : events) {
        std::visit(handler, event);
    }

    return 0;
}
