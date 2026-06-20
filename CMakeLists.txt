cmake_minimum_required(VERSION 3.16)
project(slot_engine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source fajlovi
set(SLOT_ENGINE_SOURCES
    src/reel.cpp
    src/screen.cpp
    src/paytable.cpp
    src/spin_engine.cpp
    src/win_evaluator.cpp
    src/game_config.cpp
    src/slot_engine.cpp
)

# Kreiraj STATIC biblioteku
add_library(slot_engine STATIC ${SLOT_ENGINE_SOURCES})

# Include direktorijum - KORISTI PUBLIC da bi se propagirao
target_include_directories(slot_engine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(slot_engine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Kreiraj testove SAMO ako je slot-engine glavni projekt
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(slot_engine_test tests/main.cpp)
    target_link_libraries(slot_engine_test slot_engine)
    target_include_directories(slot_engine_test
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    enable_testing()
    add_test(NAME slot_engine_test COMMAND slot_engine_test)
endif()
