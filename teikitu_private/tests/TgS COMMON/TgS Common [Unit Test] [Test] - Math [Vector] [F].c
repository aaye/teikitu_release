/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common [Unit Test] [Test] - Math [Vector] [F].c_inc
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD2)
    #define ENABLE_RELOAD_GUARD2

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

#if (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE /* MACRO_COMPILE_NATIVE_MATRIX_GUARD */

/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Test Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_V_UT(tgMH_ADD) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_ADD) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();

    sV2.vN = FCN_V(tgMH_ADD)( sV0.vN, sV1.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( sV0.vT.m_aData[uiIndex] + sV1.vT.m_aData[uiIndex] - sV2.vT.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MAD) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MAD) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();
    sV2.vN = FCN_V(tgMH_RAND)();

    sV3.vN = FCN_V(tgMH_MAD)( sV0.vN, sV1.vN, sV2.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( sV0.vT.m_aData[uiIndex] * sV1.vT.m_aData[uiIndex] + sV2.vT.m_aData[uiIndex] - sV3.vT.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NMS) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NMS) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();
    sV2.vN = FCN_V(tgMH_RAND)();

    sV3.vN = FCN_V(tgMH_NMS)( sV0.vN, sV1.vN, sV2.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T()                             fCheck;

        fCheck = -(sV0.vT.m_aData[uiIndex] * sV1.vT.m_aData[uiIndex] - sV2.vT.m_aData[uiIndex]);
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( fCheck - sV3.vT.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DOT) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DOT) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;
    VAR_T()                             fTest;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();

    sV2.vN = FCN_V(tgMH_DOT)( sV0.vN, sV1.vN );
    fTest = FCN_V(tgMH_DOT_S)( sV0.vT, sV1.vT );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( fTest - sV2.vT.x ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_MUL) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_MUL) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();

    sV2.vN = FCN_V(tgMH_MUL)( sV0.vN, sV1.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( sV0.vT.m_aData[uiIndex] * sV1.vT.m_aData[uiIndex] - sV2.vT.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_DIV) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_DIV) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();

    sV2.vN = FCN_V(tgMH_DIV)( sV0.vN, sV1.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( sV0.vT.m_aData[uiIndex] / sV1.vT.m_aData[uiIndex] - sV2.vT.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SUB) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SUB) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();

    sV2.vN = FCN_V(tgMH_SUB)( sV0.vN, sV1.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( sV0.vT.m_aData[uiIndex] - sV1.vT.m_aData[uiIndex] - sV2.vT.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_LSQ) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_LSQ) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;
    VAR_T()                             fTest;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_LSQ)( sV0.vN );
    fTest = FCN_V(tgMH_LSQ_S)( sV0.vT );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( fTest - sV1.vT.x ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_LEN) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_LEN) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;
    VAR_T()                             fTest;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_LEN)( sV0.vN );
    fTest = FCN_V(tgMH_LEN_S)( sV0.vT );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( fTest - sV1.vT.x ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NEG) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NEG) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_NEG)( sV0.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV1.vT.m_aData[uiIndex] + sV0.vT.m_aData[uiIndex]));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SQRT) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SQRT) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;

    sV0.vN = FCN_V(tgMH_ABS)( FCN_V(tgMH_RAND)() );

    sV1.vN = FCN_V(tgMH_SQRT)( sV0.vN );
    sV2.vT = FCN_V(tgMH_SQRT_S)( sV0.vT );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( sV1.vT.m_aData[uiIndex] - sV2.vT.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_RSQRT) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_RSQRT) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;

    sV0.vN = FCN_V(tgMH_ABS)( FCN_V(tgMH_RAND)() );

    sV1.vN = FCN_V(tgMH_RSQRT)( sV0.vN );
    sV2.vT = FCN_V(tgMH_RSQRT_S)( sV0.vT );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0)( sV1.vT.m_aData[uiIndex] - sV2.vT.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NORM_LEN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NORM_LEN) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3, sV4;
    VAR_T()                             fTest;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_NORM_LEN)( &sV2.vN, sV0.vN );
    sV3.vT = FCN_V(tgMH_NORM_LEN_S)( &fTest, sV0.vT );

    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV2.vT.x - fTest ) );

    sV4.vN = FCN_V(tgMH_LEN)( sV1.vN );
    Test__Expect_EQ(true, FCN_F(tgCM_NR1)( sV4.vT.x ));

    sV4.vN = FCN_V(tgMH_LEN)( FCN_V(tgMH_SUB)( sV1.vN, sV3.vN ) );
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV4.vT.x ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NORM) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NORM) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_NORM)( sV0.vN );
    sV2.vT = FCN_V(tgMH_NORM_S)( sV0.vT );

    sV3.vN = FCN_V(tgMH_LEN)( sV1.vN );
    Test__Expect_EQ(true, FCN_F(tgCM_NR1)( sV3.vT.x ));

    sV3.vN = FCN_V(tgMH_LEN)( FCN_V(tgMH_SUB)( sV1.vN, sV2.vN ) );
    Test__Expect_EQ(true, FCN_F(tgCM_NR0)( sV3.vT.x ));

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_FLR) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_FLR) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_FLR)( sV0.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0) (FCN_F(tgPM_FLOOR)( sV0.vT.m_aData[uiIndex] ) - sV1.vT.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CEL) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CEL) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_CEL)( sV0.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        Test__Expect_NE(false, FCN_F(tgCM_NR0) (FCN_F(tgPM_CEIL)( sV0.vT.m_aData[uiIndex] ) - sV1.vT.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_CLP) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_CLP) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2, sV3;

    sV0.vN = FCN_V(tgMH_SET1)(0);
    sV1.vN = FCN_V(tgMH_SET1)(1);
    sV2.vN = FCN_V(tgMH_SET1)(2);

    for (TgRSIZE ui0 = 0; ui0 < TEMPLATE__VECTOR_DIM; ++ui0)
    {
        while (          TYPE_K(0) == (sV0.vT.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (sV0.vT.m_aData[ui0] >= (sV1.vT.m_aData[ui0] = FCN_F(tgCM_RAND)()));
        while (sV1.vT.m_aData[ui0] >= (sV2.vT.m_aData[ui0] = FCN_F(tgCM_RAND)()));
    };

    sV3.vN = FCN_V(tgMH_CLP)( sV1.vN, sV0.vN, sV2.vN );
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)( sV0.vT.m_aData[uiIndex], sV2.vT.m_aData[uiIndex] );
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)( sV1.vT.m_aData[uiIndex], tMin );

        Test__Expect_NE(false, FCN_F(tgCM_NR0)( tMax - sV3.vT.m_aData[uiIndex] ));
    };

    sV3.vN = FCN_V(tgMH_CLP)( sV0.vN, sV1.vN, sV2.vN );
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)( sV0.vT.m_aData[uiIndex], sV2.vT.m_aData[uiIndex] );
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)( sV1.vT.m_aData[uiIndex], tMin);

        Test__Expect_NE(false, FCN_F(tgCM_NR0)( tMax - sV3.vT.m_aData[uiIndex] ));
    };

    sV3.vN = FCN_V(tgMH_CLP)( sV2.vN, sV0.vN, sV1.vN );
    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)( sV0.vT.m_aData[uiIndex], sV2.vT.m_aData[uiIndex] );
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)( sV1.vT.m_aData[uiIndex], tMin);

        Test__Expect_NE(false, FCN_F(tgCM_NR0)( tMax - sV3.vT.m_aData[uiIndex] ));
    };


    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_SAT) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_SAT) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1;

    sV0.vN = FCN_V(tgMH_RAND)();

    sV1.vN = FCN_V(tgMH_SAT)( sV0.vN );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        VAR_T(C)        tMin = FCN_F(tgCM_MIN)( sV0.vT.m_aData[uiIndex], TYPE_K(1) );
        VAR_T(C)        tMax = FCN_F(tgCM_MAX)( TYPE_K(0), tMin );

        Test__Expect_NE(false, FCN_F(tgCM_NR0)( tMax - sV1.vT.m_aData[uiIndex] ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_NAN) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_NAN) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV3;
    VAR_T()                             tInvalid, tZero;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_RAND)();

    tgMM_Set_U08_0xFF( &tInvalid, sizeof( VAR_T() ) );
    tgMM_Set_U08_0x00( &tZero, sizeof( VAR_T() ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM; ++uiIndex)
    {
        sV3.vN = sV1.vN;
        Test__Expect_EQ(false, !FCN_V(tgMH_Is_Valid)( sV3.vN ));
        sV3.vT.m_aData[uiIndex] = tInvalid;
        Test__Expect_EQ(true,  !FCN_V(tgMH_Is_Valid)( sV3.vN ));
    };

    TEST_END_METHOD( KTgS_OK );
}


