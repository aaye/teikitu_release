/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Constraints.c
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
/*  Generic, Internal and File Local Command Functions                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Constraint_Init_Do_Command ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint_Init_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_CONSTRAINT_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Constraint_P                psCT;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the form, assuming the identifier is still valid. */
    psCT = tgPH_Constraint_Get_Constraint_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psCT)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Constraint ID submitted for init." );
        return;
    };

    TgPARAM_CHECK(KTgID__INVALID_VALUE != psCT->m_tiConstraint.m_uiKI)

    psCT->m_uiUsed_Index = TgSTD_ATOMIC(fetch_add_explicit)( g_axnuiPH_Constraint_Total__Used + psCT->m_tiConstraint.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    g_aapsPH_Constraint_Used[psCT->m_tiConstraint.m_uiWorld][psCT->m_uiUsed_Index] = psCT;
}


/* ---- tgPH_Constraint_Reset_Do_Command ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint_Reset_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_CONSTRAINT_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Constraint_P                psCT;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    TgPARAM_CHECK( uCMD.pCommand );
    (void)nbyCommand_Buffer;

    /* Acquire the form, assuming the identifier is still valid. */
    psCT = tgPH_Constraint_Get_Constraint_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psCT)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Constraint ID submitted for reset." );
        return;
    };

    TgPARAM_CHECK(KTgID__INVALID_VALUE != psCT->m_tiConstraint.m_uiKI)

    tgMM_Set_U08_0x00( psCT, sizeof(STg2_PH_Constraint) );
    psCT->m_tiConstraint.m_uiKI = KTgID__INVALID_VALUE;

    tgCM_UT_LF__ST__Push( &g_asPH_Constraint_Free_Stack[uCMD.pCommand->tiID.m_uiWorld].m_sStack, &psCT->m_sStack_Node );
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Constraint + uCMD.pCommand->tiID.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) ); /* Incremented in the generic Init function. */
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Constraint_Query_Connected ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgPH_Constraint_Query_Connected( TgATTRIBUTE_MAYBE_UNUSED TgPH_BODY_ID_C tiBY0, TgATTRIBUTE_MAYBE_UNUSED TgPH_BODY_ID_C tiBY1 )
{
    return false;
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Macro Functions                                                                                                                                                         */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Body_0_ID,TgPH_BODY_ID,m_tiBY0)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Body_1_ID,TgPH_BODY_ID,m_tiBY1)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Breakable_Compressive_Force,TgFLOAT32,m_fMin)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Breakable_Extension_Force,TgFLOAT32,m_fMax)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Breakable_Max_Torque,TgFLOAT32,m_fMax_Moment)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Static_Coefficient_of_Friction,TgFLOAT32,m_fμs)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Dynamic_Coefficient_of_Friction,TgFLOAT32,m_fμd)
PHYSICS_FUNCTION_ACCESSOR_DEFINITION__SET_DEFER__ASSIGN(Constraint,CONSTRAINT,Breakable,TgBOOL,m_bBreakable)

PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Next_Constraint_ID_For_Body_0,TgPH_CONSTRAINT_ID,m_tiNext_0)
PHYSICS_FUNCTION_QUERY_DEFINITION__ASSIGN(Constraint,CONSTRAINT,Next_Constraint_ID_For_Body_1,TgPH_CONSTRAINT_ID,m_tiNext_1)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Constraint__Init_IMM ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Constraint__Init_IMM( STg2_PH_Constraint_PP ppsCT, ETgPH_CONSTRAINT_C enCT, TgPH_BODY_ID_C tiBY0, TgPH_BODY_ID_C tiBY1 )
{
    STg2_PH_Body_PC                     psBY0 = tgPH_Body_Get_Body_From_ID( tiBY0 );
    STg2_PH_Body_PC                     psBY1 = tgPH_Body_Get_Body_From_ID( tiBY1 );
    TgRSIZE                             uiWorld;
    union
    {
        STg2_PH_Constraint_P                psCT;
        STg2_UT_ST__ST_Node_P               psNode;
        
    }                                   uCT;
    TgUINT_E32                          uiIndex;

    /* Constraints are required to have at least one valid body. The second body may be invalid as the constraint itself could have an absolute anchor point in the World. */
    if((KTgID__INVALID_VALUE == tiBY0.m_uiKI) || (nullptr == psBY0))
    {
        if((KTgID__INVALID_VALUE == tiBY1.m_uiKI) || (nullptr == psBY1))
        {
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Invalid parameters: Both bodies are invalid and / or stale." );
            return KTgE_FAIL;
        }
        else
        {
            uiWorld =  tiBY1.m_uiWorld;
        };
    }
    else
    {
        uiWorld =  tiBY0.m_uiWorld;
        if((KTgID__INVALID_VALUE != tiBY1.m_uiKI) && (nullptr != psBY1))
        {
            TgDIAG(uiWorld == tiBY1.m_uiWorld);
        };
        TgDIAG(uiWorld < ETgPH_MAX_WORLD);
    };

    /* This is an immediate function and so we are not acquiring a constraint through the deferred functions. Directly pop the next free constraint off the stack. */
    uCT.psNode = tgCM_UT_LF__ST__Pop( &g_asPH_Constraint_Free_Stack[uiWorld].m_sStack );
    if (nullptr == uCT.psNode) TgATTRIBUTE_UNLIKELY
    {
        TgPH_WORLD_ID_C                     tiWorld = g_asPH_World[uiWorld].m_tiWorld;

        /* It is ASSUMED that all new / delete operations for a World are done on a single thread, and not overlapped with any of the deferred commands. There are no execution
           guards on this function to prevent multiple threads running it concurrently. That would not be good. */
        uCT.psCT = tgPH_Constraint_Grow_Commit_List( tiWorld );
        if (nullptr == uCT.psNode) TgATTRIBUTE_UNLIKELY
        {
            TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unable to create a new constraint." );
            return (KTgE_FAIL);
        };
    };

    uiIndex = (TgUINT_E32)(uCT.psCT - g_aasPH_Constraint[uiWorld]);
    tgPH_CONSTRAINT_ID_Init( &uCT.psCT->m_tiConstraint, uiIndex, (TgUINT_E08)uiWorld, KTgPH_MAX_SCENE );
    uCT.psCT->m_tiBY0 = tiBY0;
    uCT.psCT->m_tiBY1 = tiBY1;
    uCT.psCT->m_enConstraint = enCT;

    *ppsCT = uCT.psCT;

    /* Add this Constraint to be added to Body's Constraint linked list and to the World. */
    tgCM_UT_LF__ST__Push( &g_asPH_Update__Constraint_IMM[uiWorld].m_sStack, uCT.psNode );

    return KTgS_OK;
}


/* ---- tgPH_Constraint__Bind_IMM ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: WRITES to Bodies, Constraints                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint__Bind_IMM( TgPH_WORLD_ID_C tiWorld )
{
    union
    {
        STg2_PH_Constraint_P                psCT;
        STg2_UT_ST__ST_Node_P               psNode;
        
    }                                   uCT;

    uCT.psNode = tgCM_UT_LF__ST__Pop( &g_asPH_Update__Constraint_IMM[tiWorld.m_uiI].m_sStack );
    while (uCT.psNode)
    {
        STg2_PH_Body_PC                     psBY0 = tgPH_Body_Get_Body_From_ID( uCT.psCT->m_tiBY0 );
        STg2_PH_Body_PC                     psBY1 = tgPH_Body_Get_Body_From_ID( uCT.psCT->m_tiBY1 );

        /* IMPORTANT: This is the primary data synchronization to register a new constraint into the world. It is ASSUMED that all new / delete operations for a World are done on a
        single thread, and not overlapped with any of the deferred commands. Thus, there are not synchronization guards on either the Init or Free functions. */

        uCT.psCT->m_uiUsed_Index = TgSTD_ATOMIC(fetch_add_explicit)( g_axnuiPH_Constraint_Total__Used + tiWorld.m_uiI, 1, TgSTD_MEMORY_ORDER(relaxed) );
        g_aapsPH_Constraint_Used[tiWorld.m_uiI][uCT.psCT->m_uiUsed_Index] = uCT.psCT; /* Assign the constraint into the world used array. */
        TgSTD_ATOMIC(fetch_add_explicit)( g_axnuiPH_Constraint + tiWorld.m_uiI, 1, TgSTD_MEMORY_ORDER(relaxed) );
        TgSTD_ATOMIC(fetch_add_explicit)( g_aaxnuiPH_Constraint_Total__Used_By_Type[tiWorld.m_uiI] + uCT.psCT->m_enConstraint, 1, TgSTD_MEMORY_ORDER(relaxed) );

        /* Add the constraint to the first body's link list. */
        if (nullptr != psBY0)
        {
            uCT.psCT->m_tiNext_0 = psBY0->m_tiCT;
            psBY0->m_tiCT = uCT.psCT->m_tiConstraint;
        };

        /* Add the constraint to the second body's link list. */
        if (nullptr != psBY1)
        {
            uCT.psCT->m_tiNext_1 = psBY1->m_tiCT;
            psBY1->m_tiCT = uCT.psCT->m_tiConstraint;
        };

        uCT.psNode = tgCM_UT_LF__ST__Pop( &g_asPH_Update__Constraint_IMM[tiWorld.m_uiI].m_sStack );
    };
}


