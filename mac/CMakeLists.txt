cmake_minimum_required(VERSION 3.27)
project(BitCraft-mac)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit")

set(BITCRAFT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../)
add_subdirectory(${BITCRAFT_DIR} EXCLUDE_FROM_ALL build)
include_directories(${BITCRAFT_DIR}/src)

list(APPEND BITCRAFT_INCLUDES vendor/glfw/mac/include)

add_executable(bitcraft-mac main.cpp)

#list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/vendor/libpag/mac/arm64/libMcProxy.a)
list(APPEND libs bitcraft)
list(APPEND libs ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/mac/arm64/libmac.a)

target_link_libraries(bitcraft-mac PRIVATE ${libs})
target_include_directories(bitcraft-mac PUBLIC include PRIVATE ${BITCRAFT_INCLUDES})
