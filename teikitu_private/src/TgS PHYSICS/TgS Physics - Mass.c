/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Mass.c
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

/* ---- tgPH_Mass_Move ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Move( STg2_PH_Mass_PC psMass, TgVEC_F32_04_1_C vDS )
{
    TgUN_V128                           u00, u01, u02, u03, u04;
    TgUN_V128                           u10, u11, u12, u13, u14;
    TgUN_V128                           u20, u21, u22;

    u00.m_vF32_04_1 = tgMH_Init_Vector_F32_04_1( psMass->m_vCG );
    u01.m_vF32_04_1 = tgMH_NEG_F32_04_1( u00.m_vF32_04_1 );
    u10.m_vF32_04_1 = tgMH_ADD_F32_04_1( u00.m_vF32_04_1, vDS );
    u11.m_vF32_04_1 = tgMH_SUB_F32_04_1( u10.m_vF32_04_1, vDS );

    u02.m_vS_F32_04_1.x = u01.m_vS_F32_04_1.z * u00.m_vS_F32_04_1.z + u00.m_vS_F32_04_1.y * u01.m_vS_F32_04_1.y;
    u02.m_vS_F32_04_1.y = u00.m_vS_F32_04_1.y * u00.m_vS_F32_04_1.x;
    u02.m_vS_F32_04_1.z = u01.m_vS_F32_04_1.z * u01.m_vS_F32_04_1.x;
    u02.m_vS_F32_04_1.w = 0.0F;

    u03.m_vS_F32_04_1.x = u02.m_vS_F32_04_1.y;
    u03.m_vS_F32_04_1.y = u01.m_vS_F32_04_1.z * u00.m_vS_F32_04_1.z + u01.m_vS_F32_04_1.x * u00.m_vS_F32_04_1.x;
    u03.m_vS_F32_04_1.z = u00.m_vS_F32_04_1.y * u00.m_vS_F32_04_1.z;
    u03.m_vS_F32_04_1.w = 0.0F;

    u04.m_vS_F32_04_1.x = u02.m_vS_F32_04_1.z;
    u04.m_vS_F32_04_1.y = u03.m_vS_F32_04_1.z;
    u04.m_vS_F32_04_1.z = u00.m_vS_F32_04_1.y * u01.m_vS_F32_04_1.y + u00.m_vS_F32_04_1.x * u01.m_vS_F32_04_1.x;
    u04.m_vS_F32_04_1.w = 0.0F;

    u12.m_vS_F32_04_1.x = u11.m_vS_F32_04_1.z * u10.m_vS_F32_04_1.z + u10.m_vS_F32_04_1.y * u11.m_vS_F32_04_1.y;
    u12.m_vS_F32_04_1.y = u10.m_vS_F32_04_1.y * u10.m_vS_F32_04_1.x;
    u12.m_vS_F32_04_1.z = u11.m_vS_F32_04_1.z * u11.m_vS_F32_04_1.x;
    u12.m_vS_F32_04_1.w = 0.0F;

    u13.m_vS_F32_04_1.x = u12.m_vS_F32_04_1.y;
    u13.m_vS_F32_04_1.y = u11.m_vS_F32_04_1.z * u10.m_vS_F32_04_1.z + u11.m_vS_F32_04_1.x * u10.m_vS_F32_04_1.x;
    u13.m_vS_F32_04_1.z = u10.m_vS_F32_04_1.y * u10.m_vS_F32_04_1.z;
    u13.m_vS_F32_04_1.w = 0.0F;

    u14.m_vS_F32_04_1.x = u12.m_vS_F32_04_1.z;
    u14.m_vS_F32_04_1.y = u13.m_vS_F32_04_1.z;
    u14.m_vS_F32_04_1.z = u10.m_vS_F32_04_1.y * u11.m_vS_F32_04_1.y + u10.m_vS_F32_04_1.x * u11.m_vS_F32_04_1.x;
    u14.m_vS_F32_04_1.w = 0.0F;

    u20.m_vF32_04_1 = tgMH_SUB_F32_04_1( u02.m_vF32_04_1, u12.m_vF32_04_1 );
    u21.m_vF32_04_1 = tgMH_SUB_F32_04_1( u03.m_vF32_04_1, u13.m_vF32_04_1 );
    u22.m_vF32_04_1 = tgMH_SUB_F32_04_1( u04.m_vF32_04_1, u14.m_vF32_04_1 );

    psMass->m_mMOI.m_avCol[0] = tgMH_MAD_F32_04_1( u20.m_vF32_04_1, psMass->m_uMass.m_vF32_04_1, psMass->m_mMOI.m_avCol[0] );
    psMass->m_mMOI.m_avCol[1] = tgMH_MAD_F32_04_1( u21.m_vF32_04_1, psMass->m_uMass.m_vF32_04_1, psMass->m_mMOI.m_avCol[1] );
    psMass->m_mMOI.m_avCol[2] = tgMH_MAD_F32_04_1( u22.m_vF32_04_1, psMass->m_uMass.m_vF32_04_1, psMass->m_mMOI.m_avCol[2] );

    psMass->m_vCG = tgMH_ADD_F32_04_1( psMass->m_vCG, vDS );

    return (KTgS_OK);
}


/* ---- tgPH_Mass_Rotate_Mat ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Rotate_Mat( STg2_PH_Mass_PC psMass, TgVEC_F32_04_3_CPCU pmR0 )
{
    TgUN_V128                           uA0, uA1, uA2, uA3, uA4, uA5, uA6, uA7, uA8;
    TgUN_V128                           uM0, uR0, uM1, uR1, uM2, uR2;
    TgVEC_F32_04_1                      vCG;

    uM0.m_vF32_04_1 = psMass->m_mMOI.m_avCol[0];
    uM1.m_vF32_04_1 = psMass->m_mMOI.m_avCol[1];
    uM2.m_vF32_04_1 = psMass->m_mMOI.m_avCol[2];

    uR0.m_vF32_04_1 = pmR0->m_avCol[0];
    uR1.m_vF32_04_1 = pmR0->m_avCol[1];
    uR2.m_vF32_04_1 = pmR0->m_avCol[2];

    uA0.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM0.m_vF32_04_1, uR0.m_vF32_04_1 );
    uA1.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM0.m_vF32_04_1, uR1.m_vF32_04_1 );
    uA2.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM0.m_vF32_04_1, uR2.m_vF32_04_1 );

    uA3.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM1.m_vF32_04_1, uR0.m_vF32_04_1 );
    uA4.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM1.m_vF32_04_1, uR1.m_vF32_04_1 );
    uA5.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM1.m_vF32_04_1, uR2.m_vF32_04_1 );

    uA6.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM2.m_vF32_04_1, uR0.m_vF32_04_1 );
    uA7.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM2.m_vF32_04_1, uR1.m_vF32_04_1 );
    uA8.m_vF32_04_1 = tgMH_DOT3_F32_04_1( uM2.m_vF32_04_1, uR2.m_vF32_04_1 );

    uM0.m_vS_F32_04_1.x = uR0.m_vS_F32_04_1.x * uA0.m_vS_F32_04_1.x + uR0.m_vS_F32_04_1.y * uA3.m_vS_F32_04_1.x + uR0.m_vS_F32_04_1.z * uA6.m_vS_F32_04_1.x;
    uM0.m_vS_F32_04_1.y = uR0.m_vS_F32_04_1.x * uA1.m_vS_F32_04_1.x + uR0.m_vS_F32_04_1.y * uA4.m_vS_F32_04_1.x + uR0.m_vS_F32_04_1.z * uA7.m_vS_F32_04_1.x;
    uM0.m_vS_F32_04_1.z = uR0.m_vS_F32_04_1.x * uA2.m_vS_F32_04_1.x + uR0.m_vS_F32_04_1.y * uA5.m_vS_F32_04_1.x + uR0.m_vS_F32_04_1.z * uA8.m_vS_F32_04_1.x;

    uM1.m_vS_F32_04_1.x = uM0.m_vS_F32_04_1.x;
    uM1.m_vS_F32_04_1.y = uR1.m_vS_F32_04_1.x * uA1.m_vS_F32_04_1.x + uR1.m_vS_F32_04_1.y * uA4.m_vS_F32_04_1.x + uR1.m_vS_F32_04_1.z * uA7.m_vS_F32_04_1.x;
    uM1.m_vS_F32_04_1.z = uR1.m_vS_F32_04_1.x * uA2.m_vS_F32_04_1.x + uR1.m_vS_F32_04_1.y * uA5.m_vS_F32_04_1.x + uR1.m_vS_F32_04_1.z * uA8.m_vS_F32_04_1.x;

    uM2.m_vS_F32_04_1.x = uM0.m_vS_F32_04_1.z;
    uM2.m_vS_F32_04_1.y = uM1.m_vS_F32_04_1.z;
    uM2.m_vS_F32_04_1.z = uR2.m_vS_F32_04_1.x * uA2.m_vS_F32_04_1.x + uR2.m_vS_F32_04_1.y * uA5.m_vS_F32_04_1.x + uR2.m_vS_F32_04_1.z * uA8.m_vS_F32_04_1.x;

    psMass->m_mMOI.m_avCol[0] = uM0.m_vF32_04_1;
    psMass->m_mMOI.m_avCol[1] = uM1.m_vF32_04_1;
    psMass->m_mMOI.m_avCol[2] = uM2.m_vF32_04_1;

    vCG = psMass->m_vCG;
    psMass->m_vCG = tgMH_SEL_F32_04_1( psMass->m_vCG, tgMH_DOT3_F32_04_1( vCG, pmR0->m_avCol[0] ), KTgF000_V128.m_vF32_04_1 );
    psMass->m_vCG = tgMH_SEL_F32_04_1( psMass->m_vCG, tgMH_DOT3_F32_04_1( vCG, pmR0->m_avCol[1] ), KTg0F00_V128.m_vF32_04_1 );
    psMass->m_vCG = tgMH_SEL_F32_04_1( psMass->m_vCG, tgMH_DOT3_F32_04_1( vCG, pmR0->m_avCol[2] ), KTg00F0_V128.m_vF32_04_1 );

    return (KTgS_OK);
}
