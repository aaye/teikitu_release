/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - LA Ring Buffer SRSW.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_LA_RING_BUFFER_SRSW_INL)
#define TGS_COMMON_UTIL_MT_LA_RING_BUFFER_SRSW_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_LF__LA_RB_SRSW__Init --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__LA_RB_SRSW__Init( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW, TgRSIZE_C uiMaxSize )
{
    atomic_store( &psLA_RB_SRSW->m_nuiPushed, 0 );
    atomic_store( &psLA_RB_SRSW->m_nuiPopped, 0 );
    psLA_RB_SRSW->m_uiMaxSize = uiMaxSize;
}


/* ---- tgCM_UT_LF__LA_RB_SRSW__Query_Used_Size ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_LF__LA_RB_SRSW__Query_Used_Size( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW )
{
    return (atomic_load( &psLA_RB_SRSW->m_nuiPushed ) - atomic_load( &psLA_RB_SRSW->m_nuiPopped ));
}


/* ---- tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_LF__LA_RB_SRSW__Query_Free_Size( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW )
{
    return (tgCM_UT_LF__LA_RB_SRSW__Query_Max_Size( psLA_RB_SRSW ) - tgCM_UT_LF__LA_RB_SRSW__Query_Used_Size( psLA_RB_SRSW ));
}


/* ---- tgCM_UT_LF__LA_RB_SRSW__Query_Max_Size ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_LF__LA_RB_SRSW__Query_Max_Size( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW )
{
    return ((TgUINT_F32)psLA_RB_SRSW->m_uiMaxSize);
}


/* ---- tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_LF__LA_RB_SRSW__Push_Next_Index( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW )
{
    return (atomic_load( &psLA_RB_SRSW->m_nuiPushed ) % tgCM_UT_LF__LA_RB_SRSW__Query_Max_Size( psLA_RB_SRSW ));
}


/* ---- tgCM_UT_LF__LA_RB_SRSW__Push_Commit -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__LA_RB_SRSW__Push_Commit( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW )
{
    atomic_thread_fence( cxx__memory_order_seq_cst );
    atomic_fetch_add( &psLA_RB_SRSW->m_nuiPushed, 1 );
}


/* ---- tgCM_UT_LF__LA_RB_SRSW__Pop_Next_Index ----------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_LF__LA_RB_SRSW__Pop_Next_Index( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW )
{
    return (atomic_load( &psLA_RB_SRSW->m_nuiPopped ) % tgCM_UT_LF__LA_RB_SRSW__Query_Max_Size( psLA_RB_SRSW ) );
}


/* ---- tgCM_UT_LF__LA_RB_SRSW__Pop_Commit --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_LF__LA_RB_SRSW__Pop_Commit( STg2_UT_LF__LA_RB_SRSW_PCU NONULL psLA_RB_SRSW )
{
    atomic_thread_fence( cxx__memory_order_seq_cst );
    atomic_fetch_add( &psLA_RB_SRSW->m_nuiPopped, 1 );
}


/* =============================================================================================================================================================================== */
#endif
