/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PARTITION_TYPE_H)
#define TGS_PARTITION_TYPE_H
#pragma once

#if !defined(TGS_PARTITION_H)
#error This file should not be included directly - use the correct platform include wrapper
#endif

#include "TgS Ring 0 - Type.h"


/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_PA_PnS_PointEnd,)
{
    TgFLOAT32                                   m_fVal; /**< The axis projected min/max value */
    TgUINT_E16                                  m_uiNext; /**< Index of the AABB/Object */
    TgUINT_E16                                  m_uiPrev; /**< Index of the AABB/Object */
    TgBOOL                                      m_bMax;
    TgUINT_E08                                  m_iPad[3];
};

TgTYPE_STRUCT(STg2_PA_PnS,)
{
    /* SoA access pattern to increase cache coherency for common routines */

    STg2_PA_PnS_PointEnd                        m_asX0[KTgPA_PNS_MAX_INTERVAL + 1];
    STg2_PA_PnS_PointEnd                        m_asX1[KTgPA_PNS_MAX_INTERVAL + 1];
    STg2_PA_PnS_PointEnd                        m_asX2[KTgPA_PNS_MAX_INTERVAL + 1];
    TgUINT_E08                                  m_iPad_0[4];

    /* Category Mask is a bit field to describe the object and used in bit operations against the collide mask.  Any object for whom an and of the collide and category */
    /* masks result in a zero value for the first 30 bits do not interact in any way. The 31st bit is used to indicate of the slot in the system is currently being used. */

    TgUINT_MAX                                  m_uiCallbackID[KTgPA_PNS_MAX_OBJECTS]; /**< ID used to pass into collision callback */
    TgUINT_E64                                  m_uiCategory[KTgPA_PNS_MAX_OBJECTS]; /**< Object category mask */
    TgUINT_E64                                  m_uiCollide[KTgPA_PNS_MAX_OBJECTS]; /**< Object collide mask */
    TgUINT_E08                                  m_iPad_1[8];
    TgBOXAA_F32_04                              m_asBA[KTgPA_PNS_MAX_OBJECTS]; /**< Object AABB */
    TgPNS_OBJECT_ID_SINGLETON                   m_atiObject[KTgPA_PNS_MAX_OBJECTS]; /**< Object ID in this PnS partition */
    TgRSIZE                                     m_auiContact_Linked_List_Head[KTgPA_PNS_MAX_OBJECTS]; /**< Index to first element of the linked list */

                                                /* Pool of nodes for a linked list per object */
    TgPNS_OBJECT_ID                             m_atiContact_Object[KTgPA_PNS_MAX_CONTACT_PAIR]; /**< The opposing object id in contact set */
    TgRSIZE                                     m_auiContact_Next[KTgPA_PNS_MAX_CONTACT_PAIR]; /**< Index to next element in side-chain */

    TgRSIZE                                     m_nuiObjects;
    TgRSIZE                                     m_uiEmpty; /**< First empty contact element */

    STg1_MT_MX                                  m_csSystemLock;
#if 0 != (SIZE_STg1_MT_MX % 16)
    TgUINT_E08                                  m_uiPad[16 - SIZE_STg1_MT_MX % 16];
#endif
};


/* =============================================================================================================================================================================== */
#endif
