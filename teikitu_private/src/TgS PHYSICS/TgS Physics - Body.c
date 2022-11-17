/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Body.c
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

/* ---- tgPH_Body_Add_Force_At_Location ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Body_Add_Force_At_Location( TgPH_BODY_ID_C tiBY0, TgVEC_F32_04_1_C vF0, TgVEC_F32_04_1_C vS0 )
{
    STg2_PH_Body_PC                     psBody = tgPH_Body_Get_Body_From_ID( tiBY0 );

    if (nullptr == psBody)
    {
        return (KTgE_FAIL);
    }
    else
    {
        TgVEC_F32_04_1_C                    v00 = tgMH_SUB_F32_04_1( vS0, psBody->m_sMass.m_vCG );
        TgVEC_F32_04_1_C                    v01 = tgMH_CX_F32_04_1( v00, vF0 );

        psBody->m_vPF = tgMH_ADD_F32_04_1( psBody->m_vPF, vF0 );
        psBody->m_vPT = tgMH_ADD_F32_04_1( psBody->m_vPT, v01 );

        psBody->m_fDisable_Timer = 0.0F;

        return (KTgS_OK);
    }
}


/* ---- tgPH_Body_Apply_Drag ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Body_Apply_Drag( TgPH_BODY_ID_C tiBY0, TgFLOAT32_C fDrag )
{
    STg2_PH_Body_PC                     psBody = tgPH_Body_Get_Body_From_ID( tiBY0 );

    if ((nullptr == psBody) || !(fDrag >= 0.0F) || !(fDrag <= 1.0F) )
    {
        TgPARAM_CHECK( (fDrag >= 0.0F) && (fDrag <= 1.0F) );
        return (KTgE_FAIL);
    }
    else
    {
        TgVEC_F32_04_1_C                    vDrag = tgMH_SET1_F32_04_1( fDrag );

        psBody->m_vLV = tgMH_MUL_F32_04_1( vDrag, psBody->m_vLV );
        psBody->m_vAV = tgMH_MUL_F32_04_1( vDrag, psBody->m_vAV );

        psBody->m_fDisable_Timer = 0.0F;

        return (KTgS_OK);
    }
}


/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Body,BODY,First_Form_ID,TgPH_FORM_ID,m_tiForm)
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Body,BODY,First_Constraint_ID,TgPH_CONSTRAINT_ID,m_tiConstraint)




/* ---- Body Geometry ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Position,TgVEC_F32_04_1,m_vPos_W) // TODO Update Forms or mark dirty, set last position, clear tunnelling
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_SIMPLE(Body,BODY,Transform,TgVEC_F32_04_3,m_mRot_W) // TODO Update Forms or mark dirty
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Rotation,TgVEC_F32_04_1,m_vRot_W) // TODO Update Forms or mark dirty

PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Body,BODY,Last_Position,TgVEC_F32_04_1,m_vPos_Last_Valid_W)




/* ---- Body Mass ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_QUERY__DEFINITION_COPY(Body,BODY,Moment_Of_Inertia,TgVEC_F32_04_3,m_sMass.m_mMOI)
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Body,BODY,Centre_Of_Gravity,TgVEC_F32_04_1,m_sMass.m_vCG)
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Body,BODY,Mass,TgVEC_F32_04_1,m_sMass.m_uMass.m_vF32_04_1)
PHYSICS_FUNCTION_QUERY__DEFINITION_COPY(Body,BODY,Inverse_Moment_Of_Inertia,TgVEC_F32_04_3,m_sMass.m_mInv_MOI) 
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Body,BODY,Inverse_Mass,TgVEC_F32_04_1,m_sMass.m_uInv_Mass.m_vF32_04_1)




/* ---- Body Linear Velocity and Force ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Linear_Velocity,TgVEC_F32_04_1,m_vLV) // TODO Reset sleep timer
PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Force,TgVEC_F32_04_1,m_vXF) // TODO Reset sleep timer
PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Dampening_Force,TgVEC_F32_04_1,m_vXF) // TODO Reset sleep timer
PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Persistent_Force,TgVEC_F32_04_1,m_vPF) // TODO Reset sleep timer
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Linear_Velocity,TgVEC_F32_04_1,m_vLV) // TODO Reset sleep timer
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Persistent_Force,TgVEC_F32_04_1,m_vPF) // TODO Reset sleep timer
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN_CUSTOM_INTERNAL(Body,BODY,External_Force,TgVEC_F32_04_1,*pVal = tgMH_ADD_F32_04_1(psBody->m_vPF,psBody->m_vXF);) // TODO Reset sleep timer




/* ---- Body Angular Velocity and Force ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Angular_Velocity,TgVEC_F32_04_1,m_vAV) // TODO Reset sleep timer
PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Torque,TgVEC_F32_04_1,m_vXT) // TODO Reset sleep timer
PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Persistent_Torque,TgVEC_F32_04_1,m_vPT) // TODO Reset sleep timer
PHYSICS_FUNCTION_ADD__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Dampening_Torque,TgVEC_F32_04_1,m_vXT) // TODO Reset sleep timer
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Angular_Velocity,TgVEC_F32_04_1,m_vAV) // TODO Reset sleep timer
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Persistent_Torque,TgVEC_F32_04_1,m_vPT) // TODO Reset sleep timer
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN_CUSTOM_INTERNAL(Body,BODY,External_Torque,TgVEC_F32_04_1,*pVal = tgMH_ADD_F32_04_1(psBody->m_vPT,psBody->m_vXT);) // TODO Reset sleep timer




/* ---- Body Simulation Configuration -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Tunneling,TgVEC_F32_04_1,m_vTunneling)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Force_Field_Factor,TgVEC_F32_04_1,m_vForce_Field_Factor)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Time_Factor,TgVEC_F32_04_1,m_vTime_Factor)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Disable_Timer,TgFLOAT32,m_fDisable_Timer)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Enabled,TgBOOL,m_bEnabled)

PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Body,BODY,Ragdoll,TgBOOL,m_bRagdoll)




/* ---- Body User Functions ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,CalcFM_FCN,TgCALCFM_FCN,m_pfnCalcFM)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Contact_FCN,TgCONTACT_FCN,m_pfnContact)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Moved_FCN,TgMOVED_FCN,m_pfnMoved)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Body,BODY,Context,TgUINT_PTR,m_uiContext)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Body_Add_Form ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Body_Add_Form( TgPH_BODY_ID_C tiBY0, TgPH_FORM_ID_C tiFM0 )
{
    STg2_PH_Body_P                      psBody;
    STg2_PH_Form_P                      psFM0;

    psFM0 = tgPH_Form_Get_Form_From_ID( tiFM0 );
    if (nullptr == psFM0)
    {
        return (KTgE_FAIL);
    };

    /* Forms can only belong to a single body at a time */
    if (KTgID__INVALID_VALUE != psFM0->m_tiBody.m_uiKI)
    {
        return (KTgE_FAIL);
    };

    psBody = tgPH_Body_Get_Body_From_ID( tiBY0 );
    if (nullptr == psBody)
    {
        return (KTgE_FAIL);
    };

    /* Add the form into the body's form list. */
    psFM0->m_tiBody = tiBY0;
    psFM0->m_tiNext = psBody->m_tiForm;
    psBody->m_tiForm = tiFM0;

    tgPH_Form_Update_From_Body( tiFM0 );
    return (KTgS_OK);
}


