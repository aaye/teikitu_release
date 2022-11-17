/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - World [Simulation].c
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
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Update_World__Simulate_Batch ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Simulate_Batch( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    }
    else
    {
        STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + tiWorld.m_uiI;
        TgVEC_F32_04_1_C                    vStep_Size_RCP = tgMH_RCP_F32_04_1( psWorld->m_vStep_Size );
        TgVEC_F32_04_1_C                    vOne = tgMH_SET1_F32_04_1( 1.0F );
        TgRSIZE                             uiIndex;

        tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );

        #pragma region Recalculate all active AABBs.
        #pragma endregion

        #pragma region Initialize all of the simulation frame values.
        for (uiIndex = uiBegin; uiIndex < uiEnd; ++uiIndex)
        {
            STg2_PH_Body_PC                     psBody = g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex];
            TgVEC_F32_04_1_C                    vForce_Field = tgMH_MUL_F32_04_1( psWorld->m_vForce_Field, psBody->m_vForce_Field_Factor );
            TgVEC_F32_04_3                      mK0, mK1, mIT;
            TgVEC_F32_04_1                      vAM, vAMxAV;
            TgVEC_F32_04_1                      vDisable_Test;
        
            #pragma region Calculate the Inertia Tensor and its Inverse.
            tgMH_MUL_F32_04_3( &mK0, &psBody->m_sMass.m_mMOI, &psBody->m_mRot_W );
            tgMH_MUL_F32_04_3( &mIT, &psBody->m_mRot_W, &mK0 );
            tgMH_MUL_F32_04_3( &mK1, &psBody->m_sMass.m_mInv_MOI, &psBody->m_mRot_W );
            tgMH_MUL_F32_04_3( &psBody->m_mInverse_Inertia_Tensor, &psBody->m_mRot_W, &mK1 );
            #pragma endregion

            #pragma region Calculate Rotational Force and External Moment.
            vAM = tgMH_TX_F32_04_3( psBody->m_vAV, &mIT );
            vAMxAV = tgMH_CX_F32_04_1( vAM, psBody->m_vAV );
            psBody->m_vXT = tgMH_SUB_F32_04_1( psBody->m_vPT, vAMxAV );
            #pragma endregion

            #pragma region Add Force Field and External Force.
            psBody->m_vXF = tgMH_MAD_F32_04_1( vForce_Field, psBody->m_sMass.m_uMass.m_vF32_04_1, psBody->m_vPF );
            #pragma endregion

            #pragma region Check for a user defined function to determine force/moments.
            if (nullptr != psBody->m_pfnCalcFM)
            {
                TgVEC_F32_04_1                      vF, vT;

                psBody->m_pfnCalcFM( &vF, &vT, psBody->m_tiBody, psBody->m_uiContext, psWorld->m_vStep_Size );
                psBody->m_vXF = tgMH_ADD_F32_04_1( psBody->m_vXF, vF );
                psBody->m_vXT = tgMH_ADD_F32_04_1( psBody->m_vXT, vT );
            };
            #pragma endregion

            #pragma region Calculate the desired state.
            {
                TgVEC_F32_04_1_C                    vScaled_Step_Size = tgMH_MUL_F32_04_1( psBody->m_vTime_Factor, psWorld->m_vStep_Size );
                TgVEC_F32_04_1_C                    vScaled_Mult = tgMH_MUL_F32_04_1( vScaled_Step_Size, psBody->m_sMass.m_uInv_Mass.m_vF32_04_1 );
                TgVEC_F32_04_1_C                    vLV = tgMH_MAD_F32_04_1( vScaled_Mult, psBody->m_vXF, psBody->m_vLV );

                TgVEC_F32_04_1_C                    vTMP_00 = tgMH_TX_F32_04_3( psBody->m_vXT, &psBody->m_mInverse_Inertia_Tensor );
                TgVEC_F32_04_1_C                    vTMP_01 = tgMH_MUL_F32_04_1( vScaled_Step_Size, vTMP_00 );
                TgVEC_F32_04_1_C                    vAV = tgMH_ADD_F32_04_1( psBody->m_vAV, vTMP_01 );
                TgVEC_F32_04_1_C                    vΔQ = tgMH_QT_MUL_F32_04_1( vAV, psBody->m_vRot_W );
                TgVEC_F32_04_1_C                    vQ = tgMH_MAD_F32_04_1( vΔQ, vScaled_Step_Size, psBody->m_vRot_W );

                TgVEC_F32_04_1_C                    vTMP_02 = tgMH_MUL_F32_04_1( psBody->m_vLV, vStep_Size_RCP );

                psUpdate_Simulation->m_avPos_W[uiIndex] = tgMH_MAD_F32_04_1( vScaled_Step_Size, vLV, psBody->m_vPos_W );
                psUpdate_Simulation->m_avRot_W[uiIndex] = tgMH_NORM_F32_04_1( vQ );
                psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 0] = tgMH_MAD_F32_04_1( psBody->m_sMass.m_uInv_Mass.m_vF32_04_1, psBody->m_vXF, vTMP_02 );
                psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 1] = tgMH_MAD_F32_04_1( vStep_Size_RCP, psBody->m_vAV, vTMP_00 );

                vDisable_Test = tgMH_AND_F32_04_1( tgMH_CMP_LT_F32_04_1( tgMH_LSQ_F32_04_1( vLV ), vOne ), tgMH_CMP_LT_F32_04_1( tgMH_LSQ_F32_04_1( vAV ), vOne ) );
            };
            #pragma endregion
            #pragma region Test for auto-disable (sleep).
            {
                vDisable_Test = tgMH_AND_F32_04_1( tgMH_LSQ_F32_04_1( psBody->m_vXF ), vDisable_Test );
                vDisable_Test = tgMH_AND_F32_04_1( tgMH_LSQ_F32_04_1( psBody->m_vXT ), vDisable_Test );
                if (!tgMH_CMP_ALL_TO_BOOL_F32_04_1( vDisable_Test ))
                    psBody->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
                else
                    psBody->m_fDisable_Timer -= psWorld->m_fStep_Size_Seconds;
            };
            #pragma endregion
        };
        #pragma endregion

        TgERROR_MSGF( uiIndex == g_anuiPH_Body_Total__Used[tiWorld.m_uiI], STD_MSG_LITERAL_1, STD_MSG_POST, u8"World Body link list length does not match the count." );
        tgCM_UT_LF__RW__Exit_Read( &g_asPH_World_Data_Lock[tiWorld.m_uiI ].m_sLock );

        /* Update the Prune and Sweep with a swept region of the collision volume. */

//# Update Collision Graph (PnS)
    };
}
