/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Module.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static ETgMODULE_STATE                      s_enPhysics_State = ETgMODULE_STATE__FREED;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Init --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Module_Init( TgVOID )
{
    ETgPH_WORLD                         enWorld;
    TgRSIZE                             uiIndex;

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__FREED == s_enPhysics_State );
    s_enPhysics_State = ETgMODULE_STATE__INITIALIZING;

    PROFILE_INIT( PH_COMMANDS__CLIENT );

#if defined(TgBUILD_FEATURE__CLIENT) || defined(TgBUILD_FEATURE__SERVER)
    PROFILE_INIT( PH_SIMULATE_BATCH_TOTAL );
    PROFILE_INIT( PH_COLLIDE_BATCH_TOTAL );
    PROFILE_INIT( PH_BUILD_SETS_TOTAL );
    PROFILE_INIT( PH_SOLVE_SETS_TOTAL );
    PROFILE_INIT( PH_SOLVER_BATCH_TOTAL );
    PROFILE_INIT( PH_CMD_BUFFER_EXECEUTE_TOTAL );
    uiIndex = 0;
/*# defined(TgBUILD_FEATURE__CLIENT) || defined(TgBUILD_FEATURE__SERVER) */
#endif
#if defined(TgBUILD_FEATURE__CLIENT)
    PROFILE_ARRAY_INIT( 0, _CLIENT_FX, PH_SIMULATE_BATCH );
    PROFILE_ARRAY_INIT( 0, _CLIENT_FX, PH_COLLIDE_BATCH );
    PROFILE_ARRAY_INIT( 0, _CLIENT_FX, PH_BUILD_SETS );
    PROFILE_ARRAY_INIT( 0, _CLIENT_FX, PH_SOLVE_SETS );
    PROFILE_ARRAY_INIT( 0, _CLIENT_FX, PH_UPDATE_WORLD__SIMULATE_BATCH );
    PROFILE_ARRAY_INIT( 0, _CLIENT_FX, PH_CMD_BUFFER_EXECEUTE );
    PROFILE_ARRAY_INIT( 1, _CLIENT_UI, PH_SIMULATE_BATCH );
    PROFILE_ARRAY_INIT( 1, _CLIENT_UI, PH_COLLIDE_BATCH );
    PROFILE_ARRAY_INIT( 1, _CLIENT_UI, PH_BUILD_SETS );
    PROFILE_ARRAY_INIT( 1, _CLIENT_UI, PH_SOLVE_SETS );
    PROFILE_ARRAY_INIT( 1, _CLIENT_UI, PH_UPDATE_WORLD__SIMULATE_BATCH );
    PROFILE_ARRAY_INIT( 1, _CLIENT_UI, PH_CMD_BUFFER_EXECEUTE );
    uiIndex = 2;
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif
#if defined(TgBUILD_FEATURE__SERVER)
    PROFILE_ARRAY_INIT( uiIndex, _SERVER_DEFAULT, PH_SIMULATE_BATCH );
    PROFILE_ARRAY_INIT( uiIndex, _SERVER_DEFAULT, PH_COLLIDE_BATCH );
    PROFILE_ARRAY_INIT( uiIndex, _SERVER_DEFAULT, PH_BUILD_SETS );
    PROFILE_ARRAY_INIT( uiIndex, _SERVER_DEFAULT, PH_SOLVE_SETS );
    PROFILE_ARRAY_INIT( uiIndex, _SERVER_DEFAULT, PH_UPDATE_WORLD__SIMULATE_BATCH );
    PROFILE_ARRAY_INIT( uiIndex, _SERVER_DEFAULT, PH_CMD_BUFFER_EXECEUTE );
/*# defined(TgBUILD_FEATURE__SERVER) */
#endif

    tgMM_Set_U08_0x00( g_asPH_Update__Simulation, sizeof( g_asPH_Update__Simulation ) );
    for (enWorld = ETgPH_WORLD__BEGIN; enWorld < ETgPH_WORLD__END; enWorld = (ETgPH_WORLD)((TgSINT_E32)enWorld + 1))
    {
        tgCM_UT_LF__ST__Init( &g_asPH_Update__Constraint_IMM[uiIndex].m_sStack );
    };

    tgCM_UT_LF__RW__Init( &g_sPH_Lock__Update_Module.m_sLock );

    g_pfnPH_Update_World__Collide = nullptr;
    tgPA_PnS_Init( &g_sPH_SG_PnS );

    g_bPH_Module__Paused = false;
    g_uiPH_Module__Loop_Max = 1000;

    g_tiPH_CN_Module__Paused.m_uiKI = KTgID__INVALID_VALUE;
    g_tiPH_CN_Module__Loop_Max.m_uiKI = KTgID__INVALID_VALUE;

    tgPH_Update_World__Init_Jobs();

    for (uiIndex = 0; uiIndex < TgARRAY_COUNT(g_asPH_Command_To_World); ++uiIndex)
    {
        tgCM_UT__CMD_BUF__Init( g_asPH_Command_To_World + uiIndex, 256u*1024u );
    }

    tgPH_Module_Material_Init();
    tgPH_Module_Form_Init();
    tgPH_Module_Body_Init();
    tgPH_Module_Constraint_Init();
    tgPH_Module_Motor_Init();
    tgPH_Module_Ragdoll_Init();
    tgPH_Module_Scene_Init();
    tgPH_Module_World_Init();

