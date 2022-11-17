# 015482FC-A4BD-4E1C-AE49-A30E5728D73A

INCLUDE (CMakeParseArguments)
INCLUDE (CMakePrintHelpers)
INCLUDE (GNUInstallDirs) # Introduce variables: CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_BINDIR, CMAKE_INSTALL_INCLUDEDIR
INCLUDE (CMakePackageConfigHelpers)
INCLUDE (GenerateExportHeader)

##########################################################################################################################################################################################################
MACRO(SET_APPEND_GNU_COMPILER_OPTION existing_flags initization_values) 
    SET (${existing_flags} ${${initization_values}})
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " -${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_GNU_COMPILER_OPTION existing_flags) 
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " -${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_GNU_DISABLE_WARNING existing_flags) 
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " -Wno-${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(SET_APPEND_MSVC_COMPILER_OPTION existing_flags initization_values) 
    SET (${existing_flags} ${${initization_values}})
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " /${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_MSVC_COMPILER_OPTION existing_flags) 
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " /${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(APPEND_MSVC_DISABLE_WARNING existing_flags) 
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                STRING (APPEND ${existing_flags} " /Wd${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(TGS_SOURCE_APPEND_GNU_COMPILER_OPTION source_file) 
    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                SET_PROPERTY(SOURCE ${source_file} APPEND_STRING PROPERTY COMPILE_FLAGS " -${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
MACRO(TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION source_file) 
    IF (MK_COMPILER_FRONTEND__MSVC)
        FOREACH (OPTION IN ITEMS ${ARGN})
            IF (NOT ${OPTION} STREQUAL "")
                SET_PROPERTY(SOURCE ${source_file} APPEND_STRING PROPERTY COMPILE_FLAGS " /${OPTION}")
            ENDIF ()
        ENDFOREACH ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# Dump out all cmake variables that match a regex
function(dump_cmake_variables)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        if (ARGV0)
            unset(MATCHED)

            #case sensitive match
            # string(REGEX MATCH ${ARGV0} MATCHED ${_variableName})
            #
            #case insenstitive match
            string( TOLOWER "${ARGV0}" ARGV0_lower )
            string( TOLOWER "${_variableName}" _variableName_lower )
            string(REGEX MATCH ${ARGV0_lower} MATCHED ${_variableName_lower})

            if (NOT MATCHED)
                continue()
            endif()
        endif()
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endfunction()


##########################################################################################################################################################################################################
# Determine the appropriate object (intermediate) directory for the current module (CMakeFile)
MACRO(TGS_GET_MODULE_OBJECT_OUTPUT_DIRECTORY) 
    #CMAKE_PATH ( GET CMAKE_SOURCE_DIR PARENT_PATH PROJECT_ROOT_DIR )
    #CMAKE_PATH ( GET MODULE_PATH_ROOT PARENT_PATH MODULE_TEST_PATH )

    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${PROJECT_ROOT_DIR} -- ${MODULE_PATH_ROOT} -- ${MODULE_TEST_PATH}" )

    # Assuming that the directory containing the cmakelists.txt is the module name, determine the folder name and use it for the module name
    CMAKE_PATH ( GET CMAKE_CURRENT_LIST_DIR PARENT_PATH MODULE_PATH_ROOT ) # Used to determine the module name
    FILE ( RELATIVE_PATH MODULE_NAME ${MODULE_PATH_ROOT} ${CMAKE_CURRENT_LIST_DIR} )
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${MODULE_NAME}" )

    # Add the relative path from project root this cmakelist for the object directory.
    CMAKE_PATH ( SET CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY NORMALIZE ${CMAKE_OBJECT_OUTPUT_DIRECTORY})
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}" )
    FILE ( RELATIVE_PATH EXTRA_PATH_SEGMENT ${GIT_ROOT_PATH} ${CMAKE_CURRENT_LIST_DIR} )
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${EXTRA_PATH_SEGMENT}" )
    SET ( CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}${EXTRA_PATH_SEGMENT}${ARGN}/ )
    #MESSAGE( STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}" )

    IF (NOT EXISTS ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
        FILE (MAKE_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
        MESSAGE( STATUS "Created directory: ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY}")
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_FILE_TO_IDE source_files header_files test_assigned test_current file)
    CMAKE_PARSE_ARGUMENTS (TGS_ADD_FILE_TO_IDE "" "IDE_PATH" "" ${ARGN} )
    #MESSAGE("${source_files}")
    #MESSAGE("${TGS_ADD_FILE_TO_IDE_IDE_PATH}")
    #MESSAGE("${file}")
    #MESSAGE(TEST: ${test_current} ${test_assigned})

    # Add the file to the correct list for compilation
    IF ((${test_current} STREQUAL ${test_assigned}))
        SET (${source_files} ${${source_files}} "${file}")

    ELSEIF (MK_IDE__INCLUDE_NON_SOURCE_FILES)
        SET (${header_files} ${${header_files}} "${file}")
        SET_PROPERTY(SOURCE ${file} PROPERTY HEADER_FILE_ONLY TRUE)

    ENDIF ()

    # Assign an IDE path (folder structure)
    IF (TGS_ADD_FILE_TO_IDE_IDE_PATH AND NOT ${TGS_ADD_FILE_TO_IDE_IDE_PATH} STREQUAL "")
        STRING (REPLACE "/" "\\" IDE_PATH_FIXED ${TGS_ADD_FILE_TO_IDE_IDE_PATH})
        #MESSAGE("${IDE_PATH_FIXED}")

        IF (MK_IDE__INCLUDE_NON_SOURCE_FILES AND NOT (${test_current} STREQUAL ${test_assigned}))
            SET (IDE_PATH_FIXED "${IDE_PATH_FIXED}\\${test_assigned} (Inactive)")
        ENDIF ()
        #MESSAGE("${IDE_PATH_FIXED}")

        SOURCE_GROUP ("${IDE_PATH_FIXED}" FILES "${file}")

    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_SOURCE_FILE source_files header_files test_assigned test_current ide_path file)
    IF (EXISTS ${file})
        TGS_ADD_FILE_TO_IDE(${source_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
        IF ((${test_current} STREQUAL ${test_assigned}))
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.c)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.c)
        ELSE ()
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
        ENDIF ()
    ELSE ()
        MESSAGE("FILE DOES NOT EXIST: " ${file})
    ENDIF ()
