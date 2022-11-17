/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_H)
#if !defined (ENABLE_RELOAD_GUARD)

#include "TgS PHYSICS/TgS Physics - Constants.h"
#include "TgS PHYSICS/TgS Physics - Type.h"
#include "TgS PHYSICS/TgS Physics - Data.h"
#include "TgS PHYSICS/TgS Physics - Macro.h"


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @addtogroup TGS_PHYSICS_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPH_Module_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPH_Module_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgPH_Module_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgPH_Module_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgPH_Module_Update(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module functions: Set the current configuration of the module. */
TgEXTN TgVOID
tgPH_Load_Config( TgVOID );

/** @brief Standard Module function: Save the current configuration of the module. */
TgEXTN TgVOID
tgPH_Save_Config( TgVOID );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state.
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgPH_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state.
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgPH_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module.
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgPH_Query_Fixed_Memory( TgVOID );


#if TgS_STAT__PHYSICS
/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object. */
TgEXTN TgVOID
tgPH_Stats(
    STg2_Output_P OUT0 );
#endif

/** @} TGS_PHYSICS_MODULE */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Physics Functions                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- System Functions ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_SYSTEM */
/** @{ */

#if defined(TgBUILD_FEATURE__SERVER)
/** @brief Server Update
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgVOID
tgPH__Server__Update(
    TgFLOAT32_C ARG0 );

/** @brief Wait for the Server Physics Update to finish. */
TgEXTN TgVOID
tgPH__Server__Wait_For_Update_Finish( TgVOID );

/*# defined(TgBUILD_FEATURE__SERVER) */
#endif

#if defined(TgBUILD_FEATURE__CLIENT)
/** @brief Client Update for sets not impacted by the player controlled updates.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgVOID
tgPH__Client__Update_PreInput(
    TgFLOAT32_C ARG0 );

/** @brief Update for sets impacted by player controlled updates.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds. */
TgEXTN TgVOID
tgPH__Client__Update_PostInput(
    TgFLOAT32_C ARG0 );

/** @brief Wait for the Client Physics Update to finish. */
TgEXTN TgVOID
tgPH__Client__Wait_For_Update_Finish( TgVOID );

/*# defined(TgBUILD_FEATURE__CLIENT) */
#endif

/** @} TGS_PHYSICS_SYSTEM */


/* -- System Configuration ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_SYSTEM_CONFIGURATION */
/** @{ */

/** @brief Places the module into a pause state. */
TgEXTN TgVOID
tgPH_Set_Pause_Module(
    TgBOOL_C ARG0 );

TgEXTN TgBOOL
tgPH_Is_Module_Paused( TgVOID );

/** @brief Set the maximum number of iterations used during a world update. */
TgEXTN TgVOID
tgPH_Set_Iteration_Limit(
    TgUINT_E64_C ARG0 );

TgEXTN TgUINT_E64
tgPH_Query_Iteration_Limit( TgVOID );

/** @} TGS_PHYSICS_SYSTEM_CONFIGURATION */


/* -- Utilities ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

//TgEXTN TgVEC_F32_04_1
//tgPH_Impulse_To_Force(
//    TgFLOAT32_C ARG0, TgVEC_F32_04_1_C ARG1 );  /* #IMPLEMENT */

TgEXTN TgVEC_F32_04_1
tgPH_Body_Query_LV_Point(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );  /* #IMPLEMENT */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Physics Objects                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Material ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_MATERIAL */
/** @{ */

/** Many material characteristics vary with the temperature of the material. Since we are not attempting to simulate physical correctness to that level of detail, the material
    data structure does not allow for a time series. Different materials can be created for distinct temperate values as a way to emulate the time series, assuming that the
    material tempature can be known apriori. */


/** @brief Return the material id associated with the given enumerated default material value. 
    @param ARG0 Enumeration value selecting the default material.
    @return The material id associated with the enumeration value or the invalid material id otherwise. */
TgEXTN TgPH_MATERIAL_ID
tgPH_Material_Query_Default(
    ETgPH_MATERIAL_DEFAULT_C ARG0 );

/* Material -- Material Component */

/** @brief Simple accessors for the density of the material. Default materials assumed that it is measured in grams / cubic centimeter
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Density,TgFLOAT32)

/** @brief Simple accessors for the density of the material.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Hardness_Brinell,TgFLOAT32)

/** @brief Simple accessors for yield strength. Default materials assumed that it is measured in Pascals.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Tensile_Strength_Ultimate,TgFLOAT32)

/** @brief Simple accessors for tensile strength. Default materials assumed that it is measured in Pascals.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Tensile_Strength_Yield,TgFLOAT32)

/** @brief Simple accessors for tensile strength. Default materials assumed that it is measured in percentage.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Elongation_At_Break,TgFLOAT32)

/** @brief Simple accessors for the Modulus of Elasticity. Default materials assumed that it is measured in Pascals.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Modulus_Elasticity,TgFLOAT32)

/** @brief Simple accessors for poisson ratio.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Poisson_Ratio,TgFLOAT32)

/** @brief Simple accessors for shear modulus. Default materials assumed that it is measured in Pascals.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Shear_Modulus,TgFLOAT32)


/* Material -- Thermal Component */

/** @brief Simple accessors for thermal expansion. Default materials assumed that it is measured in µm/m°C.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Thermal_Expansion,TgFLOAT32)

/** @brief Simple accessors for thermal conductivity. Default materials assumed that it is measured in W/mK.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Thermal_Conductivity,TgFLOAT32)

/** @brief Simple accessors for melting temperature. Default materials assumed that it is measured in Celsius.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Melting_Temperature,TgFLOAT32)

/** @brief Simple accessors for melting temperature. Default materials assumed that it is measured in Celsius.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Boiling_Temperature,TgFLOAT32)


/* Material -- Fluid Component */

/** @brief Simple accessors for vapour pressure. Default materials assumed that it is measured in Bar.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Vapour_Pressure,TgFLOAT32)

/** @brief Simple accessors for surface tension. Default materials assumed that it is measured in dynes / cm.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Surface_Tension,TgFLOAT32)

/** @brief Simple accessors for dynamic viscosity. Default materials assumed that it is measured in Pascal Seconds.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Dynamic_Viscosity,TgFLOAT32)

/** @brief Simple accessors for kinematic viscosity. Default materials assumed that it is measured in Stokes.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Kinematic_Viscosity,TgFLOAT32)

/** @brief Simple accessors for the gas constant. Default materials assumed that it is measured in metre / second.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Material,MATERIAL,Speed_of_Sound,TgFLOAT32)

/** @} TGS_PHYSICS_MATERIAL */




/* -- Form ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_FORM */
/** @{ */

/* Form -- Configuration */

/** @brief Simple accessors for the category bits assigned to this form.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Category,TgUINT_E64)

/** @brief Simple accessors for the collision bits assigned to this form.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Collide,TgUINT_E64)

/** @brief Simple accessors for the enabled flag.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Enabled,TgBOOL)

/** @brief Simple accessors to control the axis-aligned bounding box updates.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Update_BA,TgBOOL)


/* Form -- Geometry */

/** @brief Simple accessors for the primitive type of the form.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Primitive,ETgPRIMITIVE)

/** @brief Simple accessors for the material identifier.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Material_ID,TgPH_MATERIAL_ID)

/** @brief Simple query for the last position of the form relative to a parent space (most often an owning body).
    Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_QUERY__DECLERATION_ASSIGN(Form,FORM,Last_Position,TgVEC_F32_04_1)

/** @brief Simple accessors for the position of the form relative to a parent space (most often an owning body).
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Position,TgVEC_F32_04_1) // First transform to be concatenated (base geometry to local space)

/** @brief Simple accessors for the axis-aligned bounding box.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_COPY(Form,FORM,BA,TgBOXAA_F32_04)


/* Form -- Body and Transform */

/** @brief If the form identifier at ARG1 is valid, store in OUT0 the form's attribute
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Form identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Form_Query_Next_Form_ID(
    TgPH_FORM_ID_PC OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief If the form identifier at ARG1 is valid, store in OUT0 the form's attribute
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Form identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Form_Query_Final(
    TgVEC_F32_04_3_PC OUT0, TgPH_FORM_ID_C ARG1 );

/** @brief Simple accessors for the identifier of the owning body.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Body_ID,TgPH_BODY_ID)

/** @brief Simple accessors for the spacial partitioning identifier.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Sweep_ID,TgPNS_OBJECT_ID)

/** @brief Simple accessors for the local transform of the form (relative to the most immediate parent space).
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_COPY(Form,FORM,Local,TgVEC_F32_04_3) // First transform to be concatenated (base geometry to local space)

/** @brief Simple accessors for an immediate scale of the base form geometry.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Scale,TgVEC_F32_04_1) // Scale to be applied to the base geometry

/** @brief Simple accessors for the identifier associated with this form.
    Set( Form ID, Value ). Query( Pointer to Output Value, Form ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Form,FORM,Colour,TgVEC_F32_04_1) // Debug Colour

/** @} TGS_PHYSICS_FORM */




/* -- Body ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_BODY */
/** @{ */

/** @brief Apply a force at the given location to the body.
    @param ARG0 Body identifier.
    @param ARG1 Force vector to be applied.
    @param ARG2 Location where the force is applied in body space.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */
TgEXTN TgRESULT
tgPH_Body_Add_Force_At_Location(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1, TgVEC_F32_04_1_C ARG2 );

/** @brief Set the drag co-efficient on the body.
    @param ARG0 Body identifier.
    @param ARG1 Drag co-efficient.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */
TgEXTN TgRESULT
tgPH_Body_Apply_Drag(
    TgPH_BODY_ID_C ARG0, TgFLOAT32_C ARG1 ); /**< Apply a constant drag to both velocities. */

/** @brief Return the first form (in the linked list) associated with this body.
    @param [out] OUT0 Pointer to the output value.
    @param [in] ARG1 Body identifier.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_First_Form_ID(
    TgPH_FORM_ID_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief Return the first constraint (in the linked list) associated with this body.
    @param [out] OUT0 Pointer to the output value.
    @param [in] ARG1 Body identifier.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_First_Constraint_ID(
    TgPH_CONSTRAINT_ID_PC OUT0, TgPH_BODY_ID_C ARG1 );


/* Body -- Geometry */

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Position,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_COPY(Body,BODY,Transform,TgVEC_F32_04_3)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Rotation,TgVEC_F32_04_1)

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's last valid position in world space
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Last_Position(
    TgVEC_F32_04_1_PC NONULL OUT0, TgPH_BODY_ID_C ARG1 );


