/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - Prune and Sweep.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID                               tgPA_PnS_Object_Update_Interval( STg2_PA_PnS_PCU, STg2_PA_PnS_PointEnd_PCU, TgFLOAT32_C, TgFLOAT32_C, TgFLOAT32_C, TgFLOAT32_C, TgPNS_OBJECT_ID_C );
static TgVOID                               tgPA_PnS_Interval_Push( STg2_PA_PnS_PointEnd_PCU, TgFLOAT32_C, TgFLOAT32_C, TgRSIZE_C );
static TgVOID                               tgPA_PnS_Interval_Update( STg2_PA_PnS_PointEnd_PCU, TgUINT_E16_C, TgUINT_E16_C );
static TgBOOL                               tgPA_PnS_Pair_Push( STg2_PA_PnS_PCU, TgRSIZE_C, TgRSIZE_C );
static TgBOOL                               tgPA_PnS_Remove_Contact_Pair( STg2_PA_PnS_PCU, TgRSIZE_C, TgRSIZE_C );
static TgVOID                               tgPA_PnS_Remove_Object_Contact_List( STg2_PA_PnS_PCU, TgRSIZE_C  );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPA_PnS_Init ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPA_PnS_Init( STg2_PA_PnS_PCU NONULL psPnS )
{
    psPnS->m_asX0[KTgPA_PNS_MAX_INTERVAL].m_uiNext = KTgPA_PNS_MAX_INTERVAL;
    psPnS->m_asX0[KTgPA_PNS_MAX_INTERVAL].m_uiPrev = KTgPA_PNS_MAX_INTERVAL;
    psPnS->m_asX1[KTgPA_PNS_MAX_INTERVAL].m_uiNext = KTgPA_PNS_MAX_INTERVAL;
    psPnS->m_asX1[KTgPA_PNS_MAX_INTERVAL].m_uiPrev = KTgPA_PNS_MAX_INTERVAL;
    psPnS->m_asX2[KTgPA_PNS_MAX_INTERVAL].m_uiNext = KTgPA_PNS_MAX_INTERVAL;
    psPnS->m_asX2[KTgPA_PNS_MAX_INTERVAL].m_uiPrev = KTgPA_PNS_MAX_INTERVAL;

    tgMM_Set_U08_0xFF( psPnS->m_uiCallbackID, sizeof( psPnS->m_uiCallbackID ) );
    tgMM_Set_U08_0x00( psPnS->m_uiCategory, sizeof( psPnS->m_uiCategory ) );
    tgMM_Set_U08_0x00( psPnS->m_uiCollide, sizeof( psPnS->m_uiCollide ) );

    for (TgRSIZE uiIndex = 0; uiIndex < KTgPA_PNS_MAX_OBJECTS; ++uiIndex)
    {
        tgGM_BA_Reset_F32_04( psPnS->m_asBA + uiIndex );
        tgPNS_OBJECT_ID_Invalidate( psPnS->m_atiObject + uiIndex );
        psPnS->m_auiContact_Linked_List_Head[uiIndex] = KTgPA_PNS_MAX_CONTACT_PAIR;
    };

    tgMM_Set_U08_0xFF( psPnS->m_atiContact_Object, sizeof( psPnS->m_atiContact_Object ) );

    for (TgRSIZE uiIndex = 0; uiIndex < KTgPA_PNS_MAX_CONTACT_PAIR; ++uiIndex)
    {
        psPnS->m_auiContact_Next[uiIndex] = uiIndex + 1;
    };

    psPnS->m_nuiObjects = 0;
    psPnS->m_uiEmpty = 0;

    /* Create the Critical Section if MP-Safe requested */
    tgPM_MT_MX_Init( &psPnS->m_csSystemLock, nullptr );
}


