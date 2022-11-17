/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Internal - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_INTERNAL_TYPE_H)
#define TGS_PHYSICS_INTERNAL_TYPE_H
#pragma once

/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* -- Material ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Material, )
{
    STg2_UT_ST__ST_Node                         m_sStack_Node;
    TgPH_MATERIAL_ID                            m_tiMaterial;
    TgFLOAT32                                   m_fDensity;
    TgFLOAT32                                   m_fHardness_Brinell;
    TgFLOAT32                                   m_fTensile_Strength_Ultimate;
    TgFLOAT32                                   m_fTensile_Strength_Yield;
    TgFLOAT32                                   m_fElongation_At_Break;
    TgFLOAT32                                   m_fModulus_Elasticity;
    TgFLOAT32                                   m_fPoisson_Ratio;
    TgFLOAT32                                   m_fShear_Modulus;
    TgFLOAT32                                   m_fThermal_Conductivity;
    TgFLOAT32                                   m_fThermal_Expansion;
    TgFLOAT32                                   m_fMelting_Temperature;
    TgFLOAT32                                   m_fBoiling_Temperature;
    TgFLOAT32                                   m_fVapour_Pressure;
    TgFLOAT32                                   m_fSurface_Tension;
    TgFLOAT32                                   m_fDynamic_Viscosity;
    TgFLOAT32                                   m_fKinematic_Viscosity;
    TgFLOAT32                                   m_fSpeed_of_Sound;
    TgUINT_E08                                  m_uiPad[4];
};


/* -- Mass ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Mass, )
{
    TgVEC_F32_04_3                              m_mMOI; /**< Moment of Inertia */
    TgVEC_F32_04_3                              m_mInv_MOI; /**< Inverse Moment of Inertia. */
    TgVEC_F32_04_1                              m_vCG; /**< Centre of gravity (mass). */
    TgUN_V128                                   m_uMass; /**< Mass value. */
    TgUN_V128                                   m_uInv_Mass; /**< Inverse mass value. */
};


/* -- Form ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Form, )
{
    STg2_UT_ST__ST_Node                         m_sStack_Node;
    TgPH_FORM_ID                                m_tiForm; /**< Unique identifier for this Form. */

    TgVEC_F32_04_1                              m_vPos_Last_Valid_W; /**< Previous Position of the Form in World Space. */
    TgVEC_F32_04_1                              m_vPos_W; /**< Position of the Form in World Space. */
    TgBOXAA_F32_04                              m_sBA; /**< Axis-Aligned Bounding Box of the Form. */
    TgVEC_F32_04_3                              m_mLocal; /**< Transform for the Form in the owning Body space. */
    TgVEC_F32_04_1                              m_vScale; /**< Scale that is applied in Body space prior to other transforms. */
    TgVEC_F32_04_3                              m_mFinal; /**< Transform into world space. */

    TgVEC_F32_04_1                              m_vDebug_Colour;

    TgPH_BODY_ID                                m_tiBody; /**< Parent Body. */
    TgPH_FORM_ID                                m_tiNext; /**< Next form that is linked to the same parent body. */
    TgPNS_OBJECT_ID                             m_tiPnS; /**< Prune and Sweep ID. */
    TgUINT_E64                                  m_uiCategory;  /**< Bitfield representing the fields this form is categorized. */
    TgUINT_E64                                  m_uiCollide; /**< Bitfield representing those fields this form collides. */

    STg2_PH_Form_Collision_CP                   m_psCollision; /**< Pointer to collision data. */

    TgFLOAT32                                   m_fDisable_Timer; /**< A measure of the time the form has experiened movement under the sleep threshold. */
    TgUINT_E32                                  m_uiPad;

    TgUINT_E64                                  m_bEnabled : 1; /**< Btifield boolean flag indicating that the Form is enabled. */
    TgUINT_E64                                  m_bUpdate_BA : 1; /**< Bitfield boolean flag indicating that the bounding box needs to be udpated. */

    TgUINT_E64                                  m_bDirty_F : 1; /**< Bitfield boolean flag indicating that the final transform needs to be udpated. */
    TgUINT_E64                                  m_bDirty : 1; /**< Bitfield boolean flag indicating that the object needs to be udpated. */
    TgUINT_E64                                  m_bDirty_IT : 1; /**< Bitfield boolean flag indicating that the Inertia Tensor needs to be udpated. */
    TgUINT_E64                                  m_bDirty_IIT : 1; /**< Bitfield boolean flag indicating that the Inverse Inertia Tensor needs to be udpated. */
    TgUINT_E64                                  m_bDirty_Q : 1; /**< Bitfield boolean flag indicating that the rotation needs to be udpated. */
    TgUINT_E64                                  m_bDirty_M : 1; /**< Bitfield boolean flag indicating that the moment needs to be udpated. */
    TgUINT_E64                                  m_bDirty_AM : 1; /**< Bitfield boolean flag indicating that the angular momentum needs to be udpated. */
    TgUINT_E64                                  m_uiPad1 : 55; /**< Bitfield boolean flag indicating that the angular momentum needs to be udpated. */
};


