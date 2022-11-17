/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgRESULT
tgPH_Update_World__Job__Solve_Sets(
    STg2_Job_PC ARG0 );

static TgRESULT
tgPH_Update_World__Job__Simulate_Batch(
    STg2_Job_PC ARG0 );

static TgRESULT
tgPH_Update_World__Job__Collide_Batch(
    STg2_Job_PC ARG0 );

static TgRESULT
tgPH_Update_World__Job__Build_Sets(
    STg2_Job_PC ARG0 );

static TgRESULT
tgPH_Update_World__Job__Finish(
    STg2_Job_PC ARG0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Scene_Enable -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgPH_WORLD_ID tgPH_World_Query_World_Id( ETgPH_WORLD_C enWorld )
{
    if ((ETgPH_WORLD__BEGIN <= enWorld) && (enWorld <= ETgPH_WORLD__END))
    {
        return g_asPH_World[enWorld].m_tiWorld;
    }
    else
    {
        return KTgPH_WORLD_ID__INVALID;
    };
}


/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Pause_State,TgBOOL,m_uiPaused)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Single_Step,TgBOOL,m_uiSingle_Step)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Simulation_Enable,TgBOOL,m_uiSimulate)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Collision_Enable,TgBOOL,m_uiCollide)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Fixed_Time_Step,TgVEC_F32_04_1,m_vStep_Size)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Force_Field,TgVEC_F32_04_1,m_vForce_Field)

PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Threshold_Depth,TgFLOAT32,m_fThreshold__Depth)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Threshold_LV,TgVEC_F32_04_1,m_vThreshold__LV_LSQ)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(World,WORLD,Threshold_AV,TgVEC_F32_04_1,m_vThreshold__AV_LSQ)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

//PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(World,WORLD,Body_Count,TgRSIZE,m_nuiBody_Total__Used)
//PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(World,WORLD,Form_Count,TgRSIZE,m_nuiForm_Total__Used)
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(World,WORLD,Simulate_Batch_Size,TgRSIZE,m_uiSimulate_Min_Batch_Size)
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(World,WORLD,Collide_Batch_Size,TgRSIZE,m_uiCollide_Min_Batch_Size)


/* ---- tgPH_World_Init_Internal ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_World_Init_Internal( STg2_PH_World_P psWorld )
{
    TgPARAM_CHECK(nullptr != psWorld)

    tgPH_WORLD_ID_Init( &psWorld->m_tiWorld, (TgUINT_F32)(psWorld - g_asPH_World), 0, 0 );

    /* Solver Configuration */
    psWorld->m_uiSimulate_Min_Batch_Size = 50; // PIOMA
    psWorld->m_uiCollide_Min_Batch_Size = 50; // PIOMA
    psWorld->m_uiSolver_Min_Body_Per_Job = 50; // PIOMA
    psWorld->m_uiSolver_Min_DoF_Per_Job = 100; // PIOMA
    psWorld->m_nuiSolver_Iterations = 10; // PIOMA

    psWorld->m_fCFM = 0.0F; // PIOMA - TODO FILL THIS OUT
    psWorld->m_fStep_Size_Seconds = 1.0F / 60.0F;

    psWorld->m_fThreshold__Depth = 0.001F; // PIOMA
    psWorld->m_uiPad = 0;
    psWorld->m_vThreshold__LV_LSQ = tgMH_Init_Vector_ELEM_F32_04_1( 0.001F, 0.001F, 0.001F ); // PIOMA
    psWorld->m_vThreshold__AV_LSQ = tgMH_Init_Vector_ELEM_F32_04_1( 0.001F, 0.001F, 0.001F ); // PIOMA

    /* World Configuration */
    psWorld->m_vForce_Field = tgMH_Init_Vector_ELEM_F32_04_1( 0.0F, 9.81F, 0.0F );
    psWorld->m_vStep_Size = tgMH_SET1_F32_04_1( psWorld->m_fStep_Size_Seconds );

    /* Run Time Configuration */
    psWorld->m_uiPaused = 0;
    psWorld->m_uiSingle_Step = 0;
    psWorld->m_uiSimulate = 1;
    psWorld->m_uiCollide = 1;

    /* Serialization */
    psWorld->m_psScene = nullptr;
    return KTgS_OK;
}