/* ---- tgPA_PnS_Exe_Func -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_PnS_Exe_Func( STg2_PA_PnS_PCU NONULL psPnS, TgVOID(*pfnExec)( TgUINT_MAX_C , TgUINT_MAX_C ) )
{
    TgUINT_MAX                          uiCallbackID;

    if (nullptr == pfnExec)
    {
        return (KTgE_FAIL);
    };

    tgPM_MT_MX_Wait_Block( &psPnS->m_csSystemLock );

    for (TgRSIZE uiIndex = 0, nuiObjects = 0; uiIndex < KTgPA_PNS_MAX_OBJECTS && nuiObjects < psPnS->m_nuiObjects; ++uiIndex)
    {
        if (0 == ((3u << 30) & psPnS->m_uiCategory[uiIndex]))
        {
            continue;
        };

        ++nuiObjects;

        uiCallbackID = psPnS->m_uiCallbackID[uiIndex];

        for (TgRSIZE uiContact_Index = psPnS->m_auiContact_Linked_List_Head[uiIndex]; uiContact_Index < KTgPA_PNS_MAX_CONTACT_PAIR; )
        {
            pfnExec( uiCallbackID, psPnS->m_uiCallbackID[uiContact_Index] );
            uiContact_Index = psPnS->m_auiContact_Next[uiContact_Index];
        };
    };

    tgPM_MT_MX_Release( &psPnS->m_csSystemLock );

    return (KTgS_OK);
}


/* ---- tgPA_PnS_Remove_Object --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_PnS_Remove_Object( STg2_PA_PnS_PCU psPnS, TgPNS_OBJECT_ID_C tiObject )
{
    TgRSIZE                             uiIndex_Interval_0 = 2 * tiObject.m_uiI + 0;
    TgRSIZE                             uiIndex_Interval_1 = 2 * tiObject.m_uiI + 1;

    tgPM_MT_MX_Wait_Block( &psPnS->m_csSystemLock );

    TgERROR( (tiObject.m_uiI < KTgPA_PNS_MAX_OBJECTS) && (0 != (psPnS->m_uiCategory[tiObject.m_uiI] & (3u << 30))) );

    /* Remove the respective min and max projections of the bounding box on each axis. */

    psPnS->m_asX0[psPnS->m_asX0[uiIndex_Interval_0].m_uiPrev].m_uiNext = psPnS->m_asX0[uiIndex_Interval_0].m_uiNext;
    psPnS->m_asX0[psPnS->m_asX0[uiIndex_Interval_0].m_uiNext].m_uiPrev = psPnS->m_asX0[uiIndex_Interval_0].m_uiPrev;
    psPnS->m_asX0[psPnS->m_asX0[uiIndex_Interval_1].m_uiPrev].m_uiNext = psPnS->m_asX0[uiIndex_Interval_1].m_uiNext;
    psPnS->m_asX0[psPnS->m_asX0[uiIndex_Interval_1].m_uiNext].m_uiPrev = psPnS->m_asX0[uiIndex_Interval_1].m_uiPrev;

    psPnS->m_asX1[psPnS->m_asX1[uiIndex_Interval_0].m_uiPrev].m_uiNext = psPnS->m_asX1[uiIndex_Interval_0].m_uiNext;
    psPnS->m_asX1[psPnS->m_asX1[uiIndex_Interval_0].m_uiNext].m_uiPrev = psPnS->m_asX1[uiIndex_Interval_0].m_uiPrev;
    psPnS->m_asX1[psPnS->m_asX1[uiIndex_Interval_1].m_uiPrev].m_uiNext = psPnS->m_asX1[uiIndex_Interval_1].m_uiNext;
    psPnS->m_asX1[psPnS->m_asX1[uiIndex_Interval_1].m_uiNext].m_uiPrev = psPnS->m_asX1[uiIndex_Interval_1].m_uiPrev;

    psPnS->m_asX2[psPnS->m_asX2[uiIndex_Interval_0].m_uiPrev].m_uiNext = psPnS->m_asX2[uiIndex_Interval_0].m_uiNext;
    psPnS->m_asX2[psPnS->m_asX2[uiIndex_Interval_0].m_uiNext].m_uiPrev = psPnS->m_asX2[uiIndex_Interval_0].m_uiPrev;
    psPnS->m_asX2[psPnS->m_asX2[uiIndex_Interval_1].m_uiPrev].m_uiNext = psPnS->m_asX2[uiIndex_Interval_1].m_uiNext;
    psPnS->m_asX2[psPnS->m_asX2[uiIndex_Interval_1].m_uiNext].m_uiPrev = psPnS->m_asX2[uiIndex_Interval_1].m_uiPrev;

    tgPA_PnS_Remove_Object_Contact_List( psPnS, tiObject.m_uiI ); /**< Remove all pairs that contain this ID */
    TgERROR( KTgPA_PNS_MAX_CONTACT_PAIR == psPnS->m_auiContact_Linked_List_Head[tiObject.m_uiI] );

    psPnS->m_uiCallbackID[tiObject.m_uiI] = KTgMAX_UMAX;
    psPnS->m_uiCategory[tiObject.m_uiI] = 0;
    psPnS->m_uiCollide[tiObject.m_uiI] = 0;
    tgGM_BA_Reset_F32_04( psPnS->m_asBA + tiObject.m_uiI );
    tgPNS_OBJECT_ID_Invalidate( psPnS->m_atiObject + tiObject.m_uiI );
    psPnS->m_auiContact_Linked_List_Head[tiObject.m_uiI] = KTgPA_PNS_MAX_CONTACT_PAIR;

    --psPnS->m_nuiObjects;

    tgPM_MT_MX_Release( &psPnS->m_csSystemLock );

    return (KTgS_OK);
}