/* -- Body ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Body, )
{
    union
    {
        STg2_UT_ST__ST_Node                         m_sStack_Node;
        TgRSIZE                                     m_uiUsed_Index;
    };
    TgPH_BODY_ID                                m_tiBody;
    TgPH_FORM_ID                                m_tiForm; /**< The first form associated with this body.  */
    TgPH_CONSTRAINT_ID                          m_tiConstraint; /**< The first constraint associated with this body.  */

    STg2_PH_Mass                                m_sMass; /**< Mass representation in body space  */

    TgVEC_F32_04_1                              m_vPos_Last_Valid_W; /**< Last Position  */
    TgVEC_F32_04_1                              m_vPos_W; /**< Position  */
    TgVEC_F32_04_1                              m_vRot_W; /**< Rotation in quaternion form  */
    TgVEC_F32_04_3                              m_mRot_W; /**< Full Transform, used primarily for rotation  */

    TgVEC_F32_04_1                              m_vLV; /**< Linear Velocity  */
    TgVEC_F32_04_1                              m_vPF; /**< Persistent Force  */

    TgVEC_F32_04_1                              m_vAV; /**< Angular Velocity  */
    TgVEC_F32_04_1                              m_vPT; /**< Persistent Torque  */

    TgVEC_F32_04_1                              m_vTunneling; /**< Floating Point Flag - 1.0 if body tunnelled this frame.  */
    TgVEC_F32_04_1                              m_vForce_Field_Factor; /**< Floating Point Flag - 1.0 if influenced by the force field.  */
    TgVEC_F32_04_1                              m_vTime_Factor; /**< Used to manipulate time on a per-body basis (Matrix Effect).  */
    TgFLOAT32                                   m_fDisable_Timer; /**< Timer for auto-disabling the body  */
    TgUINT_E32                                  m_bEnabled : 1;
    TgUINT_E32                                  m_bRagdoll : 1;
    TgUINT_E32                                  m_bPad_1 : 30;

    TgCALCFM_FCN                                m_pfnCalcFM; /**< User defined function to generate force and moments.  */
    TgCONTACT_FCN                               m_pfnContact; /**< Function called when a contact occurs involving this body.  */
    TgMOVED_FCN                                 m_pfnMoved; /**< Function called when a contact occurs involving this body.  */
    TgUINT_PTR                                  m_uiContext; /**< Void pointed passed into one of the user defined call backs.  */

    TgUINT_E64                                  m_uiCategory;  /**< Bitfield representing the fields this form is categorized  */

                                                /* Calculated and used during world update. */
    TgVEC_F32_04_3                              m_mInverse_Inertia_Tensor; /**< Inverse Inertia Tensor: Used to transform torque into rotation updates, and in the solver. */
    TgVEC_F32_04_1                              m_vXF; /**< Force Accumulation: Used for predicted and final position. */
    TgVEC_F32_04_1                              m_vXT; /**< Torque Accumulation: Used for predicted and final rotation. */
};


/* -- Motor ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Motor,)
{
    STg2_UT_ST__ST_Node                         m_sStack_Node;
    TgPH_MOTOR_ID                               m_tiMotor;
    TgUINT_E64                                  m_uiCategory;  /**< Bitfield representing the fields this form is categorized  */
};


/* -- Constraints ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */


TgTYPE_STRUCT(STg2_PH_Constraint_Ball_Socket,)
{
    TgVEC_F32_04_1                              m_vPad;
};

TgTYPE_STRUCT(STg2_PH_Constraint_Contact,)
{
    TgVEC_F32_04_1                              m_vPad;
};

TgTYPE_STRUCT(STg2_PH_Constraint,)
{
    STg2_UT_ST__ST_Node                         m_sStack_Node;
    TgPH_CONSTRAINT_ID                          m_tiConstraint; /**< Unique identifier for this constraint. */
    TgUINT_E64                                  m_uiCategory;  /**< Bitfield representing the fields this form is categorized  */
    TgPH_BODY_ID                                m_tiBody_0; /**< Identifier for the first body in the constraint. */
    TgPH_CONSTRAINT_ID                          m_tiNext_0; /**< Identifier for the next constraint that is associated with Body 0. */
    TgPH_BODY_ID                                m_tiBody_1; /**< Identifier for the second body in the constraint. */
    TgPH_CONSTRAINT_ID                          m_tiNext_1; /**< Identifier for the next constraint that is associated with Body 1. */

    TgUINT_E32                                  m_nuiDoF; /**< Number of degrees of freedom for the joint. */

    TgFLOAT32                                   m_fMin; /**< Lower Limit, Point of compression failure. */
    TgFLOAT32                                   m_fMax; /**< Upper Limit, Point of fracture. */
    TgFLOAT32                                   m_fMax_Force;
    TgFLOAT32                                   m_fMax_Moment;
    TgFLOAT32                                   m_fμs, m_fμd; /**< Static and Dynamic coefficients of friction. */

    ETgPH_CONSTRAINT                            m_enConstraint;

    TgUINT_E64                                  m_bBreakable : 1;
    TgUINT_E64                                  m_bEnabled : 1;
    TgUINT_E64                                  m_uiPad : 62;

    TgVEC_F32_04_1                              m_vOffset;

    TgVEC_F32_04_1                              m_VFoR_Rot; /**< Frame of Reference of the constraint, Quaternion */
    TgVEC_F32_04_1                              m_VFoR_Pos; /**< Frame of Reference of the constraint, Position */

    union {
        STg2_PH_Constraint_Ball_Socket          m_sBall_Socket;
        STg2_PH_Constraint_Contact              m_sContact;
    };

#if defined(TGS_PS_JOINT_FEEDBACK)
    TgVEC_F32_04_1                              m_tvF0, m_tvT0;
    TgVEC_F32_04_1                              m_tvF1, m_tvT1;
#endif
};


/* -- Ragdoll -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Ragdoll_Bone,)
{
    TgVEC_F32_04_3                              m_mTX_W; /**< Bone[3D] in the rag doll reference frame. */
    TgVEC_F32_04_1                              m_vPos_0; /**< Position of the untransformed, neutral animated bone. */
    TgBOXAA_F32_04                              m_sAABB; /**< AABB for joint in its own reference frame. */

    TgFLOAT32                                   m_fOrig_Length; /**< Original length of the bone. */
    TgUINT_E32                                  m_idxParent;
    TgUINT_E32                                  m_idxBone;
    TgFLOAT32                                   m_fMass; /**< Mass of the object. */
    ETgPRIMITIVE                                m_enPM; /**< Primitive used to represent this bone (e.g. capsule/sphere) */
    ETgPH_CONSTRAINT                            m_enCN; /**< Constraint type connecting this bone (e.g. ball socket, hinge) */

    STg2_PH_Body_P                              m_psBody; /**< The primary simulation object (force/moments etc.). */
    STg2_PH_Form_P                              m_psForm; /**< Geometric definition defined in the simulation state machine. */
    STg2_PH_Motor_P                             m_psMotor; /**< Used to drive the simulation to the animation state. */
    STg2_PH_Constraint_P                        m_psConstraint; /**< The constraint binding this bone to the rag doll tree. */
    TgUINT_E08                                  m_uiPad[8];
};


