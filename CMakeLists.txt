cmake_minimum_required(VERSION 3.10)
project(Math)

set(CMAKE_CXX_STANDARD 17)

add_library(MathOperation Math.cpp)

add_executable(app main.cpp)

target_link_libraries(app MathOperation)

add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    -Werror
    ${SOURCES}
    ${HEADERS}
)