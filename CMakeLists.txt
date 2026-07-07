cmake_minimum_required(VERSION 3.17)

project(Logger
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(Logger
    src/Logger.cpp
    src/ConsoleColor.cpp
)

target_include_directories(Logger
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(LoggerExample
    main.cpp
)

target_link_libraries(LoggerExample
    PRIVATE Logger
)