/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Math [Vector] [F].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_MATH_VECTOR_F_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V(tgMH_RAND_ONE) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_RAND_ONE)( TgVOID )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_RAND_ONE_S)() };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_Is_Valid) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Valid)( VEC_T(1,C) vARG_0 )
{
    return (FCN_V(tgMH_Is_Valid_S)( *(VEC_S_T(1,CP))&vARG_0 ));
}


/* ---- FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar) ----------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( VEC_T(1,C) vARG_0 )
{
    return (FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar_S)( *(VEC_S_T(1,CP))&vARG_0 ));
}


/* ---- FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar) --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( VEC_T(1,C) vARG_0 )
{
    return (FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar_S)( *(VEC_S_T(1,CP))&vARG_0 ));
}


/* ---- FCN_V(tgMH_Is_Valid_Broadcast_Scalar) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Valid_Broadcast_Scalar)( VEC_T(1,C) vARG_0 )
{
    return (FCN_V(tgMH_Is_Valid_Broadcast_Scalar_S)( *(VEC_S_T(1,CP))&vARG_0 ));
}


/* ---- FCN_V(tgMH_Is_Contained_In_Interval) ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_Contained_In_Interval)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2 )
{
    return FCN_V(tgMH_Is_Contained_In_Interval_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1, *(VEC_S_T(1,CP))&vARG_2 );
}


/* ---- FCN_V(tgMH_Is_BND) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_BND)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1 )
{
    return FCN_V(tgMH_Is_BND_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1 );
}


/* ---- FCN_V(tgMH_Is_PRX_CMP_EQ) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_PRX_CMP_EQ)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1 )
{
    return FCN_V(tgMH_Is_PRX_CMP_EQ_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1 );
}


/* ---- FCN_V(tgMH_Is_NR0) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_NR0)( VEC_T(1,C) vARG_0 )
{
    return FCN_V(tgMH_Is_NR0_S)( *(VEC_S_T(1,CP))&vARG_0 );
}


/* ---- FCN_V(tgMH_Is_NR1) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_V(tgMH_Is_NR1)( VEC_T(1,C) vARG_0 )
{
    return FCN_V(tgMH_Is_NR1_S)( *(VEC_S_T(1,CP))&vARG_0 );
}


/* ---- FCN_V(tgMH_MAD) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_MAD)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_MAD_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1, *(VEC_S_T(1,CP))&vARG_2 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_NMS) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_NMS)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_NMS_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1, *(VEC_S_T(1,CP))&vARG_2 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_DOT) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_DOT)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1 )
{
    VAR_T(C)        fResult = FCN_V(tgMH_DOT_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1 );
    return FCN_V(tgMH_SET1)( fResult );
}


/* ---- FCN_V(tgMH_MUL) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_MUL)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_MUL_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_DIV) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_DIV)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_DIV_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_RCP) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_RCP)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_RCP_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_LRP) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_LRP)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1, VEC_T(1,C) vARG_2 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_LRP_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1, *(VEC_S_T(1,CP))&vARG_2 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_LSQ) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_LSQ)( VEC_T(1,C) vARG_0 )
{
    VAR_T() fResult = FCN_V(tgMH_LSQ_S)( *(VEC_S_T(1,CP))&vARG_0 );
    return FCN_V(tgMH_SET1)( fResult );
}


/* ---- FCN_V(tgMH_LEN) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_LEN)( VEC_T(1,C) vARG_0 )
{
    VAR_T() fResult = FCN_F(tgPM_SQRT)( FCN_V(tgMH_LSQ_S)( *(VEC_S_T(1,CP))&vARG_0 ) );
    return FCN_V(tgMH_SET1)( fResult );
}


/* ---- FCN_V(tgMH_NEG) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_NEG)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_NEG_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_SQRT) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SQRT)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SQRT_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_RSQRT) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_RSQRT)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_RSQRT_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_NORM) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_NORM)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_NORM_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_NORM_LEN) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_NORM_LEN)( VEC_T(1,PCU) pfLength, VEC_T(1,C) vARG_0 )
{
    VAR_T()                             fLen;

    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_NORM_LEN_S)( &fLen, *(VEC_S_T(1,CP))&vARG_0 ) };
    *pfLength = FCN_V(tgMH_SET1)( fLen );
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CP_SGN) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CP_SGN)( VEC_T(1,C) vARG_0, VEC_T(1,C) vARG_1 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CP_SGN_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vARG_1 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_PRX_SGN) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_PRX_SGN)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_PRX_SGN_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_FLR) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_FLR)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_FLR_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CEL) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CEL)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CEL_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_CLP) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_CLP)( VEC_T(1,C) vARG_0, VEC_T(1,C) vMin, VEC_T(1,C) vMax )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_CLP_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vMin, *(VEC_S_T(1,CP))&vMax ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_SAT) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_SAT)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_SAT_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_NAN) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_NAN)( VEC_T(1,C) vARG_0 )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_NAN_S)( *(VEC_S_T(1,CP))&vARG_0 ) };
    return (VEC_UN_1_MEMBER(uResult));
}


/* ---- FCN_V(tgMH_BND) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_V(tgMH_BND)( VEC_T(1,C) vARG_0, VEC_T(1,C) vBound )
{
    VEC_UN_T(1,C)                       uResult = { VEC_S_UN_1_MEMBER() = FCN_V(tgMH_BND_S)( *(VEC_S_T(1,CP))&vARG_0, *(VEC_S_T(1,CP))&vBound ) };
    return (VEC_UN_1_MEMBER(uResult));
}




/* =============================================================================================================================================================================== */
#endif
