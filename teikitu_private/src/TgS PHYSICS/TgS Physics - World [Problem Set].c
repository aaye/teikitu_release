/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World [Problem Set].c
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

static TgVOID
tgPH_Update_World__Init_Solver_Set(
    STg2_PH_Solver__Set_PC ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgRSIZE_P ARG3 );

#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
static TgVOID
tgPH_Update_World__Build_Sets__Validate( 
    TgPH_WORLD_ID_C ARG0, TgUINT_E64_P ARG1, TgUINT_E64_P ARG2 );
//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Build_Sets -------------------------------------------------------------------------------------------------------------------------------------------- */
/* PreCondition: World Data Lock. Parameters are known to be valid                                                                                                                 */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Update_World__Build_Sets( TgPH_WORLD_ID_C tiWorld )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld)
    {
        return (KTgE_FAIL);
    }

    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
    if (g_anuiPH_Body_Total__Used[tiWorld.m_uiI] <= 0)
    {
        tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
        return (KTgS_OK);
    }

    /* Reset the solve counts. */
    atomic_store( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + tiWorld.m_uiI, 0 );

    {
        STg2_Job_PC                         psJob = g_asPH__Job__Update_World__Solve_Sets + tiWorld.m_uiI;
        union { STg2_PH_Job__Update_World__Solve_Set_Data_P psSolve_Set_Data; TgUINT_F08_P pui; } const sJob_Data = { .pui  = psJob->m_auiData };

        STg2_PH_Solver__Set_PC              psSolver_Set = &sJob_Data.psSolve_Set_Data->m_sSolver_Set;

        TgRSIZE_C                           nuiBody_World = g_anuiPH_Body_Total__Used[tiWorld.m_uiI];
        TgRSIZE_C                           nuiConstraint_World = g_anuiPH_Constraint_Total__Used[tiWorld.m_uiI];
        TgRSIZE_C                           nuiCollision_Fixes = atomic_load( g_axuiPH__UPDATE_WORLD__COLLISION_FIXES + tiWorld.m_uiI );

        TgUINT_E64_P                        auiVisited_Body; // Bitfield to track when a body is added to a set.
        TgUINT_E64_P                        auiVisited_Constraint; // Bitfield to track when a constraint is added to a set.
        STg2_PH_Body_PP                     apsBody_Stack;

        TgRSIZE                             uiCollision_Index;
        TgRSIZE                             nuiBody_Stack;
        TgRSIZE                             uiIndex_Body;
        TgPH_BODY_ID                        tiBody;
        STg2_PH_Body_P                      psBody;
        TgPH_CONSTRAINT_ID                  tiConstraint;
        STg2_PH_Constraint_P                psConstraint;
        TgBOOL                              bFinish_Batch;
        TgFLOAT32                           fMax_Disable_Timer;
        TgRSIZE                             uiSet_Start;

        tgMM_Set_U08_0x00( psSolver_Set, sizeof( STg2_PH_Solver__Set ) );
        sJob_Data.psSolve_Set_Data->m_tiWorld = tiWorld;

        /* The collision system is responsible for preventing bodies from generating overly large penetrations or tunnelling. Since collision is executed on the list of forms, it
           is necessary to aggregate the corrections on a per body basis once all of the corrections are known. */

        #pragma region Tunneling Fixes
//# TODO: Tunneling Fixes
        for (uiCollision_Index = 0; uiCollision_Index < nuiCollision_Fixes; ++uiCollision_Index)
        {
        };
        #pragma endregion

        /* The goal of set generation is to create a sequence of closed sets (all bodies, constraints and contacts in a set only involve other entities in the set) that result in
           an even amount of computation. In the case where it is not possible to have even work loads, then the heavier jobs should come first as they will have more time to
           complete. The heuristic to determine an even amount of computation is to use the number of bodies and the total number of degrees of freedom to be determined. A set is
           a component of the graph constructed using bodies as the nodes, and constraints as the edges. */

        #pragma region Memory Allocation - Function Local
        auiVisited_Body = (TgUINT_E64_P)TgMALLOC_TEMP( sizeof( TgUINT_E64 ) * ((nuiBody_World + 63) >> 6) );
        TgCRITICAL_MSGF( nullptr != auiVisited_Body, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
        tgMM_Set_U08_0x00( auiVisited_Body, sizeof( TgUINT_E64 ) * ((nuiBody_World + 63) >> 6) );

        nuiBody_Stack = 0;

        if (nuiConstraint_World > 0)
        {
            auiVisited_Constraint = (TgUINT_E64_P)TgMALLOC_TEMP( sizeof( TgUINT_E64 ) * ((nuiConstraint_World + 63) >> 6) );
            TgCRITICAL_MSGF( nullptr != auiVisited_Constraint, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
            tgMM_Set_U08_0x00( auiVisited_Constraint, sizeof( TgUINT_E64 ) * ((nuiConstraint_World + 63) >> 6) );

            apsBody_Stack = (STg2_PH_Body_PP)TgMALLOC_TEMP( sizeof( STg2_PH_Body_P ) * tgCM_MIN_UMAX( nuiBody_World, nuiConstraint_World ) );
            TgCRITICAL_MSGF( nullptr != apsBody_Stack, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
        }
        else
        {
            auiVisited_Constraint = nullptr;
            apsBody_Stack = nullptr;
        }
        #pragma endregion

        #pragma region Memory Allocation - Solver Set
        tgPH_Update_World__Init_Solver_Set( psSolver_Set, nuiBody_World, nuiConstraint_World, g_aanuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] );
        #pragma endregion

        #pragma region Create the Closed Sets to be Solved
        for (uiIndex_Body = 0; uiIndex_Body < nuiBody_World; ++uiIndex_Body)
        {
            /* Test the visited bit for this body. */
            if (0 != (auiVisited_Body[uiIndex_Body >> 6] & (uiIndex_Body & 63ULL)))
                continue;

            /* Test the disabled bit for this body. */
            psBody = g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex_Body];
            if (true != psBody->m_bEnabled)
                continue;

            /* Mark the body as visited. */
            auiVisited_Body[uiIndex_Body >> 6] |= (uiIndex_Body & 63ULL);
            nuiBody_Stack = 0;
            fMax_Disable_Timer = 0.0F;
            uiSet_Start = psSolver_Set->m_nuiBody;
            while(1)
            {
                TgVEC_F32_04_1_C                    vTMP_00 = tgMH_NMS_F32_04_1( psBody->m_vPos_W, psBody->m_vTunneling, psBody->m_vPos_W );

                #pragma region Add a body to the Set
                /* Assign the body into the set. */
                psSolver_Set->m_apsBody[psSolver_Set->m_nuiBody] = psBody;
                ++psSolver_Set->m_nuiBody;
                psBody->m_bEnabled = true;
                fMax_Disable_Timer = tgCM_MAX_F32( fMax_Disable_Timer, psBody->m_fDisable_Timer );

                /* Store the last known good position and rotation. */
                psBody->m_vPos_Last_Valid_W = tgMH_MAD_F32_04_1( psBody->m_vPos_Last_Valid_W, psBody->m_vTunneling, vTMP_00 );
                psBody->m_vTunneling = tgMH_SET1_F32_04_1( 0.0F );
                #pragma endregion

                /* Process the joints attached to this body. Avoid the use of a recursive function call by adding other bodies into an array which is processed inside the loop. */
                tiConstraint.m_uiKI = psBody->m_tiConstraint.m_uiKI;
                while (KTgID__INVALID_VALUE != tiConstraint.m_uiKI)
                {
                    TgERROR_MSGF( nuiConstraint_World > 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Logic Failure: a valid constraint id in a world with no constraints." );
                    psConstraint = g_aasPH_Constraint[tiWorld.m_uiI] + tiConstraint.m_uiI;

                    /* Test the visited bit for this constraint. */
                    if (0 == (auiVisited_Constraint[tiConstraint.m_uiI >> 6] & (tiConstraint.m_uiI & 63ULL)))
                    {
                        #pragma region Add a constraint to the set

                        /* Mark the constraint as visited. */
                        auiVisited_Constraint[tiConstraint.m_uiI >> 6] |= (tiConstraint.m_uiI & 63ULL);

                        /* Assign the constraint into the set for the constraint type. */
                        psSolver_Set->m_apsConstraint[psConstraint->m_enConstraint][psSolver_Set->m_nuiConstraint[psConstraint->m_enConstraint]] = psConstraint;
                        psSolver_Set->m_apuiDoF[psConstraint->m_enConstraint][psSolver_Set->m_nuiConstraint[psConstraint->m_enConstraint]] = psSolver_Set->m_nuiDoF;
                        ++psSolver_Set->m_nuiConstraint[psConstraint->m_enConstraint];

                        #pragma region Add the first body attached to this constraint to the processing stack if it is has not already been visited.
                        tiBody.m_uiKI = psConstraint->m_tiBody_0.m_uiKI;
                        TgPARAM_CHECK(KTgID__INVALID_VALUE != tiBody.m_uiKI);
                        if (0 == (auiVisited_Body[tiBody.m_uiI >> 6] & (tiBody.m_uiI & 63ULL)))
                        {
                            auiVisited_Body[tiBody.m_uiI >> 6] |= (tiBody.m_uiI & 63ULL);
                            apsBody_Stack[nuiBody_Stack] = g_aasPH_Body[tiWorld.m_uiI] + tiBody.m_uiI;
                            ++nuiBody_Stack;
                        };
                        #pragma endregion

                        #pragma region Add copies of required data to the solver data structure matching the same order as the constraint list.

                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 0] = psBody->m_sMass.m_uInv_Mass.m_vF32_04_1;
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 1] = tgMH_Query_Col_0_F32_04_3( &psBody->m_mInverse_Inertia_Tensor );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 2] = tgMH_Query_Col_1_F32_04_3( &psBody->m_mInverse_Inertia_Tensor );
                        psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 3] = tgMH_Query_Col_2_F32_04_3( &psBody->m_mInverse_Inertia_Tensor );

                        tiBody.m_uiKI = psConstraint->m_tiBody_1.m_uiKI;
                        if (KTgID__INVALID_VALUE != tiBody.m_uiKI)
                        {
                            STg2_PH_Body_P                      psBY1 = g_aasPH_Body[tiWorld.m_uiI] + tiBody.m_uiI;

                            #pragma region Add the second body attached to this constraint to the processing stack if it is has not already been visited.
                            if (0 == (auiVisited_Body[tiBody.m_uiI >> 6] & (tiBody.m_uiI & 63ULL)))
                            {
                                auiVisited_Body[tiBody.m_uiI >> 6] |= (tiBody.m_uiI & 63ULL);
                                apsBody_Stack[nuiBody_Stack] = g_aasPH_Body[tiWorld.m_uiI] + tiBody.m_uiI;
                                ++nuiBody_Stack;
                            };
                            #pragma endregion

                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 4] = psBY1->m_sMass.m_uInv_Mass.m_vF32_04_1;
                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 5] = tgMH_Query_Col_0_F32_04_3(&psBY1->m_mInverse_Inertia_Tensor);
                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 6] = tgMH_Query_Col_1_F32_04_3(&psBY1->m_mInverse_Inertia_Tensor);
                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 7] = tgMH_Query_Col_2_F32_04_3(&psBY1->m_mInverse_Inertia_Tensor);
                        }
                        else
                        {
                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 4] = tgMH_SET1_F32_04_1( 0.0F );
                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 5] = tgMH_SET1_F32_04_1( 0.0F );
                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 6] = tgMH_SET1_F32_04_1( 0.0F );
                            psSolver_Set->m_avInverse_Mass_Inertia_Tensor[psSolver_Set->m_nuiConstraint_Total*8 + 7] = tgMH_SET1_F32_04_1( 0.0F ); 
                        };

                        #pragma endregion

                        /* Aggregate the number of degrees of freedom that will need to be solved. */
                        psSolver_Set->m_nuiDoF += psConstraint->m_nuiDoF;
                        ++psSolver_Set->m_nuiConstraint_Total;
                        #pragma endregion
                    };

                    /* Continue down the linked list of constraints that match the original body id. */

                    #pragma region Continue walking through the list of contraints attached to the body from the start of the loop.
                    if (psConstraint->m_tiBody_0.m_uiKI == psBody->m_tiBody.m_uiKI)
                    {
                        tiConstraint.m_uiKI = psConstraint->m_tiNext_0.m_uiKI;
                        continue;
                    };

                    if (psConstraint->m_tiBody_1.m_uiKI == psBody->m_tiBody.m_uiKI)
                    {
                        tiConstraint.m_uiKI = psConstraint->m_tiNext_1.m_uiKI;
                        continue;
                    };
                    #pragma endregion

                    tiConstraint.m_uiKI = KTgID__INVALID_VALUE;
                }

                if (0 == nuiBody_Stack)
                    break;

                psBody = apsBody_Stack[nuiBody_Stack - 1];
                --nuiBody_Stack;
            };

            /* Handle auto disable (sleeping) of bodies. */

            if (fMax_Disable_Timer < psWorld->m_fStep_Size_Seconds)
            {
                do
                {
                    --psSolver_Set->m_nuiBody;
                    psSolver_Set->m_apsBody[psSolver_Set->m_nuiBody]->m_bEnabled = false;
                }
                while (psSolver_Set->m_nuiBody > uiSet_Start);
                continue;
            };

            /* If there are no more bodies left in the world to process, or if we exceed the minimum computer limits then queue the job. */

            bFinish_Batch  = uiIndex_Body + 1 >= nuiBody_World;
            bFinish_Batch |= psSolver_Set->m_nuiBody >= psWorld->m_uiSolver_Min_Body_Per_Job;
            bFinish_Batch |= psSolver_Set->m_nuiDoF >= psWorld->m_uiSolver_Min_DoF_Per_Job;

            #pragma region Queue this Set to be solved once it has exceeded the minimal compute limits.
            if (bFinish_Batch)
            {
                atomic_fetch_add( g_axuiPH_FENCE__UPDATE_WORLD__SOLVE_SETS + tiWorld.m_uiI, 1 );
                if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Client_Normal, psJob )))
                {
                    /* On failure, execute the job directly. */
                    TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
                    tgPH_Update_World__Job__Solve_Sets( psJob );
                };

                /* Initialize a the body and constraint data structure used in this loop. */
                tgPH_Update_World__Init_Solver_Set( psSolver_Set, nuiBody_World, nuiConstraint_World, g_aanuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] );
            };
            #pragma endregion
        };
        #pragma endregion

        /* Free the memory that was used to create the batch jobs. */
        if (nullptr != psSolver_Set->m_avInverse_Mass_Inertia_Tensor) TgFREE_POOL( psSolver_Set->m_avInverse_Mass_Inertia_Tensor );
        for (ETgPH_CONSTRAINT enConstraint = ETgPH_CONSTRAINT__MAX - 1; enConstraint > ETgPH_CONSTRAINT__UNKNOWN; --enConstraint)
        {
            if (nullptr !=  psSolver_Set->m_apuiDoF[enConstraint]) TgFREE_POOL( psSolver_Set->m_apuiDoF[enConstraint] );
            if (nullptr !=  psSolver_Set->m_apsConstraint[enConstraint]) TgFREE_POOL( psSolver_Set->m_apsConstraint[enConstraint] );
        }
        if (nullptr != psSolver_Set->m_apsBody) TgFREE_POOL( psSolver_Set->m_apsBody );
        tgMM_Set_U08_0x00( psSolver_Set, sizeof( STg2_PH_Solver__Set ) );

        atomic_thread_fence( cxx__memory_order_seq_cst );
        atomic_fetch_sub( g_axuiPH_FENCE__UPDATE_WORLD__BUILD_SETS + tiWorld.m_uiI, 1 );

        #if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
            tgPH_Update_World__Build_Sets__Validate( tiWorld, auiVisited_Body, auiVisited_Constraint );
        //# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
        #endif

        if (nullptr != apsBody_Stack)
            TgFREE_TEMP( apsBody_Stack );
        if (nullptr != auiVisited_Constraint)
            TgFREE_TEMP( auiVisited_Constraint );
        TgFREE_TEMP( auiVisited_Body );
    };
    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI].m_sLock );
    return (KTgS_OK);
}


