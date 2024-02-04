cmake_minimum_required(VERSION 3.27)
project(judger)

set(CMAKE_CXX_STANDARD 20)

add_executable(judger main.cpp
        Robot.h
        Solider.cpp
        Solider.h
        Def.h
        Engineer.cpp
        Engineer.h
        Manager.cpp
        Manager.h
        Command.h)