/* ---- tgPA_PnS_Insert_Object --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgPNS_OBJECT_ID tgPA_PnS_Insert_Object( STg2_PA_PnS_PCU psPnS, TgUINT_MAX_C uiCallbackID, TgUINT_E64_C uiCategory, TgUINT_E64_C uiCollide, TgBOXAA_F32_04_CPCU psBA )
{
    TgUINT_E32                          uiIndex_Object;
    //TgRSIZE                             uiIndex_Interval_0, uiIndex_Interval_1;
    TgUN_V128                           vMin, vMax;

    /* Data consistency check - mask values must have valid (one) 30th and 31st bits */

    if ((0 != (uiCategory & (3u << 30))) || !tgGM_BA_Is_Valid_F32_04( psBA ) || !tgGM_BA_Is_Empty_F32_04( psBA ))
    {
        return (KTgPNS_OBJECT_ID__INVALID);
    }

    tgPM_MT_MX_Wait_Block( &psPnS->m_csSystemLock );

    /* Find an open array element. */

    for (uiIndex_Object = 0; uiIndex_Object < KTgPA_PNS_MAX_OBJECTS && (0 != (psPnS->m_uiCategory[uiIndex_Object] & (3u << 30))); ++uiIndex_Object);

    if (uiIndex_Object >= KTgPA_PNS_MAX_OBJECTS)
    {
        tgPM_MT_MX_Release( &psPnS->m_csSystemLock );
        return (KTgPNS_OBJECT_ID__INVALID);
    };

    //uiIndex_Interval_0 = 2 * uiIndex_Object + 0;
    //uiIndex_Interval_1 = 2 * uiIndex_Object + 1;

    vMin.m_vF32_04_1 = tgGM_BA_Query_Min_F32_04( psBA );
    vMax.m_vF32_04_1 = tgGM_BA_Query_Max_F32_04( psBA );

    tgPA_PnS_Interval_Push( psPnS->m_asX0, vMin.m_vS_F32_04_1.x, vMax.m_vS_F32_04_1.x, uiIndex_Object );
    tgPA_PnS_Interval_Push( psPnS->m_asX1, vMin.m_vS_F32_04_1.y, vMax.m_vS_F32_04_1.y, uiIndex_Object );
    tgPA_PnS_Interval_Push( psPnS->m_asX2, vMin.m_vS_F32_04_1.z, vMax.m_vS_F32_04_1.z, uiIndex_Object );

    /* Check this object against all current objects, adding all existing pair-wise potential contact sets */

    for (TgRSIZE uiTest_Object = 0, nuiObjects = 0; uiTest_Object < KTgPA_PNS_MAX_OBJECTS && nuiObjects < psPnS->m_nuiObjects; ++uiTest_Object)
    {
        if ((0 == (psPnS->m_uiCategory[uiTest_Object] & (3u << 30))) || (uiIndex_Object == uiTest_Object))
        {
            continue;
        };

        ++nuiObjects;

        if (   0 != (psPnS->m_uiCategory[uiTest_Object] & uiCollide)
            && 0 != (psPnS->m_uiCollide[uiTest_Object] & uiCategory)
            && tgCO_BA_Test_BA_F32_04( psBA, psPnS->m_asBA + uiTest_Object )
        )
        {
            tgPA_PnS_Pair_Push( psPnS, uiIndex_Object, uiTest_Object );
        };
    };

    /*  Store the mask value, which is also used to indicate the ID is now in use.  This must be done after the AABB loop so that */
    /* the trivial case of self intersection can be trivially ignored. */

    psPnS->m_uiCallbackID[uiIndex_Object] = uiCallbackID;
    psPnS->m_uiCategory[uiIndex_Object] = (uiCategory | (3u << 30));
    psPnS->m_uiCollide[uiIndex_Object] = uiCollide;
    tgGM_BA_Copy_F32_04( psPnS->m_asBA + uiIndex_Object, psBA ); /* Set the AABB data values */
    tgPNS_OBJECT_ID_Init( psPnS->m_atiObject + uiIndex_Object, uiIndex_Object );
    TgERROR(KTgPA_PNS_MAX_CONTACT_PAIR == psPnS->m_auiContact_Linked_List_Head[uiIndex_Object]);

    ++psPnS->m_nuiObjects;

    tgPM_MT_MX_Release( &psPnS->m_csSystemLock );
    return (tgPNS_OBJECT_ID_Query_Unsafe( psPnS->m_atiObject + uiIndex_Object ));
}


