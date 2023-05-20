cmake_minimum_required(VERSION 3.15)
project(DIVEUP)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics)

include_directories(include)

set(SOURCES src/main.cpp
            src/diveup.cpp
            src/states/game-state.cpp
            src/states/splashscreen-state.cpp
            src/states/gameover-state.cpp
            src/states/playing-state.cpp
            src/objects/visible-object.cpp
            src/objects/visible-object-manager.cpp
            src/objects/gui/splashscreen.cpp
)

add_executable(DIVEUP ${SOURCES})

target_link_libraries(DIVEUP sfml-graphics)

