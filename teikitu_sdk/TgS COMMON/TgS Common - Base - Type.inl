/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_TYPES_INL)
#define TGS_COMMON_BASE_TYPES_INL
#pragma once

#include "TgS COMMON/TgS Common - Base - Type [IO].inl"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgPath_Check_File_Block_With_Assert -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgPath_Check_File_Block_With_Assert( STg2_File_Block_CPCU psFB )
{
    TgERROR(TgFOURCC( 'T', 'G', 'S', 'F' ) == psFB->m_uiFourCC_Tool);
    TgERROR(sizeof( STg2_File_Block ) == psFB->m_uiSize);
    TgERROR(0x01 == psFB->m_uiVersion);
    TgERROR(0x01 == psFB->m_uiSection_Version);
    TgERROR(sizeof( STg2_File_Section ) == psFB->m_uiSection_Size);
}


/* =============================================================================================================================================================================== */
#endif