TgTYPE_STRUCT(STg2_PH_Ragdoll,)
{
    STg2_UT_ST__ST_Node                         m_sStack_Node;
    TgPH_RAGDOLL_ID                             m_tiRagdoll;
    TgUINT_E64                                  m_uiCategory;  /**< Bitfield representing the fields this form is categorized. */

    STg2_PH_Ragdoll_Bone_P                      m_atgBone[KTgPH_MAX_BONES]; /**< List of rag doll bones */
    TgRSIZE                                     m_nuiBone; /**< Number of rag doll bones. */

    TgVOID_P                                    m_pOwner; /// The owning object - most often an actor

    TgUINT_E64                                  m_bConstraint_Init : 1;
    TgUINT_E64                                  m_bConstraint_Locked : 1;
    TgUINT_E64                                  m_uiPad : 62;
};


/* ---- Scene -------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Scene,)
{
    STg2_UT_ST__ST_Node                         m_sStack_Node;
    TgPH_SCENE_ID                               m_tiScene;
};


/* ---- World ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_World,)
{
    TgPH_WORLD_ID                               m_tiWorld;

                                                /* Solver Configuration */
    TgRSIZE                                     m_uiSimulate_Min_Batch_Size; /**< Minimum number of bodies per job call. */
    TgRSIZE                                     m_uiCollide_Min_Batch_Size; /**< Minimum number of forms per job call. */
    TgRSIZE                                     m_uiSolver_Min_Body_Per_Job; /**< Minimum number of bodies per job call. */
    TgRSIZE                                     m_uiSolver_Min_DoF_Per_Job; /**< Minimum number of degrees of freedom per job call. */
    TgRSIZE                                     m_nuiSolver_Iterations; /**< Number of iterations of the solver loop to execute. */

    TgFLOAT32                                   m_fCFM;
    TgFLOAT32                                   m_fStep_Size_Seconds; /**< Floating point time step in seconds used for each simulation step. */

    TgFLOAT32                                   m_fThreshold__Depth; /**< The penetration depth sleep threshold. */
    TgUINT_E32                                  m_uiPad;
    TgVEC_F32_04_1                              m_vThreshold__LV_LSQ; /**< The linear velocity sleep threshold. */
    TgVEC_F32_04_1                              m_vThreshold__AV_LSQ; /**< The angular velocity sleep threshold. */

                                                /* World Configuration */
    TgVEC_F32_04_1                              m_vForce_Field; /**< The acceleration field applied to all bodies during simulation. */
    TgVEC_F32_04_1                              m_vStep_Size; /**< The size of the fixed time step used during update. */

                                                /* Run Time Configuration */
    TgUINT_E64                                  m_uiPaused : 1; /**< True if the world is in a pause state, and false otherwise. */
    TgUINT_E64                                  m_uiSingle_Step : 1; /**< True if the module should execute a single step, and false otherwise. */
    TgUINT_E64                                  m_uiSimulate : 1; /**< True if the simulation pass is active, and false otherwise. */
    TgUINT_E64                                  m_uiCollide : 1; /**< True if the collision pass is active, and false otherwise. */
    TgUINT_E64                                  m_uiPad1 : 60;

                                                /* Serialization */
    STg2_PH_Scene_P                             m_psScene; /**< List of all the scenes associated with this world. */
};


/* ---- Solver ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT( STg2_PH_Update__Simulation, )
{
                                                /* These lists are 1:1 with g_aapsBody_Used. */
    TgVEC_F32_04_1_P                            m_avPos_W; /**< Predicted Position: Used in Collision Pass */
    TgVEC_F32_04_1_P                            m_avRot_W; /**< Predicted Rotation: Used in Collision Pass */
    TgVEC_F32_04_1_P                            m_avRHS_LA; /**< Linear, Angular Right Hand Side component, used in Constraint Coefficient generation to finalize RHS. */
};