/* ---- tgPH_Update_World__Define_Problem_And_Solve ------------------------------------------------------------------------------------------------------------------------------ */
/* PreCondition: World Data Lock                                                                                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Define_Problem_And_Solve( TgPH_WORLD_ID_C tiWorld, STg2_PH_Solver__Set_PC psSolver_Set )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if ((nullptr == psWorld) || (nullptr == psSolver_Set))
    {
        return;
    }

    if (psSolver_Set->m_nuiDoF <= 0 )
        return;

    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[tiWorld.m_uiI].m_sLock );
    {
        TgRSIZE_C                           nuiBody_Solve = psSolver_Set->m_nuiBody;
        TgRSIZE_C                           nuiDoF_Solve = psSolver_Set->m_nuiDoF;
        TgRSIZE_C                           nbyConstraint_Result = sizeof( TgVEC_F32_04_1 ) * 2 * nuiBody_Solve;

        TgRSIZE                             uiIndex;

        /* The solver routines are assumed to be vectored and so the data sets are created to be vector friendly. */

        psSolver_Set->m_avProblem_Coefficients = (TgVEC_F32_04_1_P)TgMALLOC_TEMP( sizeof( TgVEC_F32_04_1 )*ETgPH_PCI__VECTORS_PER_DOF*nuiDoF_Solve );
        psSolver_Set->m_auiJacobian_Index = (TgRSIZE_P)TgMALLOC_TEMP( sizeof( TgRSIZE )*2*nuiDoF_Solve );
        psSolver_Set->m_avResult = (TgVEC_F32_04_1_P)TgMALLOC_TEMP( nbyConstraint_Result );

        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_avProblem_Coefficients, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_auiJacobian_Index, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_avResult, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        tgMM_Set_U08_0x00( psSolver_Set->m_avResult, nbyConstraint_Result );

        /* Call each of the constraint solver functions. */

        tgPH_Constraint_Fixed__Problem_Definition( tiWorld, psSolver_Set );

        /* Solve the LCP */

        tgPH_SV_SOR_LCP( tiWorld, psSolver_Set );

        /* Apply the constraint forces and torques over the full time step (i.e. disregarding the body's time factor). This prevents issues with the simulation when time is
           manipulated (e.g. bullet time). Non-constraint forces and torques are time scaled, as is the integration into the position and rotation update. */
        for (uiIndex = 0; uiIndex < nuiBody_Solve; ++uiIndex)
        {
            STg2_PH_Body_P                      psBody = psSolver_Set->m_apsBody[uiIndex];

            psBody->m_vLV = tgMH_MAD_F32_04_1( psBody->m_vLV, psWorld->m_vStep_Size, psSolver_Set->m_avResult[uiIndex*2 + 0] );
            psBody->m_vAV = tgMH_MAD_F32_04_1( psBody->m_vAV, psWorld->m_vStep_Size, psSolver_Set->m_avResult[uiIndex*2 + 1] );
        };

        TgFREE_TEMP( psSolver_Set->m_avResult );
        psSolver_Set->m_avResult = nullptr;

        TgFREE_TEMP( psSolver_Set->m_auiJacobian_Index );
        psSolver_Set->m_auiJacobian_Index = nullptr;

        TgFREE_TEMP( psSolver_Set->m_avProblem_Coefficients );
        psSolver_Set->m_avProblem_Coefficients = nullptr;
    };
    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
}


