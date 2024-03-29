/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math API [Vector] [S] [F].c_inc
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD2)
    #define ENABLE_RELOAD_GUARD2

    TEST_LOCAL TgFLOAT32 tgMH_ERR_S_F32_02_1( TgVEC_S_F32_02_1_C v0 ) { return (tgCM_MAX_F32( 10.0F*tgMH_LEN_S_F32_02_1( v0 ), 1.0F )); }
    TEST_LOCAL TgFLOAT32 tgMH_ERR_S_F32_03_1( TgVEC_S_F32_03_1_C v0 ) { return (tgCM_MAX_F32( 10.0F*tgMH_LEN_S_F32_03_1( v0 ), 1.0F )); }
    TEST_LOCAL TgFLOAT32 tgMH_ERR_S_F32_04_1( TgVEC_S_F32_04_1_C v0 ) { return (tgCM_MAX_F32( 10.0F*tgMH_LEN_S_F32_04_1( v0 ), 1.0F )); }
    TEST_LOCAL TgFLOAT64 tgMH_ERR_S_F64_02_1( TgVEC_S_F64_02_1_C v0 ) { return (tgCM_MAX_F64(  10.0*tgMH_LEN_S_F64_02_1( v0 ), 1.0 )); }
    TEST_LOCAL TgFLOAT64 tgMH_ERR_S_F64_03_1( TgVEC_S_F64_03_1_C v0 ) { return (tgCM_MAX_F64(  10.0*tgMH_LEN_S_F64_03_1( v0 ), 1.0 )); }
    TEST_LOCAL TgFLOAT64 tgMH_ERR_S_F64_04_1( TgVEC_S_F64_04_1_C v0 ) { return (tgCM_MAX_F64(  10.0*tgMH_LEN_S_F64_04_1( v0 ), 1.0 )); }

    #define TEMPLATE__TEST_AND_UNLOAD_TEMPLATE_MACROS
    #define TEMPLATE__VECTOR_DIM 2
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 3
    #include __FILE__

    #define TEMPLATE__VECTOR_DIM 4
#endif

#if !defined (ENABLE_RELOAD_GUARD)
    #define ENABLE_RELOAD_GUARD
    #if !defined(TEMPLATE__TYPE_SIZE)
        #define TEMPLATE__TYPE_SIZE 32
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #define TEMPLATE__TYPE_SIZE 64
    #endif
    #undef ENABLE_RELOAD_GUARD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#define FCN_V_UT(...)                       MULTI_MACRO(FCN_V_UT, __VA_ARGS__)
