message(STATUS "Script executed start: building openssl")
set(CURRENT_SCRIPT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(MAC_OPENSSL_LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/../third_party/out/openssl/mac/lib)
set(ANDROID_OPENSSL_LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/../third_party/out/openssl/android/${ANDROID_ABI}/lib)

if (ANDROID)
    set(OPENSSL_PLATFORM "android")
    set(OPENSSL_LIB_PATH ${ANDROID_OPENSSL_LIB_PATH})
else ()
    set(OPENSSL_PLATFORM "mac")
    set(OPENSSL_LIB_PATH ${MAC_OPENSSL_LIB_PATH})
endif ()

# 使用 shell 脚本来构建 OpenSSL 静态库
add_custom_command(
        OUTPUT ${OPENSSL_LIB_PATH}/libssl.a ${OPENSSL_LIB_PATH}/libcrypto.a
        COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/openssl_build.sh ${CURRENT_SCRIPT_DIR} ${OPENSSL_PLATFORM} ${CMAKE_ANDROID_NDK}
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../third_party/openssl
        COMMENT "Building OpenSSL static libraries"
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/openssl_build.sh
)

list(APPEND OPENSSL_STATIC_LIBRARIES ${OPENSSL_LIB_PATH}/libssl.a)
list(APPEND OPENSSL_STATIC_LIBRARIES ${OPENSSL_LIB_PATH}/libcrypto.a)

# 定义一个自定义目标，表示构建 OpenSSL 静态库
add_custom_target(openssl-vendor ALL DEPENDS ${OPENSSL_STATIC_LIBRARIES} COMMENT "Generating openssl")