/* ---- tgPH_World_Reset_Internal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_World_Reset_Internal( STg2_PH_World_P psWorld )
{
    (void)psWorld;
    return KTgE_FAIL;
}


/* ---- tgPH_Update_World__Init_Jobs --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Init_Jobs( TgVOID )
{
    TgRSIZE                             uiWorld_Index;

    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Simulate_Batch, sizeof( g_asPH__Job__Update_World__Simulate_Batch ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Collide_Batch, sizeof( g_asPH__Job__Update_World__Collide_Batch ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Build_Sets, sizeof( g_asPH__Job__Update_World__Build_Sets ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Solve_Sets, sizeof( g_asPH__Job__Update_World__Solve_Sets ) );
    tgMM_Set_U08_0x00( &g_asPH__Job__Update_World__Finish, sizeof( g_asPH__Job__Update_World__Finish ) );

    for (uiWorld_Index = 0; uiWorld_Index < ETgPH_MAX_WORLD; ++uiWorld_Index)
    {
        atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + uiWorld_Index, 0u );
        atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH + uiWorld_Index, 0u );
        atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + uiWorld_Index, 0u );
        atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + uiWorld_Index, 0u );
        atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__FINISH + uiWorld_Index, 0u );

        atomic_store( g_axuiPH__UPDATE_WORLD__COLLISION_FIXES + uiWorld_Index, 0u );

        g_asPH__Job__Update_World__Simulate_Batch[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Simulate_Batch;
        g_asPH__Job__Update_World__Simulate_Batch[uiWorld_Index].m_pxuiFinish = g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + uiWorld_Index;

        g_asPH__Job__Update_World__Collide_Batch[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Collide_Batch;
        g_asPH__Job__Update_World__Collide_Batch[uiWorld_Index].m_pxuiTrigger = g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + uiWorld_Index;
        g_asPH__Job__Update_World__Collide_Batch[uiWorld_Index].m_pxuiFinish = g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH + uiWorld_Index;

        g_asPH__Job__Update_World__Build_Sets[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Build_Sets;
        g_asPH__Job__Update_World__Build_Sets[uiWorld_Index].m_pxuiTrigger = g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH + uiWorld_Index;
        g_asPH__Job__Update_World__Build_Sets[uiWorld_Index].m_pxuiFinish = g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + uiWorld_Index;

        g_asPH__Job__Update_World__Solve_Sets[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Solve_Sets;
        g_asPH__Job__Update_World__Solve_Sets[uiWorld_Index].m_pxuiFinish = g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + uiWorld_Index;

        g_asPH__Job__Update_World__Finish[uiWorld_Index].m_pfnExecute = tgPH_Update_World__Job__Finish;
        g_asPH__Job__Update_World__Finish[uiWorld_Index].m_pxuiTrigger = g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + uiWorld_Index;
        g_asPH__Job__Update_World__Finish[uiWorld_Index].m_pxuiFinish = g_axuiPH_FENCE__UPDATE_WORLD__FINISH + uiWorld_Index;
    }
}


/* ---- tgPH_Update_World -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Pre-Conditions
    1. End of previous Simulation Frame (both server and client).
    2. Execute deferred commands from game thread (on the client).
   Execution
    1. Accumulate all known forces and moments (execute user specific force and moment generators) to create a predicted next step position and rotation.
    2. Run collision detection on all forms to prevent tunnelling and to create contact constraints.
        i. A collision scene graph should be used to optimize the O(n^2) performance.
        ii. Tunnelling corrections are modelled as an impulse on the body and added as an external force and moment.
    3. Construct all of the sets (self contained closed sets)
    4. Run the solver to determine the resulting final forces and moments.
    5. Construct the final next step position and rotation. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Update_World( TgPH_WORLD_ID_C tiWorld )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if ((nullptr == psWorld) || (0 == psWorld->m_uiSimulate_Min_Batch_Size))
    {
        return (KTgE_FAIL);
    };

    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
    {
        TgRSIZE_C                           nuiForm_World = g_anuiPH_Form_Total__Used[tiWorld.m_uiI];
        TgRSIZE_C                           nuiBody_World = g_anuiPH_Body_Total__Used[tiWorld.m_uiI];

        TgBOOL                              bIs_Paused;
        TgBOOL                              bRunSimulation;
        TgBOOL                              bRunCollision;

        atomic_store( g_axuiPH_FENCE__UPDATE_WORLD + tiWorld.m_uiI, 1 );

        /* Check the pause state for the world. */
        bIs_Paused  = 0 != psWorld->m_uiPaused;
        bIs_Paused &= 0 == psWorld->m_uiSingle_Step;
        bIs_Paused |= tgPH_Is_Module_Paused();

        /* Check for the conditions to run the simulation. */
        bRunSimulation = !bIs_Paused && (0 != psWorld->m_uiSimulate) && (psWorld->m_uiSimulate_Min_Batch_Size > 0) && (nuiBody_World > 0);

        /* Simulation Pass: Determine the forces and moments assuming no constraints */
        if (bRunSimulation)
        {
            TgRSIZE                             uiSimulate_Min_Batch_Size;
            STg2_Job_P                          psJob;
            TgRSIZE                             uiBody_Index;

            /* Calculate the number of jobs (batches) to create, and the number of bodies per job (batch). */
            uiSimulate_Min_Batch_Size = psWorld->m_uiSimulate_Min_Batch_Size;
            if (((nuiBody_World + uiSimulate_Min_Batch_Size - 1) / uiSimulate_Min_Batch_Size) >= KTgPH_MAX_SIMULATION_JOB)
            {
                uiSimulate_Min_Batch_Size = (nuiBody_World + KTgPH_MAX_SIMULATION_JOB - 1) / KTgPH_MAX_SIMULATION_JOB;
            };

            /* Allocate memory for the output data structure from simulation for the solver. */
            g_asPH_Update__Simulation[tiWorld.m_uiI].m_avPos_W = (TgVEC_F32_04_1_P)TgMALLOC_POOL( sizeof(TgVEC_F32_04_1) * nuiBody_World );
            g_asPH_Update__Simulation[tiWorld.m_uiI].m_avRot_W = (TgVEC_F32_04_1_P)TgMALLOC_POOL( sizeof(TgVEC_F32_04_1) * nuiBody_World );
            g_asPH_Update__Simulation[tiWorld.m_uiI].m_avRHS_LA = (TgVEC_F32_04_1_P)TgMALLOC_POOL( sizeof(TgVEC_F32_04_1) * 2 * nuiBody_World );

            /* Set the fence to be the total number of bodies in the world. */
            atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + tiWorld.m_uiI, nuiBody_World );

            /* Create all of the jobs necessary to batch the simulation calls for all bodies. */
            psJob = g_asPH__Job__Update_World__Simulate_Batch + tiWorld.m_uiI;
            for (uiBody_Index = 0; uiBody_Index < nuiBody_World; uiBody_Index += uiSimulate_Min_Batch_Size)
            {
                union { STg2_PH_Job__Update_World__Simulate_Data_P psSimulate_Data; TgUINT_F08_P pui; } const psJob_Data = { .pui  = psJob->m_auiData };

                psJob_Data.psSimulate_Data->m_tiWorld = tiWorld;
                psJob_Data.psSimulate_Data->m_uiBody_Index_Begin = uiBody_Index;
                psJob_Data.psSimulate_Data->m_uiBody_Index_End = tgCM_MIN_UMAX( uiBody_Index + uiSimulate_Min_Batch_Size, nuiBody_World );

                if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
                {
                    TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                    tgPH_Update_World__Job__Simulate_Batch( psJob );
                };
            };
        };

        /* Check for the conditions to run collision. */
        bRunCollision = !bIs_Paused && (0 != psWorld->m_uiCollide) && (psWorld->m_uiCollide_Min_Batch_Size > 0) && (nuiForm_World > 0);

        /* Collision Pass: Check for collisions, prevent tunnelling and create contact constraints. */
        if (bRunCollision)
        {
            TgRSIZE                             uiCollide_Min_Batch_Size;
            STg2_Job_P                          psJob;
            TgRSIZE                             uiForm_Index;

            /* Calculate the number of jobs (batches) to create, and the number of bodies per job (batch). */
            uiCollide_Min_Batch_Size = psWorld->m_uiCollide_Min_Batch_Size;
            if (((nuiForm_World + uiCollide_Min_Batch_Size - 1) / uiCollide_Min_Batch_Size) >= KTgPH_MAX_COLLIDE_JOB)
            {
                uiCollide_Min_Batch_Size = (nuiForm_World + KTgPH_MAX_COLLIDE_JOB - 1) / KTgPH_MAX_COLLIDE_JOB;
            };

            /* Set the fence to be the total number of forms in the world. */
            atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH + tiWorld.m_uiI, nuiForm_World );

            /* Create all of the jobs necessary to batch the collide calls for all forms. */
            psJob = g_asPH__Job__Update_World__Collide_Batch + tiWorld.m_uiI;
            for (uiForm_Index = 0; uiForm_Index < nuiForm_World; uiForm_Index += uiCollide_Min_Batch_Size)
            {
                union { STg2_PH_Job__Update_World__Collide_Data_P psCollide_Data; TgUINT_F08_P pui; } const psJob_Data = { .pui  = psJob->m_auiData };

                psJob_Data.psCollide_Data->m_tiWorld = tiWorld;
                psJob_Data.psCollide_Data->m_uiForm_Index_Begin = uiForm_Index;
                psJob_Data.psCollide_Data->m_uiForm_Index_End = tgCM_MIN_UMAX( uiForm_Index + uiCollide_Min_Batch_Size, nuiForm_World );
                psJob_Data.psCollide_Data->m_bExecute_Command_Buffer = !bRunSimulation;

                if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
                {
                    TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
//# TODO Need to make sure all the simulate jobs are done
                    tgPH_Update_World__Job__Collide_Batch( psJob );
                };
            };
        };

        /* Build the Sets, Solve, and then Update the Bodies. */
        if (bRunSimulation)
        {
            STg2_Job_PC                         psJob = g_asPH__Job__Update_World__Build_Sets + tiWorld.m_uiI;

            union { STg2_PH_Job__Update_World__Build_Set_Data_P psBuild_Set_Data; TgUINT_F08_P pui; } const psJob_Data = { .pui  = psJob->m_auiData };

            psJob_Data.psBuild_Set_Data->m_tiWorld = tiWorld;
            atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + tiWorld.m_uiI, 1 );
            if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, g_asPH__Job__Update_World__Build_Sets + tiWorld.m_uiI )))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                tgPH_Update_World__Job__Build_Sets( g_asPH__Job__Update_World__Build_Sets + tiWorld.m_uiI );
            };
        };

        /* Update based on resulting forces and moments. */
        if (!bRunSimulation && !bRunCollision)
        {
            atomic_fetch_sub( g_axuiPH_FENCE__UPDATE_WORLD + tiWorld.m_uiI, 1 );
            tgCM_UT__CMD_BUF__Execute( g_asPH_Command_To_World + tiWorld.m_uiI );
        };
    }
    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Job__Simulate_Batch ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Simulate_Batch( STg2_Job_PC psJob )
{
    union { STg2_PH_Job__Update_World__Simulate_Data_P psSimulate_Data; TgUINT_F08_P pui; } const psJob_Data = { .pui  = psJob->m_auiData };
    TgERROR(psJob_Data.psSimulate_Data);

    PROFILE_ARRAY_START( psJob_Data.psSimulate_Data->m_tiWorld.m_uiI, PH_SIMULATE_BATCH, tgPH_Update_World__Job__Solver_Batch ); /* Profile Tag for this particular world. */
    PROFILE_START( PH_SIMULATE_BATCH_TOTAL, tgPH_Update_World__Job__Solver_Batch ); /* Profile Tag for all of the batches. */
    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[psJob_Data.psSimulate_Data->m_tiWorld.m_uiI ].m_sLock );

    if (nullptr == tgPH_World_Get_World_From_ID( psJob_Data.psSimulate_Data->m_tiWorld ))
    {
        tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psSimulate_Data->m_tiWorld.m_uiI ].m_sLock );
        return (KTgS_OK);
    };

    tgPH_Update_World__Simulate_Batch(
        psJob_Data.psSimulate_Data->m_tiWorld,
        psJob_Data.psSimulate_Data->m_uiBody_Index_Begin,
        psJob_Data.psSimulate_Data->m_uiBody_Index_End );

    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psSimulate_Data->m_tiWorld.m_uiI ].m_sLock );
    PROFILE_STOP( PH_SIMULATE_BATCH_TOTAL, tgPH_Update_World__Job__Solver_Batch );
    PROFILE_ARRAY_STOP( psJob_Data.psSimulate_Data->m_tiWorld.m_uiI, PH_SIMULATE_BATCH, tgPH_Update_World__Job__Solver_Batch );

    atomic_thread_fence( cxx__memory_order_seq_cst );
    atomic_fetch_sub( g_axuiPH_FENCE__UPDATE_WORLD__SIMULATE_BATCH + psJob_Data.psSimulate_Data->m_tiWorld.m_uiI,
                      psJob_Data.psSimulate_Data->m_uiBody_Index_End - psJob_Data.psSimulate_Data->m_uiBody_Index_Begin );

    TgERROR(nullptr != tgPH_World_Get_World_From_ID( psJob_Data.psSimulate_Data->m_tiWorld ));
    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Job__Collide_Batch ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Collide_Batch( STg2_Job_PC psJob )
{
    union { STg2_PH_Job__Update_World__Collide_Data_P psCollide_Data; TgUINT_F08_P pui; } const psJob_Data = { .pui  = psJob->m_auiData };
    TgERROR(psJob_Data.psCollide_Data);

    PROFILE_ARRAY_START( psJob_Data.psCollide_Data->m_tiWorld.m_uiI, PH_COLLIDE_BATCH, tgPH_Update_World__Job__Solver_Batch ); /* Profile Tag for this particular world. */
    PROFILE_START( PH_COLLIDE_BATCH_TOTAL, tgPH_Update_World__Job__Solver_Batch ); /* Profile Tag for all of the batches. */
    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[psJob_Data.psCollide_Data->m_tiWorld.m_uiI ].m_sLock );

    if (nullptr == tgPH_World_Get_World_From_ID( psJob_Data.psCollide_Data->m_tiWorld ))
    {
        tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psCollide_Data->m_tiWorld.m_uiI ].m_sLock );
        return (KTgS_OK);
    };

    tgPH_Update_World__Collide_Batch( psJob_Data.psCollide_Data->m_tiWorld, psJob_Data.psCollide_Data->m_uiForm_Index_Begin, psJob_Data.psCollide_Data->m_uiForm_Index_End );

    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psCollide_Data->m_tiWorld.m_uiI ].m_sLock );
    PROFILE_STOP( PH_COLLIDE_BATCH_TOTAL, tgPH_Update_World__Job__Solver_Batch );
    PROFILE_ARRAY_STOP( psJob_Data.psCollide_Data->m_tiWorld.m_uiI, PH_COLLIDE_BATCH, tgPH_Update_World__Job__Solver_Batch );

    atomic_thread_fence( cxx__memory_order_seq_cst );
    atomic_fetch_sub( g_axuiPH_FENCE__UPDATE_WORLD__COLLIDE_BATCH + psJob_Data.psCollide_Data->m_tiWorld.m_uiI,
                      psJob_Data.psCollide_Data->m_uiForm_Index_End - psJob_Data.psCollide_Data->m_uiForm_Index_Begin );

    if (psJob_Data.psCollide_Data->m_bExecute_Command_Buffer)
    {
        tgCM_UT__CMD_BUF__Execute( g_asPH_Command_To_World + psJob_Data.psCollide_Data->m_tiWorld.m_uiI );
    }

    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Job__Build_Sets --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Build_Sets( STg2_Job_PC psJob )
{
    union { STg2_PH_Job__Update_World__Build_Set_Data_P psBuild_Sets_Data; TgUINT_F08_P pui; } const psJob_Data = { .pui  = psJob->m_auiData };
    TgERROR(psJob_Data.psBuild_Sets_Data);

    PROFILE_ARRAY_START( psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI, PH_BUILD_SETS, tgPH_Update_World__Job__Solver_Batch );
    PROFILE_START( PH_BUILD_SETS_TOTAL, tgPH_Update_World__Job__Solver_Batch );
    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI ].m_sLock );

    if (nullptr == tgPH_World_Get_World_From_ID( psJob_Data.psBuild_Sets_Data->m_tiWorld ))
    {
        tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI ].m_sLock );
        return (KTgS_OK);
    };

    tgPH_Update_World__Build_Sets( psJob_Data.psBuild_Sets_Data->m_tiWorld );

    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI ].m_sLock );
    PROFILE_STOP( PH_BUILD_SETS_TOTAL, tgPH_Update_World__Job__Solver_Batch );
    PROFILE_ARRAY_STOP( psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI, PH_BUILD_SETS, tgPH_Update_World__Job__Solver_Batch );

    atomic_thread_fence( cxx__memory_order_seq_cst );
    atomic_fetch_sub( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI, 1 );

    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, g_asPH__Job__Update_World__Finish + psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        tgPH_Update_World__Job__Finish( g_asPH__Job__Update_World__Finish + psJob_Data.psBuild_Sets_Data->m_tiWorld.m_uiI );
    };

    return (KTgS_OK);
}

