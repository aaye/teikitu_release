/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Capsule-Plane.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COLLISION/TgS Collision - Plane-Linear.inl"
#include "TgS COLLISION/TgS Collision - Plane-Point.inl"
#include "TgS COLLISION/TgS Collision - Plane-Segment.inl"

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_CP_Closest_PN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgCO_CP_Closest_PN)( VEC_T(1,PC) pfCP0, VEC_T(1,PC) pvPN0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    VEC_T(1,C)                          vOG = FCN_VO(tgGM_TB_Query_Origin)( psCP0 );
    VEC_T(1,C)                          vTest = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vOG );

    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, psCP0->m_vRadius ) ))
    {
        return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
    }
    else
    {
        VEC_T(1,C)                          vUAX = FCN_VO(tgGM_TB_Query_Axis_Unit)( psCP0 );
        VEC_T(1,C)                          vUAX_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, vUAX );
        VEC_T(1,C)                          vE2 = FCN_V(tgMH_MUL)( psCP0->m_vExtent, FCN_V(tgMH_ABS)( vUAX_N ) );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_ADD)( vE2, psCP0->m_vRadius ), vTest ) ))
        {
            /* The capsule is penetrating this plane, return back the error state. */
            return (FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) ));
        }
        else
        {
            VEC_T(1,C)                          vAx = FCN_V(tgMH_NEG)( FCN_V(tgMH_PRX_SGN)( vUAX_N ) );
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, psPN0->m_vNormal );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_SUB)( vOG, vK0 );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vAx, psCP0->m_vHAX );
            VEC_T(1,C)                          vPnt = FCN_V(tgMH_ADD)( vK1, vK2 );
            VEC_T(1,C)                          vDist = FCN_V(tgMH_SUB)( vTest, FCN_V(tgMH_ADD)( vE2, psCP0->m_vRadius ) );
            VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vDist, psPN0->m_vNormal );

            *pfCP0 = vPnt;
            *pvPN0 = FCN_V(tgMH_SUB)( vPnt, vK3 );

            return (vDist);
        }
    }
}


/* ---- FCN_VO(tgCO_PN_Penetrate_CP) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Penetrate_CP)(VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgTUBE,CPC) psCP0)
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        /* Project the capsule onto the plane normal and verify that some portion lies below the plane. */
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        VEC_T(1)                            vDepth;

        VEC_T(1,C)                          vCP_AX__PN_N = FCN_V(tgMH_DOT)( psPN0->m_vNormal, psCP0->m_vHAX ); /* Projection of the capsule primary extent onto the plane normal */
        VEC_T(1,C)                          vPRX_Sign = FCN_V(tgMH_PRX_SGN)( vCP_AX__PN_N );  /* Sign of the projection with error range */
        VEC_T(1,C)                          vCP_OG = FCN_V(tgMH_Query_Axis_3,3)( &psCP0->m_mReference_Frame ); /* Origin for the capsule */
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Sign_Dist_PT)( psPN0, vCP_OG ); /* Distance of the capsule origin from the plane */

        VEC_T(1,C)                          vα0 = FCN_V(tgMH_MAD)( vPRX_Sign, vCP_AX__PN_N, psCP0->m_vRadius ); /* Additional depth due to capsule axis and radius */
        VEC_T(1,C)                          vα1 = FCN_V(tgMH_NMS)( vPRX_Sign, psCP0->m_vHAX, vCP_OG ); /* Point on axis of deepest penetration */
        VEC_T(1,C)                          vα2 = FCN_V(tgMH_NMS)( psCP0->m_vRadius, psPN0->m_vNormal, vα1 ); /* Point of deepest penetration on the capsule surface */
        VEC_T(1,C)                          vα3 = FCN_V(tgMH_DIV)( vCP_AX__PN_N, psCP0->m_vExtent ); /* Calculate the projection based on the primary unit axis */

        vDepth = FCN_V(tgMH_SUB)( vα0, vDist );
        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDepth, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
        {
            return (KTgE_NO_INTERSECT);
        };

        psContact = psPacket->m_psContact + psPacket->m_nuiContact;

        psContact->m_vS0 = vα2;
        psContact->m_vN0 = psPN0->m_vNormal;
        psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
        psContact->m_vDepth = vDepth;

        ++psPacket->m_nuiContact;

        /* If the capsule is at a 45 degree angle or less to the plane, create contact points at both extreme points of the capsule. */

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( FCN_V(tgMH_ABS)( vα3 ), FCN_V(tgMH_SET1)( VAR_K(KTgSQRT1_2) ) ) ))
        {
            VEC_T(1,C)                          vPRX_Sign_NEG = FCN_V(tgMH_NEG)( vPRX_Sign );
            VEC_T(1,C)                          vβ0 = FCN_V(tgMH_MAD)( vPRX_Sign_NEG, vCP_AX__PN_N, psCP0->m_vRadius ); /* Additional depth due to capsule axis and radius */
            VEC_T(1,C)                          vβ1 = FCN_V(tgMH_NMS)( vPRX_Sign_NEG, psCP0->m_vHAX, vCP_OG ); /* Point on axis of least penetration */
            VEC_T(1,C)                          vβ2 = FCN_V(tgMH_NMS)( psCP0->m_vRadius, psPN0->m_vNormal, vβ1 ); /* Point of deepest penetration for the above point */

            vDepth = FCN_V(tgMH_SUB)( vβ0, vDist );
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDepth, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                return (KTgS_OK);
            };

            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
            {
                return (KTgE_MAX_CONTACTS);
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = vβ2;
            psContact->m_vN0 = psPN0->m_vNormal;
            psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
            psContact->m_vDepth = vDepth;

            ++psPacket->m_nuiContact;
        };

        return (KTgS_OK);
    }
}


