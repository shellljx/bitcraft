cmake_minimum_required(VERSION 3.27)
project(BitCraft-linux)
set(CMAKE_CXX_STANDARD 17)

set(BITCRAFT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
add_subdirectory(${BITCRAFT_DIR} EXCLUDE_FROM_ALL build)
include_directories(${BITCRAFT_DIR}/src)

list(APPEND BITCRAFT_INCLUDES vendor/glfw/mac/include)

add_executable(bitcraft-linux main.cpp)

#list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libpag/mac/arm64/libMcProxy.a)
list(APPEND libs bitcraft)
list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/mac/arm64/libmac.a)

target_link_libraries(bitcraft-linux PRIVATE ${libs})
target_include_directories(bitcraft-linux PUBLIC include PRIVATE ${BITCRAFT_INCLUDES})