/* Body -- Mass */

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's moment of inertia
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Moment_Of_Inertia(
    TgVEC_F32_04_3_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's centre of gravity
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Centre_Of_Gravity(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's mass
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Mass(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's inverse moment of inertia
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Inverse_Moment_Of_Inertia(
    TgVEC_F32_04_3_PC OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's inverse mass
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Inverse_Mass(
    TgVEC_F32_04_1_PC OUT0, TgPH_BODY_ID_C ARG1 );


/* Body -- Linear Velocity and Force */

/** @brief Set the linear velocity of the body
    @param ARG0 Body identifier
    @param ARG1 Vector of linear velocity in body space
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Linear_Velocity(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 ); /**< Linear Velocity */

/** @brief Set the linear velocity of the body
    @param ARG0 Body identifier
    @param ARG1 Vector of the force to apply at the centre of gravity.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Force(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Add this force each frame to the body.
    @param ARG0 Body identifier
    @param ARG1 Vector of the force to apply at the centre of gravity.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Dampening_Force(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 ); /**< Dampening Force */

/** @brief Add this force each frame to the body.
    @param ARG0 Body identifier
    @param ARG1 Vector of the force to persist at the centre of gravity.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Persistent_Force(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 ); /**< Persistent Force */

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Linear_Velocity,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Persistent_Force,TgVEC_F32_04_1)

///** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's accumulated external force
//    @param OUT0 Pointer to hold the queried for value
//    @param ARG1 Body identifier
//    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_External_Force(
    TgVEC_F32_04_1_PC NONULL OUT0, TgPH_BODY_ID_C ARG1 );


/* Body -- Angular Velocity and Torques */

/** @brief Set the angular velocity of the body
    @param ARG0 Body identifier
    @param ARG1 Vector of the angular velocity in body space
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Angular_Velocity(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 ); /**< Angular Velocity */

/** @brief Set the angular velocity of the body
    @param ARG0 Body identifier
    @param ARG1 Vector of the angular velocity in body space
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Torque(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 );

/** @brief Set the angular velocity of the body
    @param ARG0 Body identifier
    @param ARG1 Vector of the angular velocity in body space
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Dampening_Torque(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 ); /**< Dampening Torque */

/** @brief Set the angular velocity of the body
    @param ARG0 Body identifier
    @param ARG1 Vector of the angular velocity in body space
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Add_Persistent_Torque(
    TgPH_BODY_ID_C ARG0, TgVEC_F32_04_1_C ARG1 ); /**< Persistent Torque */

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Angular_Velocity,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Persistent_Torque,TgVEC_F32_04_1)

///** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's accumulated angular moment
//    @param OUT0 Pointer to hold the queried for value
//    @param ARG1 Body identifier
//    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
//TgEXTN TgRESULT
//tgPH_Body_Query_Angular_Torque(
//    TgVEC_F32_04_1_PC NONULL OUT0, TgPH_BODY_ID_C ARG1 );

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's accumulated external moments
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_External_Torque(
    TgVEC_F32_04_1_PC NONULL OUT0, TgPH_BODY_ID_C ARG1 );


/* Body -- Simulation Configuration */

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Tunneling,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Force_Field_Factor,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Time_Factor,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Disable_Timer,TgFLOAT32)

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the body's ragdoll flag
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Ragdoll(
    TgBOOL_PC NONULL OUT0, TgPH_BODY_ID_C ARG1 );


