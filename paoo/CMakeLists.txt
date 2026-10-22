cmake_minimum_required(VERSION 3.10)

# Numele proiectului
project(paoo)

# Setarea standardului C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crearea executabilului pe baza fișierului sursă
add_executable(paoo main.cpp)