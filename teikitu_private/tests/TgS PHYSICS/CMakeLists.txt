cmake_minimum_required(VERSION 3.23)
cmake_policy(VERSION 3.23)
cmake_policy(SET CMP0015 NEW)
#    �Version�   5.21 | �GUID� AEEC8393-9780-4ECA-918D-E3E11F7E2744 */

CMAKE_PATH ( SET MK_BUILD_ROOT__MODULE_NAME "UNIT_TEST__PHYSICS" )
CMAKE_PATH ( SET MK_BUILD_MODULE__SRC_DIR NORMALIZE "${CMAKE_CURRENT_SOURCE_DIR}" )




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library unit test

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.c" )
TGS_ADD_HEADER_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] - Unit Test.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "~Unit Test" "${MK_BUILD_MODULE__SRC_DIR}/../TgS UNIT TEST/TgS Common [Unit Test] [Boot].c")


TGS_ADD_INCSRC_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics [Unit Test] - Internal.h")
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics [Link Test].c" )
TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "-" "-" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS Physics [Unit Test].c" )

TGS_ADD_SOURCE_FILE( exe_source_files exe_header_files "DX12" "${MK_BUILD__GRAPHICS_NAME}" "/" "${MK_BUILD_MODULE__SRC_DIR}/TgS (DX12) Physics [Unit Test].c" )




#PHYSICS




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#library platform specific files




# ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ #
#build library unit test
ADD_EXECUTABLE ("Unit_Test___Ring_3___TgS_PHYSICS" ${APP_TYPE} ${exe_source_files} ${exe_header_files})
TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY()
SET( PCH_INCLUDE_DEFAULT "TgS Physics [Unit Test] - Internal.h")
TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES( "Unit_Test___Ring_3___TgS_PHYSICS" "${MK_BUILD_MODULE__SRC_DIR}" "TgS Physics [Unit Test]" ${PCH_INCLUDE_DEFAULT} exe_source_files exe_header_files )

TARGET_LINK_LIBRARIES("Unit_Test___Ring_3___TgS_PHYSICS" PRIVATE ${_Ring_0___COMMON_LIBS} ${_Ring_2___COMMON_LIBS} ${_Ring_3___COMMON_LIBS} "_Ring_3___TgS_PHYSICS_SP")