/* ---- FCN_V_UT(tgMH_BND) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TEST_METHOD_DEFINE( FCN_V_UT(tgMH_BND) )
{
    union
    {
        VEC_T(1)                            vN;
        VEC_S_T(1)                          vT;
    }                                   sV0, sV1, sV2;
    VAR_T()                             tTrue, tFalse;
    TgBOOL                              bBnd_Test = true;

    sV0.vN = FCN_V(tgMH_RAND)();
    sV1.vN = FCN_V(tgMH_ABS)( FCN_V(tgMH_RAND)() );

    sV2.vN = FCN_V(tgMH_BND)( sV0.vN, sV1.vN );

    tgMM_Set_U08_0xFF( &tTrue, sizeof( VAR_T() ) );
    tgMM_Set_U08_0x00( &tFalse, sizeof( VAR_T() ) );

    for (TgRSIZE uiIndex = 0; uiIndex < TEMPLATE__VECTOR_DIM && bBnd_Test; ++uiIndex)
    {
        if ((sV0.vT.m_aData[uiIndex] < -sV1.vT.m_aData[uiIndex]) || (sV0.vT.m_aData[uiIndex] > sV1.vT.m_aData[uiIndex]))
        {
            Test__Expect_EQ(0, memcmp( &tFalse, sV2.vT.m_aData + uiIndex, sizeof( VAR_T() ) ));
        }
        else
        {
            Test__Expect_EQ(0, memcmp( &tTrue, sV2.vT.m_aData + uiIndex, sizeof( VAR_T() ) ));
        };
    };

    TEST_END_METHOD( KTgS_OK );
}


/* =============================================================================================================================================================================== */

/*# (!VEC_IS_NATIVE && TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE) || VEC_IS_NATIVE */
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

#undef FCN_V_UT
#undef FCN_V_UT_1
#undef FCN_V_UT_2
