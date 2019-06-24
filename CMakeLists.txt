cmake_minimum_required(VERSION 3.0)
project(X)

#headers dirs
list (APPEND X_HEADERS "src/headers")

#src
list (APPEND X_SOURCES "src/headers/CMain.h")
list (APPEND X_SOURCES "src/sources/CMain.cpp")
list (APPEND X_SOURCES "src/main.cpp")

include_directories(${X_HEADERS})

add_executable(red_alert ${X_SOURCES})
