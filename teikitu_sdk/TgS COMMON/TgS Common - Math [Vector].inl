/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(tgMH_SETU) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SETU)( VAR_T(CPCU) pty )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SETU_S)( pty ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_SETA) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SETA)( VAR_T(CPCU) pty )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SETA_S)( pty ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_SET1) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SET1)( VAR_T(C) fX )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SET1_S)( fX ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_RAND) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_RAND)( TgVOID )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_RAND_S)() };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_ADD) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_ADD)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_ADD_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_SUB) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SUB)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SUB_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_AVG) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_AVG)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_AVG_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_PERM) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_PERM)( VEC_T(1,C) v0, VEC_T(1,C) v1, VEC_T(1,C) vMask )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_PERM_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1, (UVAR_T(CP))&vMask ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_SEL) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SEL)( VEC_T(1,C) v0, VEC_T(1,C) v1, VEC_T(1,C) vMask )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SEL_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1, (UVAR_T(CP))&vMask ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_AND) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_AND)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_AND_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_OR) ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_OR)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_OR_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_XOR) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_XOR)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_XOR_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_MAX) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_MAX)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_MAX_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_MAX_ELEM) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCN_V(tgMH_MAX_ELEM)( VEC_T(1,C) v0 )
{
    return (FCN_V(tgMH_MAX_ELEM_S)( *(VEC_S_T(1,CP))&v0 ));
}


/* ---- FCN_V(tgMH_MIN) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_MIN)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_MIN_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_MIN_ELEM) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VAR_T() FCN_V(tgMH_MIN_ELEM)( VEC_T(1,C) v0 )
{
    return (FCN_V(tgMH_MIN_ELEM_S)( *(VEC_S_T(1,CP))&v0 ));
}


/* ---- FCN_V(tgMH_ABS) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_ABS)( VEC_T(1,C) v0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_ABS_S)( *(VEC_S_T(1,CP))&v0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_SGN) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SGN)( VEC_T(1,C) v0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SGN_S)( *(VEC_S_T(1,CP))&v0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CMP_EQ) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CMP_EQ)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CMP_EQ_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CMP_NE) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CMP_NE)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CMP_NE_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CMP_GE) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CMP_GE)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CMP_GE_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CMP_GT) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CMP_GT)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CMP_GT_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CMP_LE) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CMP_LE)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CMP_LE_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CMP_LT) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CMP_LT)( VEC_T(1,C) v0, VEC_T(1,C) v1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CMP_LT_S)( *(VEC_S_T(1,CP))&v0, *(VEC_S_T(1,CP))&v1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CMP_ALL_TO_BOOL) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_CMP_ALL_TO_BOOL)( VEC_T(1,C) v0 )
{
    return (FCN_V(tgMH_CMP_ALL_TO_BOOL_S)( *(VEC_S_T(1,CP))&v0 ));
}


/* ---- FCN_V(tgMH_CMP_ANY_TO_BOOL) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_CMP_ANY_TO_BOOL)( VEC_T(1,C) v0 )
{
    VEC_UN_T(1,C)                       uV0 = { VEC_UN_1_MEMBER() = v0 };
    return (FCN_V(tgMH_CMP_ANY_TO_BOOL_S)( VEC_S_UN_1_MEMBER(uV0) ));
}


/* =============================================================================================================================================================================== */
#endif
