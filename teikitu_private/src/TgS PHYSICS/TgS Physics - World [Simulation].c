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

/* ---- tgPH_Update_World__Simulate_Batch_IMM ------------------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: READS World, WRITES to Bodies that are contained in this Batch (ONLY) - Each Batch is guaranteed to be unique and independent (No access by other jobs).                  */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Simulate_Batch_IMM( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );
    STg2_PH_Update__Simulation_CPC      psUpdate_Simulation = g_asPH_Update__Simulation + tiWorld.m_uiI;
    TgVEC_F32_04_1_C                    vStep_Size_RCP = tgMH_RCP_F32_04_1( psWorld->m_vStep_Size );
    TgVEC_F32_04_1_C                    vOne = tgMH_SET1_F32_04_1( 1.0F );
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK(nullptr != psWorld);

    /* We need access to read the world, and update (write) access to world updates fields (not done through synchronization objects). */

    #pragma region Recalculate all active AABBs.
    #pragma endregion

    #pragma region Initialize all of the simulation frame values.
    for (uiIndex = uiBegin; uiIndex < uiEnd; ++uiIndex)
    {
        STg2_PH_Body_PC                     psBY = g_aapsPH_Body_Used[tiWorld.m_uiI][uiIndex];
        TgVEC_F32_04_1_C                    vForce_Field = tgMH_MUL_F32_04_1( psWorld->m_vForce_Field, psBY->m_vForce_Field_Factor );
        TgVEC_F32_04_3                      mK0, mK1, mIT;
        TgVEC_F32_04_1                      vAM, vAMxAV;
        TgVEC_F32_04_1                      vLV_LV, vAV_AV;
    
        TgDIAG(uiIndex == psBY->m_uiUsed_Index);

        #pragma region Calculate the Inertia Tensor and its Inverse.
        tgMH_MUL_F32_04_3( &mK0, &psBY->m_sMass.m_mMOI, &psBY->m_mRot_O2W );
        tgMH_MUL_F32_04_3( &mIT, &psBY->m_mRot_O2W, &mK0 );
        tgMH_MUL_F32_04_3( &mK1, &psBY->m_sMass.m_mInv_MOI, &psBY->m_mRot_O2W );
        tgMH_MUL_F32_04_3( &psBY->m_mInverse_Inertia_Tensor, &psBY->m_mRot_O2W, &mK1 );
        #pragma endregion

        #pragma region Calculate Rotational Force and Torque(て).
        vAM = tgMH_TX_F32_04_3( psBY->m_vAV, &mIT );
        vAMxAV = tgMH_CX_F32_04_1( vAM, psBY->m_vAV );
        psBY->m_vXT = tgMH_SUB_F32_04_1( psBY->m_vPT, vAMxAV );
        #pragma endregion

        #pragma region Add Force Field and External Force.
        #if defined(TgBUILD_DEBUG__PHYSICS__EXTENSIVE_DATA_CHECK)
        TgDIAG(((TgVEC_S_F32_04_1_CP)&vForce_Field)->w == 0.0F);
        TgDIAG(((TgVEC_S_F32_04_1_CP)&psBY->m_vPF)->w == 0.0F);
        TgDIAG(((TgVEC_S_F32_04_1_CP)&psBY->m_vXF)->w == 0.0F);
        #endif
        psBY->m_vXF = tgMH_MAD_F32_04_1( vForce_Field, psBY->m_sMass.m_uMass.m_vF32_04_1, tgMH_ADD_F32_04_1( psBY->m_vPF, psBY->m_vXF ) );
        #pragma endregion

        #pragma region Check for a user defined function to determine force/moments.
        if (nullptr != psBY->m_pfnCalcFM)
        {
            TgVEC_F32_04_1                      vF, vT;

            psBY->m_pfnCalcFM( &vF, &vT, psBY->m_tiBody, psBY->m_uiContext, psWorld->m_vStep_Size );
            psBY->m_vXF = tgMH_ADD_F32_04_1( psBY->m_vXF, vF );
            psBY->m_vXT = tgMH_ADD_F32_04_1( psBY->m_vXT, vT );
        };
        #pragma endregion

        #pragma region Calculate the desired state.
        {
            TgVEC_F32_04_1_C                    vLA = tgMH_MUL_F32_04_1( psBY->m_sMass.m_uInv_Mass.m_vF32_04_1, psBY->m_vXF ); /* Predicted Linear Acceleration */
            TgVEC_F32_04_1_C                    vLV = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vLA, psBY->m_vLV ); /* Predicted Linear Velocity */

            TgVEC_F32_04_1_C                    vAA = tgMH_TX_F32_04_3( psBY->m_vXT, &psBY->m_mInverse_Inertia_Tensor ); /* Predicted Angular Acceleration */
            TgVEC_F32_04_1_C                    vAV = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vAA, psBY->m_vAV ); /* Predicted Angular Velocity */
            TgVEC_F32_04_1_C                    vΔQ = tgMH_QT_MUL_F32_04_1( vAV, psBY->m_vRot_O2W ); /* Predicted change in Rotation */
            TgVEC_F32_04_1_C                    vQ = tgMH_MAD_F32_04_1( vΔQ, psWorld->m_vStep_Size, psBY->m_vRot_O2W ); /* Predicted Rotation */

            psUpdate_Simulation->m_avPos_W[uiIndex] = tgMH_MAD_F32_04_1( psWorld->m_vStep_Size, vLV, psBY->m_vPos_O2W ); /* Predicted Position */
            psUpdate_Simulation->m_avRot_W[uiIndex] = tgMH_NORM_F32_04_1( vQ ); /* Predicted Rotation (Normalized) */
            psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 0] = tgMH_MAD_F32_04_1( psBY->m_vLV, vStep_Size_RCP, vLA ); /* RHS - Linear Constraint */
            psUpdate_Simulation->m_avRHS_LA[uiIndex*2 + 1] = tgMH_MAD_F32_04_1( psBY->m_vAV, vStep_Size_RCP, vAA );  /* RHS - Angular Constraint */

            vLV_LV = tgMH_LSQ_F32_04_1( vLV );
            vAV_AV = tgMH_LSQ_F32_04_1( vAV );
        };
        #pragma endregion
        #pragma region Test for auto-disable (sleep).
        {
            TgVEC_F32_04_1                      vDisable_Test;

            vDisable_Test = tgMH_AND_F32_04_1( tgMH_CMP_LT_F32_04_1( vLV_LV, vOne ), tgMH_CMP_LT_F32_04_1( vAV_AV, vOne ) );
            vDisable_Test = tgMH_AND_F32_04_1( tgMH_LSQ_F32_04_1( psBY->m_vXF ), vDisable_Test );
            vDisable_Test = tgMH_AND_F32_04_1( tgMH_LSQ_F32_04_1( psBY->m_vXT ), vDisable_Test );
            if (!tgMH_CMP_ALL_TO_BOOL_F32_04_1( vDisable_Test ))
                psBY->m_fDisable_Timer = KTgPH_MAX_DISABLE_TIMER;
            else
                psBY->m_fDisable_Timer -= psWorld->m_fStep_Size_Seconds;
        };
        #pragma endregion
    };
    #pragma endregion

    /* Update the Prune and Sweep with a swept region of the collision volume. */
    //# Update Collision Graph (PnS)
}
