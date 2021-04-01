cmake_minimum_required(VERSION 3.17)
project(SyllableBase)

set(SOURCE_FILES
        ../src/SyllableBase.cpp
        ../src/Dictionary.cpp
        ../src/Options.cpp
        )

add_library(SyllableBase ${SOURCE_FILES})

target_include_directories(SyllableBase PUBLIC include)