/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal - Data.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_DATA_H)
#if !defined (ENABLE_RELOAD_GUARD)


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Material - Object memory allocation is done by the generic code path. */
TgEXTN TgPH_MATERIAL_ID                     g_atiPH_Material_Default[ETgPH_MATERIAL__MAX];

/* Form - Object memory allocation is done by the generic code path. */

/* Body - Object memory allocation is done by the generic code path. */

/* Motor - Object memory allocation is done by the generic code path. */

/* Constraint - Object memory allocation is done by the generic code path. */
TgEXTN TgRSIZE                              g_aanuiPH_Constraint_Total__Used_By_Type[ETgPH_MAX_WORLD][ETgPH_CONSTRAINT__MAX];

/* Ragdoll - Object memory allocation is done by the generic code path. */

/* Scene */

/* World */

/* Contact */

/* Solver */

TgEXTN STg2_PH_Update__Simulation           g_asPH_Update__Simulation[KTgPH_MAX_WORLD];

/* Module */

TgEXTN STg2_UT_LF_ISO__RW                   g_sPH_Lock__Update_Module;

TgEXTN TgWORLD_UPDATE_COLLIDE_FCN           g_pfnPH_Update_World__Collide;
TgEXTN STg2_PA_PnS                          g_sPH_SG_PnS; //« Prune and Sweep scene graph used for active forms

                                            /* Run time Configuration */

TgEXTN TgBOOL                               g_bPH_Module__Paused; /**< True if the module is in a pause state, and false otherwise */
TgEXTN TgUINT_E64                           g_uiPH_Module__Loop_Max; /**< Maximum number of iterations allowed per frame */

TgEXTN TgCN_VAR_ID                          g_tiPH_CN_Module__Paused;
TgEXTN TgCN_VAR_ID                          g_tiPH_CN_Module__Loop_Max;

                                            /* Synchronization Fences */ 
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS[ETgPH_MAX_WORLD];
TgEXTN TgRSIZE_A                            g_axuiPH_FENCE__UPDATE_WORLD__FINISH[ETgPH_MAX_WORLD];

TgEXTN TgRSIZE_A                            g_axuiPH__UPDATE_WORLD__COLLISION_FIXES[ETgPH_MAX_WORLD];

                                            /* Jobs */
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Simulate_Batch[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Collide_Batch[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Build_Sets[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Solve_Sets[ETgPH_MAX_WORLD];
TgEXTN STg2_Job                             g_asPH__Job__Update_World__Finish[ETgPH_MAX_WORLD];

TgEXTN STg2_UT__CMD_BUF                     g_asPH_Command_To_World[KTgPH_MAX_WORLD + 1];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Internal - Data.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_INTERNAL_DATA_H


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  History Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_PHYSICS_HISTORY) && TgS_PHYSICS_HISTORY

TgEXTN TgVEC_F32_04_1                       g_vPH_History__Body_Pos_W[KTgPH_MAX_HISTORY_BODY];
TgEXTN TgVEC_F32_04_1                       g_vPH_History__Body_Rot_W[KTgPH_MAX_HISTORY_BODY];
TgEXTN TgPH_BODY_ID                         g_tiPH_History__Body_ID[KTgPH_MAX_HISTORY_BODY];
TgEXTN TgRSIZE_A                            g_xnuiPH_History;

//# defined(TgS_PHYSICS_HISTORY) && TgS_PHYSICS_HISTORY
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Data                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS

                                            /* Visualization */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Body_Enabled; /**< Debug Colour: Enabled Body */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Body_Sleep; /**< Debug Colour: Body is being considered for sleep (disabled)  */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Body_Disabled; /**< Debug Colour: Disabled Body */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Form_Enabled; /**< Debug Colour: Enabled Form */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Form_Disabled; /**< Debug Colour: Disabled Form */
TgEXTN TgVEC_F32_04_1                       g_vPH_Debug_Colour__Ragdoll; /**< Debug Colour: Ragdoll */

TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Body_Enabled;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Body_Sleep;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Body_Disabled;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Form_Enabled;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Form_Disabled;
TgEXTN TgCN_VAR_ID                          g_tiPH_Debug_Colour__Ragdoll;

//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Stat Data                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS

//# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS
#endif




/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Data Storage for Physics Objects in a combination of array of structure and structure of array approach. Data to be used by the solver is kept in a structure of array pattern.
   Data used for the individual object update is in an array of structure pattern.*/

#if !defined(T_STATIC)

TgEXTN TgRSIZE                              T_NAME_DECLARE(nuiPH_,_Increase_Commit); /**< The additional number of objects to commit to grow the total objects committed. */
TgEXTN TgRSIZE                              T_NAME_DECLARE(nuiPH_,_Total_Commit); /**< The total number of objects committed. */
TgEXTN TgRSIZE                              T_NAME_DECLARE(nuiPH_,_Total_Reserve); /**< The total number of objects reserved. */

TgEXTN STg2_UT_LF_ISO__ST                   T_NAME_DECLARE(sPH_,_Free_Stack); /**< Atomic stack of available objects. */
TgEXTN TgRSIZE_A                            T_NAME_DECLARE(xnuiPH_,); /**< Current count of the number of active objects. */
TgEXTN T_NAME(STg2_PH_,_P)                  T_NAME_DECLARE(asPH_,); /**< Array of all reserved objects. */

TgEXTN STg2_UT_LF_ISO__SN                   T_NAME_DECLARE(sPH_,_Commit_Lock); /**< Lock used to increase the number of committed objects in the array. */
TgEXTN T_NAME(STg2_PH_,_PP)                 T_NAME_DECLARE(apsPH_,_Used); /**< Array of pointers to all of the used objects. */
TgEXTN TgRSIZE                              T_NAME_DECLARE(nuiPH_,_Total__Used); /**< The total number of objects used. */

//# !defined(T_STATIC)
#else

TgEXTN T_NAME(STg2_PH_,)                    T_NAME_DECLARE(asPH_,)[T_ID(ETgPH_MAX_,)]; /**< Simple fixed array for this resource, one for each world. */
TgEXTN STg2_UT_LF_ISO__RW                   T_NAME_DECLARE(asPH_,_Data_Lock)[T_ID(ETgPH_MAX_,)]; /**< Guarantee that updates are done outside of data reading. */

//# !defined(T_STATIC)
#endif

//# defined (ENABLE_RELOAD_GUARD)
#endif

/* =============================================================================================================================================================================== */
//# defined (TGS_PHYSICS_INTERNAL_DATA_H)
#endif
