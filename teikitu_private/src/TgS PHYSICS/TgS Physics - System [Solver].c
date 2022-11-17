
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - System [Solver].c
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
/*  Reference and Theory                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Theory (Based on Linear Complementarity Problem)

ᵀ
¹
⁻¹
    References
    1. Baraff D (1993) Dynamic Simulation of Non-Penetrating Rigid Bodies, PhD Thesis, https://hdl.handle.net/1813/7115

*/



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_SV_SOR_LCP ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_SV_SOR_LCP( TgPH_WORLD_ID_C tiWorld, STg2_PH_Solver__Set_CPC psSolver_Set )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if ((nullptr == psWorld) || (nullptr == psSolver_Set))
    {
        return;
    };

    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
    {
        TgRSIZE_C                           nuiSolver_Iteration_Max = psWorld->m_nuiSolver_Iterations;

        TgRSIZE_C                           nuiDoF_Solver = psSolver_Set->m_nuiDoF;

        TgVEC_F32_04_1_CPC                  avInverse_Mass_Inertia_Tensor = psSolver_Set->m_avInverse_Mass_Inertia_Tensor;
        TgVEC_F32_04_1_CPC                  avProblem_Coefficients = psSolver_Set->m_avProblem_Coefficients;
        TgRSIZE_CPC                         auiJacobian_Index = psSolver_Set->m_auiJacobian_Index;
        TgVEC_F32_04_1_PC                   avResult = psSolver_Set->m_avResult;

        TgVEC_F32_04_1_P                    avλ; // Constraint Impulse, read-modify-write

        TgRSIZE                             nuiDoF, nuiSolver_Iteration;

        /* Allocate memory for the solver and outputs, padding out to be vector aligned. */

        avλ = (TgVEC_F32_04_1_P)TgMALLOC_TEMP( sizeof( TgVEC_F32_04_1 ) * nuiDoF_Solver );
        TgCRITICAL_MSGF( nullptr != avλ, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
        tgMM_Set_U08_0x00( avλ, sizeof( TgVEC_F32_04_1 ) * nuiDoF_Solver );

        /* Process the data sent to match the needed form for solving. */
        for (nuiDoF = 0; nuiDoF < nuiDoF_Solver; ++nuiDoF)
        {
            TgVEC_F32_04_1_PC                   avDoF_Coeff_Update = psSolver_Set->m_avProblem_Coefficients + nuiDoF*ETgPH_PCI__VECTORS_PER_DOF;
            TgVEC_F32_04_1_CPC                  avDoF_Coefficients = avProblem_Coefficients + nuiDoF*ETgPH_PCI__VECTORS_PER_DOF;
            TgVEC_F32_04_1_CPC                  avIMIT = avInverse_Mass_Inertia_Tensor + nuiDoF*8;
            /* Jacobian has an entry for each potential body attached to a constraint. The values will be zero in the case there is no body. */
            TgVEC_F32_04_1_C                    vCFM = tgMH_SPZ_F32_04_1( avDoF_Coefficients[ETgPH_PCI__MIN_MAX_CFM_RHS] );
//# TODO OPT: Better to branch on the existence of the a second body, or just do the math? */
            TgVEC_F32_04_1_C                    vLJ0 = tgMH_MUL_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_0], avIMIT[0] );
            TgVEC_F32_04_1_C                    vAJ0 = tgMH_TX_F32_04_3( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_0], (TgVEC_F32_04_3_CPC)(avIMIT + 1) );
            TgVEC_F32_04_1_C                    vLJ1 = tgMH_MUL_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_1], avIMIT[4] );
            TgVEC_F32_04_1_C                    vAJ1 = tgMH_TX_F32_04_3( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_1], (TgVEC_F32_04_3_CPC)(avIMIT + 5) );
