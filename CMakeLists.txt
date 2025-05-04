cmake_minimum_required(VERSION 3.10.0)
project(computer-club VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable("${CMAKE_PROJECT_NAME}" main.cpp)
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE src/parsing/ParseHelpers.cpp)
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE src/model/Time.cpp)
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE src/model/ComputerClub.cpp)
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE src/event/EventHandler.cpp)
