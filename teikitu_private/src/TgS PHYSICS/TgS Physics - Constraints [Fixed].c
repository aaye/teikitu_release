/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Constraints [Fixed].c
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
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Constraint_Fixed__Init ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgPH_CONSTRAINT_ID tgPH_Constraint_Fixed__Init( TgPH_WORLD_ID tiWorld, TgPH_BODY_ID_C tiBY0, TgPH_BODY_ID_C tiBY1 )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    STg2_PH_Body_CPC                    psBody_0 = tgPH_Body_Get_Body_From_ID( tiBY0 );
    TgPH_CONSTRAINT_ID                  tiConstraint;
    STg2_PH_Constraint_P                psConstraint;

    if ((nullptr == psWorld) || (nullptr == psBody_0))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid function parameters." );
        return KTgPH_CONSTRAINT_ID__INVALID;
    }

    tiConstraint = tgPH_Constraint_Init( tiWorld );
    psConstraint = tgPH_Constraint_Get_Constraint_From_ID( tiConstraint );
    if ((KTgID__INVALID_VALUE == tiConstraint.m_uiKI) || (nullptr == psConstraint))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to create a new constraint." );
        return KTgPH_CONSTRAINT_ID__INVALID;
    }

    psConstraint->m_tiBody_0 = tiBY0;
    psConstraint->m_tiBody_1 = tiBY1;

    if (nullptr == psBody_0)
    {
        STg2_PH_Body_CPC                    psBody_1 = tgPH_Body_Get_Body_From_ID( tiBY1 );

        if (nullptr == psBody_1)
        {
            psConstraint->m_VFoR_Rot = tgMH_QT_MUL_F32_04_1( psBody_0->m_vRot_W, psBody_1->m_vRot_W );
            psConstraint->m_VFoR_Pos = tgMH_SUB_F32_04_1( psBody_0->m_vPos_W, psBody_1->m_vPos_W );
            psConstraint->m_VFoR_Pos = tgMH_QT_TX_F32_04_1( psConstraint->m_VFoR_Pos, psBody_0->m_vRot_W );
        }
        else
        {
            psConstraint->m_VFoR_Rot = tgMH_QT_INV_F32_04_1( psBody_0->m_vRot_W );
            psConstraint->m_VFoR_Pos = psBody_0->m_vPos_W;
        };
    };

    psConstraint->m_nuiDoF = 6;
    psConstraint->m_enConstraint = ETgPH_CONSTRAINT__FIXED;
    psConstraint->m_bEnabled = true;

    return tiConstraint;
}


