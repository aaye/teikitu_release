/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal.inl
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_INL)
#if !defined (ENABLE_RELOAD_GUARD)


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- tgPH_Mass_Reset ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPH_Mass_Reset( STg2_PH_Mass_PCU psMS )
{
    tgMH_CLI_F32_04_3( &psMS->m_mMOI );
    tgMH_CLI_F32_04_3( &psMS->m_mInv_MOI );
    psMS->m_vCG = tgMH_SET1_F32_04_1( 0.0F );
    psMS->m_uMass.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );
    psMS->m_uInv_Mass.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );
}

/* ---- tgPH_Mass_Move_Elem ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgPH_Mass_Move_Elem( STg2_PH_Mass_PC psMass, TgFLOAT32_C fDS_X, TgFLOAT32_C fDS_Y, TgFLOAT32_C fDS_Z )
{
    return (tgPH_Mass_Move( psMass, tgMH_Init_Vector_ELEM_F32_04_1( fDS_X, fDS_Y, fDS_Z ) ));
}


/* ---- tgPH_Mass_Rotate_Eul_Elem ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgPH_Mass_Rotate_Eul_Elem( STg2_PH_Mass_PC psMass, TgFLOAT32_C fEul_X, TgFLOAT32_C fEul_Y, TgFLOAT32_C fEul_Z )
{
    TgVEC_UN_F32_04_3                   uM0;

    tgMH_Init_Euler_ELEM_S_F32_04_3( &uM0.m_mS_F32_04_3, fEul_X, fEul_Y, fEul_Z );
    return (tgPH_Mass_Rotate_Mat( psMass, &uM0.m_mF32_04_3 ));
}


/* ---- tgPH_Mass_Rotate_Eul ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgPH_Mass_Rotate_Eul( STg2_PH_Mass_PC psMass, TgVEC_F32_04_1_C vEul )
{
    TgUN_V128_C                         uEul = { .m_vF32_04_1 = vEul };

    return (tgPH_Mass_Rotate_Eul_Elem( psMass, uEul.m_vS_F32_04_1.x, uEul.m_vS_F32_04_1.y, uEul.m_vS_F32_04_1.z ));
}


/* ---- tgPH_Mass_Rotate_Quat ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgPH_Mass_Rotate_Quat( STg2_PH_Mass_PC psMass, TgVEC_F32_04_1_C qR0 )
{
    TgVEC_F32_04_3                    mR0;

    tgMH_Init_Quat_F32_04_3( &mR0, qR0 );
    return (tgPH_Mass_Rotate_Mat( psMass, &mR0 ));
}


/* ---- tgPH_Mass_Set_Mass ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgPH_Mass_Set_Mass( STg2_PH_Mass_PC psMass, TgFLOAT32_C fMass )
{
    if (!(fMass >= 0.0F))
    {
        psMass->m_uMass.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );
        psMass->m_uInv_Mass.m_vF32_04_1 = tgMH_SET1_F32_04_1( 0.0F );
    }
    else
    {
        psMass->m_uMass.m_vF32_04_1 = tgMH_SET1_F32_04_1( fMass );
        psMass->m_uInv_Mass.m_vF32_04_1 = tgMH_SET1_F32_04_1( 1.0F / fMass );
    };
    return (KTgS_OK);
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Internal.inl"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_INTERNAL_INL


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- T_ID(tgPH_,_ID_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE T_ID(TgPH_,_ID) T_ID(tgPH_,_ID_Init)( T_ID(TgPH_,_ID_PCU) psKI, TgUINT_F32_C uiI, TgUINT_F08_C uiWorld, TgUINT_F08_C uiScene )
{
    T_ID(TgPH_,_ID)                      sInit;

    sInit.m_uiK = atomic_fetch_add( &(T_ID(tgKI_NUI_PH_,_ID)), 1 );
    sInit.m_uiScene = uiScene;
    sInit.m_uiWorld = uiWorld;
    sInit.m_uiI = uiI;
    psKI->m_uiKI = sInit.m_uiKI;
    return (sInit);
}


/* ---- T_FCN(tgPH_,_Get_,_From_ID) ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE T_NAME(STg2_PH_,_P) T_FCN(tgPH_,_Get_,_From_ID)( T_ID(TgPH_,_ID_C) tiID )
{
    T_NAME(STg2_PH_,_P)                 T_NAME(ps,);

#if !defined(T_STATIC)
#if defined(T_GLOBAL)
    /* Check that the identifier is valid */
    if ((KTgID__INVALID_VALUE == tiID.m_uiKI) || (tiID.m_uiI >= T_NAME(g_nuiPH_,_Total_Commit)))
    {
        TgPARAM_CHECK(false);
        return (nullptr);
    };

    T_NAME(ps,) = T_NAME(g_asPH_,) + tiID.m_uiI;

//# defined(T_GLOBAL)
#else

    /* Check that the identifier is valid */
    if ((KTgID__INVALID_VALUE == tiID.m_uiKI) || (tiID.m_uiWorld >= ETgPH_MAX_WORLD) || (tiID.m_uiI >= T_NAME(g_anuiPH_,_Total_Commit)[tiID.m_uiWorld]))
    {
        TgPARAM_CHECK(false);
        return (nullptr);
    };

    /* Get a pointer to the object */
    T_NAME(ps,) = T_NAME(g_aasPH_,)[tiID.m_uiWorld] + tiID.m_uiI;

//# !defined(T_GLOBAL)
#endif

//# !defined(T_STATIC)
#else

    /* Check that the identifier is valid */
    if ((KTgID__INVALID_VALUE == tiID.m_uiKI) || (tiID.m_uiI >= T_ID(ETgPH_MAX_,)))
    {
        TgPARAM_CHECK(false);
        return (nullptr);
    };

    T_NAME(ps,) = T_NAME(g_asPH_,) + tiID.m_uiI;

//# !defined(T_STATIC)
#endif

    /* Validate that the identifier matches the singleton identifier in the object */
    if (T_NAME(ps,)->T_NAME(m_ti,).m_uiKI != tiID.m_uiKI)
    {
        TgPARAM_CHECK(false);
        return (nullptr);
    };

    return (T_NAME(ps,));
}




/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_INTERNAL_INL) */
#endif