/* ---- tgPA_PnS_Test_AABB ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgPA_PnS_Test_AABB( STg2_PA_PnS_PCU psPnS, TgUINT_E64_C uiCategory, TgUINT_E64_C uiCollide, TgBOXAA_F32_04_CPCU psBA )
{
    /* Check this object against all current objects, adding all existing pair-wise potential contact sets */

    for (TgRSIZE uiIndex = 0, nuiObjects = 0; uiIndex < KTgPA_PNS_MAX_OBJECTS && nuiObjects < psPnS->m_nuiObjects; ++uiIndex)
    {
        if (0 == (psPnS->m_uiCategory[uiIndex] & (3u << 30)))
        {
            continue;
        };

        ++nuiObjects;

        if (   0 != (psPnS->m_uiCategory[uiIndex] & uiCollide)
            && 0 != (psPnS->m_uiCollide[uiIndex] & uiCategory)
            && tgCO_BA_Test_BA_F32_04( psBA, psPnS->m_asBA + uiIndex ) )
        {
            return (true);
        };
    };

    return (false);
}


/* ---- tgPA_PnS_Object_Update --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_PnS_Object_Update( STg2_PA_PnS_PCU psPnS, TgPNS_OBJECT_ID_C tiObject, TgBOXAA_F32_04_CPCU psBA )
{
    TgUN_V128                           vOldMin, vOldMax, vNewMin, vNewMax;

    TgERROR( tiObject.m_uiI < KTgPA_PNS_MAX_OBJECTS );

    tgPM_MT_MX_Wait_Block( &psPnS->m_csSystemLock );

    /* Update respective projections of bounding box on each axis. */

    vOldMin.m_vF32_04_1 = tgGM_BA_Query_Min_F32_04( psPnS->m_asBA + tiObject.m_uiI );
    vOldMax.m_vF32_04_1 = tgGM_BA_Query_Max_F32_04( psPnS->m_asBA + tiObject.m_uiI );
    vNewMin.m_vF32_04_1 = tgGM_BA_Query_Min_F32_04( psBA );
    vNewMax.m_vF32_04_1 = tgGM_BA_Query_Max_F32_04( psBA );

    tgPA_PnS_Object_Update_Interval( psPnS, psPnS->m_asX0, vOldMin.m_vS_F32_04_1.x, vOldMax.m_vS_F32_04_1.x, vNewMin.m_vS_F32_04_1.x, vNewMax.m_vS_F32_04_1.x, tiObject );
    tgPA_PnS_Object_Update_Interval( psPnS, psPnS->m_asX1, vOldMin.m_vS_F32_04_1.y, vOldMax.m_vS_F32_04_1.y, vNewMin.m_vS_F32_04_1.y, vNewMax.m_vS_F32_04_1.y, tiObject );
    tgPA_PnS_Object_Update_Interval( psPnS, psPnS->m_asX2, vOldMin.m_vS_F32_04_1.z, vOldMax.m_vS_F32_04_1.z, vNewMin.m_vS_F32_04_1.z, vNewMax.m_vS_F32_04_1.z, tiObject );

    tgGM_BA_Copy_F32_04( psPnS->m_asBA + tiObject.m_uiI, psBA );

    return (KTgS_OK);
}


