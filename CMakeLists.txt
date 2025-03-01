cmake_minimum_required(VERSION 3.27)
project(BitCraft)

set(CMAKE_CXX_STANDARD 17)

include(./third_party/vendor_tools/vendor.cmake)
include(./vendor/openssl.cmake)

list(APPEND BITCRAFT_INCLUDES src)
#freetype
list(APPEND BITCRAFT_STATIC_VENDORS freetype)
list(APPEND BITCRAFT_INCLUDES third_party/freetype/include)
#harfbuzz
list(APPEND BITCRAFT_STATIC_VENDORS harfbuzz)
list(APPEND BITCRAFT_INCLUDES third_party/harfbuzz/src)
#asio
list(APPEND BITCRAFT_INCLUDES third_party/asio/asio/include)
#openssl
list(APPEND BITCRAFT_INCLUDES third_party/openssl/include)
#stb
list(APPEND BITCRAFT_INCLUDES third_party/stb)
#rectpack2D
list(APPEND BITCRAFT_INCLUDES third_party/rectpack2D/src)
#glm
list(APPEND BITCRAFT_INCLUDES third_party/glm)
#json
list(APPEND BITCRAFT_INCLUDES third_party/json/include)
#zlib
list(APPEND BITCRAFT_STATIC_VENDORS zlib)
list(APPEND BITCRAFT_INCLUDES third_party/zlib)

file(GLOB_RECURSE SRC_FILES
        src/base/*.*
        src/rendering/*.*)
list(APPEND BITCRAFT_FILES ${SRC_FILES})

if (ANDROID)
    file(GLOB_RECURSE PLATFORM_FILES src/platform/*.*)
    list(APPEND BITCRAFT_FILES ${PLATFORM_FILES})
endif ()

add_vendor_target(bitcraft-vendor STATIC_VENDORS ${BITCRAFT_STATIC_VENDORS} SHARED_VENDORS ${BITCRAFT_SHARED_VENDORS})
find_vendor_libraries(bitcraft-vendor STATIC BITCRAFT_VENDOR_STATIC_LIBRARIES SHARED BITCRAFT_VENDOR_SHARED_LIBRARIES)
list(APPEND BITCRAFT_STATIC_LIBS ${BITCRAFT_VENDOR_STATIC_LIBRARIES})
list(APPEND BITCRAFT_STATIC_LIBS ${OPENSSL_STATIC_LIBRARIES})
list(APPEND BITCRAFT_SHARED_LIBS ${BITCRAFT_VENDOR_SHARED_LIBRARIES})

list(APPEND BITCRAFT_DEPEND_TARGETS bitcraft-vendor)
list(APPEND BITCRAFT_DEPEND_TARGETS openssl-vendor)

if (ANDROID)
    add_library(bitcraft SHARED ${BITCRAFT_FILES})
else ()
    add_library(bitcraft STATIC ${BITCRAFT_FILES})
    merge_libraries_into(bitcraft ${BITCRAFT_STATIC_LIBS})
endif ()

add_dependencies(bitcraft ${BITCRAFT_DEPEND_TARGETS})
target_include_directories(bitcraft PUBLIC include PUBLIC ${BITCRAFT_INCLUDES})
target_link_libraries(bitcraft ${BITCRAFT_STATIC_LIBS} ${BITCRAFT_SHARED_LIBS})
target_compile_definitions(bitcraft PRIVATE ASIO_STANDALONE)