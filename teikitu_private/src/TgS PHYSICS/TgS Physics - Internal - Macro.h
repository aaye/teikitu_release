/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal - Macro.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_MACRO_H)
#if !defined (ENABLE_RELOAD_GUARD)

/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Macros Code Helpers                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN_CUSTOM_INTERNAL(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,...)                                                                     \
TgRESULT tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( ATTRIBUTE_TYPE * const pVal, TgPH_##OBJ_ID##_ID_C tiID )                                                                              \
{                                                                                                                                                                                   \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( tiID );                                                                                                              \
                                                                                                                                                                                    \
    if ((nullptr == pVal) || (nullptr == ps##OBJ_NAME))                                                                                                                             \
    {                                                                                                                                                                               \
        TgPARAM_CHECK( nullptr != pVal );                                                                                                                                           \
        return (KTgE_FAIL);                                                                                                                                                         \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    __VA_ARGS__                                                                                                                                                                     \
                                                                                                                                                                                    \
    return (KTgS_OK);                                                                                                                                                               \
}

#define PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                   \
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN_CUSTOM_INTERNAL(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,*pVal = ps##OBJ_NAME->FIELD;)

#define PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_CUSTOM_INTERNAL(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD,...)                                                             \
CLANG_WARN_DISABLE_PUSH(padded)                                                                                                                                                     \
MSVC_PRAGMA(warning(push))                                                                                                                                                          \
MSVC_PRAGMA(warning(disable: 4820))                                                                                                                                                 \
static TgVOID tgPH_##FCN_NAME##_Do_Command( TgVOID_CPC NONULL pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )                                                                        \
{                                                                                                                                                                                   \
    typedef struct {                                                                                                                                                                \
        TgPH_##OBJ_ID##_ID TgALIGN(16) tiID;                                                                                                                                        \
        ATTRIBUTE_TYPE Val;                                                                                                                                                         \
    } STg2_FCN_Command;                                                                                                                                                             \
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };                                             \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
                                                                                                                                                                                    \
    TgPARAM_CHECK(sizeof(STg2_FCN_Command) == nbyCommand_Buffer)                                                                                                                    \
    (void)nbyCommand_Buffer;                                                                                                                                                        \
                                                                                                                                                                                    \
    if (nullptr == uCMD.pCommand)                                                                                                                                                   \
    {                                                                                                                                                                               \
        return;                                                                                                                                                                     \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( uCMD.pCommand->tiID );                                                                                               \
                                                                                                                                                                                    \
    if (nullptr == ps##OBJ_NAME)                                                                                                                                                    \
    {                                                                                                                                                                               \
        return;                                                                                                                                                                     \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    __VA_ARGS__                                                                                                                                                                     \
}                                                                                                                                                                                   \
                                                                                                                                                                                    \
                                                                                                                                                                                    \
TgRESULT tgPH_##FCN_NAME( TgPH_##OBJ_ID##_ID_C tiID, ATTRIBUTE_TYPE const Val )                                                                                                     \
{                                                                                                                                                                                   \
    struct {                                                                                                                                                                        \
        TgPH_##OBJ_ID##_ID_C tiID;                                                                                                                                                  \
        ATTRIBUTE_TYPE Val;                                                                                                                                                         \
    } sCommand = { tiID, Val };                                                                                                                                                     \
                                                                                                                                                                                    \
    return tgCM_UT__CMD_BUF__Queue_Command( g_asPH_Command_To_World + tiID.m_uiWorld, tgPH_##FCN_NAME##_Do_Command, sizeof(sCommand), &sCommand );                                  \
}                                                                                                                                                                                   \
CLANG_WARN_DISABLE_POP(padded)                                                                                                                                                      \
MSVC_PRAGMA(warning(pop))

#define PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                         \
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_CUSTOM_INTERNAL(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD,ps##OBJ_NAME->FIELD = uCMD.pCommand->Val;)             \
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)

#define PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_CUSTOM(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD,...)                                                                     \
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_CUSTOM_INTERNAL(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD,__VA_ARGS__)                                           \
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)

#define PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                              \
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_CUSTOM_INTERNAL(OBJ_NAME##_Add_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD,                                                       \
                                                             ps##OBJ_NAME->FIELD = tgMH_ADD_F32_04_1( ps##OBJ_NAME->FIELD, uCMD.pCommand->Val );)




#define PHYSICS_FUNCTION_QUERY__DEFINITION_COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                                     \
TgRESULT tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( ATTRIBUTE_TYPE * const pVal, TgPH_##OBJ_ID##_ID_C tiID )                                                                              \
{                                                                                                                                                                                   \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( tiID );                                                                                                              \
                                                                                                                                                                                    \
    if ((nullptr == pVal) || (nullptr == ps##OBJ_NAME))                                                                                                                             \
    {                                                                                                                                                                               \
        TgPARAM_CHECK( nullptr != pVal );                                                                                                                                           \
        return (KTgE_FAIL);                                                                                                                                                         \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    tgMM_Copy( pVal, sizeof( ATTRIBUTE_TYPE ), &ps##OBJ_NAME->FIELD, sizeof( ps##OBJ_NAME->FIELD ) );                                                                               \
                                                                                                                                                                                    \
    return (KTgS_OK);                                                                                                                                                               \
}

#define PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_CUSTOM_INTERNAL(FCN_NAME,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD,...)                                                               \
CLANG_WARN_DISABLE_PUSH(padded)                                                                                                                                                     \
MSVC_PRAGMA(warning(push))                                                                                                                                                          \
MSVC_PRAGMA(warning(disable: 4820))                                                                                                                                                 \
static TgVOID tgPH_##FCN_NAME##_Do_Command( TgVOID_CPC NONULL pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )                                                                        \
{                                                                                                                                                                                   \
    typedef struct {                                                                                                                                                                \
        TgPH_##OBJ_ID##_ID TgALIGN(16) tiID;                                                                                                                                        \
        ATTRIBUTE_TYPE Val;                                                                                                                                                         \
    } STg2_FCN_Command;                                                                                                                                                             \
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };                                             \
    STg2_PH_##OBJ_NAME##_P              ps##OBJ_NAME;                                                                                                                               \
                                                                                                                                                                                    \
    TgPARAM_CHECK(sizeof(STg2_FCN_Command) == nbyCommand_Buffer)                                                                                                                    \
    (void)nbyCommand_Buffer;                                                                                                                                                        \
                                                                                                                                                                                    \
    if (nullptr == uCMD.pCommand)                                                                                                                                                   \
    {                                                                                                                                                                               \
        return;                                                                                                                                                                     \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    ps##OBJ_NAME = tgPH_##OBJ_NAME##_Get_##OBJ_NAME##_From_ID( uCMD.pCommand->tiID );                                                                                               \
                                                                                                                                                                                    \
    if (nullptr == ps##OBJ_NAME)                                                                                                                                                    \
    {                                                                                                                                                                               \
        return;                                                                                                                                                                     \
    };                                                                                                                                                                              \
                                                                                                                                                                                    \
    __VA_ARGS__                                                                                                                                                                     \
}                                                                                                                                                                                   \
                                                                                                                                                                                    \
                                                                                                                                                                                    \
TgRESULT tgPH_##FCN_NAME( TgPH_##OBJ_ID##_ID_C tiID, ATTRIBUTE_TYPE const * pVal )                                                                                                  \
{                                                                                                                                                                                   \
    struct {                                                                                                                                                                        \
        TgPH_##OBJ_ID##_ID TgALIGN(16) tiID;                                                                                                                                        \
        ATTRIBUTE_TYPE Val;                                                                                                                                                         \
    } sCommand;                                                                                                                                                                     \
                                                                                                                                                                                    \
    sCommand.tiID.m_uiKI = tiID.m_uiKI;                                                                                                                                             \
    tgMM_Copy( (TgVOID_P)&sCommand.Val, sizeof( ATTRIBUTE_TYPE ), (TgVOID_CP)pVal, sizeof( ATTRIBUTE_TYPE ) );                                                                      \
                                                                                                                                                                                    \
    return tgCM_UT__CMD_BUF__Queue_Command( g_asPH_Command_To_World + tiID.m_uiWorld, tgPH_##FCN_NAME##_Do_Command, sizeof(sCommand), &sCommand );                                  \
}                                                                                                                                                                                   \
CLANG_WARN_DISABLE_POP(padded)                                                                                                                                                      \
MSVC_PRAGMA(warning(pop))

#define PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_SIMPLE(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)                                                                           \
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_CUSTOM_INTERNAL(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD,                                                         \
                                                  tgMM_Copy( (TgVOID_P)&ps##OBJ_NAME->FIELD, sizeof( ps##OBJ_NAME->FIELD ),                                                         \
                                                             (TgVOID_CP)&uCMD.pCommand->Val, sizeof( ATTRIBUTE_TYPE ) );)  \
PHYSICS_FUNCTION_QUERY__DEFINITION_COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)

#define PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_CUSTOM(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD,...)                                                                       \
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_CUSTOM_INTERNAL(OBJ_NAME##_Set_##ATTRIBUTE,OBJ_NAME,OBJ_ID,ATTRIBUTE_TYPE,FIELD,__VA_ARGS__)                                             \
PHYSICS_FUNCTION_QUERY__DEFINITION_COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE,FIELD)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Macros                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Internal - Macro.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_INTERNAL_MACRO_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Macros                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */









/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_INTERNAL_MACROS_H) */
#endif
