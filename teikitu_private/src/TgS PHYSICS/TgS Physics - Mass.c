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

/* ---- tgPH_Mass_Reset ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Mass_Reset( STg2_PH_Mass_PCU psMS )
{
    tgPH_Mass_Set_Mass( psMS, 0.0F, ETgPM_UNKNOWN, nullptr );
    psMS->m_vCG = KTgUNIT_W_F32_04_1;
}


/* ---- tgPH_Mass_Set_Mass ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Set_Mass( STg2_PH_Mass_PC psMS, TgFLOAT32_C fMass, ETgPM_SHORT enPM, UTg2_CO_Primitive_F32_04_P puPM )
{
    if (!(fMass > 0.0F))
    {
        tgMM_Set_U08_0x00( &psMS->m_mMOI, sizeof(psMS->m_mMOI) );
        tgMM_Set_U08_0x00( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
        psMS->m_uMass.m_vF32_04_1 = KTgZERO_F32_04_1;
        psMS->m_uInv_Mass.m_vF32_04_1 = KTgZERO_F32_04_1;
        return (KTgS_OK);
    };

    psMS->m_uMass.m_vF32_04_1 = tgMH_SET1_F32_04_1( fMass );
    psMS->m_uInv_Mass.m_vF32_04_1 = tgMH_SET1_F32_04_1( 1.0F / fMass );

    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)
    switch (enPM) {
    case ETgPM_BX: { /* Width = x, Height = y, Depth =z */
        TgVEC_UN_F32_04_1_C                 uExtent = { .m_vF32_04_1 = puPM->m_sBX.m_vExtent };
        TgFLOAT32_C                         fMass_Coeff = (1.0F / 12.0F) * fMass;
        TgVEC_UN_F32_04_3                   uM0;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fMass_Coeff * (uExtent.m_vS_F32_04_1.y*uExtent.m_vS_F32_04_1.y + uExtent.m_vS_F32_04_1.z*uExtent.m_vS_F32_04_1.z);
        uM0.m_mS_F32_04_3._22 = fMass_Coeff * (uExtent.m_vS_F32_04_1.x*uExtent.m_vS_F32_04_1.x + uExtent.m_vS_F32_04_1.z*uExtent.m_vS_F32_04_1.z);
        uM0.m_mS_F32_04_3._33 = fMass_Coeff * (uExtent.m_vS_F32_04_1.x*uExtent.m_vS_F32_04_1.x + uExtent.m_vS_F32_04_1.y*uExtent.m_vS_F32_04_1.y);
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = 1.0F / uM0.m_mS_F32_04_3._11;
        uM0.m_mS_F32_04_3._22 = 1.0F / uM0.m_mS_F32_04_3._22;
        uM0.m_mS_F32_04_3._33 = 1.0F / uM0.m_mS_F32_04_3._33;
        tgMM_Copy( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
        tgPH_Mass_Rotate_Mat( psMS, &puPM->m_sBX.m_mReference_Frame );
    } break;
    case ETgPM_SP: {
        TgVEC_UN_F32_04_1_C                 uRadius = { .m_vF32_04_1 = puPM->m_sSP.m_vRadius };
        TgFLOAT32_C                         fVal = 0.4F * fMass * uRadius.m_vS_F32_04_1.x;
        TgFLOAT32_C                         fInv_Val = 1.0F / fVal;
        TgVEC_UN_F32_04_3                   uM0;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fVal;
        uM0.m_mS_F32_04_3._22 = fVal;
        uM0.m_mS_F32_04_3._33 = fVal;
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fInv_Val;
        uM0.m_mS_F32_04_3._22 = fInv_Val;
        uM0.m_mS_F32_04_3._33 = fInv_Val;
        tgMM_Copy( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
    } break;
    case ETgPM_TB: TgATTRIBUTE_FALLTHROUGH
    case ETgPM_CY: TgATTRIBUTE_FALLTHROUGH
    case ETgPM_CP: {
        TgVEC_UN_F32_04_1_C                 uRadiusSq = { .m_vF32_04_1 = puPM->m_sTB.m_vRadiusSq };
        TgVEC_UN_F32_04_1_C                 uExtent = { .m_vF32_04_1 = puPM->m_sTB.m_vExtent };
        TgVEC_UN_F32_04_3                   uM0;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = (1.0F / 12.0F)*fMass*(3.0F*uRadiusSq.m_vS_F32_04_1.x + uExtent.m_vS_F32_04_1.x*uExtent.m_vS_F32_04_1.x*4.0F);
        uM0.m_mS_F32_04_3._22 = (1.0F / 2.0F)*fMass*uRadiusSq.m_vS_F32_04_1.x;
        uM0.m_mS_F32_04_3._33 = (1.0F / 12.0F)*fMass*(3.0F*uRadiusSq.m_vS_F32_04_1.x + uExtent.m_vS_F32_04_1.x*uExtent.m_vS_F32_04_1.x*4.0F);
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = 1.0F / uM0.m_mS_F32_04_3._11;
        uM0.m_mS_F32_04_3._22 = 1.0F / uM0.m_mS_F32_04_3._22;
        uM0.m_mS_F32_04_3._33 = 1.0F / uM0.m_mS_F32_04_3._33;
        tgMM_Copy( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
        tgPH_Mass_Rotate_Mat( psMS, &puPM->m_sTB.m_mReference_Frame );
    } break;
    default: {
        TgVEC_UN_F32_04_3                   uM0;
        TgFLOAT32_C                         fInv_Mass = 1.0F / fMass;

        tgMM_Set_U08_0x00( &uM0, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fMass;
        uM0.m_mS_F32_04_3._22 = fMass;
        uM0.m_mS_F32_04_3._33 = fMass;
        tgMM_Copy( &psMS->m_mMOI, sizeof(psMS->m_mMOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        uM0.m_mS_F32_04_3._11 = fInv_Mass;
        uM0.m_mS_F32_04_3._22 = fInv_Mass;
        uM0.m_mS_F32_04_3._33 = fInv_Mass;
        tgMM_Copy( &psMS->m_mInv_MOI, sizeof(psMS->m_mInv_MOI), &uM0.m_mF32_04_3, sizeof(uM0) );
        psMS->m_vCG = KTgUNIT_W_F32_04_1;
    } break;
    };
    TgWARN_DISABLE_POP()
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Private Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Mass_Move ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Move( STg2_PH_Mass_PC psMass, TgVEC_F32_04_1_C vDS )
{
    TgUN_V128                           u00, u01, u02, u03, u04;
    TgUN_V128                           u10, u11, u12, u13, u14;
    TgUN_V128                           u20, u21, u22;
    TgVEC_F32_04_4                      m44;

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

    tgMH_INV_F32_04_3( &m44, &psMass->m_mMOI );
    psMass->m_mInv_MOI.m_vC0 = m44.m_vC0;
    psMass->m_mInv_MOI.m_vC1 = m44.m_vC1;
    psMass->m_mInv_MOI.m_vC2 = m44.m_vC2;

    return (KTgS_OK);
}


/* ---- tgPH_Mass_Rotate_Mat ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Mass_Rotate_Mat( STg2_PH_Mass_PC psMass, TgVEC_F32_04_3_CPCU pmR0 )
{
    TgUN_V128                           uA0, uA1, uA2, uA3, uA4, uA5, uA6, uA7, uA8;
    TgUN_V128                           uM0, uR0, uM1, uR1, uM2, uR2;
    TgVEC_F32_04_1                      vCG;
    TgVEC_F32_04_4                      m44;

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

    tgMH_INV_F32_04_3( &m44, &psMass->m_mMOI );
    psMass->m_mInv_MOI.m_vC0 = m44.m_vC0;
    psMass->m_mInv_MOI.m_vC1 = m44.m_vC1;
    psMass->m_mInv_MOI.m_vC2 = m44.m_vC2;

    return (KTgS_OK);
}