/* ---- tgPH_Update_World__Job__Solve_Sets --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Update_World__Job__Solve_Sets( STg2_Job_PC psJob )
{
    union { STg2_PH_Job__Update_World__Solve_Set_Data_P psSolve_Sets_Data; TgUINT_F08_P pui; } const psJob_Data = { .pui  = psJob->m_auiData };
    TgERROR(psJob_Data.psSolve_Sets_Data);

    PROFILE_ARRAY_START( psJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI, PH_SOLVE_SETS, tgPH_Update_World__Job__Solver_Batch ); /* Profile Tag for this particular world. */
    PROFILE_START( PH_SOLVE_SETS_TOTAL, tgPH_Update_World__Job__Solver_Batch ); /* Profile Tag for all of the batches. */
    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[psJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI ].m_sLock );

    if (nullptr == tgPH_World_Get_World_From_ID( psJob_Data.psSolve_Sets_Data->m_tiWorld ))
    {
        tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI ].m_sLock );
        return (KTgS_OK);
    };

    tgPH_Update_World__Define_Problem_And_Solve(
        psJob_Data.psSolve_Sets_Data->m_tiWorld,
        &psJob_Data.psSolve_Sets_Data->m_sSolver_Set );

    tgPH_Update_World__Update_Bodies(
        psJob_Data.psSolve_Sets_Data->m_tiWorld,
        &psJob_Data.psSolve_Sets_Data->m_sSolver_Set );

    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[psJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI ].m_sLock );
    PROFILE_STOP( PH_SOLVE_SETS_TOTAL, tgPH_Update_World__Job__Solver_Batch );
    PROFILE_ARRAY_STOP( psJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI, PH_SOLVE_SETS, tgPH_Update_World__Job__Solver_Batch );

    atomic_thread_fence( cxx__memory_order_seq_cst );
    atomic_fetch_sub( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + psJob_Data.psSolve_Sets_Data->m_tiWorld.m_uiI, 1 );

    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Job__Finish ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT tgPH_Update_World__Job__Finish( STg2_Job_PC psJob )
{
    union { STg2_PH_Job__Update_World__Build_Set_Data_P psJob; TgUINT_F08_P pui; } const psData = { .pui  = psJob->m_auiData };
    TgERROR(psData.psJob);

    atomic_fetch_sub( g_axuiPH_FENCE__UPDATE_WORLD + psData.psJob->m_tiWorld.m_uiI, 1 );

    if (nullptr != g_asPH_Update__Simulation[psData.psJob->m_tiWorld.m_uiI].m_avPos_W)
        TgFREE_POOL( g_asPH_Update__Simulation[psData.psJob->m_tiWorld.m_uiI].m_avPos_W );
    if (nullptr != g_asPH_Update__Simulation[psData.psJob->m_tiWorld.m_uiI].m_avRot_W)
        TgFREE_POOL( g_asPH_Update__Simulation[psData.psJob->m_tiWorld.m_uiI].m_avRot_W );
    if (nullptr != g_asPH_Update__Simulation[psData.psJob->m_tiWorld.m_uiI].m_avRHS_LA)
        TgFREE_POOL( g_asPH_Update__Simulation[psData.psJob->m_tiWorld.m_uiI].m_avRHS_LA );

    tgMM_Set_U08_0x00( g_asPH_Update__Simulation + psData.psJob->m_tiWorld.m_uiI, sizeof(STg2_PH_Update__Simulation) );

    tgCM_UT__CMD_BUF__Execute( g_asPH_Command_To_World + psData.psJob->m_tiWorld.m_uiI );
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_World_Validate ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
TgVOID tgPH_World_Validate( STg2_Output_PC psOUT, TgPH_WORLD_ID_C tiWorld )
{
//# TODO: tgPH_World_Validate
    (void)psOUT;
    (void)tiWorld;

}
//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif
