/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Constraints [Contact].c
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

/* ---- tgPH_Constraint_Contact__Init_IMM ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgPH_CONSTRAINT_ID tgPH_Constraint_Contact__Init_IMM( TgPH_BODY_ID_C tiBY0, TgPH_BODY_ID_C tiBY1, STg2_CO_Contact_F32_04_CPC psContact )
{
    STg2_PH_Constraint_P                psCT;

    if (TgFAILED(tgPH_Constraint__Init_IMM( &psCT, ETgPH_CONSTRAINT__CONTACT, tiBY0, tiBY1 ))) TgATTRIBUTE_UNLIKELY
    {
        return KTgPH_CONSTRAINT_ID__INVALID;
    };

    tgMM_Copy( &psCT->m_sContact.m_sContact, sizeof(psCT->m_sContact.m_sContact), psContact, sizeof(STg2_CO_Contact_F32_04) );

    psCT->m_nuiDoF = 3;
    psCT->m_bEnabled = true;

    return psCT->m_tiConstraint;
}


/* ---- tgPH_Constraint_Contact__Free_IMM ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint_Contact__Free_IMM( TgPH_CONSTRAINT_ID_C tiCT_CT )
{
    tgPH_Constraint__Free_IMM( tiCT_CT, ETgPH_CONSTRAINT__CONTACT );
}


/* ---- tgPH_Constraint_Contact__Free_All_IMM ------------------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: WRITES to Bodies, Constraints                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint_Contact__Free_All_IMM( STg2_PH_Solver__Set_PC psSolver_Set )
{
    TgRSIZE_C                           nuiConstraint = psSolver_Set->m_nuiConstraint[ETgPH_CONSTRAINT__CONTACT];
    TgRSIZE                             uiConstraint_Index;

    TgPARAM_CHECK(nullptr != psSolver_Set);

    for (uiConstraint_Index = 0; uiConstraint_Index < nuiConstraint; ++uiConstraint_Index)
    {
        STg2_PH_Constraint_PC               psConstraint = psSolver_Set->m_apsConstraint[ETgPH_CONSTRAINT__CONTACT][uiConstraint_Index];

        /* If this becomes a bottle neck we should move to a double linked list to remove the linked list walk for the delete. */
        tgPH_Constraint__Free_IMM( psConstraint->m_tiConstraint, ETgPH_CONSTRAINT__CONTACT );
    };

    for (uiConstraint_Index = 0; uiConstraint_Index < psSolver_Set->m_nuiInvalid_Contact_Constraint; ++uiConstraint_Index)
    {
        STg2_PH_Constraint_PC               psConstraint = psSolver_Set->m_apsInvalid_Contact_Constraint[uiConstraint_Index];

        /* If this becomes a bottle neck we should move to a double linked list to remove the linked list walk for the delete. */
        tgPH_Constraint__Free_IMM( psConstraint->m_tiConstraint, ETgPH_CONSTRAINT__CONTACT );
    };
}


