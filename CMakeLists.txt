cmake_minimum_required(VERSION 3.20)

project(ContainerTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

set(LIB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Container.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Set.h
)

add_library(container_lib INTERFACE ${LIB_HEADERS})

target_include_directories(container_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(container_lib PROPERTIES CXX_STANDARD 20)
target_compile_options(container_lib INTERFACE -Wall -Wextra -Werror -Wpedantic)

set(APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/build/main.cpp 
)

add_executable(${CMAKE_PROJECT_NAME} ${APP_SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE container_lib)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(
    clang-format
    COMMAND clang-format
    --dry-run
    --Werror
    ${SOURCES}
    ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    format-fix
    COMMAND clang-format
    -i
    ${SOURCES}
    ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