/* ---- tgPA_PnS_Object_Exe_Func ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_PnS_Object_Exe_Func( STg2_PA_PnS_PCU psPnS, TgPNS_OBJECT_ID_C tiObject, TgVOID(*pfnExec)( TgUINT_MAX_C , TgUINT_MAX_C ) )
{
    TgUINT_MAX                          uiCallbackID;

    TgPARAM_CHECK_INDEX( tiObject.m_uiI, psPnS->m_auiContact_Linked_List_Head );

    if (tiObject.m_uiI > KTgPA_PNS_MAX_OBJECTS || nullptr == pfnExec)
    {
        return (KTgE_FAIL);
    };

    tgPM_MT_MX_Wait_Block( &psPnS->m_csSystemLock );

    uiCallbackID = psPnS->m_uiCallbackID[tiObject.m_uiI];

    for (TgRSIZE uiContact_Index = psPnS->m_auiContact_Linked_List_Head[tiObject.m_uiI]; uiContact_Index < KTgPA_PNS_MAX_CONTACT_PAIR; )
    {
        pfnExec( uiCallbackID, psPnS->m_uiCallbackID[uiContact_Index] );
        uiContact_Index = psPnS->m_auiContact_Next[uiContact_Index];
    };

    tgPM_MT_MX_Release( &psPnS->m_csSystemLock );
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Data and Functions */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPA_PnS_Object_Update_Interval --------------------------------------------------------------------------------------------------------------------------------------------------- */
/*  Searches for new overlapping pairs as indicated by overlap on a single axis.  The state of overlap on the other axes is  */
/* unknown and can already be in overlap, entering overlap or separated. */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPA_PnS_Object_Update_Interval(
    STg2_PA_PnS_PCU psPnS, STg2_PA_PnS_PointEnd_PCU psX, TgFLOAT32_C fMin0, TgFLOAT32_C fMax0, TgFLOAT32_C fMin1, TgFLOAT32_C fMax1, TgPNS_OBJECT_ID_C tiObject )
{
    /* Local assignments of the min and max positions along the axis for the initial and final AABBs */

    TgUINT_E16_C                        uiIndex_Interval_0 = 2 * (TgUINT_E16)tiObject.m_uiI + 0u;
    TgUINT_E16_C                        uiIndex_Interval_1 = 2 * (TgUINT_E16)tiObject.m_uiI + 1u;
    TgUINT_E64_C                        uiCategory = psPnS->m_uiCategory[tiObject.m_uiI];
    TgUINT_E64_C                        uiCollide = psPnS->m_uiCollide[tiObject.m_uiI];

    TgUINT_E16                          uiInsert;

    if (fMin0 > fMin1 && uiIndex_Interval_0 != psX[KTgPA_PNS_MAX_INTERVAL].m_uiNext) /**< Moving down the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_0].m_uiPrev;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal > fMin1; uiInsert = psX[uiInsert].m_uiPrev)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1u);

            if (!psX[uiTest_Object].m_bMax)
            {
                continue;
            };

            if (   0 != (psPnS->m_uiCategory[uiTest_Object] & uiCollide)
                && 0 != (psPnS->m_uiCollide[uiTest_Object] & uiCategory)
                && tgCO_BA_Test_BA_F32_04( psPnS->m_asBA + uiTest_Object, psPnS->m_asBA + tiObject.m_uiI ))
            {
                tgPA_PnS_Pair_Push( psPnS, tiObject.m_uiI, uiTest_Object );
            };
        };

        tgPA_PnS_Interval_Update( psX, uiIndex_Interval_0, psX[uiInsert].m_uiNext );
    }
    else if (fMin0 < fMin1 && uiIndex_Interval_0 != psX[KTgPA_PNS_MAX_INTERVAL].m_uiPrev) /**< Moving up the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_0].m_uiNext;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal < fMin1; uiInsert = psX[uiInsert].m_uiNext)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1);

            if (!psX[uiTest_Object].m_bMax)
            {
                continue;
            };

            if (   0 != (psPnS->m_uiCategory[uiTest_Object] & uiCollide)
                && 0 != (psPnS->m_uiCollide[uiTest_Object] & uiCategory)
                && tgCO_BA_Test_BA_F32_04( psPnS->m_asBA + uiTest_Object, psPnS->m_asBA + tiObject.m_uiI ))
            {
                tgPA_PnS_Remove_Contact_Pair( psPnS, tiObject.m_uiI, uiTest_Object );
            };
        };

        tgPA_PnS_Interval_Update( psX, uiIndex_Interval_0, uiInsert );
    };

    psX[uiIndex_Interval_0].m_fVal = fMin1; /**< Update the interval value */

    if (fMax0 > fMax1 && uiIndex_Interval_1 != psX[KTgPA_PNS_MAX_INTERVAL].m_uiNext) /**< Moving down the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_1].m_uiPrev;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal > fMax1; uiInsert = psX[uiInsert].m_uiPrev)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1);

            if (psX[uiTest_Object].m_bMax)
            {
                continue;
            };

            if (   0 != (psPnS->m_uiCategory[uiTest_Object] & uiCollide)
                && 0 != (psPnS->m_uiCollide[uiTest_Object] & uiCategory)
                && tgCO_BA_Test_BA_F32_04( psPnS->m_asBA + uiTest_Object, psPnS->m_asBA + tiObject.m_uiI ))
            {
                tgPA_PnS_Remove_Contact_Pair( psPnS, tiObject.m_uiI, uiTest_Object );
            };
        };

        tgPA_PnS_Interval_Update( psX, uiIndex_Interval_1, psX[uiInsert].m_uiNext );
    }
    else if (fMax0 < fMax1 && uiIndex_Interval_1 != psX[KTgPA_PNS_MAX_INTERVAL].m_uiPrev) /**< Moving up the number line (projection) */
    {
        uiInsert = psX[uiIndex_Interval_1].m_uiNext;

        for (; uiInsert < KTgPA_PNS_MAX_INTERVAL && psX[uiInsert].m_fVal < fMax1; uiInsert = psX[uiInsert].m_uiNext)
        {
            TgRSIZE_C       uiTest_Object = (TgRSIZE)(uiInsert >> 1);

            if (psX[uiTest_Object].m_bMax)
            {
                continue;
            };

            if (   0 != (psPnS->m_uiCategory[uiTest_Object] & uiCollide)
                && 0 != (psPnS->m_uiCollide[uiTest_Object] & uiCategory)
                && tgCO_BA_Test_BA_F32_04( psPnS->m_asBA + uiTest_Object, psPnS->m_asBA + tiObject.m_uiI ))
            {
                tgPA_PnS_Pair_Push( psPnS, tiObject.m_uiI, uiTest_Object );
            };
        };

        tgPA_PnS_Interval_Update( psX, uiIndex_Interval_1, uiInsert );
    };

    psX[uiIndex_Interval_1].m_fVal = fMax1; /**< Update the interval value */
}


