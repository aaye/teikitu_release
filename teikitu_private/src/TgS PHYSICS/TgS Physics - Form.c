/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Form.c
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

/* ---- Form Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Form,FORM,Category,TgUINT_E64,m_uiCategory)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Form,FORM,Collide,TgUINT_E64,m_uiCollide)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Form,FORM,Enabled,TgBOOL,m_bEnabled)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Form,FORM,Update_BA,TgBOOL,m_bUpdate_BA)


/* ---- Form Geometry ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Form,FORM,Primitive,ETgPRIMITIVE,m_psCollision->m_enPM)
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Form,FORM,Material_ID,TgPH_MATERIAL_ID,m_psCollision->m_tiMaterial)
PHYSICS_FUNCTION_QUERY__DEFINITION_ASSIGN(Form,FORM,Last_Position,TgVEC_F32_04_1,m_vPos_Last_Valid_W)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_CUSTOM(Form,FORM,Position,TgVEC_F32_04_1,m_vPos_W,
    psForm->m_vPos_W = uCMD.pCommand->Val;
    psForm->m_vPos_Last_Valid_W = uCMD.pCommand->Val;
    //TODO Update Bounding Box, Sweep Information
)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_SIMPLE(Form,FORM,BA,TgBOXAA_F32_04,m_sBA)


/* ---- Form Body and Transform -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- Simple Accessors --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

PHYSICS_FUNCTION_QUERY__DEFINITION_COPY(Form,FORM,Next_Form_ID,TgPH_FORM_ID,m_tiNext)
PHYSICS_FUNCTION_QUERY__DEFINITION_COPY(Form,FORM,Final,TgVEC_F32_04_3,m_mFinal)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_CUSTOM(Form,FORM,Body_ID,TgPH_BODY_ID,m_tiBody,
    TgPARAM_CHECK( uCMD.pCommand->Val.m_uiI < g_anuiPH_Body_Total_Commit[uCMD.pCommand->Val.m_uiWorld] );

    /* If the form is already connected to a body, get a pointer to this body. */
    if (KTgID__INVALID_VALUE != psForm->m_tiBody.m_uiKI)
    {
        if (TgFAILED(tgPH_Body_Remove_Form( uCMD.pCommand->tiID )))
        {
            return;
        };
    };

    /* Get a pointer to the body identified by the parameter body id. */
    if (KTgID__INVALID_VALUE != uCMD.pCommand->Val.m_uiKI)
    {
        if (TgFAILED(tgPH_Body_Add_Form( uCMD.pCommand->Val, uCMD.pCommand->tiID )))
        {
            return;
        };
    };
)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Form,FORM,Sweep_ID,TgPNS_OBJECT_ID,m_tiPnS)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_COPY_SIMPLE(Form,FORM,Local,TgVEC_F32_04_3,m_mLocal)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Form,FORM,Scale,TgVEC_F32_04_1,m_vScale)
PHYSICS_FUNCTION_ACCESSOR__DEFINITION_ASSIGN_SIMPLE(Form,FORM,Colour,TgVEC_F32_04_1,m_vDebug_Colour)




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Form_Init_Internal -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Update_From_Body( TgPH_FORM_ID_C tiForm )
{
    (void)tiForm;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgPH_Module_Form_Init_Internal ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Module_Form_Init_Internal( TgVOID )
{
#if defined(TgBUILD_FEATURE__CLIENT)
    g_anuiPH_Form_Increase_Commit[ETgPH_WORLD__CLIENT_FX] = 10;
    g_anuiPH_Form_Total_Commit[ETgPH_WORLD__CLIENT_FX] = 0;
    g_anuiPH_Form_Total_Reserve[ETgPH_WORLD__CLIENT_FX] = 10000;

    g_anuiPH_Form_Increase_Commit[ETgPH_WORLD__CLIENT_UI] = 10;
    g_anuiPH_Form_Total_Commit[ETgPH_WORLD__CLIENT_UI] = 0;
    g_anuiPH_Form_Total_Reserve[ETgPH_WORLD__CLIENT_UI] = 10000;
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

#if defined(TgBUILD_FEATURE__SERVER)
    g_anuiPH_Form_Increase_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 10;
    g_anuiPH_Form_Total_Commit[ETgPH_WORLD__SERVER_DEFAULT] = 0;
    g_anuiPH_Form_Total_Reserve[ETgPH_WORLD__SERVER_DEFAULT] = 100000;
/*# defined(TgBUILD_FEATURE__SERVER) */
#endif
}


/* ---- tgPH_Form_Init_Do_Command ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Init_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    (void)pCommand_Buffer;
    (void)nbyCommand_Buffer;
}


/* ---- tgPH_Form_Reset_Do_Command ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Reset_Do_Command( TgVOID_CPC pCommand_Buffer, TgRSIZE_C nbyCommand_Buffer )
{
    (void)pCommand_Buffer;
    (void)nbyCommand_Buffer;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Debug Functions                                                                                                                                                       */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS

/* ---- tgPH_Form_Validate ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPH_Form_Validate( STg2_Output_PC psOUT, TgPH_FORM_ID_C tiWorld )
{
    (void)psOUT;
    (void)tiWorld;

}

//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif


