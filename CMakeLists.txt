cmake_minimum_required(VERSION 3.15)
project(DIVEUP)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics)
find_package(SFML 2.5.1 COMPONENTS audio)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

include_directories(include)
include_directories(lib)

set(SOURCES src/main.cpp
            src/diveup.cpp
            src/states/game-state.cpp
            src/states/splashscreen-state.cpp
            src/states/gameover-state.cpp
            src/states/playing-state.cpp
            src/states/nextlevel-state.cpp
            src/states/debug-state.cpp
            src/objects/visible-object.cpp
            src/objects/visible-object-manager.cpp
            src/objects/gui/splashscreen.cpp
            src/objects/gui/gameoverscreen.cpp
            src/objects/gui/newgame-button.cpp
            src/objects/gui/exit-button.cpp
            src/objects/gui/playagain-button.cpp
            src/objects/gui/nextlevel-button.cpp
            src/objects/gui/aircounter.cpp
            src/objects/gui/nextlevel.cpp
            src/objects/entities/bubble.cpp
            src/objects/entities/field.cpp
            src/objects/entities/diver.cpp
            src/objects/entities/cliff.cpp
            src/objects/entities/finishline.cpp
            src/objects/entities/triangle.cpp
            lib/collision.cpp
            lib/Collision.cpp
            lib/music-manager.cpp
)

add_executable(DIVEUP ${SOURCES})

target_link_libraries(DIVEUP sfml-graphics sfml-audio)