/* ---- tgPA_PnS_Interval_Push ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_PnS_Interval_Push( STg2_PA_PnS_PointEnd_PCU psX, TgFLOAT32_C fMin, TgFLOAT32_C fMax, TgRSIZE_C uiIndex_Object )
{
    TgUINT_E16                          uiIndex_Interval_0, uiIndex_Interval_1, uiAxis_Index, uiPrev_Axis_Index;

    TgPARAM_CHECK( uiIndex_Object < (KTgMAX_U16 >> 2) - 2 );

    uiIndex_Interval_0 = 2 * (TgUINT_E16)uiIndex_Object + 0u;
    uiIndex_Interval_1 = 2 * (TgUINT_E16)uiIndex_Object + 1u;
    uiAxis_Index = psX[KTgPA_PNS_MAX_INTERVAL].m_uiNext;

    for (; uiAxis_Index < KTgPA_PNS_MAX_INTERVAL && psX[uiAxis_Index].m_fVal < fMin; uiAxis_Index = psX[uiAxis_Index].m_uiNext);

    uiPrev_Axis_Index = psX[uiAxis_Index].m_uiPrev;

    psX[uiIndex_Interval_0].m_fVal = fMin;
    psX[uiIndex_Interval_0].m_uiPrev = uiPrev_Axis_Index;
    psX[uiIndex_Interval_0].m_uiNext = uiAxis_Index;
    psX[uiIndex_Interval_0].m_bMax = 0;

    psX[uiPrev_Axis_Index].m_uiNext = uiIndex_Interval_0;
    if (KTgPA_PNS_MAX_INTERVAL != uiAxis_Index)
    {
        psX[uiAxis_Index].m_uiPrev = uiIndex_Interval_0;
    };

    for (; uiAxis_Index < KTgPA_PNS_MAX_INTERVAL && psX[uiAxis_Index].m_fVal < fMax; uiAxis_Index = psX[uiAxis_Index].m_uiNext);

    uiPrev_Axis_Index = psX[uiAxis_Index].m_uiPrev;

    psX[uiIndex_Interval_1].m_fVal = fMax;
    psX[uiIndex_Interval_1].m_uiPrev = uiPrev_Axis_Index;
    psX[uiIndex_Interval_1].m_uiNext = uiAxis_Index;
    psX[uiIndex_Interval_1].m_bMax = 1;

    psX[uiPrev_Axis_Index].m_uiNext = uiIndex_Interval_1;
    if (KTgPA_PNS_MAX_INTERVAL != uiAxis_Index)
    {
        psX[uiAxis_Index].m_uiPrev = uiIndex_Interval_1;
    };
}


/* ---- tgPA_PnS_Interval_Update ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_PnS_Interval_Update( STg2_PA_PnS_PointEnd_PCU psX, TgUINT_E16_C uiVal, TgUINT_E16_C uiInsert )
{
    TgUINT_E16                          uiPrev;

    if (uiVal == uiInsert)
    {
        return;
    };

    uiPrev = psX[uiInsert].m_uiPrev;

    /* Cut the element out of the list */

    psX[psX[uiVal].m_uiPrev].m_uiNext = psX[uiVal].m_uiNext;
    psX[psX[uiVal].m_uiNext].m_uiPrev = psX[uiVal].m_uiPrev;

    /* Stitch the element into its new position */

    TgERROR( uiVal != uiPrev && uiVal != uiInsert && uiPrev != uiInsert );

    psX[uiVal].m_uiPrev = uiPrev;
    psX[uiVal].m_uiNext = uiInsert;
    psX[uiPrev].m_uiNext = uiVal;
    psX[uiInsert].m_uiPrev = uiVal;
}