ENDMACRO ()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_INCSRC_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY HEADER_FILE_ONLY TRUE)
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HEADER_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_EXPLICIT_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY XCODE_LAST_KNOWN_FILE_TYPE sourcecode.c.h)
            SET_PROPERTY(SOURCE ${file} PROPERTY  HEADER_FILE_ONLY TRUE)
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_CMAKE_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO()

##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HLSL_FILE_AND_COMPILE_TO_HEADER source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            GET_FILENAME_COMPONENT (FILE_NAME_E "${file}" NAME_WLE)
            GET_FILENAME_COMPONENT (HLSL_CHECK "${file}" LAST_EXT)
            IF (${HLSL_CHECK} STREQUAL ".hlsl")
                GET_FILENAME_COMPONENT (FILE_NAME "${FILE_NAME_E}" NAME_WE)
                GET_FILENAME_COMPONENT (SHADER_TYPE "${FILE_NAME_E}" LAST_EXT)
                IF (${SHADER_TYPE} STREQUAL ".vs")
                    SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_TYPE Vertex)
                    SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_VARIABLE_NAME "g_ui${FILE_NAME}_VS_Compiled")
                    SET (HEADER_PATH "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}/${FILE_NAME}_vs.hlsl.h")
                    CMAKE_PATH (SET HEADER_PATH_NORMALIZED NORMALIZE "${HEADER_PATH}")
                    SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_OUTPUT_HEADER_FILE "${HEADER_PATH_NORMALIZED}")
                    CMAKE_PATH (SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files/${MK_COMPILE__TYPE}")
                    IF (NOT EXISTS "${HEADER_PATH}")
                        FILE (WRITE "${HEADER_PATH}" "")
                        MESSAGE (STATUS "Created file: ${HEADER_PATH}")
                    ENDIF ()
                    TGS_ADD_FILE_TO_IDE (${header_files} ${header_files} ${test_assigned} ${test_current} "${HEADER_PATH}" IDE_PATH ${IDE_HEADER_PATH})
                    SET_PROPERTY (SOURCE "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}/${FILE_NAME}_vs.hlsl.h" PROPERTY HEADER_FILE_ONLY TRUE)
                ELSEIF (${SHADER_TYPE} STREQUAL ".ps")
                    SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_TYPE Pixel)
                    SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_VARIABLE_NAME "g_ui${FILE_NAME}_PS_Compiled")
                    SET (HEADER_PATH "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}/${FILE_NAME}_ps.hlsl.h")
                    CMAKE_PATH (SET HEADER_PATH_NORMALIZED NORMALIZE "${HEADER_PATH}")
                    SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_OUTPUT_HEADER_FILE "${HEADER_PATH_NORMALIZED}")
                    CMAKE_PATH (SET IDE_HEADER_PATH NORMALIZE "${ide_path}/../Header Files/${MK_COMPILE__TYPE}")
                    IF (NOT EXISTS "${HEADER_PATH}")
                        FILE (WRITE "${HEADER_PATH}" "")
                        MESSAGE (STATUS "Created file: ${HEADER_PATH}")
                    ENDIF ()
                    TGS_ADD_FILE_TO_IDE (${header_files} ${header_files} ${test_assigned} ${test_current} "${HEADER_PATH}" IDE_PATH ${IDE_HEADER_PATH})
                    SET_PROPERTY (SOURCE "${MK_BUILD_MODULE__SRC_DIR}/${MK_COMPILE__TYPE}/${FILE_NAME}_ps.hlsl.h" PROPERTY HEADER_FILE_ONLY TRUE)
                ELSE ()
                    MESSAGE ("UNKNOWN HLSL SHADER FILE TYPE: " ${SHADER_TYPE} " - " ${file})
                ENDIF ()

                #SET_PROPERTY(SOURCE ${file} PROPERTY VS_SETTINGS "ExcludedFromBuild=true")
                STRING (REPLACE "/" "\\" INCLUDE_FIXED "${GIT_ROOT_PATH}/teikitu_sdk/TgS KERNEL")
                SET_PROPERTY (SOURCE ${file} PROPERTY VS_SETTINGS "AdditionalIncludeDirectories=${INCLUDE_FIXED}")

                SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_MODEL 6.2)
                SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_ENTRYPOINT main)
                SET_PROPERTY (SOURCE ${file} PROPERTY VS_SHADER_FLAGS [=[-HV 2021 -Zpc -Fd "$(OutDir)%(Filename).debug" -Frs "$(OutDir)%(Filename).root_sig" -Fre "$(OutDir)%(Filename).reflection" -Fsh "$(OutDir)%(Filename).hash" -Zsb -Zi]=])
            ELSE ()
                MESSAGE ("FILE NAME DOES NOT TERMINATE WITH HLSL: " ${HLSL_CHECK} " - " ${file})
            ENDIF ()
        ELSE ()
            MESSAGE ("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()


##########################################################################################################################################################################################################
# add a source file to the given list
MACRO(TGS_ADD_HLSL_FILE source_files header_files test_assigned test_current ide_path file)
    IF(MK_IDE__INCLUDE_NON_SOURCE_FILES)
        IF (EXISTS ${file})
            TGS_ADD_FILE_TO_IDE(${header_files} ${header_files} ${test_assigned} ${test_current} ${file} IDE_PATH ${ide_path})
            GET_FILENAME_COMPONENT( FILE_NAME_E "${file}" NAME_WLE )
            GET_FILENAME_COMPONENT( HLSL_CHECK "${file}" LAST_EXT )
            IF (${HLSL_CHECK} STREQUAL ".hlsl")
                GET_FILENAME_COMPONENT( FILE_NAME "${FILE_NAME_E}" NAME_WE )
                GET_FILENAME_COMPONENT( SHADER_TYPE "${FILE_NAME_E}" LAST_EXT )
                IF (${SHADER_TYPE} STREQUAL ".vs")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Vertex)
                ELSEIF (${SHADER_TYPE} STREQUAL ".ps")
                    SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_TYPE Pixel)
                ELSE ()
                    MESSAGE("UNKNOWN HLSL SHADER FILE TYPE: " ${SHADER_TYPE} " - " ${file})
                ENDIF ()

                STRING (REPLACE "/" "\\" INCLUDE_FIXED "${GIT_ROOT_PATH}/teikitu_sdk/TgS KERNEL")
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SETTINGS "AdditionalIncludeDirectories=${INCLUDE_FIXED}")

                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_MODEL 6.2)
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_ENTRYPOINT main)
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_OBJECT_FILE_NAME [=[$(LOCALAPPDATA)\Teikitu\%(Filename).cso]=])
                SET_PROPERTY(SOURCE ${file} PROPERTY VS_SHADER_FLAGS [=[-HV 2021 -Zpc -Fd "$(OutDir)%(Filename).debug" -Frs "$(OutDir)%(Filename).root_sig" -Fre "$(OutDir)%(Filename).reflection" -Fsh "$(OutDir)%(Filename).hash" -Zsb -Zi]=])
            ELSE ()
                MESSAGE("FILE NAME DOES NOT TERMINATE WITH HLSL: " ${HLSL_CHECK} " - " ${file})
            ENDIF ()
        ELSE ()
            MESSAGE("FILE DOES NOT EXIST: " ${file})
        ENDIF ()
    ENDIF ()
