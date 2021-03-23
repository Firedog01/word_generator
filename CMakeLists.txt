cmake_minimum_required(VERSION 3.17)
project(generator_slow)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(res)


FILE(COPY res/dict.txt DESTINATION "${CMAKE_BINARY_DIR}/res")
FILE(COPY res/preset.txt DESTINATION "${CMAKE_BINARY_DIR}/res")