TgTYPE_STRUCT( STg2_PH_Update__Contact, )
{
    TgVEC_F32_04_1                              m_vS0_W; /**< Position of Contact */
    TgVEC_F32_04_1                              m_vN0_W; /**< Normal of impact */
    TgFLOAT32                                   m_fT0; /**< Sweep time value */
    TgFLOAT32                                   m_fDepth; /**< Penetration depth */
    TgPH_FORM_ID                                m_tiForm0;
    TgPH_FORM_ID                                m_tiForm1; /**< The two forms involved in the contact */
    TgPH_MATERIAL_ID                            m_tiMaterial; /**< The material used to describe the contact */
};

TgTYPE_STRUCT( STg2_PH_Solver__Set, )
{
                                                /* Generated when creating the closed sets for the solver jobs. */
    STg2_PH_Body_PP                             m_apsBody; /**< List of all the bodies in this world. */
    TgRSIZE                                     m_nuiBody; /**< Number of bodies in the set. */

    STg2_PH_Constraint_PP                       m_apsConstraint[ETgPH_CONSTRAINT__MAX]; /**< Lists of all the constraints in this world. */
    TgRSIZE                                     m_nuiConstraint[ETgPH_CONSTRAINT__MAX]; /**< Count of constraints by constraint type. */
    TgRSIZE_P                                   m_apuiDoF[ETgPH_CONSTRAINT__MAX]; /**< The DoF count when this constraint was added to the set. */
    TgRSIZE                                     m_nuiDoF; /**< Total sum of the number of degrees of freedom. Total rows in the Jacobian. */
    TgRSIZE                                     m_nuiConstraint_Total; /**< Total sum of the number of degrees of freedom. Total rows in the Jacobian. */
    TgVEC_F32_04_1_P                            m_avInverse_Mass_Inertia_Tensor; /**< Inverse Mass, Inverse Inertia Tensor for each constraint and each body in the constraint. */

                                                /* Generated data (per DoF, Body) representing the requirements (constraints) of the solution. */
    TgVEC_F32_04_1_P                            m_avProblem_Coefficients; /**< Linear constraints in constraint space. Memory layout by DoF for cache purposes. */
    TgRSIZE_P                                   m_auiJacobian_Index; /**< The two bodies associated with each DoF; */
    TgVEC_F32_04_1_P                            m_avResult; /**< Resulting Force and Torque per body from the solver. */
};


/* ---- Job Data ----------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Simulate_Data,)
{
    TgPH_WORLD_ID TgALIGN(16)                   m_tiWorld;
    TgRSIZE                                     m_uiBody_Index_Begin;
    TgRSIZE                                     m_uiBody_Index_End;
    TgUINT_E08                                  m_uiPad[8];
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Simulate_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Collide_Data,)
{
    TgPH_WORLD_ID TgALIGN(16)                   m_tiWorld;
    TgRSIZE                                     m_uiForm_Index_Begin;
    TgRSIZE                                     m_uiForm_Index_End;
    TgBOOL                                      m_bExecute_Command_Buffer;
    TgUINT_E08                                  m_uiPad[7];
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Collide_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Build_Set_Data,)
{
    TgPH_WORLD_ID TgALIGN(16)                   m_tiWorld;
    TgUINT_E08                                  m_uiPad[8];
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Build_Set_Data ) <= KTgJOB_DATA_SIZE, 0 );

TgTYPE_STRUCT(STg2_PH_Job__Update_World__Solve_Set_Data,)
{
    TgPH_WORLD_ID TgALIGN(16)                   m_tiWorld;
    STg2_PH_Solver__Set                         m_sSolver_Set;
};
TgCOMPILER_ASSERT( sizeof( STg2_PH_Job__Update_World__Solve_Set_Data ) <= KTgJOB_DATA_SIZE, 0 );


/* =============================================================================================================================================================================== */
#endif

