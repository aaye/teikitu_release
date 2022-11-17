/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS Common.h"
#include "TgS Collision.h"
#include "TgS Partition.h"
#include "TgS Kernel.h"
#include "TgS Kernel [GPU].h"
#include "TgS Physics.h"

#include "TgS Physics - Internal - Constants.h"
#include "TgS Physics - Internal - Type.h"
#include "TgS Physics - Internal - Data.h"

#include "TgS Physics - Internal - Macro.h"

#include "TgS COMMON/TgS Common.inl"




/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN TgVOID
tgPH_Update_World__Init_Jobs( TgVOID );


/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_MASS */
/** @{ */

/** @brief Claer the mass structure..
    @param [out] OUT0 Pointer to a mass data structure that is cleared. */
TgINLINE TgVOID 
tgPH_Mass_Reset(
    STg2_PH_Mass_PCU OUT0 );

/** @brief Update the mass structure based on moving the centre of mass.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Scalar value
    @param [in] ARG2 Scalar value
    @param [in] ARG3 Scalar value
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgINLINE TgRESULT
tgPH_Mass_Move_Elem(
    STg2_PH_Mass_PC INOUT0, TgFLOAT32_C ARG1, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3 );

/** @brief Update the mass structure based on moving the centre of mass.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Vector value
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Mass_Move(
    STg2_PH_Mass_PC INOUT0, TgVEC_F32_04_1_C ARG1 );

/** @brief Update the mass structure based on a rotation (euler angles).
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Scalar value
    @param [in] ARG2 Scalar value
    @param [in] ARG3 Scalar value
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgINLINE TgRESULT
tgPH_Mass_Rotate_Eul_Elem(
    STg2_PH_Mass_PC INOUT0, TgFLOAT32_C ARG1, TgFLOAT32_C ARG2, TgFLOAT32_C ARG3 );

/** @brief Update the mass structure based on a rotation (euler angles).
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Vector value
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgINLINE TgRESULT
tgPH_Mass_Rotate_Eul( 
    STg2_PH_Mass_PC INOUT0, TgVEC_F32_04_1_C ARG1 );

/** @brief Update the mass structure based on a rotation (quaternion).
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Vector value
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgINLINE TgRESULT
tgPH_Mass_Rotate_Quat(
    STg2_PH_Mass_PC INOUT0, TgVEC_F32_04_1_C ARG1 );

/** @brief Update the mass structure based on a rotation (matrix).
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Pointer to an array of vectors (matrix)
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Mass_Rotate_Mat(
    STg2_PH_Mass_PC INOUT0, TgVEC_F32_04_3_CPCU ARG1 );

/** @brief Update the mass structure mass related values.
    @param [in,out] INOUT0 Pointer to a mass data structure that is updated.
    @param [in] ARG1 Form identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgINLINE TgRESULT
tgPH_Mass_Set_Mass(
    STg2_PH_Mass_PC INOUT0, TgFLOAT32_C ARG1 );

/** @} TGS_PHYSICS_MASS */




/* -- Material ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Used in the module boot (tgPH_Module_Boot) to create standard materials. */
TgEXTN TgVOID
tgPH_Module_Material_Boot( TgVOID );


/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* -- Form ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgPH_Form_Update_From_Body(
    TgPH_FORM_ID_C ARG0 );


/* -- Body ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgRESULT
tgPH_Body_Set_Enabled(
    TgPH_BODY_ID_C ARG0, TgBOOL_C );

TgEXTN TgRESULT
tgPH_Body_Add_Form(
    TgPH_BODY_ID_C ARG0, TgPH_FORM_ID_C ARG1 );

TgEXTN TgRESULT
tgPH_Body_Remove_Form(
    TgPH_FORM_ID_C ARG1 );

TgEXTN TgVOID
tgPH_Body_Contact_Default(
    TgPH_BODY_ID_C, TgFLOAT32_C );

TgEXTN TgVOID
tgPH_Body_Move_Default(
    TgPH_BODY_ID_C, TgFLOAT32_C );


/* -- Motor ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */



/* -- Constraint ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgPH_CONSTRAINT_ID
tgPH_Constraint_Fixed__Init(
    TgPH_WORLD_ID ARG0, TgPH_BODY_ID_C ARG1, TgPH_BODY_ID_C ARG2 );

/*  @brief Iterate through all of the fixed type constraints in this problem set and fill in the required data for the solver.
    @param [in,out] ARG0 Pointer to a solver data structure that include the problem set, supporting solver data, and the resulting solution outcomes.
    @parma [in] ARG1 Pointer to the side data generated during the simulation prediction step. */
TgEXTN TgVOID
tgPH_Constraint_Fixed__Problem_Definition(
    TgPH_WORLD_ID ARG0, STg2_PH_Solver__Set_CPC NONULL ARG1 );


/* -- Ragdoll -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* -- Scene ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgEXTN TgVOID
tgPH_Scene_Validate(
    STg2_Output_PC OUT0, TgPH_SCENE_ID_C ARG1 );


/* -- World --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */


/* Collision Updates */