/* ---- tgPH_Constraint_Fixed__Problem_Definition -------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint_Fixed__Problem_Definition( TgPH_WORLD_ID_C tiWorld, STg2_PH_Solver__Set_CPC psSolver_Set )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if ((nullptr == psWorld) || (nullptr == psSolver_Set))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid function parameters." );
        return;
    }

    tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
    {
        STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + tiWorld.m_uiI;
        TgVEC_F32_04_1_C                    vStep_Size_RCP = tgMH_RCP_F32_04_1( psWorld->m_vStep_Size );
        TgRSIZE_C                           nuiConstraint = psSolver_Set->m_nuiConstraint[ETgPH_CONSTRAINT__FIXED];
        TgFLOAT32_C                         fCFM = psWorld->m_fCFM / psWorld->m_fStep_Size_Seconds;

        TgRSIZE                             uiConstraint_Index;
        TgRSIZE                             uiDoF;
        TgVEC_F32_04_1                      vError_TMP, avRHS_Component[6];
        TgUN_V128                           auRHS[6];

        for (uiConstraint_Index = 0; uiConstraint_Index < nuiConstraint; ++uiConstraint_Index)
        {
            TgRSIZE_C                           uiDoF_Index = psSolver_Set->m_apuiDoF[ETgPH_CONSTRAINT__FIXED][uiConstraint_Index];
            TgVEC_F32_04_1_PC                   pvCoefficients = psSolver_Set->m_avProblem_Coefficients + uiDoF_Index * ETgPH_PCI__VECTORS_PER_DOF;
            TgVEC_F32_04_1_PC                   avInverse_Mass_Inertia_Tensor = psSolver_Set->m_avInverse_Mass_Inertia_Tensor + uiDoF_Index * 8;

            STg2_PH_Constraint_CPC              psConstraint = psSolver_Set->m_apsConstraint[ETgPH_CONSTRAINT__FIXED][uiConstraint_Index];

            STg2_PH_Body_CPC                    psBody_0 = g_aasPH_Body[tiWorld.m_uiI] + psConstraint->m_tiBody_0.m_uiI;
            TgVEC_F32_04_3_CPC                  pmInverse_Inertia_Tensor_0 = &psBody_0->m_mInverse_Inertia_Tensor;
            TgVEC_F32_04_1_CPC                  pvRHS_0 = psUpdate_Simulation->m_avRHS_LA + psConstraint->m_tiBody_0.m_uiI;

            STg2_PH_Body_CPC                    psBody_1 = g_aasPH_Body[tiWorld.m_uiI] + psConstraint->m_tiBody_1.m_uiI;
            TgVEC_F32_04_3_CPC                  pmInverse_Inertia_Tensor_1 = &psBody_1->m_mInverse_Inertia_Tensor;
            TgVEC_F32_04_1_CPC                  pvRHS_1 = psUpdate_Simulation->m_avRHS_LA + psConstraint->m_tiBody_1.m_uiI;

            TgVEC_F32_04_1                      vError_Rot, vError;

            TgPARAM_CHECK(KTgID__INVALID_VALUE != psConstraint->m_tiBody_0.m_uiKI);

            pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F, 0.0F );
            pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 0.0F );
            pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F, 0.0F );

            pvCoefficients[3*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[4*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[5*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_SET1_F32_04_1( 0.0F );

            pvCoefficients[3*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_Init_ELEM_F32_04_1( 1.0F, 0.0F, 0.0F, 0.0F );
            pvCoefficients[4*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_Init_ELEM_F32_04_1( 0.0F, 1.0F, 0.0F, 0.0F );
            pvCoefficients[5*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F, 1.0F, 0.0F );

            pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );

            pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );

            avInverse_Mass_Inertia_Tensor[0] = psBody_0->m_sMass.m_uMass.m_vF32_04_1;
            avInverse_Mass_Inertia_Tensor[1] = tgMH_Query_Col_0_F32_04_3( pmInverse_Inertia_Tensor_0 );
            avInverse_Mass_Inertia_Tensor[2] = tgMH_Query_Col_1_F32_04_3( pmInverse_Inertia_Tensor_0 );
            avInverse_Mass_Inertia_Tensor[3] = tgMH_Query_Col_2_F32_04_3( pmInverse_Inertia_Tensor_0 );

            if (KTgID__INVALID_VALUE != psConstraint->m_tiBody_1.m_uiKI)
            {
                TgUN_V128_C                         uRelative_Offset = { .m_vF32_04_1 = tgMH_TX_F32_04_3( psConstraint->m_vOffset, &psBody_0->m_mRot_W ) };

                TgVEC_F32_04_1_C                    vTMP_00 = tgMH_QT_MUL_F32_04_1( psBody_0->m_vRot_W, psBody_1->m_vRot_W );
                TgVEC_F32_04_1_C                    vTMP_01 = tgMH_SUB_F32_04_1( psBody_1->m_vPos_W, psBody_0->m_vPos_W );
                TgVEC_F32_04_1_C                    vTMP_02 = tgMH_ADD_F32_04_1( vTMP_01, uRelative_Offset.m_vF32_04_1 );
                TgVEC_F32_04_1_C                    vTMP_03 = tgMH_MUL_F32_04_1( vStep_Size_RCP, vTMP_02 );

                TgVEC_F32_04_1_C                    vJA0_0 = tgMH_Init_ELEM_F32_04_1( 1.0F, uRelative_Offset.m_vS_F32_04_1.z, -uRelative_Offset.m_vS_F32_04_1.y, 0.0F );
                TgVEC_F32_04_1_C                    vJA0_1 = tgMH_Init_ELEM_F32_04_1( -uRelative_Offset.m_vS_F32_04_1.z, 1.0F, uRelative_Offset.m_vS_F32_04_1.x, 0.0F );
                TgVEC_F32_04_1_C                    vJA0_2 = tgMH_Init_ELEM_F32_04_1( uRelative_Offset.m_vS_F32_04_1.y, -uRelative_Offset.m_vS_F32_04_1.x, 1.0F, 0.0F );

                pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = vJA0_0;
                pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = vJA0_1;
                pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = vJA0_2;

                pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_Init_ELEM_F32_04_1(-1.0F, 0.0F, 0.0F, 0.0F );
                pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_Init_ELEM_F32_04_1( 0.0F,-1.0F, 0.0F, 0.0F );
                pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F,-1.0F, 0.0F );

                pvCoefficients[3*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_Init_ELEM_F32_04_1(-1.0F, 0.0F, 0.0F, 0.0F );
                pvCoefficients[4*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_Init_ELEM_F32_04_1( 0.0F,-1.0F, 0.0F, 0.0F );
                pvCoefficients[5*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_Init_ELEM_F32_04_1( 0.0F, 0.0F,-1.0F, 0.0F );

                avInverse_Mass_Inertia_Tensor[4] = psBody_1->m_sMass.m_uMass.m_vF32_04_1;
                avInverse_Mass_Inertia_Tensor[5] = tgMH_Query_Col_0_F32_04_3( pmInverse_Inertia_Tensor_1 );
                avInverse_Mass_Inertia_Tensor[6] = tgMH_Query_Col_1_F32_04_3( pmInverse_Inertia_Tensor_1 );
                avInverse_Mass_Inertia_Tensor[7] = tgMH_Query_Col_2_F32_04_3( pmInverse_Inertia_Tensor_1 );

                avRHS_Component[0] = tgMH_SPX_F32_04_1( vTMP_03 );
                avRHS_Component[1] = tgMH_SPY_F32_04_1( vTMP_03 );
                avRHS_Component[2] = tgMH_SPZ_F32_04_1( vTMP_03 );

                vError_Rot = tgMH_QT_MUL_F32_04_1( vTMP_00, psConstraint->m_VFoR_Rot );
            }
            else
            {
                TgVEC_F32_04_1_C                    vTMP_00 = tgMH_SUB_F32_04_1( psConstraint->m_vOffset, psBody_0->m_vPos_W );
                TgVEC_F32_04_1_C                    vTMP_01 = tgMH_MUL_F32_04_1( vStep_Size_RCP, vTMP_00 );

                pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
                pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
                pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_SET1_F32_04_1( 0.0F );

                pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
                pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
                pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );

                pvCoefficients[3*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
                pvCoefficients[4*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
                pvCoefficients[5*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );

                avInverse_Mass_Inertia_Tensor[4] = tgMH_SET1_F32_04_1( 0.0F );
                avInverse_Mass_Inertia_Tensor[5] = tgMH_SET1_F32_04_1( 0.0F );
                avInverse_Mass_Inertia_Tensor[6] = tgMH_SET1_F32_04_1( 0.0F );
                avInverse_Mass_Inertia_Tensor[7] = tgMH_SET1_F32_04_1( 0.0F );

                avRHS_Component[0] = tgMH_SPX_F32_04_1( vTMP_01 );
                avRHS_Component[1] = tgMH_SPY_F32_04_1( vTMP_01 );
                avRHS_Component[2] = tgMH_SPZ_F32_04_1( vTMP_01 );

                vError_Rot = tgMH_QT_MUL_F32_04_1( psBody_0->m_vRot_W, psConstraint->m_VFoR_Rot );
            };

            /* If the quaternion rotation is negative, flip the axis to maintain smaller angle values. */
            vError = tgMH_TX_F32_04_3( tgMH_MUL_F32_04_1( vError_Rot, tgMH_Init_Vector_F32_04_1( tgMH_SGN_F32_04_1( tgMH_SPW_F32_04_1( vError_Rot ) ) ) ), &psBody_0->m_mRot_W );
            vError_TMP = tgMH_MUL_F32_04_1( tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( 2.0F ), vStep_Size_RCP ), vError );
            avRHS_Component[3] = tgMH_SPX_F32_04_1( vError_TMP );
            avRHS_Component[4] = tgMH_SPY_F32_04_1( vError_TMP );
            avRHS_Component[5] = tgMH_SPZ_F32_04_1( vError_TMP );

            #pragma region Consruct RHS - Needs to be done in every constraint problem data function.
            for (uiDoF = 0; uiDoF < 6; ++uiDoF)
            {
                TgVEC_F32_04_1_C                    vSUM_00 = tgMH_DOT_F32_04_1( pvRHS_0[0], pvCoefficients[uiDoF*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] );
                TgVEC_F32_04_1_C                    vSUM_01 = tgMH_DOT_F32_04_1( pvRHS_0[1], pvCoefficients[uiDoF*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] );
                TgVEC_F32_04_1_C                    vSUM_02 = tgMH_DOT_F32_04_1( pvRHS_1[0], pvCoefficients[uiDoF*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] );
                TgVEC_F32_04_1_C                    vSUM_03 = tgMH_DOT_F32_04_1( pvRHS_1[1], pvCoefficients[uiDoF*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] );
                TgVEC_F32_04_1_C                    vSUM_04 = tgMH_ADD_F32_04_1( vSUM_00, vSUM_01 );
                TgVEC_F32_04_1_C                    vSUM_05 = tgMH_ADD_F32_04_1( vSUM_02, vSUM_03 );
                TgVEC_F32_04_1_C                    vSUM_06 = tgMH_ADD_F32_04_1( vSUM_04, vSUM_05 );

                TgVEC_F32_04_1_C                    vRHS_0 = tgMH_MUL_F32_04_1( avRHS_Component[uiDoF], vStep_Size_RCP );

                auRHS[uiDoF].m_vF32_04_1 = tgMH_SUB_F32_04_1( vRHS_0, vSUM_06 );
            };
            #pragma endregion

            pvCoefficients[0*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1( -FLT_MAX, FLT_MAX, fCFM, auRHS[0].m_vS_F32_04_1.x );
            pvCoefficients[1*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1( -FLT_MAX, FLT_MAX, fCFM, auRHS[1].m_vS_F32_04_1.x );
            pvCoefficients[2*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1( -FLT_MAX, FLT_MAX, fCFM, auRHS[2].m_vS_F32_04_1.x );
            pvCoefficients[3*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1( -FLT_MAX, FLT_MAX, fCFM, auRHS[3].m_vS_F32_04_1.x );
            pvCoefficients[4*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1( -FLT_MAX, FLT_MAX, fCFM, auRHS[4].m_vS_F32_04_1.x );
            pvCoefficients[5*ETgPH_PCI__VECTORS_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1( -FLT_MAX, FLT_MAX, fCFM, auRHS[5].m_vS_F32_04_1.x );
        };
    };
    tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );
}
