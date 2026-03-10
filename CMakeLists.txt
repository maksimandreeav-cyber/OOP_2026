cmake_minimum_required(VERSION 3.20)

project(FractionTest)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(FRACTION_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Fraction.cpp
)

set(FRACTION_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Fraction.h
)

set(APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_library(Fraction STATIC ${FRACTION_SOURCES})
set_property(TARGET Fraction PROPERTY CXX_STANDARD 20)
target_include_directories(Fraction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(Fraction PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

add_executable(${CMAKE_PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} Fraction)

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)

add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    -Werror
    ${SOURCES}
    ${HEADERS}
)