TgEXTN TgVOID
tgPH_Update_World__Collide__Simple(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

TgEXTN TgVOID
tgPH_Update_World__Collide__Prune_And_Sweep(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );


/* World Updates */

TgEXTN TgRESULT
tgPH_Update_World(
    TgPH_WORLD_ID_C ARG0 );

TgEXTN TgVOID
tgPH_Update_World__Simulate_Batch(
    TgPH_WORLD_ID_C ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

TgEXTN TgVOID
tgPH_Update_World__Collide_Batch(
    TgPH_WORLD_ID_C ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

TgEXTN TgRESULT
tgPH_Update_World__Build_Sets(
    TgPH_WORLD_ID_C ARG0 );

TgEXTN TgVOID
tgPH_Update_World__Define_Problem_And_Solve(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_PC ARG1 );

TgEXTN TgVOID
tgPH_Update_World__Update_Bodies(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC ARG1 );

TgEXTN TgVOID
tgPH_Update_World__Solver_SOR(
    TgPH_WORLD_ID_C ARG0 );

TgEXTN TgVOID
tgPH_Update_World__Solver_Post(
    TgPH_WORLD_ID_C ARG0 );


/* Solvers */

TgEXTN TgVOID
tgPH_SV_SOR_LCP(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC ARG1 );

TgEXTN TgVOID
tgPH_SV_GS_LCP( 
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC ARG1 ); //« Gauss-Sidel Solver

TgEXTN TgVOID
tgPH_SV_LCP(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC ARG1 ); //« A non-iterative LCP solver

TgEXTN TgVOID
tgPH_SV_MT_LCP(
    TgPH_WORLD_ID_C ARG0, STg2_PH_Solver__Set_CPC ARG1 ); //« Multi-threaded solver.


/* Run Time Values */

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Body_Count(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Form_Count(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );


/* Job Configuration Values. */

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Simulate_Batch_Size(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );

/** @brief . */
TgEXTN TgRESULT
tgPH_World_Query_Collide_Batch_Size(
    TgRSIZE_P OUT0, TgPH_WORLD_ID_C ARG1 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define __PARENT_FILE__ "TgS Physics - Internal.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_INTERNAL_H


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Functions                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS

/* World */
TgEXTN TgVOID
tgPH_World_Validate(
    STg2_Output_PC OUT0, TgPH_WORLD_ID_C ARG1 );

//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Stat Functions                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
#if defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS

//# defined(TgS_STAT__PHYSICS) && TgS_STAT__PHYSICS
#endif


/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief Initialize all of the data values as part of the Module Init. 
    @internal Defined in Generic Functions. */
TgEXTN TgVOID
T_NAME(tgPH_Module_,_Init)( TgVOID );

/** @brief Free all dynamic allocations owned by the module, and validate that the module is in a cleared (reset) state.
    @internal Defined in Generic Functions. */
TgEXTN TgVOID
T_NAME(tgPH_Module_,_Free)( TgVOID );

#if !defined(T_STATIC)

/** @brief Override resource(type) configuration values. */
TgEXTN TgVOID
T_NAME(tgPH_Module_,_Init_Internal)( TgVOID );

/** @brief Init the object passed in the command buffer and add it to the used list.
    @param [in] ARG0 Pointer to a command buffer (byte array).
    @param [in] ARG1 Integer value for the maximum length of the command buffer. */
TgEXTN TgVOID
T_NAME(tgPH_,_Init_Do_Command)(
    TgVOID_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief Reset the object passed in the command buffer and add it to the free list.
    @param [in] ARG0 Pointer to a command buffer (byte array).
    @param [in] ARG1 Integer value for the maximum length of the command buffer. */
TgEXTN TgVOID
T_NAME(tgPH_,_Reset_Do_Command)(
    TgVOID_CPC ARG0, TgRSIZE_C ARG1 );

#else
//# !defined(T_STATIC)

/** @brief Init the object passed into the function.
    @param [in,out] ARG0 Pointer to an object to initialize. 
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */
TgEXTN TgRESULT
T_NAME(tgPH_,_Init_Internal)(
    T_NAME(STg2_PH_,_P) ARG0 );

/** @brief Reset the object passed into the function.
    @param [in,out] ARG0 Pointer to an object to initialize.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */
TgEXTN TgRESULT
T_NAME(tgPH_,_Reset_Internal)(
    T_NAME(STg2_PH_,_P) ARG0 );

//# !defined(T_STATIC)
#endif

/** @brief Initialize a resource unique identifier given the required parameters.
    @internal Defined in TgS Physics - Internal.inl.
    @param [out] OUT0 Pointer to the identifier to be initialized.
    @param [in] ARG1 Integer index of the resource.
    @param [in] ARG2 Integer index of the world.
    @param [in] ARG3 Integer index of the scene.
    @return A copy of the identifier stored in the singleton on success or INVALID otherwise. */
TgINLINE T_ID(TgPH_,_ID)
T_ID(tgPH_,_ID_Init)(
    T_ID(TgPH_,_ID_PCU) OUT0, TgUINT_F32_C ARG1, TgUINT_F08_C ARG2, TgUINT_F08_C ARG3 );

/** @brief Return a pointer to the object with the given id value.
    @internal Defined in TgS Physics - Internal.inl.
    @return A pointer to the object with the given id value, or nullptr otherwise. */
TgINLINE T_NAME(STg2_PH_,_P)
T_FCN(tgPH_,_Get_,_From_ID)(
    T_ID(TgPH_,_ID_C) ARG0 );

#if defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
/** @brief Validate an object (resource) and output the results of the validation.
    @param [in] ARG0 Pointer to an object containing the functions pointers to be used when outputing the validation messages.
    @param [in] ARG1 Unique Identifier for the resource to be tested. */
TgEXTN TgVOID
T_NAME(tgPH_,_Validate)(
    STg2_Output_PC ARG0, T_ID(TgPH_,_ID_C) ARG1 );
//# defined(TgS_DEBUG__PHYSICS) && TgS_DEBUG__PHYSICS
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_INTERNAL_H) */
#endif