/* ---- tgPA_PnS_Pair_Push ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgPA_PnS_Pair_Push( STg2_PA_PnS_PCU psPnS, TgRSIZE_C uiIndex_Object_0, TgRSIZE_C uiIndex_Object_1 )
{
    TgRSIZE                             uiNext_Empty;

    TgPARAM_CHECK( uiIndex_Object_0 < KTgPA_PNS_MAX_OBJECTS );
    TgPARAM_CHECK( uiIndex_Object_1 < KTgPA_PNS_MAX_OBJECTS );
    TgPARAM_CHECK( psPnS->m_uiEmpty < KTgPA_PNS_MAX_CONTACT_PAIR );
    TgPARAM_CHECK( uiIndex_Object_0 != uiIndex_Object_1 );

    if (KTgPA_PNS_MAX_CONTACT_PAIR == psPnS->m_uiEmpty)
    {
        tgCN_PrintF( KTgCN_CHANEL_CRITICAL, u8"%-16.16s(%-32.32s): Out of Memory - Can not store pair.\n", u8"Partition: PnS", u8"Pair_Push" );
        return (false);
    };

    uiNext_Empty = psPnS->m_auiContact_Next[psPnS->m_uiEmpty];

    /* Push this contact onto the object-pair stack */
    psPnS->m_atiContact_Object[psPnS->m_uiEmpty] = tgPNS_OBJECT_ID_Query_Unsafe( psPnS->m_atiObject + uiIndex_Object_1 );
    psPnS->m_auiContact_Next[psPnS->m_uiEmpty] = psPnS->m_auiContact_Linked_List_Head[uiIndex_Object_0];
    psPnS->m_auiContact_Linked_List_Head[uiIndex_Object_0] = psPnS->m_uiEmpty;

    psPnS->m_uiEmpty = uiNext_Empty; /* Record the next available empty pair-ID */

    if (KTgPA_PNS_MAX_CONTACT_PAIR == psPnS->m_uiEmpty)
    {
        tgCN_PrintF( KTgCN_CHANEL_CRITICAL, u8"%-16.16s(%-32.32s): Out of Memory - Can not store pair.\n", u8"Partition: PnS", u8"Pair_Push" );
        return (false);
    };

    uiNext_Empty = psPnS->m_auiContact_Next[psPnS->m_uiEmpty];

    /* Push this contact onto the object-pair stack */
    psPnS->m_atiContact_Object[psPnS->m_uiEmpty] = tgPNS_OBJECT_ID_Query_Unsafe( psPnS->m_atiObject + uiIndex_Object_0 );
    psPnS->m_auiContact_Next[psPnS->m_uiEmpty] = psPnS->m_auiContact_Linked_List_Head[uiIndex_Object_1];
    psPnS->m_auiContact_Linked_List_Head[uiIndex_Object_1] = psPnS->m_uiEmpty;

    psPnS->m_uiEmpty = uiNext_Empty; /* Record the next available empty pair-ID */

    return (true);
}


