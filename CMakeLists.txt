cmake_minimum_required(VERSION 3.16)

project(MicromouseSimulator
    VERSION 1.0.0
    DESCRIPTION "Micromouse 2D Simulation Project"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MicromouseSimulator
    src/main.cpp
    src/app/Application.cpp
    src/maze/Maze.cpp
    src/robot/Robot.cpp
    src/sensor/WallSensor.cpp
    src/solver/PathSolver.cpp
    src/simulation/Simulator.cpp
    src/ui/ConsoleRenderer.cpp
    src/stats/Statistics.cpp
)

target_include_directories(MicromouseSimulator
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(MicromouseSimulator PRIVATE /W4)
else()
    target_compile_options(MicromouseSimulator PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()