/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Data.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD)
/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Profile Markers                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PROFILE_DEFINE( PH_COMMANDS__CLIENT );

#if defined(TgBUILD_FEATURE__CLIENT) || defined(TgBUILD_FEATURE__SERVER)
PROFILE_ARRAY_DEFINE( ETgPH_MAX_WORLD, PH_SIMULATE_BATCH );
PROFILE_DEFINE( PH_SIMULATE_BATCH_TOTAL );

PROFILE_ARRAY_DEFINE( ETgPH_MAX_WORLD, PH_COLLIDE_BATCH );
PROFILE_DEFINE( PH_COLLIDE_BATCH_TOTAL );

PROFILE_ARRAY_DEFINE( ETgPH_MAX_WORLD, PH_BUILD_SETS );
PROFILE_DEFINE( PH_BUILD_SETS_TOTAL );

PROFILE_ARRAY_DEFINE( ETgPH_MAX_WORLD, PH_SOLVE_SETS );
PROFILE_DEFINE( PH_SOLVE_SETS_TOTAL );

PROFILE_ARRAY_DEFINE( ETgPH_MAX_WORLD, PH_UPDATE_WORLD__SIMULATE_BATCH );
PROFILE_DEFINE( PH_SOLVER_BATCH_TOTAL );
/*# defined(TgBUILD_FEATURE__CLIENT) || defined(TgBUILD_FEATURE__SERVER) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Material                                                                                                                                                                        */
TgPH_MATERIAL_ID                            g_atiPH_Material_Default[ETgPH_MATERIAL__MAX];

/* Constraint - Object memory allocation is done by the generic code path. */
TgRSIZE                                     g_aanuiPH_Constraint_Total__Used_By_Type[ETgPH_MAX_WORLD][ETgPH_CONSTRAINT__MAX];

/* World */

/* Solver */

STg2_PH_Update__Simulation                  g_asPH_Update__Simulation[KTgPH_MAX_WORLD];

/* Module */

STg2_UT_LF_ISO__RW                          g_sPH_Lock__Update_Module;

TgWORLD_UPDATE_COLLIDE_FCN                  g_pfnPH_Update_World__Collide;
STg2_PA_PnS                                 g_sPH_SG_PnS; //« Prune and Sweep scene graph used for active forms

                                            /* Run time Configuration */

TgBOOL                                      g_bPH_Module__Paused; /**< True if the module is in a pause state, and false otherwise */
TgUINT_E64                                  g_uiPH_Module__Loop_Max; /**< Maximum number of iterations allowed per frame */

TgCN_VAR_ID                                 g_tiPH_CN_Module__Paused;
TgCN_VAR_ID                                 g_tiPH_CN_Module__Loop_Max;

        
                                            /* Synchronization Fences */
TgRSIZE_A                                   g_axuiPH_FENCE__UPDATE_WORLD[ETgPH_MAX_WORLD];
TgRSIZE_A                                   g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH[ETgPH_MAX_WORLD];
TgRSIZE_A                                   g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH[ETgPH_MAX_WORLD];
TgRSIZE_A                                   g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS[ETgPH_MAX_WORLD];
TgRSIZE_A                                   g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS[ETgPH_MAX_WORLD];
TgRSIZE_A                                   g_axuiPH_FENCE__UPDATE_WORLD__FINISH[ETgPH_MAX_WORLD];

TgRSIZE_A                                   g_axuiPH__UPDATE_WORLD__COLLISION_FIXES[ETgPH_MAX_WORLD];

                                            /* Jobs */
STg2_Job                                    g_asPH__Job__Update_World__Simulate_Batch[ETgPH_MAX_WORLD];
STg2_Job                                    g_asPH__Job__Update_World__Collide_Batch[ETgPH_MAX_WORLD];
STg2_Job                                    g_asPH__Job__Update_World__Build_Sets[ETgPH_MAX_WORLD];
STg2_Job                                    g_asPH__Job__Update_World__Solve_Sets[ETgPH_MAX_WORLD];
STg2_Job                                    g_asPH__Job__Update_World__Finish[ETgPH_MAX_WORLD];

//STg2_PA_PnS_P                               g_psPH_SG_PnS; //« Prune and Sweep scene graph used for active forms

STg2_UT__CMD_BUF                            g_asPH_Command_To_World[KTgPH_MAX_WORLD + 1];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Data.c"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  History Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_PHYSICS_HISTORY) && TgS_PHYSICS_HISTORY