ENDMACRO ()

# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_STANDARD_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES SDK_HEADER_FILES)

    # Add standard include paths
    CMAKE_PATH ( SET PCH_SOURCE_PATH NORMALIZE "${PCH_SOURCE_DIR}")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${PCH_SOURCE_PATH}")
    #MESSAGE( STATUS "CMAKE BUILD: INCLUDE PATH ${PCH_SOURCE_PATH}")

    CMAKE_PATH ( SET PROJECT_SOURCE_PATH NORMALIZE "${GIT_ROOT_PATH}/teikitu_sdk/")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${PROJECT_SOURCE_PATH}")
    #MESSAGE( STATUS "CMAKE BUILD: INCLUDE PATH ${PROJECT_SOURCE_PATH}")

    CMAKE_PATH ( SET EXTERNAL_PATH NORMALIZE "${MK_BUILD__EXTERNAL_TARGET_DIRECTORY}")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${EXTERNAL_PATH}")
    CMAKE_PATH ( SET EXTERNAL_PATH NORMALIZE "${GIT_ROOT_PATH}/teikitu_external")
    TARGET_INCLUDE_DIRECTORIES(${TARGET} BEFORE PRIVATE "${EXTERNAL_PATH}")

    # Custom properties used in our version of CMake to set the intermediate directory
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES INTERMEDIATE_OUTPUT_DIRECTORY ${CMAKE_MODULE_OBJECT_OUTPUT_DIRECTORY})
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES VS_LLVM_VERSION 15.0.4)



    # -- SOURCE COMPILE OPTIONS AND DEFINITIONS --

    # NOTE: This marks the file, independent of the target (i.e. source file properties are retained within an instance of an invocation.
    FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SOURCE_FILES}} )

        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "FI\"${PCH_INCLUDE}\"") # Force include
        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "Yu\"${PCH_INCLUDE}\"") # Use PCH

        GET_FILENAME_COMPONENT( FILE_EXTENSION "${MK_LIST_ITEM__FILE_NAME}" EXT )
        IF (MK_COMPILER__MSVC OR ${FILE_EXTENSION} STREQUAL ".cpp")
            # stdatomic is not supported in MSVC 2022. Compile everything as a C++ project
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE CXX)
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" APPEND_STRING PROPERTY COMPILE_DEFINITIONS TgCOMPILE_FILE__CXX)
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std:c++20") # Set the CXX standard
            TGS_SOURCE_APPEND_GNU_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std=c++20") # Set the CXX standard
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" [=[Fp"$(IntDir)$(TargetName)_CXX.pch"]=])
        ELSE ()
            SET_PROPERTY(SOURCE "${MK_LIST_ITEM__FILE_NAME}" PROPERTY LANGUAGE C)
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std:c17") # Set the C standard
            TGS_SOURCE_APPEND_GNU_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" "std=c17") # Set the C standard
            TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${MK_LIST_ITEM__FILE_NAME}" [=[Fp"$(IntDir)$(TargetName)_C.pch"]=])
        ENDIF ()

    ENDFOREACH ()

    # Mark the CXX File source file for PCH creation.
    IF (EXISTS "${PCH_SOURCE_DIR}/${PCH_SOURCE}.cpp")
        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${PCH_SOURCE_DIR}/${PCH_SOURCE}.cpp" [=[Yc]=]) # Set the CXX standard
    ENDIF ()

    # Mark the C File source file for PCH creation.
    IF (EXISTS "${PCH_SOURCE_DIR}/${PCH_SOURCE}.c")
        TGS_SOURCE_APPEND_MSVC_COMPILER_OPTION ("${PCH_SOURCE_DIR}/${PCH_SOURCE}.c" [=[Yc]=]) # Set the CXX standard
    ENDIF ()



    # -- TARGET COMPILE DEFINITIONS AND OPTIONS --

    # Server/Client Compilation Flags
    GET_PROPERTY(TEST_COMPILE_OPTIONS TARGET ${TARGET} PROPERTY COMPILE_DEFINITIONS)
    LIST(FIND TEST_COMPILE_OPTIONS "TgBUILD_FEATURE__SERVER" INDEX__TgBUILD_FEATURE__SERVER)
    LIST(FIND TEST_COMPILE_OPTIONS "TgBUILD_FEATURE__CLIENT" INDEX__TgBUILD_FEATURE__CLIENT)
    IF (NOT ${INDEX__TgBUILD_FEATURE__SERVER} GREATER -1 AND NOT ${INDEX__TgBUILD_FEATURE__CLIENT} GREATER -1)
        TARGET_COMPILE_DEFINITIONS( ${TARGET} PRIVATE TgBUILD_FEATURE__SERVER)
        TARGET_COMPILE_DEFINITIONS( ${TARGET} PRIVATE TgBUILD_FEATURE__CLIENT)
    ENDIF ()

    IF (MK_COMPILER_FRONTEND__GNU)
        #TARGET_PRECOMPILE_HEADERS(${TARGET} PRIVATE ${PCH_INCLUDE})
        #TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -U __STDC_HOSTED__)
        #TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -v)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -include ${PCH_SOURCE_DIR}/${PCH_INCLUDE})
    ENDIF ()

    IF (MK_COMPILER_FRONTEND__APPLE)
        TARGET_PRECOMPILE_HEADERS(${TARGET} PRIVATE ${PCH_INCLUDE})
        SET_TARGET_PROPERTIES (${TARGET} PROPERTIES XCODE_ATTRIBUTE_GCC_PREFIX_HEADER ${PCH_SOURCE_DIR}/${PCH_INCLUDE})
    ENDIF ()

    TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE TgCOMPILE_DEFAULT_PCH=${PCH_INCLUDE})
    TARGET_COMPILE_DEFINITIONS (${TARGET} PRIVATE __MODULE__=${MK_BUILD_ROOT__MODULE_NAME})
    TARGET_COMPILE_FEATURES (${TARGET} PUBLIC c_std_${CMAKE_C_STANDARD})
    TARGET_COMPILE_FEATURES (${TARGET} PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
    SET_PROPERTY (TARGET ${TARGET} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

    IF (MK_BUILD_OS__WIN)
        ADD_COMPILE_DEFINITIONS (TgCOMPILE__PLATFORM_TIME)
        IF (MK_COMPILE_PLATFORM_TEXT__WIDE)
            TARGET_COMPILE_DEFINITIONS(${TARGET} PRIVATE _UNICODE)
            TARGET_COMPILE_DEFINITIONS(${TARGET} PRIVATE UNICODE)
        ENDIF ()
        IF (MK_COMPILER_FRONTEND__MSVC)
            TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /MD$<$<CONFIG:Debug>:d>)
        ENDIF ()
    ENDIF ()

    IF (MK_COMPILER_FRONTEND__MSVC)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /utf-8) # Use UTF8
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /EHs)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE /Wall)
    ENDIF ()

    IF (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Weverything) # Enable "Everything" warning level
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Werror) # Enforce warnings as errors
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fno-exceptions) # Disable runtime exception handling
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fno-rtti) # Disable Run Time Type Information
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -fvisibility-inlines-hidden) # Do not add inline functions into the linker symbol tables
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Xclang -fno-dllexport-inlines) # Do not add inline functions into the linker symbol tables
        IF (MK_BUILD__HARDWARE__X64)
            TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -march=x86-64-v2)
            TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -mcx16) # Include support for 16B compare exchange
            TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -msse4) # SSE4 Support, Released in CPUs from 2007/2008
        ENDIF ()
    ENDIF ()

    IF (MK_BUILD_OS__POSIX AND (MK_COMPILER_FRONTEND__GNU OR MK_COMPILER_FRONTEND__APPLE))
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-old-style-cast)
        TARGET_COMPILE_OPTIONS (${TARGET} PRIVATE -Wno-zero-as-null-pointer-constant)
    ENDIF()

    IF (MK_COMPILER__MSVC)
        TARGET_COMPILE_DEFINITIONS(${TARGET} PRIVATE D_ANALYSIS)
    ENDIF ()



    # -- STATIC LIBRARY SETTINGS ----

    GET_TARGET_PROPERTY (TARGET_TYPE ${TARGET} TYPE)
    IF (TARGET_TYPE STREQUAL "STATIC_LIBRARY")
        IF (MK_COMPILER_FRONTEND__MSVC)
            SET_TARGET_PROPERTIES (${TARGET} PROPERTIES STATIC_LIBRARY_OPTIONS /MACHINE:X64)
        ENDIF ()
    ENDIF ()



    # -- SHARED LIBRARY SETTINGS ----

    GET_TARGET_PROPERTY (TARGET_TYPE ${TARGET} TYPE)
    IF (TARGET_TYPE STREQUAL "SHARED_LIBRARY")
    ENDIF ()



    # -- LINKER SETTINGS ----

    GET_TARGET_PROPERTY (TARGET_TYPE ${TARGET} TYPE)
    IF (TARGET_TYPE STREQUAL "EXECUTABLE")
        #TARGET_LINK_OPTIONS (${TARGET} PRIVATE /errorlimit:0)

        IF (MK_COMPILER_FRONTEND__MSVC)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE /DEBUG)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE /MACHINE:X64)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE /NODEFAULTLIB)

            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "KERNEL32")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "UUID")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "ucrt$<$<CONFIG:Debug>:d>")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "vcruntime$<$<CONFIG:Debug>:d>")
            TARGET_LINK_LIBRARIES (${TARGET} PRIVATE "msvcrt$<$<CONFIG:Debug>:d>")
        ENDIF ()

        IF (MK_PLATFORM__MAC)
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework AudioToolbox")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework CoreGraphics")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework QuartzCore")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework UIKit")
            TARGET_LINK_OPTIONS (${TARGET} PRIVATE "SHELL:-framework Foundation")
        ENDIF ()
    ENDIF ()



    # -- INSTALL SETTINGS ----

    SET (MK_BUILD_VERSION_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${MK_BUILD_PACKAGE_PROJECT_NAME}ConfigVersion.cmake")
    SET (MK_BUILD_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/${MK_BUILD_PACKAGE_PROJECT_NAME}Config.cmake")
    SET (MK_BUILD_TARGETS_EXPORT_NAME "${MK_BUILD_PACKAGE_PROJECT_NAME}Targets")
    SET (MK_BUILD_NAMESPACE "${MK_BUILD_PACKAGE_PROJECT_NAME}::")
    SET (MK_BUILD_PROJECT_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${MK_BUILD_PACKAGE_PROJECT_NAME}")

    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES VERSION ${CMAKE_PROJECT_VERSION})
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES SOVERSION 0)
    SET_TARGET_PROPERTIES (${TARGET} PROPERTIES INTERFACE_${TARGET}_MAJOR_VERSION ${CMAKE_PROJECT_VERSION_MAJOR})
    SET_PROPERTY (TARGET ${TARGET} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${TARGET}_MAJOR_VERSION )

    # Install the resulting targets (libraries, excecutables, etc.)
    INSTALL (TARGETS ${TARGET}
             DESTINATION ${CMAKE_INSTALL_PREFIX}
             EXPORT "${MK_BUILD_TARGETS_EXPORT_NAME}"
             CONFIGURATIONS ${CMAKE_BUILD_TYPE}
             LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}"
             ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/${CMAKE_BUILD_TYPE}"
             RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/${CMAKE_BUILD_TYPE}"
             INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    )

    # Install the SDK related header files.
    FOREACH (MK_LIST_ITEM__FILE_NAME IN ITEMS ${${SDK_HEADER_FILES}} )

        FILE (RELATIVE_PATH MK_LIST_ITEM__RELATIVE_PATH ${GIT_ROOT_PATH}/teikitu_sdk/ ${MK_LIST_ITEM__FILE_NAME})
        CMAKE_PATH (GET MK_LIST_ITEM__RELATIVE_PATH PARENT_PATH MK_RELATIVE_PATH)
        INSTALL (FILES ${MK_LIST_ITEM__FILE_NAME} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${MK_BUILD_PACKAGE_PROJECT_NAME}/${MK_RELATIVE_PATH}/")

    ENDFOREACH ()

    # Write the cmake configuration file.
    WRITE_BASIC_PACKAGE_VERSION_FILE ("${MK_BUILD_VERSION_CONFIG_FILE}" VERSION ${CMAKE_PROJECT_VERSION} COMPATIBILITY SameMajorVersion)
    CONFIGURE_PACKAGE_CONFIG_FILE ("${GIT_ROOT_PATH}/cmake/${MK_BUILD_PACKAGE_PROJECT_NAME}-config.cmake.in" "${MK_BUILD_PROJECT_CONFIG_FILE}" INSTALL_DESTINATION "${MK_BUILD_PROJECT_CONFIG_INSTALL_DIR}")
    INSTALL (FILES "${MK_BUILD_PROJECT_CONFIG_FILE}" "${MK_BUILD_VERSION_CONFIG_FILE}" DESTINATION "${MK_BUILD_PROJECT_CONFIG_INSTALL_DIR}")
    INSTALL (EXPORT "${MK_BUILD_TARGETS_EXPORT_NAME}" NAMESPACE "${MK_BUILD_NAMESPACE}" DESTINATION "${MK_BUILD_PROJECT_CONFIG_INSTALL_DIR}")

ENDMACRO (TGS_SET_STANDARD_PROPERTIES)




# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_LIBRARY_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_STANDARD_LIBRARY_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES SDK_HEADER_FILES)

    ADD_LIBRARY (${MK_BUILD_PACKAGE_PROJECT_NAME}::${TARGET} ALIAS ${TARGET})
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET} ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES} ${SDK_HEADER_FILES})

