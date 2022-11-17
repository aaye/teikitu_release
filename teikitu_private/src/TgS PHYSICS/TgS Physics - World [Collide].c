
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
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide_Batch( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
//# tgPH_Update_World__Collide_Batch
    STg2_PH_World_PC                    psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    };

    /*  */

    // Recalculate Form AABBs

    /* Call the broad phase collision for all of the forms in the batch. */
    if (nullptr == g_pfnPH_Update_World__Collide)
    {
        g_pfnPH_Update_World__Collide( tiWorld, uiBegin, uiEnd );
    }

    /* Generate contact points and test for tunneling. */



    /*  */

}


/* ---- tgPH_Update_World__Collide__Simple --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide__Simple( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale World ID submitted for update." );
        return;
    }
    else
    {
        TgRSIZE_C                           nuiForm_World = g_anuiPH_Body_Total__Used[tiWorld.m_uiI];
        TgRSIZE                             uiIndex0, uiIndex1;

        #pragma region Iterate through this batch and find all colliding objects for it.
        for (uiIndex0 = uiBegin; uiIndex0 < uiEnd; ++uiIndex0)
        {
            STg2_PH_Form_PC                     psFM0 = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex0];

            if (!psFM0->m_bEnabled || 0ULL == psFM0->m_uiCollide)
            {
                continue;
            };

            for (uiIndex1 = uiBegin + 1; uiIndex1 < nuiForm_World; ++uiIndex1)
            {
                STg2_PH_Form_PC                     psFM1 = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex1];

                if (!psFM1->m_bEnabled)
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

                if (!tgCO_BA_Test_BA_F32_04( &psFM0->m_sBA, &psFM1->m_sBA ))
                {
                    continue;
                };

                tgPH_Update_World__Collide__Callback( psFM0->m_tiForm.m_uiKI, psFM1->m_tiForm.m_uiKI );
            };
        };
        #pragma endregion
    };
}


/* ---- tgPH_Update_World__Collide__Prune_And_Sweep ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Update_World__Collide__Prune_And_Sweep( TgPH_WORLD_ID_C tiWorld, TgRSIZE_C uiBegin, TgRSIZE_C uiEnd )
{
    STg2_PH_World_CPC                   psWorld = tgPH_World_Get_World_From_ID( tiWorld );

    if (nullptr == psWorld)
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
            STg2_PH_Form_PC                     psForm = g_aapsPH_Form_Used[tiWorld.m_uiI][uiIndex];

            if (psForm->m_bEnabled)
            {
                if (KTgID__INVALID_VALUE == psForm->m_tiPnS.m_uiKI)
                {
                    psForm->m_tiPnS = tgPA_PnS_Insert_Object( &g_sPH_SG_PnS, 0ULL, psForm->m_uiCategory, psForm->m_uiCollide, &psForm->m_sBA );
                };
            }
            else if (KTgID__INVALID_VALUE == psForm->m_tiPnS.m_uiKI)
            {
                tgPA_PnS_Remove_Object( &g_sPH_SG_PnS, psForm->m_tiPnS );
                psForm->m_tiPnS.m_uiKI = KTgID__INVALID_VALUE;
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
/* Narrow phase collision                                                                                                                                                          */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPH_Update_World__Collide__Callback( TgUINT_MAX_C uiKI_FY0, TgUINT_MAX_C uiKI_FY1 )
{
    TgPH_FORM_ID                        tiFM0 = { .m_uiKI = uiKI_FY0 };
    STg2_PH_Form_PC                     psFM0 = g_aasPH_Form[tiFM0.m_uiWorld] + tiFM0.m_uiI;

    TgPH_FORM_ID                        tiFM1 = { .m_uiKI = uiKI_FY1 };
    STg2_PH_Form_PC                     psFM1 = g_aasPH_Form[tiFM1.m_uiWorld] + tiFM1.m_uiI;

    if (tgPH_Constraint_Query_Connected( psFM0->m_tiBody, psFM1->m_tiBody ))
    {
        return;
    }

    if (psFM0->m_tiBody.m_uiKI == psFM1->m_tiBody.m_uiKI)
    {
        return;
    };
//# tgPH_Update_World__Collide__Callback
    {
        //STg2_PH_Body_PC                     psBY0 = g_aasPH_Body[psFY0->m_tiBody.m_uiWorld] + psFY0->m_tiBody.m_uiI;
        //TgVEC_F32_04_1_C                    vDT0 = tgMH_SUB_F32_04_1( psFY0->m_tvPos_W, psFY0->m_tvPos_LastValid_W );

        //STg2_PH_Body_PC                     psBY1 = g_aasPH_Body[psFY1->m_tiBody.m_uiWorld] + psFY1->m_tiBody.m_uiI;
        //TgVEC_F32_04_1_C                    vDT1 = tgMH_SUB_F32_04_1( psFY1->m_tvPos_W, psFY1->m_tvPos_LastValid_W );

        //TgFLOAT32                           fTime = 1.0F;

        //STg2_CO_Request                     sCollision_Request;

        /* Near Phase Collision Check */
        //# TODO Collision Call

        //# TODO Create a contact joint
    };
}
