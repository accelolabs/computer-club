#include <fstream>
#include <iostream>
#include <stdexcept>
#include <variant>
#include <vector>

#include "model/Time.h"
#include "event/Events.h"
#include "event/EventHandler.h"
#include "parsing/ParseHelpers.h"


bool read_line(std::ifstream& file, std::string& line, std::size_t& li) {
    if (!std::getline(file, line)) return false;
    li++;

    return true;
}


void line_error(std::size_t& li) {
    throw std::invalid_argument("Error on line " + std::to_string(li) + '\n');
}


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Input file path required\n";
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 1;
    }


    std::string line;
    std::vector<std::string> args;
    std::size_t line_index = 0;

    std::string time_open_str;
    std::string time_close_str;
    int table_count;
    int price_rate;


    // get table_count
    if (!read_line(input_file, line, line_index)) line_error(line_index);
    get_args(line, args);
    
    if (args.size() != 1 || !is_int(args[0])) line_error(line_index);
    table_count = std::stoi(args[0]);
    
    args.clear();


    // get club schedule
    if (!read_line(input_file, line, line_index)) line_error(line_index);
    get_args(line, args);

    if (args.size() != 2 || !is_time(args[0]) || !is_time(args[1])) line_error(line_index);
    Time time_open(args[0]);
    Time time_close(args[1]);

    args.clear();


    // get price_rate
    if (!read_line(input_file, line, line_index)) line_error(line_index);
    get_args(line, args);

    if (args.size() != 1 || !is_int(args[0])) line_error(line_index);
    price_rate = std::stoi(args[0]);


    EventHandler handler({time_open, time_close, table_count, price_rate}, std::cout);


    handler(OpenClubEvent(time_open));


    while (read_line(input_file, line, line_index)) {
        if (line.empty()) continue;

        args.clear();
        get_args(line, args);

        if (args.size() < 2 || !is_time(args[0]) || !is_int(args[1])) line_error(line_index);

        Time event_time(args[0]);
        int event_id = std::stoi(args[1]);
        EventVariants event;


        try {
            switch (event_id) {
                case 1:
                    if (args.size() != 3) line_error(line_index);
                    event = ClientArrivedEvent(event_time, args[2]);
                    break;
                case 2:
                    if (args.size() != 4 || !is_int(args[3])) line_error(line_index);
                    event = ClientSatEvent(event_time, args[2], std::stoi(args[3]));
                    break;
                case 3:
                    if (args.size() != 3) line_error(line_index);
                    event = ClientWaitedEvent(event_time, args[2]);
                    break;
                case 4:
                    if (args.size() != 3) line_error(line_index);
                    event = ClientLeftEvent(event_time, args[2]);
                    break;
                default:
                    line_error(line_index);
            }

        } catch (...) {
            line_error(line_index);
        }

        std::visit(handler, event);

    }

    handler(CloseClubEvent(time_close));

    return 0;
}