TgVEC_F32_04_1                              g_vPH_History__Body_Pos_W[KTgPH_MAX_HISTORY_BODY];
TgVEC_F32_04_1                              g_vPH_History__Body_Rot_W[KTgPH_MAX_HISTORY_BODY];
TgPH_BODY_ID                                g_tiPH_History__Body_ID[KTgPH_MAX_HISTORY_BODY];
TgRSIZE_A                                   g_xnuiPH_History;

//# defined(TgS_PHYSICS_HISTORY) && TgS_PHYSICS_HISTORY
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Data                                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
                                            /* Visualization */
TgVEC_F32_04_1                              g_vPH_Debug_Colour__Body_Enabled;
TgVEC_F32_04_1                              g_vPH_Debug_Colour__Body_Sleep;
TgVEC_F32_04_1                              g_vPH_Debug_Colour__Body_Disabled;
TgVEC_F32_04_1                              g_vPH_Debug_Colour__Form_Enabled;
TgVEC_F32_04_1                              g_vPH_Debug_Colour__Form_Disabled;
TgVEC_F32_04_1                              g_vPH_Debug_Colour__Ragdoll;

TgCN_VAR_ID                                 g_tiPH_Debug_Colour__Body_Enabled;
TgCN_VAR_ID                                 g_tiPH_Debug_Colour__Body_Sleep;
TgCN_VAR_ID                                 g_tiPH_Debug_Colour__Body_Disabled;
TgCN_VAR_ID                                 g_tiPH_Debug_Colour__Form_Enabled;
TgCN_VAR_ID                                 g_tiPH_Debug_Colour__Form_Disabled;
TgCN_VAR_ID                                 g_tiPH_Debug_Colour__Ragdoll;
/*# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS */
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Stat Data                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS

//# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgPH_Query_Fixed_Memory( TgVOID )
{
    return (0
           + sizeof( g_atiPH_Material_Default )
           + sizeof( g_aanuiPH_Constraint_Total__Used_By_Type )
           + sizeof( g_asPH_Update__Simulation )
           + sizeof( g_sPH_Lock__Update_Module )
           + sizeof( g_pfnPH_Update_World__Collide )
           + sizeof( g_sPH_SG_PnS )
           + sizeof( g_bPH_Module__Paused )
           + sizeof( g_uiPH_Module__Loop_Max )
           + sizeof( g_tiPH_CN_Module__Paused )
           + sizeof( g_tiPH_CN_Module__Loop_Max )
           + sizeof( g_axuiPH_FENCE__UPDATE_WORLD )
           + sizeof( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH )
           + sizeof( g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH )
           + sizeof( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS )
           + sizeof( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS )
           + sizeof( g_axuiPH_FENCE__UPDATE_WORLD__FINISH )
           + sizeof( g_axuiPH__UPDATE_WORLD__COLLISION_FIXES )
           + sizeof( g_asPH__Job__Update_World__Simulate_Batch )
           + sizeof( g_asPH__Job__Update_World__Collide_Batch )
           + sizeof( g_asPH__Job__Update_World__Build_Sets )
           + sizeof( g_asPH__Job__Update_World__Solve_Sets )
           + sizeof( g_asPH__Job__Update_World__Finish )
           + sizeof( g_asPH_Command_To_World )

           + tgPH_Query_Material_Fixed_Memory()
           + tgPH_Query_Form_Fixed_Memory()
           + tgPH_Query_Body_Fixed_Memory()
           + tgPH_Query_Constraint_Fixed_Memory()
           + tgPH_Query_Motor_Fixed_Memory()
           + tgPH_Query_Ragdoll_Fixed_Memory()
           + tgPH_Query_Scene_Fixed_Memory()
           + tgPH_Query_World_Fixed_Memory()

        #if defined(TgS_PHYSICS_HISTORY) && TgS_PHYSICS_HISTORY
            + sizeof( g_vPH_History__Body_Pos_W )
            + sizeof( g_vPH_History__Body_Rot_W )
            + sizeof( g_tiPH_History__Body_ID )
            + sizeof( g_xnuiPH_History )
        //# defined(TgS_PHYSICS_HISTORY) && TgS_PHYSICS_HISTORY
        #endif

         #if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
            + sizeof( g_vPH_Debug_Colour__Body_Enabled )
            + sizeof( g_vPH_Debug_Colour__Body_Sleep )
            + sizeof( g_vPH_Debug_Colour__Body_Disabled )
            + sizeof( g_vPH_Debug_Colour__Form_Enabled )
            + sizeof( g_vPH_Debug_Colour__Form_Disabled )
            + sizeof( g_vPH_Debug_Colour__Ragdoll )
            + sizeof( g_tiPH_Debug_Colour__Body_Enabled )
            + sizeof( g_tiPH_Debug_Colour__Body_Sleep )
            + sizeof( g_tiPH_Debug_Colour__Body_Disabled )
            + sizeof( g_tiPH_Debug_Colour__Form_Enabled )
            + sizeof( g_tiPH_Debug_Colour__Form_Disabled )
            + sizeof( g_tiPH_Debug_Colour__Ragdoll )
         /*# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS */
         #endif
    );
}