#if defined(TgBUILD_FEATURE__PHYSICS__HISTORY)
    tgMM_Set_U08_0x00( g_vPH_History__Body_Pos_W, sizeof( g_vPH_History__Body_Pos_W ) );
    tgMM_Set_U08_0x00( g_vPH_History__Body_Rot_W, sizeof( g_vPH_History__Body_Rot_W ) );
    tgMM_Set_U08_0x00( g_tiPH_History__Body_ID, sizeof( g_tiPH_History__Body_ID ) );
    TgSTD_ATOMIC(store)( &g_xnuiPH_History, 0 );
/*# defined(TgBUILD_FEATURE__PHYSICS__HISTORY) */
#endif

#if defined(TgBUILD_DEBUG__PHYSICS)
    g_vPH_Debug_Colour__Body_Enabled = tgMH_SET1_F32_04_1( 1.0F );
    g_vPH_Debug_Colour__Body_Sleep = tgMH_SET1_F32_04_1( 1.0F );
    g_vPH_Debug_Colour__Body_Disabled = tgMH_SET1_F32_04_1( 1.0F );
    g_vPH_Debug_Colour__Form_Enabled = tgMH_SET1_F32_04_1( 1.0F );
    g_vPH_Debug_Colour__Form_Disabled = tgMH_SET1_F32_04_1( 1.0F );
    g_vPH_Debug_Colour__Ragdoll = tgMH_SET1_F32_04_1( 1.0F );

    g_tiPH_Debug_Colour__Body_Enabled.m_uiKI = KTgID__INVALID_VALUE;
    g_tiPH_Debug_Colour__Body_Sleep.m_uiKI = KTgID__INVALID_VALUE;
    g_tiPH_Debug_Colour__Body_Disabled.m_uiKI = KTgID__INVALID_VALUE;
    g_tiPH_Debug_Colour__Form_Enabled.m_uiKI = KTgID__INVALID_VALUE;
    g_tiPH_Debug_Colour__Form_Disabled.m_uiKI = KTgID__INVALID_VALUE;
    g_tiPH_Debug_Colour__Ragdoll.m_uiKI = KTgID__INVALID_VALUE;
/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif

    s_enPhysics_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgPH_Module_Boot --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Module_Boot( TgVOID )
{
    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__INITIALIZED == s_enPhysics_State );
    s_enPhysics_State = ETgMODULE_STATE__BOOTING;

    LOG_STD_MSG_USZ_FMTU64( KTgCN_CHANEL_INITIALIZE_MEMORY, u8"Static Memory Size", tgPH_Query_Fixed_Memory() )

    s_enPhysics_State = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- tgPH_Module_Stop --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Stop( TgVOID )
{
    if ((ETgMODULE_STATE__FREED == s_enPhysics_State) || (ETgMODULE_STATE__INITIALIZED == s_enPhysics_State))
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__BOOTED == s_enPhysics_State );
    s_enPhysics_State = ETgMODULE_STATE__STOPPING;

    s_enPhysics_State = ETgMODULE_STATE__STOPPED;
}


/* ---- tgPH_Module_Free --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Free( TgVOID )
{
    ETgPH_WORLD                         enWorld;

    if (ETgMODULE_STATE__FREED == s_enPhysics_State)
    {
        return;
    };

    /* Verify the state of the system */
    TgERROR( ETgMODULE_STATE__STOPPED == s_enPhysics_State || ETgMODULE_STATE__INITIALIZED == s_enPhysics_State );
    s_enPhysics_State = ETgMODULE_STATE__FREEING;

    tgPH_Module_Material_Free();
    tgPH_Module_Form_Free();
    tgPH_Module_Body_Free();
    tgPH_Module_Constraint_Free();
    tgPH_Module_Motor_Free();
    tgPH_Module_Ragdoll_Free();
    tgPH_Module_Scene_Free();
    tgPH_Module_World_Free();

    /* Free the worlds. */
    for (enWorld = ETgPH_WORLD__BEGIN; enWorld < ETgPH_WORLD__END; enWorld = (ETgPH_WORLD)((TgSINT_E32)enWorld + 1))
    {
        tgCM_UT_LF__ST__Free( &g_asPH_Update__Constraint_IMM[enWorld].m_sStack );
    };

    s_enPhysics_State = ETgMODULE_STATE__FREED;
}


