cmake_minimum_required(VERSION 3.17)
project(Philosophers C)

set(CMAKE_C_STANDARD 99)

add_executable(philo_two main.c philo.h utils.c printstr.c)