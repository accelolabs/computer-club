#pragma once

#include "Time.h"


enum ClientStatus {
    WAITING,
    GAMING
};


struct ComputerClubConfig {
    Time time_open;
    Time time_close;
    int table_count;
    int price_rate;
};