/* Body -- User Functions */

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,CalcFM_FCN,TgCALCFM_FCN)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Contact_FCN,TgCONTACT_FCN)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Moved_FCN,TgMOVED_FCN)

/** @brief Simple accessors for the identifier associated with this body.
    Set( Body ID, Value ). Query( Pointer to Output Value, Body ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(Body,BODY,Context,TgUINT_PTR)


/* Body -- Run Time State */

/** @brief If the body identifier at ARG1 is valid, store in OUT0 the active/sleep state of the body.
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Body identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Body_Query_Enabled(
    TgBOOL_PC NONULL OUT0, TgPH_BODY_ID_C ARG1 );


/** @} TGS_PHYSICS_BODY */




/* -- Motor ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_MOTOR */
/** @{ */

/** @} TGS_PHYSICS_MOTOR */




/* -- Constraint ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_CONSTRAINT */
/** @{ */

/* Fixed Constraint */

TgEXTN TgVOID
tgPH_Constraint_Set_Breakable(
    TgPH_CONSTRAINT_ID_C ARG0, TgBOOL_C );

TgEXTN TgBOOL
tgPH_Constraint_Query_Connected(
    TgPH_BODY_ID_C ARG0, TgPH_BODY_ID_C );

/** @brief If the form identifier at ARG1 is valid, store in OUT0 the form's attribute
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Form identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Constraint_Query_Next_Constraint_ID_For_Body_0(
    TgPH_CONSTRAINT_ID_PC OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @brief If the form identifier at ARG1 is valid, store in OUT0 the form's attribute
    @param OUT0 Pointer to hold the queried for value
    @param ARG1 Form identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
tgPH_Constraint_Query_Next_Constraint_ID_For_Body_1(
    TgPH_CONSTRAINT_ID_PC OUT0, TgPH_CONSTRAINT_ID_C ARG1 );

/** @} TGS_PHYSICS_CONSTRAINT */




