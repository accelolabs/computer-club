#include <iostream>
#include <vector>
#include "src/event/EventHandler.h"
#include "src/event/Events.h"
#include "src/model/HelperModels.h"



int main(int, char**){
    std::vector<EventVariants> events;
    events.emplace_back(OpenClubEvent(Time("02:00")));
    events.emplace_back(ClientArrivedEvent(Time("01:44"), "Linus"));
    events.emplace_back(ClientArrivedEvent(Time("01:45"), "Marvin"));
    events.emplace_back(ClientArrivedEvent(Time("02:39"), "Terry"));
    events.emplace_back(ClientSatEvent(Time("02:39"), "Terry", 3));
    events.emplace_back(ClientSatEvent(Time("02:40"), "Terry", 2));
    events.emplace_back(ClientArrivedEvent(Time("05:59"), "Daniel"));
    events.emplace_back(CloseClubEvent(Time("05:00")));

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
