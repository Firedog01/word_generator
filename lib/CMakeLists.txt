cmake_minimum_required(VERSION 3.17)
project(BazaSylab)

set(SOURCE_FILES
        ../src/SyllableBase.cpp
        ../src/Dictionary.cpp)

add_library(BazaSylab ${SOURCE_FILES})

target_include_directories(BazaSylab PUBLIC include)