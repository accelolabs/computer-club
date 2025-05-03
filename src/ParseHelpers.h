#pragma once

#include <cstddef>
#include <string>
#include <vector>


// Get arguments separated by space as an array of strings from string
std::size_t get_args(const std::string& str, std::vector<std::string>& vec);


// Check if string is time in XX:XX format
bool is_time(const std::string& str);


// Check if string is an unsingned integer
bool is_int(const std::string& str);

