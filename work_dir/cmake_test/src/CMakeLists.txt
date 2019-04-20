project(cmake_test)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB CSRC "*.c")

add_definitions(-Wall -O2)

add_executable(${PROJECT_NAME} ${CSRC})

target_link_libraries(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

