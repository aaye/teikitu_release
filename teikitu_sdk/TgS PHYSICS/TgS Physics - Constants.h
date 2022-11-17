/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Constants.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_CONSTANTS_H)
#define TGS_PHYSICS_CONSTANTS_H
#pragma once


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_PHYSICS Physics Module and Functions
*/

    /** @defgroup TGS_PHYSICS_MODULE Module Functions
        @ingroup TGS_PHYSICS
    */

    /** @defgroup TGS_PHYSICS_SYSTEM Physics System and System Configuration
        @ingroup TGS_PHYSICS
    */

        /** @defgroup TGS_PHYSICS_SYSTEM_CONFIGURATION Physics System Configuration
            @ingroup TGS_PHYSICS_SYSTEM
        */

        /** @defgroup TGS_PHYSICS_SYSTEM_SOLVER Physics Solver
            @ingroup TGS_PHYSICS_SYSTEM
        */

    /** @defgroup TGS_PHYSICS_MATERIAL Physics Material
        @ingroup TGS_PHYSICS
    */

    /** @defgroup TGS_PHYSICS_FORM Physics Form
        @ingroup TGS_PHYSICS
    */

    /** @defgroup TGS_PHYSICS_BODY Physics Body
        @ingroup TGS_PHYSICS
    */

    /** @defgroup TGS_PHYSICS_CONSTRAINT Physics Constraint
        @ingroup TGS_PHYSICS
    */

    /** @defgroup c Physics Constraint
        @ingroup TGS_PHYSICS
    */

    /** @defgroup TGS_PHYSICS_RAGDOLL Physics Ragdoll
        @ingroup TGS_PHYSICS
    */

    /** @defgroup TGS_PHYSICS_SCENE Physics Scene
        @ingroup TGS_PHYSICS
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Configuration                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define TgS_PHYSICS_HISTORY 1

enum { KTgPH_MAX_SIMULATION_JOB                     = KTgKN_MAX_JOB_THREAD << 2,
       KTgPH_MAX_COLLIDE_JOB                        = KTgKN_MAX_JOB_THREAD << 2,
       KTgPH_MAX_SOLVE_JOB                          = KTgKN_MAX_JOB_THREAD << 2,

       KTgPH_MAX_MATERIAL                           = 256,

       KTgPH_OBJ_BIT__SCENE                         = 4,
       KTgPH_OBJ_BIT__MAX_INDEX                     = 32 - KTgPH_OBJ_BIT__SCENE,
       KTgPH_OBJ_BIT__WORLD                         = 2,
       KTgPH_OBJ_BIT__SALT                          = 32 - KTgPH_OBJ_BIT__WORLD,

       KTgPH_MAX_WORLD                              = (1 << KTgPH_OBJ_BIT__WORLD) - 1,
       KTgPH_MAX_SCENE                              = (1 << KTgPH_OBJ_BIT__SCENE) - 1,
       KTgPH_MAX_INDEX                              = (1 << KTgPH_OBJ_BIT__MAX_INDEX) - 1,

       KTgPH_MAX_HISTORY_BODY                       = 1024,

       KTgPH_MAX_BONES                              = 96,
};


typedef enum CLANG_ATTRIBUTE(enum_extensibility(closed))
{
    ETgPH_WORLD__BEGIN,

#if defined(TgBUILD_FEATURE__CLIENT)
    ETgPH_WORLD__CLIENT_FX = ETgPH_WORLD__BEGIN,
    ETgPH_WORLD__CLIENT_UI,
    #if defined(TgBUILD_FEATURE__SERVER)
        ETgPH_WORLD__SERVER_DEFAULT,
    /*# defined(TgBUILD_FEATURE__SERVER) */
    #endif
    ETgPH_WORLD__END,
/*# defined(TgBUILD_FEATURE__CLIENT) */
#else
    #if defined(TgBUILD_FEATURE__SERVER)
        ETgPH_WORLD__SERVER_DEFAULT = ETgPH_WORLD__BEGIN,
        ETgPH_WORLD__END,
    /*# defined(TgBUILD_FEATURE__SERVER) */
    #else
        ETgPH_WORLD__END = ETgPH_WORLD__BEGIN,
    /*# defined(TgBUILD_FEATURE__SERVER) */
    #endif
/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

    ETgPH_WORLD__MAX = ETgPH_WORLD__END,
    ETgPH_MAX_WORLD = ETgPH_WORLD__END - ETgPH_WORLD__BEGIN,
} ETgPH_WORLD;
TgTYPE_DECLARE( ETgPH_WORLD, ETgPH_WORLD );


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_ENUM(ETgPH_MATERIAL_DEFAULT, TgSINT_F32,

    ETgPH_MATERIAL__STEEL_1020,     ETgPH_MATERIAL__ALUMINUM_6061,  ETgPH_MATERIAL__WATER,          ETgPH_MATERIAL__OXYGEN,         ETgPH_MATERIAL__END,

    ETgPH_MATERIAL__MAX = ETgPH_MATERIAL__END,
    ETgPH_MATERIAL__BEGIN = ETgPH_MATERIAL__STEEL_1020,
);

TgTYPE_ENUM(ETgPH_CONSTRAINT, TgSINT_F32,

    ETgPH_CONSTRAINT__UNKNOWN,      ETgPH_CONSTRAINT__BALL_SOCKET,  ETgPH_CONSTRAINT__CHAIN,        ETgPH_CONSTRAINT__HINGE,        ETgPH_CONSTRAINT__LIMITED_HINGE,
    ETgPH_CONSTRAINT__PLANE,        ETgPH_CONSTRAINT__SPRING,       ETgPH_CONSTRAINT__WHEEL,        ETgPH_CONSTRAINT__FIXED,        ETgPH_CONSTRAINT__MAX,
);


/* =============================================================================================================================================================================== */
#endif