ENDMACRO (TGS_SET_STANDARD_LIBRARY_PROPERTIES)




# ========================================================================================================================================================================================================
#  Function: TGS_SET_STANDARD_EXECUTABLE_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_STANDARD_EXECUTABLE_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES)

    #SET_TARGET_PROPERTIES (${TARGET} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer: Andrew Aye")
    SET (SDK_HEADER_FILES "")
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET} ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES} SDK_HEADER_FILES)

    IF (MK_BUILD_OS__WIN)
        SET_TARGET_PROPERTIES( ${TARGET} PROPERTIES WIN32_EXECUTABLE 1)
    ENDIF ()

    IF ("${MK_BUILD_AUTOMATION}" STREQUAL "CICD_BUILD")
    ELSE()
       #ADD_CUSTOM_COMMAND(TARGET ${TARGET} POST_BUILD
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/D3D12Core.dll $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/D3D12Core.pdb $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/d3d12SDKLayers.dll $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/d3d12SDKLayers.pdb $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/WinPixEventRuntime/bin/x64/WinPixEventRuntime.dll $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND_EXPAND_LISTS
       #)
    ENDIF ()

ENDMACRO (TGS_SET_STANDARD_EXECUTABLE_PROPERTIES)




# ========================================================================================================================================================================================================
#  Function: TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES
# ========================================================================================================================================================================================================