/* ---- tgPH_Constraint__Free_IMM ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* SYNC: WRITES to Bodies, Constraints                                                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint__Free_IMM( TgPH_CONSTRAINT_ID_C tiCT, ETgPH_CONSTRAINT_C enCT )
{
    STg2_PH_Constraint_P                psCT0, psCT1;
    STg2_PH_Body_P                      psBY0, psBY1;
    TgRSIZE                             uiIndex;

    if (tiCT.m_uiWorld >= ETgPH_MAX_WORLD)
        return;

    if (tiCT.m_uiI >= g_anuiPH_Constraint_Total_Commit[tiCT.m_uiWorld])
        return;

    psCT0  = tgPH_Constraint_Get_Constraint_From_ID( tiCT );
    if (nullptr == psCT0)
        return;

    psBY0 = tgPH_Body_Get_Body_From_ID( psCT0->m_tiBY0 );
    psBY1 = tgPH_Body_Get_Body_From_ID( psCT0->m_tiBY1 );

    /* Need to remove this constraint from the bodies linked lists. */
    if (nullptr != psBY0)
    {
        if (psBY0->m_tiCT.m_uiKI == tiCT.m_uiKI)
        {
            psBY0->m_tiCT.m_uiKI = psCT0->m_tiNext_0.m_uiKI;
        }
        else
        {
            psCT1  = tgPH_Constraint_Get_Constraint_From_ID( psBY0->m_tiCT );
            while (nullptr != psCT1)
            {
                /* Purpose is to remove this Constraint from the first Body of this Constraint. Check for this body in the current constraint and continue down the link list.
                   The body could be either BY0 or BY1 in each constraint that we iterate. If the body is not found the linked list is corrupted. */

                if (psCT1->m_tiBY0.m_uiKI == psCT0->m_tiBY0.m_uiKI)
                {
                    if (psCT1->m_tiNext_0.m_uiKI == tiCT.m_uiKI)
                    {
                        psCT1->m_tiNext_0.m_uiKI = psCT0->m_tiNext_0.m_uiKI;
                        break;
                    };
                    psCT1  = tgPH_Constraint_Get_Constraint_From_ID( psCT1->m_tiNext_0 );
                    continue;
                };

                if (psCT1->m_tiBY1.m_uiKI == psCT0->m_tiBY0.m_uiKI)
                {
                    if (psCT1->m_tiNext_1.m_uiKI == tiCT.m_uiKI)
                    {
                        psCT1->m_tiNext_1.m_uiKI = psCT0->m_tiNext_0.m_uiKI;
                        break;
                    };
                    psCT1  = tgPH_Constraint_Get_Constraint_From_ID( psCT1->m_tiNext_1 );
                    continue;
                };

                break; /* Badness - the linked lists have been corrupted. Indeterminate behaviour. */
            };
        };
    };

    if (nullptr != psBY1)
    {
        if (psBY1->m_tiCT.m_uiKI == tiCT.m_uiKI)
        {
            psBY1->m_tiCT.m_uiKI = psCT0->m_tiNext_1.m_uiKI;
        }
        else
        {
            psCT1  = tgPH_Constraint_Get_Constraint_From_ID( psBY1->m_tiCT );
            while (nullptr != psCT1)
            {
                /* Purpose is to remove this Constraint from the first Body of this Constraint. Check for this body in the current constraint and continue down the link list.
                   The body could be either BY0 or BY1 in each constraint that we iterate. If the body is not found the linked list is corrupted. */

                if (psCT1->m_tiBY0.m_uiKI == psCT0->m_tiBY1.m_uiKI)
                {
                    if (psCT1->m_tiNext_0.m_uiKI == tiCT.m_uiKI)
                    {
                        psCT1->m_tiNext_0.m_uiKI = psCT0->m_tiNext_0.m_uiKI;
                        break;
                    };
                    psCT1  = tgPH_Constraint_Get_Constraint_From_ID( psCT1->m_tiNext_0 );
                    continue;
                };

                if (psCT1->m_tiBY1.m_uiKI == psCT0->m_tiBY1.m_uiKI)
                {
                    if (psCT1->m_tiNext_1.m_uiKI == tiCT.m_uiKI)
                    {
                        psCT1->m_tiNext_1.m_uiKI = psCT0->m_tiNext_0.m_uiKI;
                        break;
                    };
                    psCT1  = tgPH_Constraint_Get_Constraint_From_ID( psCT1->m_tiNext_1 );
                    continue;
                };

                break; /* Badness - the linked lists have been corrupted. Indeterminate behaviour. */
            };
        };
    };

    /* IMPORTANT: This is the primary data synchronization to remove a  constraint from the world. It is ASSUMED that all new / delete operations for a World are done on a
       single thread, and not overlapped with any of the deferred commands. Thus, there are not synchronization guards on either the Init or Free functions. */

    uiIndex = TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Constraint_Total__Used + tiCT.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    g_aapsPH_Constraint_Used[tiCT.m_uiWorld][uiIndex - 1]->m_uiUsed_Index = psCT0->m_uiUsed_Index;
    g_aapsPH_Constraint_Used[tiCT.m_uiWorld][psCT0->m_uiUsed_Index] = g_aapsPH_Constraint_Used[tiCT.m_uiWorld][uiIndex - 1];
    TgSTD_ATOMIC(fetch_sub_explicit)( g_axnuiPH_Constraint + tiCT.m_uiWorld, 1, TgSTD_MEMORY_ORDER(relaxed) );
    TgSTD_ATOMIC(fetch_sub_explicit)( g_aaxnuiPH_Constraint_Total__Used_By_Type[tiCT.m_uiWorld] + enCT, 1, TgSTD_MEMORY_ORDER(relaxed) );

    /* Reset the data to zero or its equivalents and return it to the free stack. */

    tgMM_Set_U08_0x00( psCT0, sizeof(STg2_PH_Constraint) );
    tgCM_UT_LF__ST__Push( &g_asPH_Constraint_Free_Stack[tiCT.m_uiWorld].m_sStack, &psCT0->m_sStack_Node );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Constraint_Init_Internal ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Constraint_Init_Internal( TgVOID )
{
    TgRSIZE                             uiIndex0, uiIndex1;

    for (uiIndex0 = 0; uiIndex0 < ETgPH_MAX_WORLD; ++uiIndex0)
    {
        for (uiIndex1 = 0; uiIndex1 < ETgPH_CONSTRAINT__MAX; ++uiIndex1)
        {
            TgSTD_ATOMIC(store_explicit)( g_aaxnuiPH_Constraint_Total__Used_By_Type[uiIndex0] + uiIndex1, 0, TgSTD_MEMORY_ORDER(relaxed) );
        }
    }

#if defined(TgBUILD_FEATURE__CLIENT)
    g_anuiPH_Constraint_Increase_Commit[ETgPH_WORLD__CLIENT_FX] = 10;
    g_anuiPH_Constraint_Total_Commit[ETgPH_WORLD__CLIENT_FX] = 0;
    g_anuiPH_Constraint_Total_Reserve[ETgPH_WORLD__CLIENT_FX] = 10000;

    g_anuiPH_Constraint_Increase_Commit[ETgPH_WORLD__CLIENT_UI] = 10;
    g_anuiPH_Constraint_Total_Commit[ETgPH_WORLD__CLIENT_UI] = 0;
    g_anuiPH_Constraint_Total_Reserve[ETgPH_WORLD__CLIENT_UI] = 10000;
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

#if defined(TgBUILD_FEATURE__SERVER)
    g_anuiPH_Constraint_Increase_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 10;
    g_anuiPH_Constraint_Total_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 0;
    g_anuiPH_Constraint_Total_Reserve[ETgPH_WORLD__SERVER_DEFAULT] = 100000;
/*# defined(TgBUILD_FEATURE__SERVER) */
#endif
}






/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgBUILD_DEBUG__PHYSICS)

/* ---- tgPH_Constraint_Validate ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Constraint_Validate( STg2_Output_PC psOUT, TgPH_CONSTRAINT_ID_C tiWorld )
{
    (void)psOUT;
    (void)tiWorld;

}

/*# defined(TgBUILD_DEBUG__PHYSICS) */
#endif