/* ---- tgPH_Body_Remove_Form ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPH_Body_Remove_Form( TgPH_FORM_ID_C tiFM0 )
{
    STg2_PH_Form_PC                     psFM0 = tgPH_Form_Get_Form_From_ID( tiFM0 );
    TgPH_FORM_ID                        tiFM1, tiFM2;

    if (TgSUCCEEDED(tgPH_Body_Query_First_Form_ID( &tiFM1, psFM0->m_tiBody )))
    {
        if (tiFM0.m_uiKI == tiFM1.m_uiKI)
        {
            STg2_PH_Body_PC                     psBody = tgPH_Body_Get_Body_From_ID( psFM0->m_tiBody );

            if (nullptr == psBody)
            {
                return (KTgE_FAIL);
            };

            if (nullptr == psFM0)
            {
                psBody->m_tiForm.m_uiKI = KTgID__INVALID_VALUE;
                return (KTgS_OK);
            };

            psFM0->m_tiBody.m_uiKI = KTgID__INVALID_VALUE;
            psBody->m_tiForm.m_uiKI = psFM0->m_tiNext.m_uiKI;
        }
        else
        {
            for (;TgSUCCEEDED(tgPH_Form_Query_Next_Form_ID( &tiFM2, tiFM1 )); tiFM1.m_uiKI = tiFM2.m_uiKI)
            {
                if (tiFM0.m_uiKI == tiFM2.m_uiKI)
                {
                    STg2_PH_Form_PC                     psFM1 = tgPH_Form_Get_Form_From_ID( tiFM1 );
                    STg2_PH_Form_PC                     psFM2 = tgPH_Form_Get_Form_From_ID( tiFM2 );

                    if ((nullptr == psFM1) || (nullptr == psFM2))
                    {
                        return (KTgE_FAIL);
                    };

                    psFM1->m_tiNext.m_uiKI = psFM2->m_tiNext.m_uiKI;
                    psFM2->m_tiNext.m_uiKI = KTgID__INVALID_VALUE;
                }
            };
        }
    };

    tgPH_Form_Update_From_Body( tiFM0 );
    return (KTgS_OK);
}


/* ---- tgPH_Body_Contact_Default ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Contact_Default( TgPH_BODY_ID_C UNUSED_PARAM tiBY0, TgFLOAT32_C UNUSED_PARAM fΔt )
{
}


/* ---- tgPH_Body_Move_Default --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Move_Default( TgPH_BODY_ID_C tiBY0, TgFLOAT32_C UNUSED_PARAM fΔt )
{
    TgPH_FORM_ID                        tiFM0;

    if (TgSUCCEEDED(tgPH_Body_Query_First_Form_ID( &tiFM0, tiBY0 )))
    {
        do {
            tgPH_Form_Update_From_Body( tiFM0 );
        }
        while (TgSUCCEEDED(tgPH_Form_Query_Next_Form_ID( &tiFM0, tiFM0 )));
    };

}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Body_Init_Internal ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Body_Init_Internal( TgVOID )
{
#if defined(TgBUILD_FEATURE__CLIENT)
    g_anuiPH_Body_Increase_Commit[ETgPH_WORLD__CLIENT_FX] = 10;
    g_anuiPH_Body_Total_Commit[ETgPH_WORLD__CLIENT_FX] = 0;
    g_anuiPH_Body_Total_Reserve[ETgPH_WORLD__CLIENT_FX] = 1000;

    g_anuiPH_Body_Increase_Commit[ETgPH_WORLD__CLIENT_UI] = 10;
    g_anuiPH_Body_Total_Commit[ETgPH_WORLD__CLIENT_UI] = 0;
    g_anuiPH_Body_Total_Reserve[ETgPH_WORLD__CLIENT_UI] = 1000;
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

#if defined(TgBUILD_FEATURE__SERVER)
    g_anuiPH_Body_Increase_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 10;
    g_anuiPH_Body_Total_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 0;
    g_anuiPH_Body_Total_Reserve[ETgPH_WORLD__SERVER_DEFAULT] = 10000;
/*# defined(TgBUILD_FEATURE__SERVER) */
#endif
}


