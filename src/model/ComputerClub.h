#pragma once

#include <vector>
#include "Table.h"


class ComputerClub {
private:

    std::vector<Table> tables;
    
    std::vector<std::string> queue;

public:

    bool at_tables(const std::string client_name) const;

    bool at_queue(const std::string client_name) const;

    bool at_club(const std::string client_name) const;

    bool has_tables() const;

    int tables_count() const;

    int queue_count() const;


    bool kick_client(const std::string client_name);

    bool queue_client(const std::string client_name);

    bool queue_sit_first();

    bool queue_sit(const std::string client_name);

};