/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Data                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgKI_DEFINE( T_ID(PH_,_ID) );

/* Data Storage for Physics Objects in a combination of array of structure and structure of array approach. Data to be used by the solver is kept in a structure of array pattern.
   Data used for the individual object update is in an array of structure pattern.*/

#if !defined(T_STATIC)

TgRSIZE                                     T_NAME_DECLARE(nuiPH_,_Increase_Commit); /**< The additional number of nodes to commit to grow the total nodes committed. */
TgRSIZE                                     T_NAME_DECLARE(nuiPH_,_Total_Commit); /**< The total number of nodes committed. */
TgRSIZE                                     T_NAME_DECLARE(nuiPH_,_Total_Reserve); /**< The total number of nodes reserved. */

STg2_UT_LF_ISO__ST                          T_NAME_DECLARE(sPH_,_Free_Stack); /**< Atomic stack of available objects. */
TgRSIZE_A                                   T_NAME_DECLARE(xnuiPH_,); /**< Current count of the number of active objects. */
STg2_UT_LF_ISO__SN                          T_NAME_DECLARE(sPH_,_Commit_Lock); /**< Lock used to increase the number of committed objects in the array. */
T_NAME(STg2_PH_,_P)                         T_NAME_DECLARE(asPH_,); /**< Array of all reserved objects. */

T_NAME(STg2_PH_,_PP)                        T_NAME_DECLARE(apsPH_,_Used); /**< Array of pointers to all of the used objects. */
TgRSIZE                                     T_NAME_DECLARE(nuiPH_,_Total__Used); /**< The total number of nodes used. */

/* ---- T_NAME(tgPH_Query_,_Fixed_Memory) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRSIZE T_NAME(tgPH_Query_,_Fixed_Memory)( TgVOID )
{
    return (0
           + sizeof( T_NAME_DECLARE(nuiPH_,_Increase_Commit) )
           + sizeof( T_NAME_DECLARE(nuiPH_,_Total_Commit) )
           + sizeof( T_NAME_DECLARE(nuiPH_,_Total_Reserve) )
           + sizeof( T_NAME_DECLARE(sPH_,_Free_Stack) )
           + sizeof( T_NAME_DECLARE(xnuiPH_,) )
           + sizeof( T_NAME_DECLARE(sPH_,_Commit_Lock) )
           + sizeof( T_NAME_DECLARE(asPH_,) )
           + sizeof( T_NAME_DECLARE(apsPH_,_Used) )
           + sizeof( T_NAME_DECLARE(nuiPH_,_Total__Used) )
    );
}

//# !defined(T_STATIC)
#else

T_NAME(STg2_PH_,)                           T_NAME_DECLARE(asPH_,)[T_ID(ETgPH_MAX_,)]; /**< Simple fixed array for this resource, one for each world. */
STg2_UT_LF_ISO__RW                          T_NAME_DECLARE(asPH_,_Data_Lock)[T_ID(ETgPH_MAX_,)]; /**< Guarantee that updates are done outside of data reading. */

/* ---- T_NAME(tgPH_Query_,_Fixed_Memory) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRSIZE T_NAME(tgPH_Query_,_Fixed_Memory)( TgVOID )
{
    return (0
           + sizeof( T_NAME_DECLARE(asPH_,) )
           + sizeof( T_NAME_DECLARE(asPH_,_Data_Lock) )
    );
}

//# !defined(T_STATIC)
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#endif












































