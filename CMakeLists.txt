cmake_minimum_required(VERSION 3.20)
project(QuickSort CXX)


add_subdirectory(src/Alg)

set(SOURCES
    src/main.cpp
    src/Tests.cpp
)

add_executable(QuickSort ${SOURCES})

target_include_directories(QuickSort PRIVATE src/Alg)

target_link_libraries(QuickSort PRIVATE Alg)