#define FCN_V_UT_1(F)                       TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, 1 )
#define FCN_V_UT_2(F, COL)                  TgMACRO_CONCAT5( UNIT_TEST__TEST__##F, _, GENERATE__VEC_DESC, _, COL )

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V_UT(tgMH_ADD_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_ADD_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_ADD_S)( v0, v1 );
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] + v1.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MAD_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MAD_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_MAD_S)(v0, v1, v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] * v1.m_aData[uiIndex] + v2.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NMS_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NMS_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_NMS_S)(v0, v1, v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(-(v0.m_aData[uiIndex] * v1.m_aData[uiIndex] - v2.m_aData[uiIndex]) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DOT_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DOT_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}};
    VAR_T()                             fTest;

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    fTest = TYPE_K(0);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        fTest += v0.m_aData[uiIndex] * v1.m_aData[uiIndex];
    };

    Test__Expect_NE(false, FCN_F(tgCM_NR0)(fTest - (FCN_V(tgMH_DOT_S)(v0, v1))));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MUL_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MUL_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_MUL_S)(v0, v1);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] * v1.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DIV_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DIV_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_DIV_S)(v0, v1);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] / v1.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SUB_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SUB_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_SUB_S)(v0, v1);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] - v1.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_LSQ_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_LSQ_S) )
{
    VEC_S_T(1)                          v0 = {{0}};
    VAR_T()                             fTest;

    fTest = TYPE_K(0);
    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        fTest += v0.m_aData[uiIndex] * v0.m_aData[uiIndex];
    };
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(fTest - FCN_V(tgMH_LSQ_S)(v0)) <= VAR_K(KTgEPS)*FCN_V(tgMH_LSQ_S)(v0));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_LEN_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_LEN_S) )
{
    VEC_S_T(1)                          v0 = {{0}};
    VAR_T()                             fTest;

    fTest = TYPE_K(0);
    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        fTest += v0.m_aData[uiIndex] * v0.m_aData[uiIndex];
    };
    Test__Expect_NE(false, FCN_F(tgCM_NR0)(FCN_F(tgPM_SQRT)(fTest) - FCN_V(tgMH_LEN_S)(v0)));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NEG_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NEG_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_NEG_S)(v0);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ(-v0.m_aData[uiIndex], v3.m_aData[uiIndex]);
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SQRT_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SQRT_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) >= (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_SQRT_S)(v0);

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(FCN_F(tgPM_SQRT)(v0.m_aData[uiIndex]) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_RSQRT_S) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_RSQRT_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) >= (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_RSQRT_S)(v0);

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(TYPE_K(1) / FCN_F(tgPM_SQRT)(v0.m_aData[uiIndex]) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NORM_LEN_S) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NORM_LEN_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}},v4 = {{0}}, v5 = {{0}};
    VAR_T()                             fLength;

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_NORM_LEN_S)(&fLength, v2);
    v4 = FCN_V(tgMH_MUL_SV_S)(FCN_V(tgMH_LEN_S)(v2), v3);
    v5 = FCN_V(tgMH_SUB_S)(v4, v2);
    Test__Expect_NE(false, FCN_F(tgPM_ABS)(fLength - FCN_V(tgMH_LEN_S)(v2)) <= FCN_V(tgMH_ERR_S)(v2)*FCN_V(tgMH_ERR_S)(v2));
    Test__Expect_NE(false, FCN_V(tgMH_LEN_S)(v5) <= FCN_V(tgMH_ERR_S)(v2)*FCN_V(tgMH_ERR_S)(v3));
    Test__Expect_NE(false, FCN_V(tgMH_LEN_S)(v3) <= TYPE_K(1) + FCN_V(tgMH_ERR_S)(v3));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NORM_S) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NORM_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}},v4 = {{0}}, v5 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_NORM_S)(v0);
    v4 = FCN_V(tgMH_MUL_SV_S)(FCN_V(tgMH_LEN_S)(v0), v3);
    v5 = FCN_V(tgMH_SUB_S)(v4, v0);
    Test__Expect_NE(false, FCN_V(tgMH_LEN_S)(v5) <= FCN_V(tgMH_ERR_S)(v0)*FCN_V(tgMH_ERR_S)(v3));
    Test__Expect_NE(false, FCN_V(tgMH_LEN_S)(v3) <= TYPE_K(1) + FCN_V(tgMH_ERR_S)(v3));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_FLR_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_FLR_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_FLR_S)(v0);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(FCN_F(tgPM_FLOOR)(v0.m_aData[uiIndex]) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CEL_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CEL_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_CEL_S)(v0);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(FCN_F(tgPM_CEIL)(v0.m_aData[uiIndex]) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CLP_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CLP_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (      TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (v0.m_aData[ui0] >= (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (v1.m_aData[ui0] >= (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_CLP_S)(v0, v1, v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)(v0.m_aData[uiIndex], v2.m_aData[uiIndex]);
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)(v1.m_aData[uiIndex], tMin);

        Test__Expect_NE(false, FCN_F(tgCM_NR0)(tMax - v3.m_aData[uiIndex]));
    };

    v3 = FCN_V(tgMH_CLP_S)(v0, v1, v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)(v0.m_aData[uiIndex], v2.m_aData[uiIndex]);
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)(v1.m_aData[uiIndex], tMin);

        Test__Expect_NE(false, FCN_F(tgCM_NR0)(tMax - v3.m_aData[uiIndex]));
    };

    v3 = FCN_V(tgMH_CLP_S)(v2, v0, v1);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)(v0.m_aData[uiIndex], v2.m_aData[uiIndex]);
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)(v1.m_aData[uiIndex], tMin);

        Test__Expect_NE(false, FCN_F(tgCM_NR0)(tMax - v3.m_aData[uiIndex]));
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SAT_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SAT_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_SAT_S)(v0);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)(v0.m_aData[uiIndex], TYPE_K(1));
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)(TYPE_K(0), tMin);

        Test__Expect_NE(false, FCN_F(tgCM_NR0)(tMax - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NAN_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NAN_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v3 = {{0}};
    VAR_T()                             tInvalid;

    tgMM_Set_U08_0x00( &v1, sizeof( v1 ) );

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    tgMM_Set_U08_0xFF( &tInvalid, sizeof( VAR_T() ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        v3 = v1;
        Test__Expect_EQ(false, !FCN_V(tgMH_Is_Valid_S)(v3));
        v3.m_aData[uiIndex] = tInvalid;
        Test__Expect_NE(0, !FCN_V(tgMH_Is_Valid_S)(v3));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_BND_S) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_BND_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}};
    TgBOOL                              bBnd_Test = true;

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) >= (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM && bBnd_Test; ++uiIndex)
    {
        if ((v0.m_aData[uiIndex] < -v1.m_aData[uiIndex]) || (v0.m_aData[uiIndex] > v1.m_aData[uiIndex]))
        {
            bBnd_Test = false;
        };
    };
    Test__Expect_EQ(bBnd_Test, FCN_V(tgMH_Is_BND_S)(v0, v1));
    Test__Expect_EQ(true, FCN_V(tgMH_Is_BND_S)( v1, v1 ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MAD_SVV_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MAD_SVV_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_MAD_SVV_S)(TYPE_K(2,0), v1, v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(TYPE_K(2,0)*v1.m_aData[uiIndex] + v2.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MAD_VSV_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MAD_VSV_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_MAD_VSV_S)(v0, -TYPE_K(3,0), v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] * -TYPE_K(3,0) + v2.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NMS_SVV_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NMS_SVV_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_NMS_SVV_S)(TYPE_K(2,0), v1, v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(-(TYPE_K(2,0)*v1.m_aData[uiIndex] - v2.m_aData[uiIndex]) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NMS_VSV_S) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NMS_VSV_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_NMS_VSV_S)(v0, -TYPE_K(3,0), v2);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(-(v0.m_aData[uiIndex] * -TYPE_K(3,0) - v2.m_aData[uiIndex]) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MUL_SV_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MUL_SV_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_MUL_SV_S)(TYPE_K(2,0), v1);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(TYPE_K(2,0) * v1.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MUL_VS_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MUL_VS_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_MUL_VS_S)(v0, -TYPE_K(3,0));
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] * -TYPE_K(3,0) - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DIV_SV_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DIV_SV_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_DIV_SV_S)(TYPE_K(2,0), v1);
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(TYPE_K(2,0) / v1.m_aData[uiIndex] - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DIV_VS_S) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DIV_VS_S) )
{
    VEC_S_T(1)                          v0 = {{0}}, v1 = {{0}}, v2 = {{0}}, v3 = {{0}};

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (TYPE_K(0) == (v0.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v1.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (TYPE_K(0) == (v2.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    v3 = FCN_V(tgMH_DIV_VS_S)(v0, -TYPE_K(3,0));
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C) fInvScalar = TYPE_K(1) / -TYPE_K(3,0);
        Test__Expect_NE(false, FCN_F(tgCM_NR0)(v0.m_aData[uiIndex] * fInvScalar - v3.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_V_UT
#undef FCN_V_UT_1
#undef FCN_V_UT_2
