cmake_minimum_required(VERSION 3.16)

project(slot_engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(slot
    tests/main.cpp
    src/reel.cpp
    src/screen.cpp
    src/paytable.cpp
    src/spin_engine.cpp
    src/win_evaluator.cpp
    src/game_config.cpp
    src/slot_engine.cpp
)