/* ---- tgPA_PnS_Remove_Contact_Pair --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgBOOL tgPA_PnS_Remove_Contact_Pair( STg2_PA_PnS_PCU psPnS, TgRSIZE_C uiIndex_Object_0, TgRSIZE_C uiIndex_Object_1 )
{
    TgRSIZE                             uiContact_Index;

    uiContact_Index = psPnS->m_auiContact_Linked_List_Head[uiIndex_Object_0];
    if (KTgPA_PNS_MAX_CONTACT_PAIR == uiContact_Index)
    {
        return (false);
    };

    if (uiIndex_Object_1 == psPnS->m_atiContact_Object[uiContact_Index].m_uiI)
    {
        psPnS->m_auiContact_Linked_List_Head[uiIndex_Object_0] = psPnS->m_auiContact_Next[uiContact_Index]; /**< Increment the object-pair list */

        /* Push the object-pair onto the empty stack */
        psPnS->m_atiContact_Object[uiContact_Index].m_uiKI = KTgID__INVALID_VALUE;
        psPnS->m_auiContact_Next[uiContact_Index] = psPnS->m_uiEmpty;
        psPnS->m_uiEmpty = uiContact_Index;
        return (true);
    };

    while (1)
    {
        TgRSIZE                             uiPrev_Contact_Index;

        uiPrev_Contact_Index = uiContact_Index;
        uiContact_Index = psPnS->m_auiContact_Next[uiContact_Index];
        if (KTgPA_PNS_MAX_CONTACT_PAIR == uiContact_Index)
        {
            return (false);
        };

        if (uiIndex_Object_1 == psPnS->m_atiContact_Object[uiContact_Index].m_uiI)
        {
            psPnS->m_auiContact_Next[uiPrev_Contact_Index] = psPnS->m_auiContact_Next[uiContact_Index]; /**< Increment the object-pair list */

            /* Push the object-pair onto the empty stack */
            psPnS->m_atiContact_Object[uiContact_Index].m_uiKI = KTgID__INVALID_VALUE;
            psPnS->m_auiContact_Next[uiContact_Index] = psPnS->m_uiEmpty;
            psPnS->m_uiEmpty = uiContact_Index;
            return (true);
        };
    };
}


/* ---- tgPA_PnS_Remove_Object_Contact_List -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgPA_PnS_Remove_Object_Contact_List( STg2_PA_PnS_PCU psPnS, TgRSIZE_C uiIndex_Object )
{
    TgRSIZE                             uiContact_Index;
    TgPNS_OBJECT_ID                     tiObject;

    TgPARAM_CHECK_INDEX( uiIndex_Object, psPnS->m_auiContact_Linked_List_Head );

    uiContact_Index = psPnS->m_auiContact_Linked_List_Head[uiIndex_Object];
    if (KTgPA_PNS_MAX_CONTACT_PAIR == uiContact_Index)
    {
        return; /* No Contact Pairs for this object */
    };

    tiObject = tgPNS_OBJECT_ID_Query_Unsafe(psPnS->m_atiObject + uiIndex_Object);
    while (1)
    {
        /* The entire contact pair linked list for this object will be added to the empty list, but need to find all pairs in corresponding objects */
        TgVERIFY(tgPA_PnS_Remove_Contact_Pair( psPnS, psPnS->m_atiContact_Object[uiContact_Index].m_uiI, tiObject.m_uiI ));
        psPnS->m_atiContact_Object[uiContact_Index].m_uiKI = KTgID__INVALID_VALUE;

        /* Check to see if this is the final node */
        if (KTgPA_PNS_MAX_CONTACT_PAIR == psPnS->m_auiContact_Next[uiContact_Index])
        {
            psPnS->m_auiContact_Next[uiContact_Index] = psPnS->m_uiEmpty;
            psPnS->m_uiEmpty = psPnS->m_auiContact_Linked_List_Head[uiIndex_Object];
            break;
        }
        else
        {
            uiContact_Index = psPnS->m_auiContact_Next[uiContact_Index];
        };
    };

    psPnS->m_auiContact_Linked_List_Head[uiIndex_Object] = KTgPA_PNS_MAX_CONTACT_PAIR; /* Clear the object-pair list */
}