//# TODO OPT: Can we swizzle these results to improve the sum? */
            TgVEC_F32_04_1_C                    vSUM_00 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_0], vLJ0 );
            TgVEC_F32_04_1_C                    vSUM_01 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_0], vAJ0 );
            TgVEC_F32_04_1_C                    vSUM_02 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_1], vLJ1 );
            TgVEC_F32_04_1_C                    vSUM_03 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_1], vAJ1 );

            TgVEC_F32_04_1_C                    vSUM_04 = tgMH_ADD_F32_04_1( vSUM_00, vSUM_01 );
            TgVEC_F32_04_1_C                    vSUM_05 = tgMH_ADD_F32_04_1( vSUM_02, vSUM_03 );
            TgVEC_F32_04_1_C                    vSUM_06 = tgMH_ADD_F32_04_1( vSUM_04, vSUM_05 );

            TgUN_V128_C                         uFactor = { .m_vF32_04_1 = tgMH_RCP_F32_04_1( tgMH_ADD_F32_04_1( vSUM_06, vCFM ) ) };
            TgVEC_F32_04_1_C                    vRHS_Factor = tgMH_Init_ELEM_F32_04_1( 1.0F, 1.0F, 1.0F, uFactor.m_vS_F32_04_1.x );

            avDoF_Coeff_Update[ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_MUL_F32_04_1( uFactor.m_vF32_04_1, avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_0] );
            avDoF_Coeff_Update[ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_MUL_F32_04_1( uFactor.m_vF32_04_1, avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_0] );
            avDoF_Coeff_Update[ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_MUL_F32_04_1( uFactor.m_vF32_04_1, avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_1] );
            avDoF_Coeff_Update[ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_MUL_F32_04_1( uFactor.m_vF32_04_1, avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_1] );
            avDoF_Coeff_Update[ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_MUL_F32_04_1( vRHS_Factor, avDoF_Coefficients[ETgPH_PCI__MIN_MAX_CFM_RHS] );
            avDoF_Coeff_Update[ETgPH_PCI__RCP_A_DIAG] = tgMH_NEG_F32_04_1( tgMH_MUL_F32_04_1( vCFM, uFactor.m_vF32_04_1 ) );
            avDoF_Coeff_Update[ETgPH_PCI__J_LIN_RESULT_MULT_BY_0] = vLJ0;
            avDoF_Coeff_Update[ETgPH_PCI__J_ANG_RESULT_MULT_BY_0] = vAJ0;
            avDoF_Coeff_Update[ETgPH_PCI__J_LIN_RESULT_MULT_BY_1] = vLJ1;
            avDoF_Coeff_Update[ETgPH_PCI__J_ANG_RESULT_MULT_BY_1] = vAJ1;
        }

        /* Solver */

        for (nuiSolver_Iteration = 0; nuiSolver_Iteration < nuiSolver_Iteration_Max; ++nuiSolver_Iteration)
        {
            for (nuiDoF = 0; nuiDoF < nuiDoF_Solver; ++nuiDoF)
            {
                TgVEC_F32_04_1_CPC                  avDoF_Coefficients = avProblem_Coefficients + nuiDoF*ETgPH_PCI__VECTORS_PER_DOF;

                TgVEC_F32_04_1_C                    vLower_Bound = tgMH_SPX_F32_04_1( avDoF_Coefficients[ETgPH_PCI__MIN_MAX_CFM_RHS] );
                TgVEC_F32_04_1_C                    vUpper_Bound = tgMH_SPY_F32_04_1( avDoF_Coefficients[ETgPH_PCI__MIN_MAX_CFM_RHS] );
                TgVEC_F32_04_1_C                    vRHS = tgMH_SPW_F32_04_1( avDoF_Coefficients[ETgPH_PCI__MIN_MAX_CFM_RHS] );

//# TODO OPT: Better to branch on the existence of the a second body, or just do the math? */
                TgRSIZE_C                           uiBY0 = auiJacobian_Index[nuiDoF*2 + 0];
                TgRSIZE_C                           uiBY1 = auiJacobian_Index[nuiDoF*2 + 1];

                TgVEC_F32_04_1_C                    vSUM_00 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_0], avResult[uiBY0*2 + 0] );
                TgVEC_F32_04_1_C                    vSUM_01 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_0], avResult[uiBY0*2 + 1] );
                TgVEC_F32_04_1_C                    vSUM_02 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_LIN_BY_1], avResult[uiBY1*2 + 0] );
                TgVEC_F32_04_1_C                    vSUM_03 = tgMH_DOT_F32_04_1( avDoF_Coefficients[ETgPH_PCI__JACOBIAN_ANG_BY_1], avResult[uiBY1*2 + 1] );

                TgVEC_F32_04_1_C                    vSUM_04 = tgMH_ADD_F32_04_1( vSUM_00, vSUM_01 );
                TgVEC_F32_04_1_C                    vSUM_05 = tgMH_ADD_F32_04_1( vSUM_02, vSUM_03 );
                TgVEC_F32_04_1_C                    vSUM_06 = tgMH_ADD_F32_04_1( vSUM_04, vSUM_05 );

                                                    /* Compute and clamp λ */
                TgVEC_F32_04_1_C                    vTMP_00 = tgMH_MAD_F32_04_1( avλ[nuiDoF], avDoF_Coefficients[ETgPH_PCI__RCP_A_DIAG], vRHS );
                TgVEC_F32_04_1_C                    vTMP_01 = tgMH_SUB_F32_04_1( vTMP_00, vSUM_06 );
                TgVEC_F32_04_1_C                    vTMP_02 = tgMH_ADD_F32_04_1( avλ[nuiDoF], vTMP_01 );
                TgVEC_F32_04_1_C                    vΛ = tgMH_CLP_F32_04_1( vTMP_02, vLower_Bound, vUpper_Bound ); // Clamp the new λ value to the lower and upper bound values.
                TgVEC_F32_04_1_C                    vδ = tgMH_SUB_F32_04_1( vΛ, avλ[nuiDoF] ); // Update the δ value based on the clamped λ value.

                avλ[nuiDoF] = vΛ;

                /* Update constraint force and torque */

                avResult[uiBY0*2 + 0] = tgMH_MAD_F32_04_1( vδ, avDoF_Coefficients[ETgPH_PCI__J_LIN_RESULT_MULT_BY_0], avResult[uiBY0*2 + 0] );
                avResult[uiBY0*2 + 1] = tgMH_MAD_F32_04_1( vδ, avDoF_Coefficients[ETgPH_PCI__J_ANG_RESULT_MULT_BY_0], avResult[uiBY0*2 + 1] );
                avResult[uiBY1*2 + 0] = tgMH_MAD_F32_04_1( vδ, avDoF_Coefficients[ETgPH_PCI__J_LIN_RESULT_MULT_BY_1], avResult[uiBY1*2 + 0] );
                avResult[uiBY1*2 + 1] = tgMH_MAD_F32_04_1( vδ, avDoF_Coefficients[ETgPH_PCI__J_ANG_RESULT_MULT_BY_1], avResult[uiBY1*2 + 1] );
            };
        };
        TgFREE_TEMP( avλ );
    }
    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
}
