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


/* ---- tgPH_Form_Update__WRITE -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVEC_F32_04_1 tgPH_Material_Calc_Restitution_Factor( TgATTRIBUTE_MAYBE_UNUSED STg2_PH_Body_CPC ARG0, TgATTRIBUTE_MAYBE_UNUSED STg2_PH_Body_CPC ARG1 )
{
    return tgMH_SET1_F32_04_1( -1.0F );
}

/* ---- tgPH_Form_Update__WRITE -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPH_Form_Update__WRITE( STg2_PH_Form_P psFM, STg2_PH_Body_PC psBY, TgBOOL_C bReset_Last_Position )
{
    tgMH_CAT_F32_04_3( &psFM->m_mFinal_O2W, &psFM->m_mLocal_O2B, &psBY->m_mFinal_O2W);
    psFM->m_vPos_Last_Valid_O2W = psFM->m_vPos_O2W;
    psFM->m_vPos_O2W = tgMH_Query_Axis_3_F32_04_3( &psFM->m_mFinal_O2W );
    tgGM_BA_Copy_TX_F32_04( &psFM->m_sBA_W, &psFM->m_sBA_O, &psFM->m_mFinal_O2W );

    if (bReset_Last_Position)
    {
        psFM->m_vPos_Last_Valid_O2W = psFM->m_vPos_O2W;
    }
}


/* ---- tgPH_Body_Update__WRITE -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPH_Body_Update__WRITE( STg2_PH_Body_PC psBY, TgBOOL_C bReset_Last_Position )
{
    tgMH_Init_Reference_Frame_From_Quaternion_Position_F32_04_3( &psBY->m_mFinal_O2W, psBY->m_vRot_O2W, psBY->m_vPos_O2W );

    if (bReset_Last_Position)
    {
        psBY->m_vPos_Last_Valid_O2W = psBY->m_vPos_O2W;
    }

    #pragma region Update all of the attached Forms
    if (KTgID__INVALID_VALUE != psBY->m_tiFM.m_uiKI)
    {
        STg2_PH_Form_P                      psFM = tgPH_Form_Get_Form_From_ID( psBY->m_tiFM );

        for (;nullptr != psFM; psFM = tgPH_Form_Get_Form_From_ID( psFM->m_tiNext ))
        {
            tgPH_Form_Update__WRITE( psFM, psBY, bReset_Last_Position );
        };
    };
    #pragma endregion
}


/* ---- tgPH_Update_World__Free_Solver_Set --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPH_Update_World__Free_Solver_Set( STg2_PH_Solver__Set_PC psSolver_Set )
{
    ETgPH_CONSTRAINT                    enConstraint;

    TgDIAG(nullptr != psSolver_Set);

    if (nullptr != psSolver_Set->m_avResult) { TgFREE_TEMP( psSolver_Set->m_avResult ); };
    if (nullptr != psSolver_Set->m_anuiDoF) { TgFREE_TEMP( psSolver_Set->m_anuiDoF ); };
    if (nullptr != psSolver_Set->m_auiJacobian_Index) { TgFREE_TEMP( psSolver_Set->m_auiJacobian_Index ); };
    if (nullptr != psSolver_Set->m_avInverse_Mass_Inertia_Tensor) { TgFREE_TEMP( psSolver_Set->m_avInverse_Mass_Inertia_Tensor ); };
    if (nullptr != psSolver_Set->m_apsInvalid_Contact_Constraint) { TgFREE_TEMP( psSolver_Set->m_apsInvalid_Contact_Constraint ); };
    for (enConstraint = ETgPH_CONSTRAINT__BEGIN; enConstraint < ETgPH_CONSTRAINT__END; enConstraint = (ETgPH_CONSTRAINT)((TgSINT_E32)enConstraint + 1))
    {
        if (nullptr !=  psSolver_Set->m_apuiDoF[enConstraint]) { TgFREE_TEMP( psSolver_Set->m_apuiDoF[enConstraint] ); };
        if (nullptr !=  psSolver_Set->m_apsConstraint[enConstraint]) { TgFREE_TEMP( psSolver_Set->m_apsConstraint[enConstraint] ); };
    }
    if (nullptr != psSolver_Set->m_apsBody) { TgFREE_TEMP( psSolver_Set->m_apsBody ); };
    tgMM_Set_U08_0x00( psSolver_Set, sizeof( STg2_PH_Solver__Set ) );
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
TgINLINE T_ID(TgPH_,_ID) T_ID(tgPH_,_ID_Init)( T_ID(TgPH_,_ID_PCU) psKI, TgUINT_E32_C uiI, TgUINT_E08_C uiWorld, TgUINT_E08_C uiScene )
{
    T_ID(TgPH_,_ID)                      sInit;

    sInit.m_uiK = TgSTD_ATOMIC(fetch_add)( &(T_ID(tgKI_NUI_PH_,_ID)), 1 );
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

/*# defined(T_GLOBAL) */
#else

    /* Check that the identifier is valid */
    if ((KTgID__INVALID_VALUE == tiID.m_uiKI) || (tiID.m_uiWorld >= ETgPH_MAX_WORLD) || (tiID.m_uiI >= T_NAME(g_anuiPH_,_Total_Commit)[tiID.m_uiWorld]))
    {
        return (nullptr);
    };

    /* Get a pointer to the object */
    T_NAME(ps,) = T_NAME(g_aasPH_,)[tiID.m_uiWorld] + tiID.m_uiI;

/*# !defined(T_GLOBAL) */
#endif

/*# !defined(T_STATIC) */
#else

    /* Check that the identifier is valid */
    if ((KTgID__INVALID_VALUE == tiID.m_uiKI) || (tiID.m_uiI >= T_ID(ETgPH_MAX_,)))
    {
        TgPARAM_CHECK(false);
        return (nullptr);
    };

    T_NAME(ps,) = T_NAME(g_asPH_,) + tiID.m_uiI;

/*# !defined(T_STATIC) */
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
