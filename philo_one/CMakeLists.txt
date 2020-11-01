cmake_minimum_required(VERSION 3.17)
project(philo_one C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(philo_one
        main.c
        philo.h
        printstr.c
        utils.c)