/* ---- FCN_VO(tgCO_CP_Penetrate_PN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_CP_Penetrate_PN)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgPLANE,CPC) psPN0 )
{
    TgRESULT                            iResult;
    TgRSIZE                             nuiExisting_Contact, uiIndex;

    TgPARAM_CHECK(FCN_VO(tgGM_TB_Is_Valid)( psCP0 ) && FCN_VO(tgGM_PN_Is_Valid)( psPN0 ));

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    };

    nuiExisting_Contact = psPacket->m_nuiContact;

    iResult = FCN_VO(tgCO_PN_Penetrate_CP)( psPacket, psPN0, psCP0 );
    if (TgFAILED(iResult) && (KTgE_MAX_CONTACTS != iResult))
    {
        return (iResult);
    };

    /* Need to reverse the contacts that were made in the reversed collision call. */
    for (uiIndex = nuiExisting_Contact; uiIndex < psPacket->m_nuiContact; ++uiIndex)
    {
        VEC_OBJ_T(STg2_CO_Contact,PC)       psContact = psPacket->m_psContact + uiIndex;

        psContact->m_vS0 = FCN_V(tgMH_MAD)( psContact->m_vDepth, psContact->m_vN0, psContact->m_vS0 );
        psContact->m_vN0 = FCN_V(tgMH_NEG)( psContact->m_vN0 );
    }
    return (iResult);
}


/* ---- FCN_VO(tgCO_PN_Sweep_CP) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_PN_Sweep_CP)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_T(1,PC) pvPM, VEC_OBJ_T(TgPLANE,CPC) psPN0, VEC_OBJ_T(TgTUBE,CPC) psCP0, VEC_OBJ_T(TgDELTA,CPC) psDT )
{
    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCP0) && FCN_VO(tgGM_PN_Is_Valid)(psPN0) );

    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
    {
        return (KTgE_FAIL);
    }
    else
    {
        VEC_T(1)                            vCP0, vPN0;
        VEC_T(1,C)                          vDist = FCN_VO(tgCO_PN_Closest_SG)( &vPN0, &vCP0, psPN0, &psCP0->m_sAX );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDist, psCP0->m_vRadius ) ))
        {
            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( *pvPM, psPacket->m_vSweepTol ) ))
            {
                psPacket->m_nuiContact = 0;
            };

            *pvPM = FCN_V(tgMH_SET1)( TYPE_K(0) );

            if ((psPacket->m_bReport_Penetration) && (KTgE_MAX_CONTACTS == FCN_VO(tgCO_PN_Penetrate_CP)( psPacket, psPN0, psCP0 )))
            {
                return (KTgE_MAX_CONTACTS);
            };

            return (KTgE_PREPENETRATION);
        }
        else
        {
            VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

            VEC_T(1,C)                          vDT_N = FCN_V(tgMH_NEG)( FCN_V(tgMH_DOT)( psDT->m_vDT, psPN0->m_vNormal ) );
            VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SUB)( vDist, psCP0->m_vRadius ), vDT_N );
            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( vT0, psDT->m_vDT );
            VEC_T(1,C)                          vK0 = FCN_V(tgMH_ADD)( vCP0, vK2 );
            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( psCP0->m_vRadius, psPN0->m_vNormal );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vDT_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
            {
                return (KTgE_NO_INTERSECT);
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vT0, FCN_V(tgMH_ADD)( *pvPM, psPacket->m_vSweepTol ) ) ))
            {
                return (KTgE_NO_INTERSECT);
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vT0, FCN_V(tgMH_SUB)( *pvPM, psPacket->m_vSweepTol ) ) ))
            {
                psPacket->m_nuiContact = 0;
                *pvPM = vT0;
            };

            psContact = psPacket->m_psContact + psPacket->m_nuiContact;

            psContact->m_vS0 = FCN_V(tgMH_SUB)( vK0, vK1 );
            psContact->m_vN0 = psPN0->m_vNormal;
            psContact->m_vT0 = vT0;
            psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

            ++psPacket->m_nuiContact;

            return (KTgS_OK);
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