/* ---- tgPH_Constraint_Contact__Problem_Definition ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint_Contact__Problem_Definition( TgPH_WORLD_ID_C tiWorld, STg2_PH_Solver__Set_CPC psSolver_Set )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + tiWorld.m_uiI;
    TgVEC_F32_04_1_C                    vStep_Size_RCP = tgMH_RCP_F32_04_1( psWorld->m_vStep_Size );
    TgRSIZE_C                           nuiConstraint = psSolver_Set->m_nuiConstraint[ETgPH_CONSTRAINT__CONTACT];
    TgVEC_F32_04_1_C                    vCECR_Step_Size_RCP = tgMH_MUL_F32_04_1( vStep_Size_RCP, psWorld->m_vConstraint_Error_Correction_Rate );

#if defined(TgBUILD_FEATURE__PHYSICS__CFM)
    TgFLOAT32_C                         fCFM = psWorld->m_fCFM / psWorld->m_fStep_Size_Seconds;
#else
    TgFLOAT32_C                         fCFM = 0.0F;
#endif

    TgRSIZE                             uiConstraint_Index;
    TgRSIZE                             uiDoF;
    TgVEC_F32_04_1                      avRHS_Component[6];
    TgUN_V128                           auRHS[6];

    TgPARAM_CHECK(nullptr != psSolver_Set);
    TgPARAM_CHECK(nullptr != psWorld);

    for (uiConstraint_Index = 0; uiConstraint_Index < nuiConstraint; ++uiConstraint_Index)
    {
        TgRSIZE_C                           uiDoF_Index = psSolver_Set->m_apuiDoF[ETgPH_CONSTRAINT__CONTACT][uiConstraint_Index];
        TgVEC_F32_04_1_PC                   pvCoefficients = psSolver_Set->m_avProblem_Coefficients + uiDoF_Index * ETgPH_PCI__VEC_PER_DOF;
        STg2_PH_Constraint_CPC              psConstraint = psSolver_Set->m_apsConstraint[ETgPH_CONSTRAINT__CONTACT][uiConstraint_Index];
        STg2_PH_Body_CPC                    psBY0 = KTgID__INVALID_VALUE != psConstraint->m_tiBY0.m_uiKI ? g_aasPH_Body[tiWorld.m_uiI] + psConstraint->m_tiBY0.m_uiI : nullptr;
        STg2_PH_Body_CPC                    psBY1 = KTgID__INVALID_VALUE != psConstraint->m_tiBY1.m_uiKI ? g_aasPH_Body[tiWorld.m_uiI] + psConstraint->m_tiBY1.m_uiI : nullptr;

        TgVEC_F32_04_1_C                    vNormal = psConstraint->m_sContact.m_sContact.m_vN0;

        TgVEC_F32_04_1_C                    vTMP_00 = tgMH_MUL_F32_04_1( vCECR_Step_Size_RCP, psConstraint->m_sContact.m_sContact.m_vDepth );
        TgVEC_F32_04_1_C                    vTMP_01 = tgMH_MIN_F32_04_1( vTMP_00, KTgPH_MAX_LIN_SPEED );
        TgVEC_F32_04_1_C                    vRHS_Empty[2] = { KTgZERO_F32_04_1, KTgZERO_F32_04_1 };

        TgVEC_F32_04_1                      vPN_T0, vPN_T1; /* Tangents on the plane of contact. */
        TgVEC_F32_04_1_CP                   pvRHS_0, pvRHS_1;
        TgVEC_F32_04_1                      vREST_04, vREST_05;

        TgPARAM_CHECK(KTgID__INVALID_VALUE != psConstraint->m_tiBY0.m_uiKI);

        tgMH_Init_Basis_From_Vector_F32_04_1( &vPN_T0, &vPN_T1, vNormal );

        avRHS_Component[0] = vTMP_01;
        avRHS_Component[1] = tgMH_SET1_F32_04_1( 0.0F );
        avRHS_Component[2] = tgMH_SET1_F32_04_1( 0.0F );

        if (nullptr != psBY0)
        {
            TgVEC_F32_04_1_C                    vBY0_Pos_O2W = psUpdate_Simulation->m_avPos_W[psBY0->m_uiUsed_Index];
            TgVEC_F32_04_1_C                    vContact_Rel_BY0 = tgMH_SUB_F32_04_1( psConstraint->m_sContact.m_sContact.m_vS0, vBY0_Pos_O2W );
            TgVEC_F32_04_1                      vREST_00, vREST_01;

            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_NEG_F32_04_1( vNormal );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = vPN_T0;
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = vPN_T1;

            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_CX_F32_04_1( vNormal, vContact_Rel_BY0 );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_CX_F32_04_1( vContact_Rel_BY0, vPN_T0 );
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_CX_F32_04_1( vContact_Rel_BY0, vPN_T1 );

            pvRHS_0 = psUpdate_Simulation->m_avRHS_LA + psBY0->m_uiUsed_Index * 2;

            vREST_00 = tgMH_DOT_F32_04_1( psBY0->m_vLV, pvCoefficients[ETgPH_PCI__JACOBIAN_LIN_BY_0] );
            vREST_01 = tgMH_DOT_F32_04_1( psBY0->m_vAV, pvCoefficients[ETgPH_PCI__JACOBIAN_ANG_BY_0] );
            vREST_04 = tgMH_ADD_F32_04_1( vREST_00, vREST_01 );
        }
        else
        {
            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] = tgMH_SET1_F32_04_1( 0.0F );

            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] = tgMH_SET1_F32_04_1( 0.0F );

            pvRHS_0 = vRHS_Empty;

            vREST_04 = KTgZERO_F32_04_1;
        };

        if (nullptr != psBY1)
        {
            TgVEC_F32_04_1_C                    vBY1_Pos_O2W = psUpdate_Simulation->m_avPos_W[psBY1->m_uiUsed_Index];
            TgVEC_F32_04_1_C                    vContact_Rel_BY1 = tgMH_SUB_F32_04_1( psConstraint->m_sContact.m_sContact.m_vS0, vBY1_Pos_O2W );
            TgVEC_F32_04_1                      vREST_02, vREST_03;

            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = vNormal;
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = vPN_T0;
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = vPN_T1;

            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_CX_F32_04_1( vContact_Rel_BY1, vNormal );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_CX_F32_04_1( vContact_Rel_BY1, vPN_T0 );
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_CX_F32_04_1( vContact_Rel_BY1, vPN_T1 );

            pvRHS_1 = psUpdate_Simulation->m_avRHS_LA + psBY1->m_uiUsed_Index * 2;

            vREST_02 = tgMH_DOT_F32_04_1( psBY1->m_vLV, pvCoefficients[ETgPH_PCI__JACOBIAN_LIN_BY_1] );
            vREST_03 = tgMH_DOT_F32_04_1( psBY1->m_vAV, pvCoefficients[ETgPH_PCI__JACOBIAN_ANG_BY_1] );
            vREST_05 = tgMH_ADD_F32_04_1( vREST_02, vREST_03 );
        }
        else
        {
            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] = tgMH_SET1_F32_04_1( 0.0F );

            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] = tgMH_SET1_F32_04_1( 0.0F );

            pvRHS_1 = vRHS_Empty;

            vREST_05 = KTgZERO_F32_04_1;
        };

        #pragma region Restitution
        {
            TgVEC_F32_04_1_C                    vRestitution_Factor = tgPH_Material_Calc_Restitution_Factor( psBY0, psBY1 );
            TgVEC_F32_04_1_C                    vREST_06_Uncapped = tgMH_ADD_F32_04_1( vREST_04, vREST_05 );
            TgVEC_F32_04_1_C                    vREST_06_ABS = tgMH_ABS_F32_04_1( vREST_06_Uncapped );
            TgVEC_F32_04_1_C                    vREST_LEN_CMP = tgMH_CMP_LT_F32_04_1( vREST_06_ABS, tgMH_SET1_F32_04_1( KTgEPS_F32*10.0F ) );
            TgVEC_F32_04_1_C                    vREST = tgMH_SEL_F32_04_1( vREST_06_Uncapped, KTgZERO_F32_04_1, vREST_LEN_CMP );
            TgVEC_F32_04_1_C                    vRestitution = tgMH_MUL_F32_04_1( vRestitution_Factor, vREST );

            avRHS_Component[0] = tgMH_MAX_F32_04_1( avRHS_Component[0], vRestitution );
        };
        #pragma endregion

    #if defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK)
        for (TgRSIZE uiTest = 0; uiTest < 3; ++uiTest)
        {
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( pvCoefficients[uiTest*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( pvCoefficients[uiTest*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( pvCoefficients[uiTest*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( pvCoefficients[uiTest*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] )));
            TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( avRHS_Component[uiTest] )));
        };
    /*# defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK) */
    #endif

        #pragma region Construct RHS - Needs to be done in every constraint problem data function.
        {
            TgFLOAT32_C                         fμd = psConstraint->m_fμd;

            for (uiDoF = 0; uiDoF < 3; ++uiDoF)
            {
                TgVEC_F32_04_1_C                    vSUM_00 = tgMH_DOT_F32_04_1( pvRHS_0[0], pvCoefficients[uiDoF*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_0] );
                TgVEC_F32_04_1_C                    vSUM_01 = tgMH_DOT_F32_04_1( pvRHS_0[1], pvCoefficients[uiDoF*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_0] );
                TgVEC_F32_04_1_C                    vSUM_02 = tgMH_DOT_F32_04_1( pvRHS_1[0], pvCoefficients[uiDoF*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_LIN_BY_1] );
                TgVEC_F32_04_1_C                    vSUM_03 = tgMH_DOT_F32_04_1( pvRHS_1[1], pvCoefficients[uiDoF*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__JACOBIAN_ANG_BY_1] );
                TgVEC_F32_04_1_C                    vSUM_04 = tgMH_ADD_F32_04_1( vSUM_00, vSUM_01 );
                TgVEC_F32_04_1_C                    vSUM_05 = tgMH_ADD_F32_04_1( vSUM_02, vSUM_03 );
                TgVEC_F32_04_1_C                    vSUM_06 = tgMH_ADD_F32_04_1( vSUM_04, vSUM_05 );

                TgVEC_F32_04_1_C                    vRHS_0 = tgMH_MUL_F32_04_1( avRHS_Component[uiDoF], vStep_Size_RCP );

            #if defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK)
                TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( vSUM_06 )));
                TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( vRHS_0 )));
            /*# defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK) */
            #endif

                auRHS[uiDoF].m_vF32_04_1 = tgMH_SUB_F32_04_1( vRHS_0, vSUM_06 );

            };

            pvCoefficients[0*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1(     0.0F, FLT_MAX, fCFM, auRHS[0].m_vS_F32_04_1.x );
            pvCoefficients[1*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1(     -fμd,     fμd, fCFM, auRHS[1].m_vS_F32_04_1.x );
            pvCoefficients[2*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] = tgMH_Init_ELEM_F32_04_1(     -fμd,     fμd, fCFM, auRHS[2].m_vS_F32_04_1.x );

        #if defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK)
            for (TgRSIZE uiTest = 0; uiTest < 3; ++uiTest)
            {
                TgDIAG(!tgMH_CMP_ANY_TO_BOOL_F32_04_1(tgMH_NAN_F32_04_1( pvCoefficients[uiTest*ETgPH_PCI__VEC_PER_DOF + ETgPH_PCI__MIN_MAX_CFM_RHS] )));
            };
        /*# defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK) */
        #endif
        }
        #pragma endregion

    };
}
