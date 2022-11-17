/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (POSIX) Common - STg1_MT_MX.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if TgCOMPILE__THREAD


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgPM_MT_MX_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPM_MT_MX_Init( STg1_MT_MX_PCU psMX, TgATTRIBUTE_MAYBE_UNUSED TgOSCHAR_CPCU mbzName )
{
    TgSINT_E32                          iRet;
    pthread_mutexattr_t                 sMutexAttrib;

    pthread_mutexattr_init( &sMutexAttrib );
    pthread_mutexattr_settype( &sMutexAttrib, PTHREAD_MUTEX_RECURSIVE );
    iRet = pthread_mutex_init( &psMX->m_hMutex, &sMutexAttrib);
    TgVERIFY(0 == iRet);
    return (0 != iRet ? KTgE_FAIL : KTgS_OK);
}


/* ---- tgPM_MT_MX_Free ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_MX_Free( STg1_MT_MX_PCU psMX )
{
    TgVERIFY(0 <= pthread_mutex_destroy( &psMX->m_hMutex ));
}


/* ---- tgPM_MT_MX_Wait_Block ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_MX_Wait_Block( STg1_MT_MX_PCU psMX )
{
    TgVERIFY(0 == pthread_mutex_lock( &psMX->m_hMutex ));
}


/* ---- tgPM_MT_MX_Wait ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPM_MT_MX_Wait( STg1_MT_MX_PCU psMX )
{
    TgSINT_E32                          iRet;
    
    iRet = pthread_mutex_trylock( &psMX->m_hMutex );
    return (0 != iRet ? KTgE_FAIL : KTgS_OK);
}


/* ---- tgPM_MT_MX_Release ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgPM_MT_MX_Release( STg1_MT_MX_PCU psMX )
{
    TgVERIFY(0 == pthread_mutex_unlock( &psMX->m_hMutex ));
}


/* =============================================================================================================================================================================== */
#endif