cmake_minimum_required(VERSION 3.20)

project(Polinom)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(POLINOM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Polynomial.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Term.cpp
)

set(POLINOMS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Polynomial.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Term.h
)

set(APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/build/main.cpp
)
set(APP_HEADERS)

set(ALL_SOURCES ${POLINOM_SOURCES} ${APP_SOURCES})
set(ALL_HEADERS ${POLINOMS_HEADERS} ${APP_HEADERS})

add_library(Polinoms STATIC ${POLINOM_SOURCES})
set_property(TARGET Polinoms PROPERTY CXX_STANDARD 20)
target_include_directories(Polinoms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(Polinoms PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

add_executable(${CMAKE_PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} Polinoms)

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)

add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    --Werror
    ${ALL_SOURCES}
    ${ALL_HEADERS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
