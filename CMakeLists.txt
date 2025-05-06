cmake_minimum_required(VERSION 3.10.0)
project(computer-club VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(computer_club_lib
    src/parsing/ParseHelpers.cpp
    src/model/Time.cpp
    src/model/Table.cpp
    src/model/ComputerClub.cpp
    src/event/PrintHandler.cpp
    src/event/EventHandler.cpp
)

target_include_directories(computer_club_lib PUBLIC ${PROJECT_SOURCE_DIR}/src)


add_executable("${CMAKE_PROJECT_NAME}" main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE computer_club_lib)

enable_testing()
add_subdirectory(test)
