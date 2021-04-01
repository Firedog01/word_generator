cmake_minimum_required(VERSION 3.17)
project(WordGen)

set(SOURCE_FILES
        main.cpp
        )

add_executable(WordGen ${SOURCE_FILES})

target_link_libraries(WordGen SyllableBase)