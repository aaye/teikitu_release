/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Visualize.c
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



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

TgVOID tgPH_Form_Visualize_Render( UTg2_KN_GPU_CMD_C uCMD, STg2_KN_GPU_HLSL_CB_Debug_Model_PC psModelConstantBuffer, TgPH_WORLD_ID_C tiWorld )
{
    TgRSIZE_C                           nuiForm_World = TgSTD_ATOMIC(load_explicit)( g_axnuiPH_Form_Total__Used + tiWorld.m_uiI, TgSTD_MEMORY_ORDER(relaxed) );
    TgRSIZE                             uiIndex;

    for (uiIndex = 0; uiIndex < nuiForm_World; ++uiIndex)
    {
        STg2_PH_Form_CPC                    psFM = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];
        TgVEC_UN_CONST_PTR_F32_04_3         uM0 = { .m_pmF32_04_3 = &psFM->m_mFinal_O2W };

        psModelConstantBuffer->m_uModel_Colour.m_vF32_04_1 = psFM->m_bEnabled ? psFM->m_vDebug_Colour : tgMH_Init_ELEM_F32_04_1( 5.0F, 0.0F, 0.0F, 0.25F );

        TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
        switch (psFM->m_enPM) {
        case ETgPM_PN:
            tgMM_Copy( &psModelConstantBuffer->m_vModel_Transform, sizeof(psModelConstantBuffer->m_vModel_Transform), uM0.m_pmS_F32_04_3, sizeof(TgVEC_UN_F32_04_3) );
            tgKN_GPU_EXT__CMD__Render_Debug_Geom( uCMD, ETgKN_GPU_DEBUG_PM_3D_PLANE, psModelConstantBuffer );
            break;
        case ETgPM_BX: {
                TgVEC_F32_04_1_C                    vFactor = tgMH_Init_ELEM_F32_04_1( 2.0F, 2.0F, 2.0F, 1.0F );
                TgVEC_F32_04_1_C                    vExtent = tgMH_Init_Point_F32_04_1( psFM->m_uPM.m_sBX.m_vExtent );
                TgVEC_UN_F32_04_1_C                 uScale = { .m_vF32_04_1 = tgMH_MUL_F32_04_1( vFactor, vExtent ) };
                TgVEC_UN_F32_04_3                   uM1;

                tgMH_CAT_F32_04_3( &uM1.m_mF32_04_3, &psFM->m_uPM.m_sBX.m_mReference_Frame, uM0.m_pmF32_04_3 );

                psModelConstantBuffer->m_vModel_Transform.m_vC0 = tgMH_MUL_S_F32_04_1( uM1.m_mS_F32_04_3.m_vC0, uScale.m_vS_F32_04_1 );
                psModelConstantBuffer->m_vModel_Transform.m_vC1 = tgMH_MUL_S_F32_04_1( uM1.m_mS_F32_04_3.m_vC1, uScale.m_vS_F32_04_1 );
                psModelConstantBuffer->m_vModel_Transform.m_vC2 = tgMH_MUL_S_F32_04_1( uM1.m_mS_F32_04_3.m_vC2, uScale.m_vS_F32_04_1 );
                tgKN_GPU_EXT__CMD__Render_Debug_Geom( uCMD, ETgKN_GPU_DEBUG_PM_3D_BOX, psModelConstantBuffer );
            }
            break;
        case ETgPM_SP: {
                TgVEC_F32_04_1_C                    vFactor = tgMH_Init_ELEM_F32_04_1( 2.0F, 2.0F, 2.0F, 1.0F );
                TgVEC_F32_04_1_C                    vRadius = tgMH_Init_Point_F32_04_1( psFM->m_uPM.m_sSP.m_vRadius );
                TgVEC_UN_F32_04_1_C                 uScale = { .m_vF32_04_1 = tgMH_MUL_F32_04_1( vFactor, vRadius ) };

                psModelConstantBuffer->m_vModel_Transform.m_vC0 = tgMH_MUL_S_F32_04_1( uM0.m_pmS_F32_04_3->m_vC0, uScale.m_vS_F32_04_1 );
                psModelConstantBuffer->m_vModel_Transform.m_vC1 = tgMH_MUL_S_F32_04_1( uM0.m_pmS_F32_04_3->m_vC1, uScale.m_vS_F32_04_1 );
                psModelConstantBuffer->m_vModel_Transform.m_vC2 = tgMH_MUL_S_F32_04_1( uM0.m_pmS_F32_04_3->m_vC2, uScale.m_vS_F32_04_1 );
                tgKN_GPU_EXT__CMD__Render_Debug_Geom( uCMD, ETgKN_GPU_DEBUG_PM_3D_SPHERE, psModelConstantBuffer );
            }
            break;
        default:
            break;
        }
        TgWARN_DISABLE_POP()
    }
}

/*# defined(TgBUILD_DEBUG__PHYSICS) && defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