/* -- Rag Doll ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_RAGDOLL */
/** @{ */

/** @} TGS_PHYSICS_RAGDOLL */




/* -- Scene ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_SCENE */
/** @{ */

TgEXTN TgRESULT
tgPH_Scene_Enable( TgPH_SCENE_ID_C ARG0 );  /* #IMPLEMENT */

TgEXTN TgRESULT
tgPH_Scene_Insert_Body( TgPH_SCENE_ID_C ARG0, TgPH_BODY_ID_C );  /* #IMPLEMENT */

TgEXTN TgRESULT
tgPH_Scene_Insert_Constraint( TgPH_SCENE_ID_C ARG0, TgPH_BODY_ID_C );  /* #IMPLEMENT */

TgEXTN TgRESULT
tgPH_Scene_Insert_Rag_Doll( TgPH_SCENE_ID_C ARG0, TgPH_BODY_ID_C );  /* #IMPLEMENT */

TgEXTN TgPH_SCENE_ID
tgPH_Load_File( TgUINT_F32_C ARG0, STg2_Input_PC, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C ARG0, TgPH_SCENE_ID_C) );  /* #IMPLEMENT */


/** @} TGS_PHYSICS_SCENE */



/* -- World --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_PHYSICS_WORLD */
/** @{ */

/** @brief Return the world id associated with the given enumerated value. 
    @param ARG0 Enumeration value selecting the world id.
    @return The world id associated with the enumeration value or the invalid world id otherwise. */