MACRO (TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES TARGET PCH_SOURCE_DIR PCH_SOURCE PCH_INCLUDE SOURCE_FILES HEADER_FILES)

    # Include the UWP standard runtime files
    IF (MK_BUILD__UNIVERSAL__UWP)
        SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.xaml.cpp")
        SOURCE_GROUP ("Resource Files" FILES "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.xaml.cpp")
        SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.xaml")
        SOURCE_GROUP ("Resource Files" FILES "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.xaml")
        SET_SOURCE_FILES_PROPERTIES("${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.xaml" PROPERTIES VS_XAML_TYPE "ApplicationDefinition" )

        IF (INCLUDE_NON_SOURCE_FILES)
            SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.xaml.h")
            SOURCE_GROUP ("Resource Files" FILES "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.xaml.h")
            SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/pch.h")
            SOURCE_GROUP ("Resource Files" FILES "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/pch.h")
            SET (${SOURCE_FILES} ${${SOURCE_FILES}} "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.rd.xml")
            SOURCE_GROUP ("Resource Files" FILES "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST/UnitTestApp.rd.xml")
        ENDIF (INCLUDE_NON_SOURCE_FILES)
    ENDIF ()

    # Add Unit Test paths for compilation
    TARGET_INCLUDE_DIRECTORIES(${TARGET}            PRIVATE "${GIT_ROOT_PATH}/teikitu_privates/tests/TgS UNIT TEST")

    IF (MK_BUILD__UNIVERSAL__UWP)
        #TARGET_INCLUDE_DIRECTORIES(${TARGET}            PRIVATE "$(VCInstallDir)UnitTest/include/UWP")
        #TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /LIBPATH:"$(VCInstallDir)UnitTest/lib/UWP")
    ELSEIF (MK_BUILD_OS__WIN)
        #TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE /LIBPATH:"$(VCInstallDir)UnitTest/lib/W64")
        #TARGET_LINK_OPTIONS (${TARGET}                  PRIVATE "SHELL:/defaultlib:kernel32.lib")
    ENDIF ()

    # Set UWP Unit Test configuration / references
    IF (MK_BUILD__UNIVERSAL__UWP)
        SET_TARGET_PROPERTIES(${TARGET}                 PROPERTIES VS_CPPUNITTESTFRAMEWORK_EXTENSIONS_VERSION "14.0" )
        SET_TARGET_PROPERTIES(${TARGET}                 PROPERTIES VS_TESTPLATFORM_EXTENSIONS_VERSION "14.0" )
        SET_TARGET_PROPERTIES(${TARGET}                 PROPERTIES UWP_APPLICATION_ID "vstest.executionengine.universal.App")
    ENDIF ()

    # SET_TARGET_PROPERTIES (${TARGET}                PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Sign to Run Locally")
    SET (SDK_HEADER_FILES "")
    TGS_SET_STANDARD_PROPERTIES ( ${TARGET}         ${PCH_SOURCE_DIR} ${PCH_SOURCE} ${PCH_INCLUDE} ${SOURCE_FILES} ${HEADER_FILES} SDK_HEADER_FILES)

    IF (MK_BUILD_OS__WIN)
        SET_TARGET_PROPERTIES( ${TARGET} PROPERTIES WIN32_EXECUTABLE 1)
    ENDIF ()

    IF ("${MK_BUILD_AUTOMATION}" STREQUAL "CICD_BUILD")
    ELSE()
       #ADD_CUSTOM_COMMAND(TARGET ${TARGET} POST_BUILD
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/D3D12Core.dll $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/D3D12Core.pdb $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/d3d12SDKLayers.dll $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/_directx_agile/build/native/bin/x64/d3d12SDKLayers.pdb $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GIT_ROOT_PATH}/teikitu_external/WinPixEventRuntime/bin/x64/WinPixEventRuntime.dll $<TARGET_FILE_DIR:${TARGET}>
       #    COMMAND_EXPAND_LISTS
       #)
    ENDIF ()

ENDMACRO (TGS_SET_UNITTEST_EXECUTABLE_PROPERTIES)
