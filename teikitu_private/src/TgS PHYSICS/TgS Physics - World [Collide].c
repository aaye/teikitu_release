
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World [Collide].c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision.inl"
#include "TgS Physics - Internal.inl"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID
tgPH_Update_World__Collide__Callback(
    TgUINT_MAX_C uiKI_FY0, TgUINT_MAX_C uiKI_FY1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Collide_Batch ----------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS Forms, Bodies, Constraints (in Child Functions)                                                                                                                     */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide_Batch( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
//# tgPH_Update_World__Collide_Batch
    STg2_PH_World_PC                    psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    };

    /*  */

    // Recalculate Form AABBs

    /* Call the broad phase collision for all of the forms in the batch. */
    if (nullptr != g_pfnPH_Update_World__Collide)
    {
        g_pfnPH_Update_World__Collide( tiWorld, uiBegin, uiEnd );
    }
    else
    {
        tgPH_Update_World__Collide__Simple( tiWorld, uiBegin, uiEnd );
    };

    /* Generate contact points and test for tunneling. */



    /*  */

}


/* ---- tgPH_Update_World__Collide__Simple --------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS Forms | Bodies, Constraints (in Child Functions).                                                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide__Simple( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    }
    else
    {
        TgRSIZE_C                           nuiForm_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Form_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
        TgRSIZE                             uiIndex0, uiIndex1;

        #pragma region Iterate through this batch and find all colliding objects for it.
        for (uiIndex0 = uiBegin; uiIndex0 < uiEnd; ++uiIndex0)
        {
            STg2_PH_Form_PC                     psFM0 = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex0];

            if (!psFM0->m_bEnabled || 0ULL == psFM0->m_uiCollide)
            {
                continue;
            };

            for (uiIndex1 = 0; uiIndex1 < nuiForm_World; ++uiIndex1)
            {
                STg2_PH_Form_PC                     psFM1 = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex1];

                if (!psFM1->m_bEnabled || (uiIndex1 >= uiBegin && uiIndex1 <= uiIndex0))
                {
                    continue;
                };

                if (0 == (psFM0->m_uiCategory & psFM1->m_uiCollide))
                {
                    continue;
                };

                if (0 == (psFM1->m_uiCategory & psFM0->m_uiCollide))
                {
                    continue;
                };

                //# Store predicted value for form position and rotation to do a sweep test.

                //if (!tgCO_BA_Test_BA_F32_04( &psFM0->m_sBA, &psFM1->m_sBA ))
                //{
                //    continue;
                //};

                tgPH_Update_World__Collide__Callback( psFM0->m_tiForm.m_uiKI, psFM1->m_tiForm.m_uiKI );
            };
        };
        #pragma endregion
    };
}


/* ---- tgPH_Update_World__Collide__Prune_And_Sweep ------------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: READS Forms, Bodies | Constraints (in Child Functions). WRITES to Form's PnS ID (only).                                                                                   */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide__Prune_And_Sweep( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld) TgATTRIBUTE_UNLIKELY
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    }
    else
    {
        TgRSIZE                             uiIndex;

        /* Iterate through all of the current forms to determine if changes with the prune and sweep system is necessary. Enabled forms have to be inserted into the scene graph
           and if disabled they must be removed from the system. This is an optimization requirement since the smaller the list that needs to be traversed and compared will
           drastically decrease computation time. */

        #pragma region Iterate through this batch and find all colliding objects for it.
        for (uiIndex = uiBegin; uiIndex < uiEnd; ++uiIndex)
        {
            STg2_PH_Form_PC                     psFM = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];

            if (psFM->m_bEnabled)
            {
                if (KTgID__INVALID_VALUE == psFM->m_tiPnS.m_uiKI)
                {
                    psFM->m_tiPnS = tgPA_PnS_Insert_Object( &g_sPH_SG_PnS, 0ULL, psFM->m_uiCategory, psFM->m_uiCollide, &psFM->m_sBA_W );
                };
            }
            else if (KTgID__INVALID_VALUE == psFM->m_tiPnS.m_uiKI)
            {
                tgPA_PnS_Remove_Object( &g_sPH_SG_PnS, psFM->m_tiPnS );
                psFM->m_tiPnS.m_uiKI = KTgID__INVALID_VALUE;
            };

            tgPA_PnS_Exe_Func( &g_sPH_SG_PnS, tgPH_Update_World__Collide__Callback );
        };
        #pragma endregion
    };
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Collide__Callback ------------------------------------------------------------------------------------------------------------------------------------- */
/* SYNC: READS Forms, Bodies, Constraints. WRITES to Contact Constraints created in Immediate mode (linked list modification is deferred).                                         */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPH_Update_World__Collide__Callback( TgUINT_MAX_C uiKI_FY0, TgUINT_MAX_C uiKI_FY1 )
{
    TgPH_FORM_ID_C                      tiFM0 = { .m_uiKI = uiKI_FY0 };
    STg2_PH_Form_CPC                    psFM0 = tgPH_Form_Get_Form_From_ID( tiFM0 );
    TgPH_FORM_ID_C                      tiFM1 = { .m_uiKI = uiKI_FY1 };
    STg2_PH_Form_CPC                    psFM1 = tgPH_Form_Get_Form_From_ID( tiFM1 );
    STg2_PH_Body_P                      psBY0, psBY1;

    #pragma region Input Parameter validation checks. There is no reason this function should ever get bad data.
    /* Validates that valid Forms, and the Form and Body are in the same World. */
    TgDIAG((nullptr != psFM0) && (nullptr != psFM1));
    TgDIAG(psFM0->m_tiForm.m_uiWorld == psFM0->m_tiBY.m_uiWorld);
    TgDIAG(psFM0->m_tiForm.m_uiWorld == psFM1->m_tiForm.m_uiWorld);
    TgDIAG(psFM0->m_tiBY.m_uiWorld == psFM1->m_tiBY.m_uiWorld);

    /* Tests to see if the forms have an existing constraint between their bodies. */
    if (tgPH_Constraint_Query_Connected( psFM0->m_tiBY, psFM1->m_tiBY )) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    /* Validates that the forms do not share a body. */
    if (psFM0->m_tiBY.m_uiKI == psFM1->m_tiBY.m_uiKI) TgATTRIBUTE_UNLIKELY
    {
        return;
    };

    psBY0 = tgPH_Body_Get_Body_From_ID( psFM0->m_tiBY );
    psBY1 = tgPH_Body_Get_Body_From_ID( psFM1->m_tiBY );

    /* Validate that we have at least one valid body. Reminder that forms without bodies are considered to be kinematic. */
    TgDIAG((nullptr != psBY0) || (nullptr != psBY1));
    TgDIAG(psBY0->m_uiUsed_Index < TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + psBY0->m_tiBody.m_uiWorld, TgSTD_MEMORY_ORDER(relaxed) ));
    TgDIAG(psBY1->m_uiUsed_Index < TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Body_Total__Used + psBY1->m_tiBody.m_uiWorld, TgSTD_MEMORY_ORDER(relaxed) ));
    #pragma endregion

    #pragma region Collision Test and Contact Generation.
    {
        STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + psFM0->m_tiForm.m_uiWorld;

        TgVEC_F32_04_1_C                    vBY0_Pos_O2W = psUpdate_Simulation->m_avPos_W[psBY0->m_uiUsed_Index];
        TgVEC_F32_04_1_C                    vBY0_Rot_O2W = psUpdate_Simulation->m_avRot_W[psBY0->m_uiUsed_Index];
        TgVEC_F32_04_3                      mBY0_Final_O2W, mFM0_Final_O2W;

        TgVEC_F32_04_1_C                    vBY1_Pos_O2W = psUpdate_Simulation->m_avPos_W[psBY1->m_uiUsed_Index];
        TgVEC_F32_04_1_C                    vBY1_Rot_O2W = psUpdate_Simulation->m_avRot_W[psBY1->m_uiUsed_Index];
        TgVEC_F32_04_3                      mBY1_Final_O2W, mFM1_Final_O2W;

        STg2_CO_Packet_F32_04               sCO_Packet;
        STg2_CO_Contact_F32_04              sCO_Contact[4];
        TgDELTA_F32_04                      sΔt;
        TgVEC_F32_04_1                      vFM0_Pos_O2W, vFM1_Pos_O2W, vDT0, vDT1, vTime, vFM1_Support_Point, vFM1_ΔSP_LEN, vFM1_LEN_CMP, vRestitution_Factor;
        TgVEC_F32_04_3                      mFM0_Prev_Final_O2W, mFM1_Prev_Final_O2W;

        UTg2_CO_Primitive_F32_04            uPM0,uPM1;
        TgRESULT                            iResult;
        TgRSIZE                             uiIndex;

        #pragma region Initialize the Contact Packet used to gather the Contact Points.

        sCO_Packet.m_vSweepTol = tgMH_SET1_F32_04_1( 10.0F * KTgEPS_F32 );
        sCO_Packet.m_vSnapTol = tgMH_SET1_F32_04_1( 10.0F * KTgEPS_F32 );
        sCO_Packet.m_psContact = sCO_Contact;
        sCO_Packet.m_nuiContact = 0;
        sCO_Packet.m_nuiMaxContact = TgARRAY_COUNT(sCO_Contact);
        sCO_Packet.m_bReport_Penetration = true;

        #pragma endregion

        /* Broad Phase - Swept AABB Test. The collision scene graph is responsible for determining what collision pairs to test. */
        /* Narrow Phase */


        #pragma region Based on the Translation of the Forms, determine if a Sweep Test should be used.

        /* Construct the Reference Frame for the Form based on the Body's Predicted motion from the Simulation Step. */
        tgMH_Init_Reference_Frame_From_Quaternion_Position_F32_04_3( &mBY0_Final_O2W, vBY0_Rot_O2W, vBY0_Pos_O2W );
        tgMH_CAT_F32_04_3( &mFM0_Final_O2W, &psFM0->m_mLocal_O2B, &mBY0_Final_O2W );
        tgMH_Init_Reference_Frame_From_Quaternion_Position_F32_04_3( &mBY1_Final_O2W, vBY1_Rot_O2W, vBY1_Pos_O2W );
        tgMH_CAT_F32_04_3( &mFM1_Final_O2W, &psFM1->m_mLocal_O2B, &mBY1_Final_O2W );

        /* Calculate the translation from the current to the predicted positon. */
        vFM0_Pos_O2W = tgMH_Query_Axis_3_F32_04_3( &mFM0_Final_O2W );
        vDT0 = tgMH_SUB_F32_04_1( vFM0_Pos_O2W, psFM0->m_vPos_O2W );
        vFM1_Pos_O2W = tgMH_Query_Axis_3_F32_04_3( &mFM1_Final_O2W );
        vDT1 = tgMH_SUB_F32_04_1( vFM1_Pos_O2W, psFM1->m_vPos_O2W );

        /* Calculate the movement of Form 1 in Form 0 Reference Frame. */
        tgGM_DT_Set_F32_04( &sΔt, tgMH_SUB_F32_04_1( vDT1, vDT0 ) );
        vTime = tgMH_SET1_F32_04_1( 1.0F );

        /* Determine if the Form's translation (velocity) is greater than 50% of its size along the vector of translation (centre of gravity should not penetrate other Forms). */
        vFM1_LEN_CMP = tgMH_CMP_GT_F32_04_1( sΔt.m_vMag_DT, tgMH_SET1_F32_04_1( KTgEPS_F32 ) );
        if (tgMH_CMP_ANY_TO_BOOL_F32_04_1( vFM1_LEN_CMP ) && TgSUCCEEDED(tgPH_Form_Query_Support_Point( &vFM1_Support_Point, psFM1, sΔt.m_vUDT )))
        {
            TgVEC_F32_04_1_C                    vFM1_ΔSP = tgMH_SUB_F32_04_1( vFM1_Support_Point, vFM1_Pos_O2W );
            TgVEC_F32_04_1_C                    vFM1_LEN_TST = tgMH_MUL_F32_04_1( tgMH_SET1_F32_04_1( 2.0F ), sΔt.m_vMag_DT );

            vFM1_ΔSP_LEN = tgMH_LEN_F32_04_1( vFM1_ΔSP );
            vFM1_LEN_CMP = tgMH_CMP_LT_F32_04_1( vFM1_ΔSP_LEN, vFM1_LEN_TST );
        }
        else
        {
            vFM1_ΔSP_LEN = tgMH_SET1_F32_04_1( 0.0F );
            vFM1_LEN_CMP = tgMH_SET1_F32_04_1( 0.0F );
        };

        #pragma endregion

        #pragma region Collision Sweep Test (if required).
        if (tgMH_CMP_ANY_TO_BOOL_F32_04_1( vFM1_LEN_CMP ))
        {
            /* NOTE: This sweep test differs from testing along the continuum of motion for both Forms. The difference is that the Forms are swept through their linear motion path
                     but not their rotational changes. The rotation change is done immediately (which can lead to a pre-penetration), and then we sweep the Forms through the linear
                     path. This action can create "false" results. Some attempt is made to filter these out. However, it follows the tenets of the Physics Module that we are biased
                     toward performance, believability, consistency, and reproducibility. Correctness is not a hard requirement, and we are willing to accept the occasional
                     "incorrect" contact as it would be believable. */

            #pragma region Collision Sweep Test Setup (starting for previous position sweeping to predicted position).
            tgMH_Set_Rot_F32_04_3( &mFM0_Prev_Final_O2W, &mFM0_Final_O2W ); 
            tgMH_Set_T_F32_04_3( &mFM0_Prev_Final_O2W, psFM0->m_vPos_O2W );
            psFM0->m_pfnPM_Copy_TX( &uPM0, &psFM0->m_uPM, &mFM0_Prev_Final_O2W );

            tgMH_Set_Rot_F32_04_3( &mFM1_Prev_Final_O2W, &mFM1_Final_O2W );
            tgMH_Set_T_F32_04_3( &mFM1_Prev_Final_O2W, psFM1->m_vPos_O2W );
            #pragma endregion

            /* If required, use the Sweep test. If one does not exist for this primitive pair, use a fully self contained sphere to do the sweep and then do a penetration test
            based on the time of contact. */
            if (tgCO_PM_Sweep_PM_Supported_F32_04( psFM0->m_enPM, psFM1->m_enPM ))
            {
                psFM1->m_pfnPM_Copy_TX( &uPM1, &psFM1->m_uPM, &mFM1_Prev_Final_O2W );

                #pragma region Collision Sweep Test.
                iResult = tgCO_PM_Sweep_PM_F32_04( &sCO_Packet, &vTime, psFM0->m_enPM, &uPM0, psFM1->m_enPM, &uPM1, &sΔt );
                if (TgFAILED(iResult) && (KTgE_PREPENETRATION != iResult))
                {
                    return;
                };
                #pragma endregion
            }
            else if (tgCO_PM_Sweep_PM_Supported_F32_04( psFM0->m_enPM, ETgPM_SP ))
            {
                #pragma region Collision Sweep Sphere Test - Reposition Primitive for Penetration Test.
                UTg2_CO_Primitive_F32_04            uPM2;

                tgGM_SP_Init_F32_04(&uPM2.m_sSP, psFM1->m_vPos_O2W, vFM1_ΔSP_LEN);
                iResult = tgCO_PM_Sweep_PM_F32_04( &sCO_Packet, &vTime, psFM0->m_enPM, &uPM0, ETgPM_SP, &uPM2, &sΔt );
                if (TgSUCCEEDED(iResult) || (KTgE_PREPENETRATION == iResult))
                {
                    /* Interpolate the position and rotation of the two Forms for the Penetration Test. */
                    vFM0_Pos_O2W = tgMH_MAD_F32_04_1( vDT0, vTime, psFM0->m_vPos_O2W );
                    tgMH_Set_T_F32_04_3( &mFM0_Final_O2W, vFM0_Pos_O2W );
                    vFM1_Pos_O2W = tgMH_MAD_F32_04_1( vDT1, vTime, psFM1->m_vPos_O2W );
                    tgMH_Set_T_F32_04_3( &mFM1_Final_O2W, vFM1_Pos_O2W );
                };

                /* FALL THROUGH to the Penetration test is intentional. */
                #pragma endregion
            };
        };
        #pragma endregion

        #pragma region Collision Penetration Test for Repositioned Forms and Sweep Test not Required.
        if (0 == sCO_Packet.m_nuiContact)
        {
            #pragma region Collision Penetration Test (penetration test at the predicted position).
            TgDIAG(nullptr != psFM0->m_pfnPM_Copy_TX);
            psFM0->m_pfnPM_Copy_TX( &uPM0, &psFM0->m_uPM, &mFM0_Final_O2W );
            TgDIAG(nullptr != psFM1->m_pfnPM_Copy_TX);
            psFM1->m_pfnPM_Copy_TX( &uPM1, &psFM1->m_uPM, &mFM1_Final_O2W );

            iResult = tgCO_PM_Penetrate_PM_F32_04( &sCO_Packet, psFM0->m_enPM, &uPM0, psFM1->m_enPM, &uPM1 );
            if (TgFAILED(iResult))
            {
                return;
            };
            #pragma endregion
        };
        #pragma endregion

        #pragma region Add the Contact Constraints to the World Update for the Solver.
        /* Calculate the Factor of Restitution */
        vRestitution_Factor = tgPH_Material_Calc_Restitution_Factor( psFM0, vDT0, psFM1, vDT1 );
        for (uiIndex = 0; uiIndex < sCO_Packet.m_nuiContact; ++uiIndex)
        {
            TgVEC_F32_04_1                      vX0 = tgMH_SUB_F32_04_1( vTime, KTgONE_F32_04_1 );
            TgVEC_F32_04_1                      vX1 = tgMH_MUL_F32_04_1( vX0, sΔt.m_vDT );
            TgVEC_F32_04_1                      vX2 = tgMH_DOT_F32_04_1( vX1, sCO_Contact[uiIndex].m_vN0 );

            sCO_Contact[uiIndex].m_vDepth = tgMH_ADD_F32_04_1( vX2, sCO_Contact[uiIndex].m_vDepth );
            tgPH_Constraint_Contact__Init_IMM( psFM0, psFM1, vRestitution_Factor, sCO_Contact + uiIndex );
        };
        #pragma endregion
    };
    #pragma endregion
}