/* ---- tgPH_Body_Init_Do_Command ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Init_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_BODY_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Body_P                      psBody;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    (void)nbyCommand_Buffer;

    /* Acquire the body, assuming the identifier is still valid. */
    psBody = tgPH_Body_Get_Body_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psBody)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Body ID submitted for reset." );
        return;
    };

    TgPARAM_CHECK(KTgID__INVALID_VALUE != psBody->m_tiBody.m_uiKI )

    tgPH_Mass_Reset( &psBody->m_sMass );
    tgMH_CLI_F32_04_3( &psBody->m_mRot_W );
    psBody->m_vRot_W = KTgUNIT_Z_V128.m_vF32_04_1;
    psBody->m_vForce_Field_Factor = tgMH_SET1_F32_04_1( 1.0F );
    psBody->m_vTime_Factor = tgMH_SET1_F32_04_1( 1.0F );

    psBody->m_uiUsed_Index = g_anuiPH_Body_Total__Used[psBody->m_tiBody.m_uiWorld];
    ++g_anuiPH_Body_Total__Used[psBody->m_tiBody.m_uiWorld];
    g_aapsPH_Body_Used[psBody->m_tiBody.m_uiWorld][psBody->m_uiUsed_Index] = psBody;
}


/* ---- tgPH_Body_Reset_Do_Command ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Body_Reset_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    typedef struct {
        TgPH_BODY_ID tiID;
    } STg2_FCN_Command;
    union { STg2_FCN_Command const * const pCommand; TgVOID_CPC pCommand_Buffer; } const uCMD = { .pCommand_Buffer = pCommand_Buffer };

    STg2_PH_Body_P                      psBody;
    TgPH_FORM_ID                        tiFM0;
    TgPH_CONSTRAINT_ID                  tiCT0;

    TgPARAM_CHECK( sizeof( STg2_FCN_Command ) == nbyCommand_Buffer );
    (void)nbyCommand_Buffer;

    /* Acquire the body, assuming the identifier is still valid. */
    psBody = tgPH_Body_Get_Body_From_ID( uCMD.pCommand->tiID );

    if (nullptr == psBody)
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Stale Body ID submitted for reset." );
        return;
    };

    /* Remove itself from other dependencies (form, constraints). */
    if (TgSUCCEEDED(tgPH_Body_Query_First_Constraint_ID( &tiCT0, uCMD.pCommand->tiID )))
    {
        TgPH_CONSTRAINT_ID                  tiCT1;
        STg2_PH_Constraint_P                psConstraint;

        do {
            psConstraint = tgPH_Constraint_Get_Constraint_From_ID( tiCT0 );
            if (nullptr == psConstraint)
                break;

            tiCT1.m_uiKI = KTgID__INVALID_VALUE;

            if (psConstraint->m_tiBody_0.m_uiKI == uCMD.pCommand->tiID.m_uiKI)
            {
                tgPH_Constraint_Query_Next_Constraint_ID_For_Body_0( &tiCT1, tiCT0 );
                tgPH_Constraint_Reset( tiCT0 );
                tiCT0.m_uiKI = tiCT1.m_uiKI;
            }

            if (psConstraint->m_tiBody_1.m_uiKI == uCMD.pCommand->tiID.m_uiKI)
            {
                tgPH_Constraint_Query_Next_Constraint_ID_For_Body_1( &tiCT1, tiCT0 );
                tgPH_Constraint_Reset( tiCT0 );
                tiCT0.m_uiKI = tiCT1.m_uiKI;
            }

        } while (tiCT0.m_uiKI != KTgID__INVALID_VALUE);
    };

    if (TgSUCCEEDED(tgPH_Body_Query_First_Form_ID( &tiFM0, uCMD.pCommand->tiID )))
    {
        TgPH_FORM_ID                        tiFM1;

        do {
            tgPH_Form_Query_Next_Form_ID( &tiFM1, tiFM0 );
            tgPH_Form_Reset( tiFM0 );
            tiFM1.m_uiKI = tiFM0.m_uiKI;
        } while (tiFM0.m_uiKI != KTgID__INVALID_VALUE);
    };

    /* Reset the data to zero or its equivalents. */

    tgMM_Set_U08_0x00( psBody, sizeof(STg2_PH_Body) );
    psBody->m_tiBody.m_uiKI = KTgID__INVALID_VALUE;

    tgCM_UT_LF__ST__Push( &g_asPH_Body_Free_Stack[uCMD.pCommand->tiID.m_uiWorld].m_sStack, &psBody->m_sStack_Node );
    atomic_fetch_sub( g_axnuiPH_Body + uCMD.pCommand->tiID.m_uiWorld, 1 );
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Body_Validate ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
TgVOID tgPH_Body_Validate( STg2_Output_PC psOUT, TgPH_BODY_ID_C tiBY )
{
    (void)psOUT;
    (void)tiBY;

}
//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif
