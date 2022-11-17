cmake_minimum_required(VERSION 3.23)
cmake_policy(VERSION 3.23)
cmake_policy(SET CMP0015 NEW)
#    »Version«   5.22 | »GUID« 7ECEAB43-40E4-4161-8F94-87AF31F5BA9A

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "KERNEL" )
CMAKE_PATH ( SET MK_BUILD_ROOT__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk" )
CMAKE_PATH ( SET MK_BUILD_MODULE__INC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${GIT_ROOT_PATH}/teikitu_private/src/TgS ${MK_BUILD_ROOT__MODULE_NAME}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Data.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Module.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - System.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [PCH].c")

TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File System.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File Job.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File IO.c")
TGS_ADD_SOURCE_FILE( lib_source_files lib_header_files "-" "-" "SDK/Source Files/File" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - File System - HDD.c")

TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel - Internal.h")

TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Constants.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Data.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Errors.TgS")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Ring 2 - Type.h")
TGS_ADD_HEADER_FILE( lib_source_files lib_sdk_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Kernel.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files

FOREACH (MK_LIST_ITEM__OS_NAME IN LISTS MK_GENERATE_LIST__OS_NAMES)
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Data.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Module.c" )
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Configuration.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Link Test.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - System.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Unit Test.c")
    TGS_ADD_SOURCE_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel [PCH].c")

    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Internal - Data.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Internal - Type.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Internal.h")

    TGS_ADD_HEADER_FILE( lib_os_source_files lib_sdk_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Constants.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_sdk_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel - Type.h")
    TGS_ADD_HEADER_FILE( lib_os_source_files lib_sdk_os_header_files "${MK_LIST_ITEM__OS_NAME}" ${MK_BUILD__OS_NAME} "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (${MK_LIST_ITEM__OS_NAME}) Kernel.h")

ENDFOREACH ()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal [EXT].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Internal.h")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Constants.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Data.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug [Console].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug [Geom-Text-UI].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Debug.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Module.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [DEVC].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [EXEC].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [HOST].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System [Context] [SWAP].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - System.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Unit Test.c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] [PCH].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Common].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Font] [ROM].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Shader].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Cube].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Image].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Volume].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [BMP].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [DDS].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [GIF].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [JPG].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [PNG].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [TGA].c")
TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource Storage" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource [Texture] [Load] [TIF].c")

TGS_ADD_SOURCE_FILE( lib_gpu_source_files lib_gpu_header_files "-" "-" "SDK/Source Files/Resource LIB" "${MK_BUILD_MODULE__SRC_DIR}/TgS Kernel [GPU] - Resource LIB [Common].c")

TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Constants.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [INC].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Constants].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Data].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Resource [HLSL] [Vertex].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] - Type.h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public" "${MK_BUILD_MODULE__INC_DIR}/TgS Kernel [GPU] [EXT].h")
TGS_ADD_HEADER_FILE( lib_gpu_source_files lib_sdk_gpu_header_files "-" "-" "Public" "${MK_BUILD_ROOT__INC_DIR}/TgS Kernel [GPU].h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Specialization DX12

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Constants.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Data.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Debug.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal - Type.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal.h")

TGS_ADD_INCSRC_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Inline Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Internal.inl")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Link Test.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Constants.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Debug [Geom-Text-UI].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Debug.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Data.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Module.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System.c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [DEVC].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [EXEC].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [HOST].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [SWAP].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Enumeration].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Select].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] [PCH].c")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Data Buffer].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Pipeline].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Resource" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - Resource [Texture].c")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12-WIN" "${MK_BUILD__GRAPHICS_NAME}-${MK_BUILD__OS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12-WIN) Kernel [GPU] - Module.c")

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU] - Constants.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU] - Type.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "Public" "${MK_BUILD_MODULE__INC_DIR}/TgS (DX12) Kernel [GPU].h")




TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Particle_00_PS_FX.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Particle_01_PS_FX.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_00_PS_P.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_01_PS_PC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_02_PS_PNC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_02I_PS_PNC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Geom_03_PS_PNC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Line_PS_PC.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UI_PS_UI.vs.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/VS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UI_Text_PS_UIT.vs.hlsl")

TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_FX.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UI.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UIG.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_UIT.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_P.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PN.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PC.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PCG.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_PNC.ps.hlsl")
TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files/PS" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Test_PNC.ps.hlsl")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Content/Shader Files" "${MK_BUILD_MODULE__SRC_DIR}/Standard_Debug_Common.hlsli")




TGS_SOURCE_APPEND_GNU_COMPILER_OPTION( "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Kernel [GPU] - System [Context] [HOST].c" "Wno-invalid-token-paste")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Specialization Vulkan (VLKN)

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "VLKN" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (VLKN) Kernel [GPU] - Internal.h")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "VLKN" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (VLKN) Kernel [GPU] [PCH].c")

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "VLKN-WIN" "${MK_BUILD__GRAPHICS_NAME}-${MK_BUILD__OS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (VLKN-WIN) Kernel [GPU] - Module.c")

TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "VLKN" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (VLKN) Kernel [GPU] - Constants.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - Reference STUB

TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel [GPU] [API].c")
TGS_ADD_SOURCE_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Source Files/Base" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel [GPU] [PCH].c")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "SDK/Header Files" "${MK_BUILD_MODULE__SRC_DIR}/TgS (REF) Kernel [GPU] - Internal.h")
TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_sdk_api_gpu_header_files "REF" "${MK_BUILD__GRAPHICS_NAME}" "Public/Header Files" "${MK_BUILD_MODULE__INC_DIR}/TgS (REF) Kernel [GPU] - Constants.h")




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
# GPU Library - DirectX Headers

FILE(GLOB_RECURSE children "${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/include/*")
FOREACH(child ${children})
    TGS_ADD_HEADER_FILE( lib_api_gpu_source_files lib_api_gpu_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "SDK/DirectX" "${child}")