/* ---- tgPH_Update_World__Update_Bodies ----------------------------------------------------------------------------------------------------------------------------------------- */
/* PreCondition: World Data Lock                                                                                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Update_Bodies( TgPH_WORLD_ID_C tiWorld, STg2_PH_Solver__Set_CPC psSolver_Set )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if ((nullptr == psWorld) || (nullptr == psSolver_Set))
    {
        return;
    }

    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
    {
        TgRSIZE                             uiIndex;

        /* Update all of the bodies given the calculated solution. */

        for (uiIndex = 0; uiIndex < psSolver_Set->m_nuiBody; ++uiIndex)
        {
            STg2_PH_Body_PC                     psBody = psSolver_Set->m_apsBody[uiIndex];

            TgVEC_F32_04_1_C                    vScaled_Step_Size = tgMH_MUL_F32_04_1( psBody->m_vTime_Factor, psWorld->m_vStep_Size );

            /* Calculate the linear velocity of the body (and apply limits). */

            TgVEC_F32_04_1_C                    vLV_Scaled_Mult = tgMH_MUL_F32_04_1( vScaled_Step_Size, psBody->m_sMass.m_uInv_Mass.m_vF32_04_1 );
            TgVEC_F32_04_1_C                    vLV_Unscaled = tgMH_MAD_F32_04_1( vLV_Scaled_Mult, psBody->m_vXF, psBody->m_vLV );
            TgVEC_F32_04_1_C                    vLV_LSQ = tgMH_LSQ_F32_04_1( vLV_Unscaled );
            TgVEC_F32_04_1_C                    vLV_LSQ_Capped = tgMH_MIN_F32_04_1( vLV_LSQ, psWorld->m_vThreshold__LV_LSQ );
            TgVEC_F32_04_1_C                    vLV_LSQ_Scaling_Factor = tgMH_DIV_F32_04_1( vLV_LSQ_Capped, vLV_LSQ );
            TgVEC_F32_04_1_C                    vLV_Scaling_Factor = tgMH_SQRT_F32_04_1( vLV_LSQ_Scaling_Factor );
            TgVEC_F32_04_1_C                    vLV_Scaled = tgMH_MUL_F32_04_1( vLV_Unscaled, vLV_Scaling_Factor );
            TgVEC_F32_04_1_C                    vLV_NaN_Check = tgMH_CMP_EQ_F32_04_1( vLV_Scaled, vLV_Scaled );
            TgVEC_F32_04_1_C                    vLV = tgMH_AND_F32_04_1( vLV_NaN_Check, vLV_Scaled );

            /* Calculate the angular velocity of the body (and apply limits). */

            TgVEC_F32_04_1_C                    vAV_Scaled_Mult = tgMH_MUL_F32_04_1( vScaled_Step_Size, psBody->m_vXT );
            TgVEC_F32_04_1_C                    vAV_Scaled_IIT = tgMH_TX_F32_04_3( vAV_Scaled_Mult, &psBody->m_mInverse_Inertia_Tensor );
            TgVEC_F32_04_1_C                    vAV_Unscaled = tgMH_ADD_F32_04_1( psBody->m_vAV, vAV_Scaled_IIT );

            TgVEC_F32_04_1_C                    vAV_LSQ = tgMH_LSQ_F32_04_1( vAV_Unscaled );
            TgVEC_F32_04_1_C                    vAV_LSQ_Capped = tgMH_MIN_F32_04_1( vAV_LSQ, psWorld->m_vThreshold__AV_LSQ );
            TgVEC_F32_04_1_C                    vAV_LSQ_Scaling_Factor = tgMH_DIV_F32_04_1( vAV_LSQ_Capped, vAV_LSQ );
            TgVEC_F32_04_1_C                    vAV_Scaling_Factor = tgMH_SQRT_F32_04_1( vAV_LSQ_Scaling_Factor );
            TgVEC_F32_04_1_C                    vAV_Scaled = tgMH_MUL_F32_04_1( vAV_Unscaled, vAV_Scaling_Factor );
            TgVEC_F32_04_1_C                    vAV_NaN_Check = tgMH_CMP_EQ_F32_04_1( vAV_Scaled, vAV_Scaled );
            TgVEC_F32_04_1_C                    vAV = tgMH_AND_F32_04_1( vAV_NaN_Check, vAV_Scaled );

            TgVEC_F32_04_1_C                    vΔQ = tgMH_QT_MUL_F32_04_1( vAV, psBody->m_vRot_W );
            TgVEC_F32_04_1_C                    vR1 = tgMH_MAD_F32_04_1( vΔQ, vScaled_Step_Size, psBody->m_vRot_W );
            TgVEC_F32_04_1_C                    vR1_Normalized = tgMH_NORM_F32_04_1( vR1 );

        #if defined(TgS_PHYSICS_HISTORY) // Used by the visualization system and debug output
            TgRSIZE                             uiHist_Index = atomic_fetch_add( &g_xnuiPH_History, 1 ) % KTgPH_MAX_HISTORY_BODY;

            g_vPH_History__Body_Pos_W[uiHist_Index] = psBody->m_vPos_W;
            g_vPH_History__Body_Rot_W[uiHist_Index] = psBody->m_vRot_W;
            g_tiPH_History__Body_ID[uiHist_Index] = psBody->m_tiBody;
        #endif

            /* Update the linear velocity and position of the body. */
            psBody->m_vLV = vLV;
            psBody->m_vPos_W = tgMH_MAD_F32_04_1( vScaled_Step_Size, vLV, psBody->m_vPos_W );

            /* Update the angular velocity and rotation of the body. */
            psBody->m_vAV = vAV;
            psBody->m_vRot_W = vR1_Normalized;
            tgMH_Init_Quat_F32_04_3( &psBody->m_mRot_W, vR1_Normalized );
        };
    };
    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Init_Solver_Set --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPH_Update_World__Init_Solver_Set( STg2_PH_Solver__Set_PC psSolver_Set, TgRSIZE_C nuiBody_World, TgRSIZE_C nuiConstraint_World, TgRSIZE_P pnuiConstraint )
{
    tgMM_Set_U08_0x00( psSolver_Set, sizeof( STg2_PH_Solver__Set ) );

    psSolver_Set->m_apsBody = (STg2_PH_Body_PP)TgMALLOC_POOL( sizeof( STg2_PH_Body_P ) * nuiBody_World );
    TgCRITICAL_MSGF( nullptr != psSolver_Set->m_apsBody, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

    if (nuiConstraint_World > 0)
    {
        ETgPH_CONSTRAINT                    enConstraint;

        for (enConstraint = ETgPH_CONSTRAINT__UNKNOWN + 1; enConstraint < ETgPH_CONSTRAINT__MAX; ++enConstraint)
        {
            TgRSIZE_C                           nuiConstraint = pnuiConstraint[enConstraint];

            if (0 == nuiConstraint)
                continue;

            psSolver_Set->m_apsConstraint[enConstraint] = (STg2_PH_Constraint_PP)TgMALLOC_POOL( sizeof( STg2_PH_Constraint_P ) * nuiConstraint );
            TgCRITICAL_MSGF( nullptr != psSolver_Set->m_apsConstraint[enConstraint], STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

            psSolver_Set->m_apuiDoF[enConstraint] = (TgRSIZE_P)TgMALLOC_POOL( sizeof( TgRSIZE ) * nuiConstraint );
            TgCRITICAL_MSGF( nullptr != psSolver_Set->m_apuiDoF[enConstraint], STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
        };

        psSolver_Set->m_avInverse_Mass_Inertia_Tensor = (TgVEC_F32_04_1_P)TgMALLOC_POOL( sizeof( TgVEC_F32_04_1 ) * 8 * nuiConstraint_World );
        TgCRITICAL_MSGF( nullptr != psSolver_Set->m_avInverse_Mass_Inertia_Tensor, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    };
}


/* ---- tgPH_Update_World__Build_Sets__Validate ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
static TgVOID tgPH_Update_World__Build_Sets__Validate( TgPH_WORLD_ID_C tiWorld, TgUINT_E64_P auiVisited_Body, TgUINT_E64_P auiVisited_Constraint )
{
    TgRSIZE_C                           nuiBody_World = g_anuiPH_Body_Total__Used[tiWorld.m_uiI];
    TgRSIZE_C                           nuiConstraint_World = g_anuiPH_Constraint_Total__Used[tiWorld.m_uiI];
    TgRSIZE                             uiIndex_Body;
    STg2_PH_Body_P                      psBody;
    TgRSIZE                             uiIndex_Constraint;
    STg2_PH_Constraint_P                psConstraint;

    /* Check to see if all the bodies and constraints that should have been visited were visited. */
    for (uiIndex_Body = 0; uiIndex_Body < nuiBody_World; ++uiIndex_Body)
    {
        psBody = g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex_Body];
        if (psBody->m_bEnabled)
        {
            /* Test the visited bit for this body. */
            if (0 == (auiVisited_Body[uiIndex_Body >> 6] & (uiIndex_Body & 63ULL)))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Enabled body was not visited." );
            }
        }
        else
        {
            /* Test the visited bit for this body. */
            if (0 != (auiVisited_Body[uiIndex_Body >> 6] & (uiIndex_Body & 63ULL)))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Disabled body was visited." );
            }
        }
    }

    for (uiIndex_Constraint = 0; uiIndex_Constraint < nuiConstraint_World; ++uiIndex_Constraint)
    {
        psConstraint = g_aapsPH_Constraint_Used[tiWorld.m_uiI][uiIndex_Constraint];
        if (psConstraint->m_bEnabled)
        {
            /* Check that there are two bodies and that they are both enabled. */
        }
        else
        {
            /* Test the visited bit for this constraint. */
            if (0 != (auiVisited_Constraint[uiIndex_Constraint >> 6] & (uiIndex_Constraint & 63ULL)))
            {
                TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Disabled constraint was visited." );
            }
        }
    }
}
//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif
