# 015482FC-A4BD-4E1C-AE49-A30E5728D73A

# ========================================================================================================================================================================================================
#  CONFIGURATION
# ========================================================================================================================================================================================================

# Supported Platforms, Hardware, and Compilers - Used to include inactive files into supported IDEs #=====================================================================================================

SET (MK_GENERATE_LIST__COMPILER_NAMES "APPLE" "CLANG" "MSVC")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__COMPILER_NAMES)

SET (MK_GENERATE_LIST__HARDWARE_NAMES "C17_X64" "C17_ARM")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__HARDWARE_NAMES)

SET (MK_GENERATE_LIST__THREAD_NAMES "POSIX" "WINDOWS")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__THREAD_NAMES)

SET (MK_GENERATE_LIST__UNIVERSAL_NAMES "APPLE")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__UNIVERSAL_NAMES)

SET (MK_GENERATE_LIST__OS_NAMES "WINDOWS" "POSIX" "ANDROID")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__OS_NAMES)

SET (MK_GENERATE_LIST__DEVICE_NAMES "DESKTOP" "APPLE_MAC" "APPLE_IPHONE" "APPLE_TV" "APPLE_WATCH" "XB4" "PS5")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__DEVICE_NAMES)

SET (MK_GENERATE_LIST__GRAPHICS_NAMES "NONE" "REF" "DX12" "METAL" "VULKAN")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__GRAPHICS_NAMES)

SET (MK_GENERATE_LIST__AUDIO_NAMES "NONE" "XAUDIO2")
LIST (REMOVE_DUPLICATES MK_GENERATE_LIST__AUDIO_NAMES)

# LIBRARAY DEPENDENCY GROUPS =============================================================================================================================================================================

SET (_Ring_0___COMMON_LIBS "_Ring_0___TgS_COMMON" "_Ring_0___TgS_COLLISION" "_Ring_0___TgS_PARTITION")
SET (_Ring_2___COMMON_LIBS "_Ring_2___TgS_KERNEL" "_Ring_U___TgS_UTILITY")
SET (_Ring_3___COMMON_LIBS "_Ring_3___TgS_ANIMATION" "_Ring_3___TgS_INPUT" "_Ring_3___TgS_RENDER" "_Ring_3___TgS_SOUND")
SET (_Ring_4___COMMON_LIBS "_Ring_4___TgS_OBJECT" "_Ring_4___TgS_SCRIPT" "_Ring_4___TgS_SET")

SET (_TEIKITU_LIB__MP_SERVER    ${_Ring_0___COMMON_LIBS}            "_Ring_0___TgS_PATH-AI"             ${_Ring_2___COMMON_LIBS}            "_Ring_3___TgS_PHYSICS_MP_SERVER"   ${_Ring_4___COMMON_LIBS}
                                "_Ring_5___TgS_EXECUTE_MP_SERVER")

SET (_TEIKITU_LIB__MP_CLIENT    ${_Ring_0___COMMON_LIBS}            ${_Ring_2___COMMON_LIBS}            ${_Ring_3___COMMON_LIBS}            ${_Ring_4___COMMON_LIBS}            "_Ring_3___TgS_PHYSICS_MP_CLIENT"
                                "_Ring_4___TgS_EFFECT"              "_Ring_5___TgS_EXECUTE_MP_CLIENT"   )

SET (_TEIKITU_LIB__SP           ${_Ring_0___COMMON_LIBS}            ${_Ring_2___COMMON_LIBS}            ${_Ring_3___COMMON_LIBS}            "_Ring_3___TgS_PHYSICS_SP"          "_Ring_4___TgS_EFFECT"
                                ${_Ring_4___COMMON_LIBS}            "_Ring_5___TgS_EXECUTE_SP"          )


# ========================================================================================================================================================================================================
#  PACKAGES
# ========================================================================================================================================================================================================

# Required so that the final executable can find all the library dependencies
FIND_PACKAGE (libdeflate CONFIG REQUIRED GLOBAL)
FIND_PACKAGE (TIFF MODULE REQUIRED GLOBAL)
SET (ZLIB_ROOT "${MK_BUILD__EXTERNAL_INSTALL_DIRECTORY}")
SET (ZLIB_USE_STATIC_LIBS ON)
FIND_PACKAGE (ZLIB MODULE REQUIRED GLOBAL)
FIND_PACKAGE (zstd CONFIG REQUIRED GLOBAL)
FIND_PACKAGE (mimalloc CONFIG REQUIRED GLOBAL)

IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")
    FIND_PACKAGE (directx-headers CONFIG REQUIRED QUIET)
ENDIF ()