/* ---- tgPH_Module_Update ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Module_Update( TgATTRIBUTE_MAYBE_UNUSED TgFLOAT32_C fDT )
{
    TgUN_SCALAR                         uScalar;

    if ((KTgID__INVALID_VALUE != g_tiPH_CN_Module__Paused.m_uiKI) && tgCN_Var_Query_Bool( &uScalar.m_b, g_tiPH_CN_Module__Paused ))
    {
        g_bPH_Module__Paused = uScalar.m_b;
    };

    if ((KTgID__INVALID_VALUE != g_tiPH_CN_Module__Loop_Max.m_uiKI) && tgCN_Var_Query_U64( &uScalar.m_uiE64, g_tiPH_CN_Module__Loop_Max ))
    {
        g_uiPH_Module__Loop_Max = uScalar.m_uiE64;
    };

#if defined(TgBUILD_DEBUG__PHYSICS)

    {
        TgUN_V128                           uVector;

        if ((KTgID__INVALID_VALUE != g_tiPH_Debug_Colour__Body_Enabled.m_uiKI) && tgCN_Var_Query_F32_04_1( &uVector.m_vF32_04_1, g_tiPH_Debug_Colour__Body_Enabled ))
        {
            g_vPH_Debug_Colour__Body_Enabled = uVector.m_vF32_04_1;
        };

        if ((KTgID__INVALID_VALUE != g_tiPH_Debug_Colour__Body_Sleep.m_uiKI) && tgCN_Var_Query_F32_04_1( &uVector.m_vF32_04_1, g_tiPH_Debug_Colour__Body_Sleep ))
        {
            g_vPH_Debug_Colour__Body_Sleep = uVector.m_vF32_04_1;
        };

        if ((KTgID__INVALID_VALUE != g_tiPH_Debug_Colour__Body_Disabled.m_uiKI) && tgCN_Var_Query_F32_04_1( &uVector.m_vF32_04_1, g_tiPH_Debug_Colour__Body_Disabled ))
        {
            g_vPH_Debug_Colour__Body_Disabled = uVector.m_vF32_04_1;
        };

        if ((KTgID__INVALID_VALUE != g_tiPH_Debug_Colour__Form_Enabled.m_uiKI) && tgCN_Var_Query_F32_04_1( &uVector.m_vF32_04_1, g_tiPH_Debug_Colour__Form_Enabled ))
        {
            g_vPH_Debug_Colour__Form_Enabled = uVector.m_vF32_04_1;
        };

        if ((KTgID__INVALID_VALUE != g_tiPH_Debug_Colour__Form_Disabled.m_uiKI) && tgCN_Var_Query_F32_04_1( &uVector.m_vF32_04_1, g_tiPH_Debug_Colour__Form_Disabled ))
        {
            g_vPH_Debug_Colour__Form_Disabled = uVector.m_vF32_04_1;
        };

        if ((KTgID__INVALID_VALUE != g_tiPH_Debug_Colour__Ragdoll.m_uiKI) && tgCN_Var_Query_F32_04_1( &uVector.m_vF32_04_1, g_tiPH_Debug_Colour__Ragdoll ))
        {
            g_vPH_Debug_Colour__Ragdoll = uVector.m_vF32_04_1;
        };
    }

/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif


    /* This function is called inline with the game loop and is responsible for swapping the command buffer and dispatching the current list of commands prior to starting the next
       simulation loop. Starting of simulation is dependent on minimum time between simulation frames having passed, and at least one set of commands that have been dispatched. */


    //TODO Command buffer swap

    {
        PROFILE_START(PH_COMMANDS__CLIENT, tgPH_Module_Update);
        //tgPH__Client__Process_ToClient_Command_Buffer();
        //tgPH__Client__Flush_Deleted_Objects();
        //tgPH__Client__Flush_New_Object_List();
        PROFILE_STOP( PH_COMMANDS__CLIENT, tgPH_Module_Update );
    }

    return (KTgS_OK);
}


/* ---- tgPH_Load_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Load_Config( TgVOID )
{

}


/* ---- tgPH_Save_Config --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Save_Config( TgVOID )
{

}


/* ---- tgPH_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgPH_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enPhysics_State && s_enPhysics_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgPH_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgPH_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enPhysics_State);
}


/* ---- tgPH_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__PHYSICS
TgVOID tgPH_Stats( STg2_Output_P OUT0 )
{
    (void)OUT0;
}
/*# TgS_STAT__PHYSICS */
#endif