TgEXTN TgPH_WORLD_ID
tgPH_World_Query_World_Id(
    ETgPH_WORLD_C ARG0 );

/** @brief Simple accessors for the identifier associated with this world, places the module into a pause state.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Pause_State,TgBOOL)

/** @brief Simple accessors for the identifier associated with this world, causes the module to execute a single time step, even when paused.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Single_Step,TgBOOL)

/** @brief Simple accessors for the identifier associated with this world, enables the simulation update during a world update.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Simulation_Enable,TgBOOL)

/** @brief Simple accessors for the identifier associated with this world, enables collision testing during a world update.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Collision_Enable,TgBOOL)

/** @brief Simple accessors for the identifier associated with this world, the time step used during the module update.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Fixed_Time_Step,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this world, the acceleration field applied to all bodies during simulation.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Force_Field,TgVEC_F32_04_1)


/* System Configuration -- Solver */

/** @brief Simple accessors for the identifier associated with this world, the penetration depth sleep threshold.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Threshold_Depth,TgFLOAT32)

/** @brief Simple accessors for the identifier associated with this world, the linear velocity sleep threshold.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Threshold_LV,TgVEC_F32_04_1)

/** @brief Simple accessors for the identifier associated with this world, the angular velocity sleep threshold.
    Set( World ID, Value ). Query( Pointer to Output Value, World ID). */
PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(World,WORLD,Threshold_AV,TgVEC_F32_04_1)


/** @} TGS_PHYSICS_WORLD */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Nomenclature                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/*
    Material: Holds most of the defining characteristics of a real life material. A few of these values are used for simulation, the remainder can be used by other modules.
    Form/Shape: The geometry that is composed to form a complete set of surfaces that represent the exterior of physical object.
    Mass: Set of representative values to describe the mass of an object (mass, location of the centre of gravity, inertia tensor).
    Body: Container object for a set of forms, and a mass. Used as the basis for simulation.
    Constraint: A limitation that is placed on one or more bodies that limits their motion.
    Motor: A constraint that is capable of applying a force or moment.
    Ragdoll: Set of bodies and constraints that is applied to a skeleton (see animation module).
    Scene: A packaged set of content that is loaded as a cohesive unit (and unloaded as a set). Example: a portion of a level.
    World: A set of content that can interact. Worlds can not interact with other worlds. Worlds may run at different simulation rates and have completed different configurations.

*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Declares resource specific generic object management functions. 
    Resource/Object Types: Material, Form, Body, Constraint, Motor, Ragdoll, Scene, World */

#define __PARENT_FILE__ "TgS Physics.h"
#define ENABLE_RELOAD_GUARD
#include "TgS PHYSICS/TgS Physics - Object [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_PHYSICS_H

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Generic Object Memory Management                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#if !defined(T_STATIC)
#if defined(T_GLOBAL)
/** @brief Allocate a new object.
    @return An unique identifier for a new object */
TgEXTN T_ID(TgPH_,_ID)
T_NAME(tgPH_,_Init)( TgVOID );
#else
/** @brief Allocate a new object in the world identifier by ARG0.
    @param [in] ARG0 World Configuration UID.
    @return An unique identifier for a new object */
TgEXTN T_ID(TgPH_,_ID)
T_NAME(tgPH_,_Init)(
    TgPH_WORLD_ID_C ARG0 );
#endif
//# !defined(T_STATIC)
#endif

/** @brief Reset the object identified by ARG0 and add it to the free list.
    @param ARG0 [in] Resource identifier
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise */
TgEXTN TgRESULT
T_NAME(tgPH_,_Reset)(
    T_ID(TgPH_,_ID_C) ARG0 );

#if defined(T_GLOBAL)
/** @brief Return the current count of registered objects.
    @return The current count of registered material objects */
TgEXTN TgRSIZE
T_NAME(tgPH_,_Query_Count)( TgVOID );
#else
/** @brief Return the current count of registered objects in the world identifier by ARG0.
    @param [in] ARG0 World Configuration UID.
    @return The current count of registered material objects */
TgEXTN TgRSIZE
T_NAME(tgPH_,_Query_Count)( 
    TgPH_WORLD_ID_C ARG0 );
#endif


/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/* =============================================================================================================================================================================== */
/*# defined (TGS_PHYSICS_H) */
#endif
