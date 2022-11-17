/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Set.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_SET_H)
#define TGS_SET_H
#pragma once

#define TGS_PLATFORM_SET_H



/* **** STUB FILE ****/



/* == Set ======================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

enum { KTgSE_MAX_CAMERA                     =     16 };
enum { KTgSE_MAX_VIEW                       =      8 };
enum { KtgSE_CXT_MAX_LIGHT_PER_INSTANCE     =     16 };




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgSE_DRAW_TYPE, TgSINT_F32,

    ETgSE_DRAW_TYPE__BEGIN,

    ETgSE_DRAW_TYPE__OPAQUE = ETgSE_DRAW_TYPE__BEGIN,
    ETgSE_DRAW_TYPE__TRANSPARENT,
    ETgSE_DRAW_TYPE__TARGET,

    ETgSE_DRAW_TYPE__END,
    ETgSE_DRAW_TYPE__MAX = ETgSE_DRAW_TYPE__END,
    ETgSE_DRAW_TYPE__COUNT = ETgSE_DRAW_TYPE__END - ETgSE_DRAW_TYPE__BEGIN,
);

TgTYPE_ENUM(ETgSE_CHANNEL, TgSINT_F32,

    ETgSE_CHANNEL__UNKNOWN,         ETgSE_CHANNEL__PICKING,         ETgSE_CHANNEL__SET,             ETgSE_CHANNEL__DEBRIS,          ETgSE_CHANNEL__EFFECT,
    ETgSE_CHANNEL__CHARACTER,       ETgSE_CHANNEL__RAG_DOLL,        ETgSE_CHANNEL__MAX,
);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgTYPE_STRUCT(STg2_RN_Cxt_Mesh,)
{
    TgRN_MESH_SET_ID                            m_tiMesh_Set;
    TgUINT_E32                                  m_uiLOD_Index;
    TgUINT_E32                                  m_uiFlags;

    TgVEC_F32_04_1                              m_vScale;
    TgVEC_F32_04_3                              m_xTX; /**< Local transform - this will place the object in world space */
    TgVEC_F32_04_1                              m_vLast_Scale;
    TgVEC_F32_04_3                              m_xLast_TX;

    TgVEC_F32_04_1                              m_vBA_Max_W;
    TgVEC_F32_04_1                              m_vBA_Min_W;

    TgVEC_F32_04_1                              m_vAmbient;
    TgVEC_F32_04_1                              m_vLM; /**< Light map rect (texture space) definition. */
    TgKN_GPU_TX_IMG_ID                          m_tiLM; /**< Default is a black texture */
    TgRN_MATERIAL_ID                            m_tiMaterial;
    TgRSIZE                                     m_auiLight[KtgSE_CXT_MAX_LIGHT_PER_INSTANCE];
    TgRSIZE                                     m_nuiLight;

    TgUINT_E32                                  m_uiSkeleton_0; /**< Body skeleton index used by this mesh, default is -1 (rigid) */
    TgUINT_E32                                  m_uiSkeleton_1; /**< Face skeleton index used by this mesh, default is -1 (rigid) */

    TgFLOAT32                                   m_fOpacity; /**< Default is 1.0 - Used to for mesh specific override (alpha fade). */
    TgUINT_E08                                  m_uiPad_0[12];
};
//# defined(TgBUILD_FEATURE__GRAPHICS)
#endif

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgTYPE_STRUCT(STg2_SE_View,)
{
    STg2_KN_GPU_Camera_CP TgALIGN(16)           m_psCamera;
    TgRN_TARGET_ID                              m_tiRN_Target;
    TgUINT_MAX                                  m_uiGUID;

    TgRSIZE_P                                   m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__COUNT];
    TgRSIZE_A                                   m_axnuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__COUNT];
    TgRSIZE                                     m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__COUNT];
};
//# defined(TgBUILD_FEATURE__GRAPHICS)
#endif

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgTYPE_STRUCT(STg2_SE_Context,)
{
    /* Input */
    STg2_SE_View TgALIGN(16)                    m_asView[KTgSE_MAX_VIEW];

    /* Context | Scene Data */
    STg2_RN_Cxt_Mesh_P                          m_asFrame_Mesh;
    TgRSIZE_A                                   m_xnuiFrame_Mesh;
    TgRSIZE                                     m_nuiFrame_Mesh_Max;
    TgUINT_E64                                  m_uiPad_0;

#if TgCOMPILE__RENDER_DEBUG_OUTPUT
    STg2_KN_GPU_Camera_CP                       m_psDebug_Camera;
    TgUINT_E64                                  m_uiPad_1;
//# TgCOMPILE__RENDER_DEBUG_OUTPUT
#endif
};
//# defined(TgBUILD_FEATURE__GRAPHICS)
#endif

TgTYPE_STRUCT(STg2_SE_CO_Request_F32_04,)
{
    STg2_CO_Request_F32_04                      m_sCollision_Request;

    TgOBJECT_INST_ID                            m_tiMainObject; /**< The object that initiated this collision call */
    TgOBJECT_INST_ID                            m_tiObject_Graph_Ignored[KTgOB_MAX_OBJECT_IGNORE];
    TgOBJECT_INST_ID                            m_tiObject_Ignored[KTgOB_MAX_OBJECT_IGNORE];
#if 0 != (2760 % TgBUILD_HARDWARE__CPU_CACHE_LINE_SIZE)
    TgUINT_E08                                  m_uiPad0[TgBUILD_HARDWARE__CPU_CACHE_LINE_SIZE - (2760 % TgBUILD_HARDWARE__CPU_CACHE_LINE_SIZE)];
#endif
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgSE_Module_Init( TgVOID ) { return KTgS_OK; }

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgSE_Module_Boot( TgVOID ) { return KTgS_OK; }

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgINLINE TgVOID
tgSE_Module_Stop( TgVOID ) {}

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgINLINE TgVOID
tgSE_Module_Free( TgVOID ) {}

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgINLINE TgRESULT
tgSE_Module_Update(
    TgFLOAT32_C UNUSED_PARAM ARG0 ) { return KTgS_OK; }


/** @brief Standard Module functions: Set the current configuration of the module. */
TgINLINE TgRESULT
tgSE_Load_Config( TgVOID ) { return KTgS_OK; }

/** @brief Standard Module function: Save the current configuration of the module. */
TgINLINE TgRESULT
tgSE_Save_Config( TgVOID ) { return KTgS_OK; }


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgINLINE TgBOOL
tgSE_Query_Init( TgVOID ) { return true; }

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgINLINE TgBOOL
tgSE_Query_Boot( TgVOID ) { return true; }

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgINLINE TgRSIZE
tgSE_Query_Fixed_Memory( TgVOID ) { return 0u; }


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgINLINE TgVOID
tgSE_Init_Request(
    STg2_SE_CO_Request_F32_04_PCU UNUSED_PARAM ARG0) {}

TgINLINE TgRESULT
tgSE_Collide(
    STg2_SE_CO_Request_F32_04_PCU UNUSED_PARAM ARG0, ETgSE_CHANNEL_C UNUSED_PARAM ARG1 ) { return KTgS_OK; }


/* =============================================================================================================================================================================== */
#endif
