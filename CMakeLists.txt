cmake_minimum_required(VERSION 3.17)
project(generator_slow)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(res)

set(SOURCE_FILES
        src/main.cpp
        )

add_executable(WordGen ${SOURCE_FILES})

target_link_libraries(WordGen SyllableBase)