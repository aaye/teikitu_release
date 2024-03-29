/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (APPLE) Common - Math [Vector] [F32_04].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_API_VECTOR_F32_04_INL)
#define TGS_COMMON_MATH_API_VECTOR_F32_04_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgMH_Init_ELEM_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_Init_ELEM_F32_04_1( TgFLOAT32_C fX, TgFLOAT32_C fY, TgFLOAT32_C fZ, TgFLOAT32_C fW )
{
    return (simd_make_float4( fX, fY, fZ, fW ));
}


/* ---- tgMH_SETP_S_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_Init_Point_ELEM_F32_04_1( TgFLOAT32_C fX, TgFLOAT32_C fY, TgFLOAT32_C fZ )
{
    return (simd_make_float4( fX, fY, fZ, 1.0F ));
}


/* ---- tgMH_SETV_S_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_Init_Vector_ELEM_F32_04_1( TgFLOAT32_C fX, TgFLOAT32_C fY, TgFLOAT32_C fZ )
{
    return (simd_make_float4( fX, fY, fZ, 0.0F ));
}


/* ---- tgMH_Init_Point_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_Init_Point_F32_04_1( TgVEC_F32_04_1_C vRight )
{
    return (simd_make_float4( vRight.xyz, 1.0F ));
}


/* ---- tgMH_Init_Vector_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_Init_Vector_F32_04_1( TgVEC_F32_04_1_C vRight )
{
    return (simd_make_float4( vRight.xyz, 0.0F ));
}


/* ---- tgMH_Init_Ortho_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_Init_Ortho_F32_04_1( TgVEC_F32_04_1_C vARG_0 )
{
    TgVEC_UN_F32_04_1                   uResult;

    uResult.m_vS_F32_04_1 = tgMH_Init_Ortho_S_F32_04_1( *(TgVEC_S_F32_04_1_CP)&vARG_0 );
    return (uResult.m_vF32_04_1);
}


/* ---- tgMH_SPX_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SPX_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (vLeft.xxxx);
}


/* ---- tgMH_SPY_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SPY_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (vLeft.yyyy);
}


/* ---- tgMH_SPZ_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SPZ_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (vLeft.zzzz);
}


/* ---- tgMH_SPW_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_SPW_F32_04_1( TgVEC_F32_04_1_C vLeft )
{
    return (vLeft.wwww);
}


/* ---- tgMH_Is_Valid_Point_F32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgMH_Is_Valid_Point_F32_04_1( TgVEC_F32_04_1_C vARG_0 )
{
    return (simd_all(vARG_0 == vARG_0) && (1.0F == vARG_0.w));
}


/* ---- tgMH_Is_Valid_Vector_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgMH_Is_Valid_Vector_F32_04_1( TgVEC_F32_04_1_C vARG_0 )
{
    return (simd_all(vARG_0 == vARG_0) && (0.0F == vARG_0.w));
}


/* ---- tgMH_Is_Valid_Unit_Vector_F32_04_1 --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgMH_Is_Valid_Unit_Vector_F32_04_1( TgVEC_F32_04_1_C vARG_0 )
{
    return (simd_all(vARG_0 == vARG_0) && (0.0F == vARG_0.w) && tgCM_NR1_F32( tgMH_DOT3_F32_04_1( vARG_0, vARG_0 ).x ) );
}


/* ---- tgMH_DOT3_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_DOT3_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (simd_dot( vLeft.xyz, vRight.xyz ));
}


/* ---- tgMH_CX_F32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_CX_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (simd_make_float4( simd_cross( vLeft.xyz, vRight.xyz ), 0.0F ));
}


/* ---- tgMH_UCX_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_UCX_F32_04_1( TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    return (simd_make_float4( simd_normalize( simd_cross( vLeft.xyz, vRight.xyz ) ), 0.0F ));
}


/* ---- tgMH_UCX_LEN_F32_04_1 ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_UCX_LEN_F32_04_1( TgVEC_F32_04_1_PCU ptvRet_Length, TgVEC_F32_04_1_C vLeft, TgVEC_F32_04_1_C vRight )
{
    simd_float3 vCX = simd_cross( vLeft.xyz, vRight.xyz );
    *ptvRet_Length = simd_length( vCX );
    return (simd_make_float4( simd_normalize( vCX ), 0.0F ));
}


/* ---- tgMH_PRX3_CMP_EQ_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgMH_PRX3_CMP_EQ_F32_04_1( TgVEC_F32_04_1_C vARG_0, TgVEC_F32_04_1_C vARG_1 )
{
    TgUN_V128                           uV0, uV1, uV2;
    TgVEC_F32_04_1                      vDiff;

    vDiff = tgMH_SUB_F32_04_1( vARG_0, vARG_1 );
    uV0.m_vF32_04_1 = tgMH_CMP_GE_F32_04_1( vDiff, tgMH_SET1_F32_04_1(  KTgROOT_EPS_F32 ) );
    uV1.m_vF32_04_1 = tgMH_CMP_LE_F32_04_1( vDiff, tgMH_SET1_F32_04_1( -KTgROOT_EPS_F32 ) );
    uV2.m_vF32_04_1 = simd_make_float4( tgMH_OR_F32_04_1( uV0.m_vF32_04_1, uV1.m_vF32_04_1 ).xyz, 0.0F );
    
    return (simd_all(tgMH_SET1_U32_04_1( 0 ) == uV2.m_vU32_04_1));
}


/* ---- tgMH_QT_INV_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_QT_INV_F32_04_1( TgVEC_F32_04_1_C qR1 )
{
    return (simd_inverse( simd_quaternion( qR1 ) ).vector);
}


/* ---- tgMH_QT_MUL_F32_04_1 ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_QT_MUL_F32_04_1( TgVEC_F32_04_1_C vA, TgVEC_F32_04_1_C vB )
{
    return (simd_mul( simd_quaternion( vA ), simd_quaternion( vB ) ).vector);
}


/* ---- tgMH_QT_Slerp_F32_04_1 --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_QT_Slerp_F32_04_1( TgVEC_F32_04_1_C vT, TgVEC_F32_04_1_C vA, TgVEC_F32_04_1_C vB )
{
    return (simd_slerp( simd_quaternion( vA ), simd_quaternion( vB ), vT.x ).vector);
}


/* ---- tgMH_QT_Vector_To_Vector_F32_04_1 ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_QT_Vector_To_Vector_F32_04_1( TgVEC_F32_04_1_C b, TgVEC_F32_04_1_C c )
{
    return (simd_quaternion( simd_normalize( b.xyz ), simd_normalize( c.xyz ) ).vector);
}


/* ---- tgMH_QT_TX_F32_04_1 ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_QT_TX_F32_04_1( TgVEC_F32_04_1_C vV0, TgVEC_F32_04_1_C qR0 )
{
    simd_float3 vV1 = simd_act( simd_quaternion( qR0 ), vV0.xyz );
    return (simd_make_float4( vV1, vV0.w ));
}


/* ---- tgMH_QT_INV_TX_F32_04_1 -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgMH_QT_INV_TX_F32_04_1( TgVEC_F32_04_1_C vV0, TgVEC_F32_04_1_C qR0 )
{
    simd_float3 vV1 = simd_act( simd_inverse( simd_quaternion( qR0 ) ), vV0.xyz );
    return (simd_make_float4( vV1, vV0.w ));
}


/* =============================================================================================================================================================================== */
#endif