ENDFOREACH()




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
ADD_LIBRARY("_Ring_2___TgS_KERNEL" STATIC ${lib_source_files} ${lib_header_files} ${lib_sdk_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Kernel - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( "_Ring_2___TgS_KERNEL" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [PCH]" ${PCH_INCLUDE_DEFAULT} lib_source_files lib_header_files lib_sdk_header_files)

ADD_LIBRARY("_Ring_2___TgS_KERNEL__OS" STATIC ${lib_os_source_files} ${lib_os_header_files} ${lib_sdk_os_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__OS")
SET( PCH_OS_INCLUDE_DEFAULT "TgS (${MK_BUILD__OS_NAME}) Kernel - Internal.h")
TGS_SET_STANDARD_LIBRARY_PROPERTIES( "_Ring_2___TgS_KERNEL__OS" "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__OS_NAME}) Kernel [PCH]" ${PCH_OS_INCLUDE_DEFAULT} lib_os_source_files lib_os_header_files lib_sdk_os_header_files)

SET(MK_BUILD__MODULE_GPU_LIB "_Ring_2___TgS_KERNEL__GPU")
IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    ADD_LIBRARY(${MK_BUILD__MODULE_GPU_LIB} STATIC ${lib_gpu_source_files} ${lib_gpu_header_files} ${lib_sdk_gpu_header_files})
    TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__GPU")
    SET( PCH_GPU_INCLUDE_DEFAULT "TgS Kernel [GPU] - Internal.h")
    TGS_SET_STANDARD_LIBRARY_PROPERTIES( ${MK_BUILD__MODULE_GPU_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS Kernel [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_gpu_source_files lib_gpu_header_files lib_sdk_gpu_header_files)

    TARGET_INCLUDE_DIRECTORIES(${MK_BUILD__MODULE_GPU_LIB} PUBLIC "${TIFF_INCLUDE_DIRS}")

    TARGET_LINK_LIBRARIES(${MK_BUILD__MODULE_GPU_LIB} INTERFACE ${TIFF_LIBRARIES} )
    TARGET_LINK_LIBRARIES(${MK_BUILD__MODULE_GPU_LIB} INTERFACE zstd::libzstd_static )
    TARGET_LINK_LIBRARIES(${MK_BUILD__MODULE_GPU_LIB} INTERFACE ${ZLIB_LIBRARIES} )
    TARGET_LINK_LIBRARIES(${MK_BUILD__MODULE_GPU_LIB} INTERFACE libdeflate::libdeflate_static )
ELSE () 
    ADD_CUSTOM_TARGET( ${MK_BUILD__MODULE_GPU_LIB} SOURCES ${lib_gpu_source_files} ${lib_gpu_header_files})
    SET_PROPERTY(TARGET ${MK_BUILD__MODULE_GPU_LIB} PROPERTY PROJECT_LABEL "${MK_BUILD__MODULE_GPU_LIB} (Inactive)")
ENDIF ()

SET(MK_BUILD__GRAPHICS_IMPL_LIB "_Ring_2___TgS_KERNEL__GPU__${MK_BUILD__GRAPHICS_NAME}")
IF (NOT "${MK_BUILD__GRAPHICS_NAME}" STREQUAL "NONE")
    ADD_LIBRARY(${MK_BUILD__GRAPHICS_IMPL_LIB} STATIC ${lib_api_gpu_source_files} ${lib_api_gpu_header_files} ${lib_sdk_api_gpu_header_files})
    TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY("__GPU__${MK_BUILD__GRAPHICS_NAME}")
    SET( PCH_GPU_INCLUDE_DEFAULT "TgS (${MK_BUILD__GRAPHICS_NAME}) Kernel [GPU] - Internal.h")
    TGS_SET_STANDARD_LIBRARY_PROPERTIES( ${MK_BUILD__GRAPHICS_IMPL_LIB} "${MK_BUILD_MODULE__SRC_DIR}" "TgS (${MK_BUILD__GRAPHICS_NAME}) Kernel [GPU] [PCH]" ${PCH_GPU_INCLUDE_DEFAULT} lib_api_gpu_source_files lib_api_gpu_header_files lib_sdk_api_gpu_header_files)
    TARGET_INCLUDE_DIRECTORIES(${MK_BUILD__GRAPHICS_IMPL_LIB} PRIVATE "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}")

ELSE ()
    ADD_CUSTOM_TARGET(${MK_BUILD__GRAPHICS_IMPL_LIB} SOURCES ${lib_api_gpu_source_files} ${lib_api_gpu_header_files})
    SET_PROPERTY(TARGET ${MK_BUILD__GRAPHICS_IMPL_LIB} PROPERTY PROJECT_LABEL "${MK_BUILD__GRAPHICS_IMPL_LIB} (Inactive)")
ENDIF()

IF ("${MK_BUILD__GRAPHICS_NAME}" STREQUAL "DX12")
    # DirectX Agile SDK
    TARGET_INCLUDE_DIRECTORIES(${MK_BUILD__GRAPHICS_IMPL_LIB} BEFORE INTERFACE "${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/include")
    SET_PROPERTY( TARGET ${MK_BUILD__GRAPHICS_IMPL_LIB} PROPERTY IMPORTED_LOCATION 
        ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/D3D12Core.dll;
        ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/d3d12SDKLayers.dll
    )

    # DirectX Headers
    TARGET_LINK_LIBRARIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PUBLIC Microsoft::DirectX-Headers)
    TARGET_LINK_LIBRARIES (${MK_BUILD__GRAPHICS_IMPL_LIB} PUBLIC Microsoft::DirectX-Guids)
    
    TARGET_COMPILE_DEFINITIONS (${MK_BUILD__GRAPHICS_IMPL_LIB} PUBLIC USING_DIRECTX_HEADERS)

ENDIF ()
#ADD_LIBRARY("_Ring_X___TgS_KERNEL__FILE_TEST__" STATIC ${lib_api_gpu_source_files} ${lib_api_gpu_header_files} ${lib_gpu_source_files} ${lib_gpu_header_files} ${lib_os_source_files} ${lib_os_header_files} ${lib_source_files} ${lib_header_files})