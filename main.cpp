#include <iostream>
#include <vector>
#include "src/event/EventHandler.h"
#include "src/event/Events.h"
#include "src/model/HelperModels.h"



int main(int, char**){
    std::vector<EventVariants> events;
    events.emplace_back(ClientArrivedEvent(Time("01:44"), "Linus"));
    events.emplace_back(ClientArrivedEvent(Time("01:45"), "Marvin"));
    events.emplace_back(ClientArrivedEvent(Time("02:39"), "Terry"));
    events.emplace_back(ClientWaitedEvent(Time("04:04"), "Terry"));
    events.emplace_back(ClientArrivedEvent(Time("05:59"), "Daniel"));

    ComputerClubConfig config {
        Time("02:00"),
        Time("05:00"),
        3,
        10
    };


    EventHandler handler(
        config,
        std::cout
    );
    
    for (const auto& event : events) {
        std::visit(handler, event);
    }

    return 0;
}
