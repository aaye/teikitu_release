/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_TYPE_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Ring 3 - Type.h"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Objects                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Type.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_TYPE_H




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

typedef TgVOID(*TgCALCFM_FCN)( TgVEC_F32_04_1_P, TgVEC_F32_04_1_P, TgPH_BODY_ID_C, TgUINT_PTR_C, TgVEC_F32_04_1_C );
typedef TgVOID(*TgCONTACT_FCN)( TgPH_BODY_ID_C, TgUINT_PTR_C, STg2_CO_Packet_F32_04_PCU );
typedef TgVOID(*TgMOVED_FCN)( TgPH_BODY_ID_C, TgVOID_P );
typedef TgVOID(*TgWORLD_UPDATE_COLLIDE_FCN)( TgPH_WORLD_ID_C, TgRSIZE_C, TgRSIZE_C );

TgTYPE_MODIFIER_DEFAULT(TgCALCFM_FCN);
TgTYPE_MODIFIER_DEFAULT(TgCONTACT_FCN);
TgTYPE_MODIFIER_DEFAULT(TgMOVED_FCN);
TgTYPE_MODIFIER_DEFAULT(TgWORLD_UPDATE_COLLIDE_FCN);


/* -- Form ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Form_Collision, )
{
    TgUINT_E32                                  m_uiPad;
    ETgPRIMITIVE                                m_enPM; /**< Collision primitive used by a Form. */
    TgPH_MATERIAL_ID                            m_tiMaterial; /**< Physical material properties. */
    STg2_CO_Primitive_F32_04                    m_uPrimitive; /**< Union of available collision primitives. */
};


/* -- Constraints ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Contact_Point,)
{
    TgVEC_F32_04_1                            m_vPosition;
    TgVEC_F32_04_1                            m_vNormal;
};

TgTYPE_STRUCT(STg2_PH_Contact,)
{
    TgPH_BODY_ID                                m_tiBody_0;
    TgPH_BODY_ID                                m_tiBody_1;

    STg2_PH_Contact_Point                       m_sPoint;
};


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Objects                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_UNION(T_ID(TgPH_,_ID),)
{
    TgALIGN(8) TgUINT_E64                       m_uiKI;
    struct {
        TgUINT_E64                                  m_uiScene : KTgPH_OBJ_BIT__SCENE; /**< Scene Index. */
        TgUINT_E64                                  m_uiI : KTgPH_OBJ_BIT__MAX_INDEX; /**< Index identification of object within storage array. */
        TgUINT_E64                                  m_uiWorld : KTgPH_OBJ_BIT__WORLD; /**< World Index. */
        TgUINT_E64                                  m_uiK : KTgPH_OBJ_BIT__SALT; /**< Salt value to prevent ABA atomic issues. */
    };
};
TgTYPE_MODIFIER_ALL(T_ID(TgPH_,_ID));
TgKI_CUSTOM_DECLARE_AND_INLINE(T_ID(PH_,_ID))


/*# defined (ENABLE_RELOAD_GUARD) */
#endif


/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_TYPE_H) */
#endif
