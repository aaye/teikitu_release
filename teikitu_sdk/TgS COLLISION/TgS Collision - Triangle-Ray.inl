/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TRIANGLE_RAY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_ST_DistSq_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_DistSq_RY)(VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    VEC_T(1)                            vST0, vST1, vRY0;

    return (FCN_VO(tgCO_ST_ClosestSq_PM_RY)( &vST0, &vST1, &vRY0, psST0, psRY0 ));
}


/* ---- FCN_VO(tgCO_ST_Dist_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Dist_RY)(VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_DistSq_RY)( psST0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_ST_ClosestSq_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_ClosestSq_RY)(VEC_T(1,PC) pvET0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    VEC_T(1)                            vST0, vST1, vRY0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_ST_ClosestSq_PM_RY)( &vST0, &vST1, &vRY0, psST0, psRY0 );

    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vST1, psST0->m_sCT.m_sET.m_avEdge[2] );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MAD)( vST0, psST0->m_sCT.m_sET.m_avEdge[0], psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );

    *pvRY0 = FCN_V(tgMH_MAD)( vRY0, psRY0->m_vDirN, psRY0->m_vOrigin );
    *pvET0 = FCN_V(tgMH_SUB)( vK3, vK1 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_ST_Closest_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Closest_RY)(VEC_T(1,PC) pvET0, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0)
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_ClosestSq_RY)( pvET0, pvRY0, psST0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_ST_ClosestSq_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_ClosestSq_PM_RY)( VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_ST_ClosestSq_PM_LR10)( pvST0, pvST1, pvRY0, psST0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Closest_PM_RY) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Closest_PM_RY)( VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_ClosestSq_PM_RY)( pvST0, pvST1, pvRY0, psST0, psRY0 ) ));
}


/* ---- FCN_VO(tgCO_ET_Test_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_ET_Test_RY)( VEC_OBJ_T(TgETRI,CPC) psET0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vST0, vST1, vRY0;

    return (KTgS_OK == FCN_VO(tgCO_ET_Intersect_PM_LR10)( &vST0, &vST1, &vRY0, psET0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ET_Intersect_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ET_Intersect_RY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    VEC_T(1)                            vST0, vST1, vRY0;
    TgRESULT                            iResult;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    if (TgFAILED( iResult = FCN_VO(tgCO_ET_Intersect_PM_LR10)( &vST0, &vST1, &vRY0, psET0, psRY0->m_vOrigin, psRY0->m_vDirN ) ))
    {
        return (iResult);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = FCN_V(tgMH_MAD)( vRY0, psRY0->m_vDirN, psRY0->m_vOrigin );
    psContact->m_vN0 = psET0->m_sPT.m_vNormal;
    psContact->m_vT0 = vRY0;
    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_ET_Intersect_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ET_Intersect_PM_RY)( VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_ET_Intersect_PM_LR10)( pvST0, pvST1, pvRY0, psET0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_RY)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_ST_Clip_LR10)( psCL, psST0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_F_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_F_RY)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, TgSINT_E32_PC piCode, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_ST_Clip_F_LR10)( psCL, piCode, psST0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_PM_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_ST_Clip_PM_LR10)( pvRY0, pvRY1, psST0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_PM_F_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_PM_F_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, TgSINT_E32_PC piCode, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgRAY,CPC) psRY0 )
{
    return (FCN_VO(tgCO_ST_Clip_PM_F_LR10)( pvRY0, pvRY1, piCode, psST0, psRY0->m_vOrigin, psRY0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_PM_LR10) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_PM_LR10)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    TgSINT_E32                          iCode;

    return (FCN_VO(tgCO_ST_Clip_PM_F_LR10)( pvLN0, pvLN1, &iCode, psST0, vS0, vD0) );
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_TRIANGLE_RAY_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TRIANGLE_RAY_INL) */
#endif
