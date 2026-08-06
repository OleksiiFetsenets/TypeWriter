cmake_minimum_required(VERSION 3.16)
project(TypeWriter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES main.cpp
        TW.cpp
        TW.h
)

add_executable(TypeWriter ${SOURCE_FILES})
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(TypeWriter PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
