cmake_minimum_required(VERSION 3.20)

project(BasePerson)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

set(PERSONS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Person.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Student.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Teacher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DepartmentHead.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector.cpp
)

set(PERSONS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Persons.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector.h
)

set(APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/App.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp
)
set(APP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.h
)

add_library(Persons STATIC ${PERSONS_SOURCES})
set_property(TARGET Persons PROPERTY CXX_STANDARD 20)
target_include_directories(Persons PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(Persons PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

add_executable(${CMAKE_PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} Persons)

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