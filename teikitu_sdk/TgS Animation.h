/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Animation.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_ANIMATION_H)
#define TGS_ANIMATION_H
#pragma once

#define TGS_PLATFORM_ANIMATION_H



/* **** STUB FILE ****/



/* == Animation ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Module Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgAM_Module_Init( TgVOID ) { return KTgS_OK; }

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgINLINE TgRESULT
tgAM_Module_Boot( TgVOID ) { return KTgS_OK; }

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgINLINE TgVOID
tgAM_Module_Stop( TgVOID ) {}

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgINLINE TgVOID
tgAM_Module_Free( TgVOID ) {}

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgINLINE TgRESULT
tgAM_Module_Update(
    TgFLOAT32_C TgATTRIBUTE_MAYBE_UNUSED ARG0 ) { return KTgS_OK; }


/** @brief Standard Module functions: Set the current configuration of the module. */
TgINLINE TgRESULT
tgAM_Load_Config( TgVOID ) { return KTgS_OK; }

/** @brief Standard Module function: Save the current configuration of the module. */
TgINLINE TgRESULT
tgAM_Save_Config( TgVOID ) { return KTgS_OK; }


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgINLINE TgBOOL
tgAM_Query_Init( TgVOID ) { return true; }

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgINLINE TgBOOL
tgAM_Query_Boot( TgVOID ) { return true; }

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgINLINE TgRSIZE
tgAM_Query_Fixed_Memory( TgVOID ) { return 0u; }




// /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
// /*  Animation System Functions                                                                                                                                                     */
// /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

// TgEXTN TgRESULT
// tgAM__Server__Update_Prediction(
//     TgFLOAT32_C );

// TgEXTN TgRESULT
// tgAM__Client__Update_PreInput(
//     TgFLOAT32_C );

// TgEXTN TgRESULT
// tgAM__Client__Update_PostInput(
//     TgFLOAT32_C );





// /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
// /*  Animation Resource Functions                                                                                                                                                   */
// /* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

// /* -- File Management ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// /* 1: Name Hash - Hash of the unique name (key) for this resource. */
// /* 2: Input Stream - The data stream representing the resource. */
// /* 3: Call Back Parameter - Extra parameter passed to the call back */
// /* 4: Call Back - The function (if defined) is called when loading is complete */
// TgEXTN TgAM_FILE_ID
// tgAM_Load_File(
//     TgUINT_F32_C, STg2_Input_CPC, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgAM_FILE_ID_C ) );  /* #IMPLEMENT */

// /* Free_File - Decrements reference count and closes the input stream on zero */
// TgEXTN TgUINT_F32
// tgAM_Free_File(
//     TgAM_FILE_ID_C );  /* #IMPLEMENT */

// /* Is_Filed_Loaded - Polling function to determine if a specific file has loaded */
// TgEXTN TgUINT_F32
// tgAM_Is_File_Loaded(
//     TgAM_FILE_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_Query_File_Skeleton_Count(
//     TgAM_FILE_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_Query_File_Key_Frame_Animation_Count(
//     TgAM_FILE_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_Query_File_Morph_Target_Count(
//     TgAM_FILE_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_Query_File_Skeleton_Animation_Count(
//     TgAM_FILE_ID_C );  /* #IMPLEMENT */


// /* -- Skeleton ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

// TgEXTN TgAM_SKELETON_DATA_ID
// tgAM_Init_SK(
//     TgAM_FILE_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_Free_SK(
//     TgAM_SKELETON_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_SK_Query_Bone_Count(
//     TgAM_SKELETON_DATA_ID_C );  /* #IMPLEMENT */

// /* 2: Index - Skeleton index for the queried bone */
// /* R: Name Hash - Hash of the unique name for the bone, the empty hash if not found */
// TgEXTN TgUINT_F32
// tgAM_SK_Query_Bone_Name_Hash(
//     TgAM_SKELETON_DATA_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// /* 2: Name Hash - Hash of the unique name (key) for the bone. */
// /* R: Index - Skeleton index of the queried bone, negative if not found */
// TgEXTN TgSINT_F32
// tgAM_SK_Query_Bone_Index(
//     TgAM_SKELETON_DATA_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// /* 3: Index - Skeleton index for the queried bone */
// TgEXTN TgRESULT
// tgAM_SK_Query_Bone_Bind(
//     TgVEC_F32_04_3_PCU, TgAM_SKELETON_DATA_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// /* 3: Index - Skeleton index for the queried bone */
// TgEXTN TgRESULT
// tgAM_SK_Query_Bone_Inverse_Bind(
//     TgVEC_F32_04_3_PCU, TgAM_SKELETON_DATA_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */


// /* Instance Interface ---------------------------------------------------------------------------------------------------------------- */

// TgEXTN TgAM_SKELETON_INST_ID
// tgAM_SK_Init_Inst(
//     TgAM_SKELETON_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SK_Free_Inst(
//     TgAM_SKELETON_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_SK_Query_Bone(
//     TgVEC_F32_04_3_PCU, TgAM_SKELETON_INST_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgSINT_F32
// tgAM_SK_Query_Tag_Count(
//     tgAM_MESH_SET_ID_C ); /* #IMPLEMENT */ /* Query_Tag_Count - Return the number of tags in the mesh */

// /* Query_Tag_ID - Return the Tag ID associated with a specific literal.  Since all tags are required to have a unique name  */
// /* within a mesh this will be a guaranteed 1:1 mapping. */
// TgEXTN TgSINT_F32                    
// tgAM_SK_Query_Tag(
//     tgAM_MESH_SET_ID_C, TgUINT_F32_C ); /* #IMPLEMENT */

// TgEXTN TgVEC_F32_04_1
// tgAM_SK_Query_Tag_Position(
//     tgAM_MESH_SET_ID_C, TgSINT_F32_C ); /* #IMPLEMENT */ /* Query_Tag_Position - Return the position of the tag. */

// TgEXTN TgVEC_F32_04_1
// tgAM_SK_Query_Tag_Rotation(
//     tgAM_MESH_SET_ID_C, TgSINT_F32_C ); /* #IMPLEMENT */ /* Query_Tag_Rotation - Return the rotation of the tag. */


// /* -- Key Frame ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

// TgEXTN TgAM_KEY_FRAME_ANIM_DATA_ID
// tgAM_KF_Init_Animation(
//     TgAM_FILE_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_KF_Free_Animation(
//     TgAM_KEY_FRAME_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_KF_Set_Animation_Priority(
//     TgAM_KEY_FRAME_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_KF_Set_Animation_Request(
//     TgAM_KEY_FRAME_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_KF_Set_Animation_Force_Resident(
//     TgAM_KEY_FRAME_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_KF_Is_Animation_Cached(
//     TgAM_KEY_FRAME_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_KF_Query_Animation_Name_Hash(
//     TgAM_KEY_FRAME_ANIM_DATA_ID_C );  /* #IMPLEMENT */


// /* Instance Interface ---------------------------------------------------------------------------------------------------------------- */

// /* Play_Animation */
// /* 2: Loop Count */
// /* 3: Call Back Parameter - Extra parameter passed to the call back */
// /* 4: Call Back - The function (if defined) is called when animation is complete */
// TgEXTN TgAM_KEY_FRAME_ANIM_INST_ID
// tgAM_KF_Play_Animation(
//     TgAM_KEY_FRAME_ANIM_DATA_ID_C, TgUINT_F32_C, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgAM_KEY_FRAME_ANIM_INST_ID_C) );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_KF_Kill_Animation(
//     TgAM_KEY_FRAME_ANIM_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_KF_Stop_Animation(
//     TgAM_KEY_FRAME_ANIM_INST_ID_C, TgFLOAT32_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_KF_Set_Animation_Completion_Call_Back(
//     TgAM_KEY_FRAME_ANIM_INST_ID_C, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgAM_KEY_FRAME_ANIM_INST_ID_C) );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_KF_Set_Animation_Speed(
//     TgAM_KEY_FRAME_ANIM_INST_ID_C, TgFLOAT32_C );  /* #IMPLEMENT */

// TgEXTN TgAM_KEY_FRAME_ANIM_DATA_ID
// tgMA_KF_Query_Animation_Data(
//     TgAM_KEY_FRAME_ANIM_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgFLOAT32
// tgAM_KF_Query_Animation_Speed(
//     TgAM_KEY_FRAME_ANIM_INST_ID_C );  /* #IMPLEMENT */


// /* -- Morph Target --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

// TgEXTN TgAM_MORPH_TARGET_DATA_ID
// tgAM_MT_Init(
//     TgAM_FILE_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_MT_Free(
//     TgAM_MORPH_TARGET_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_MT_Set_Animation_Priority(
//     TgAM_MORPH_TARGET_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_MT_Set_Animation_Request(
//     TgAM_MORPH_TARGET_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_MT_Set_Animation_Force_Resident(
//     TgAM_MORPH_TARGET_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_MT_Is_Animation_Cached(
//     TgAM_MORPH_TARGET_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_MT_Query_Name_Hash(
//     TgAM_MORPH_TARGET_DATA_ID_C );  /* #IMPLEMENT */


// /* Instance Interface ---------------------------------------------------------------------------------------------------------------- */

// /* 2: Loop Count */
// /* 3: Call Back Parameter - Extra parameter passed to the call back */
// /* 4: Call Back - The function (if defined) is called when animation is complete */
// TgEXTN TgAM_MORPH_TARGET_INST_ID
// tgAM_MT_Play(
//     TgAM_MORPH_TARGET_DATA_ID_C, TgUINT_F32_C, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgAM_MORPH_TARGET_INST_ID_C) );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_MT_Kill(
//     TgAM_MORPH_TARGET_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_MT_Stop(
//     TgAM_MORPH_TARGET_INST_ID_C, TgFLOAT32_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_MT_Set_Completion_Call_Back(
//     TgAM_MORPH_TARGET_INST_ID_C, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgAM_MORPH_TARGET_INST_ID_C) );  /* #IMPLEMENT */

// TgEXTN TgAM_MORPH_TARGET_DATA_ID
// tgMA_MT_Query_Animation_Data(
//     TgAM_MORPH_TARGET_INST_ID_C );  /* #IMPLEMENT */


// /* -- Skeleton Animation --------------------------------------------------------------------------------------------------------------------------------------------------------- */

// TgEXTN TgAM_SKELETON_ANIM_DATA_ID
// tgAM_Init_SA(
//     TgAM_FILE_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_Free_SA(
//     TgAM_SKELETON_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SA_Set_Priority(
//     TgAM_SKELETON_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SA_Set_Request(
//     TgAM_SKELETON_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SA_Set_Force_Resident(
//     TgAM_SKELETON_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SA_Is_Cached(
//     TgAM_SKELETON_ANIM_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_SA_Query_Name_Hash(
//     TgAM_SKELETON_ANIM_DATA_ID_C );  /* #IMPLEMENT */


// /* Instance Interface ---------------------------------------------------------------------------------------------------------------- */

// /* Play_Skeleton_Animation - Create an instance of a skeleton animation */
// /* 2: Loop Count */
// /* 3: Ease In */
// /* 4: Ease Out */
// /* 5: Call Back Parameter - Extra parameter passed to the call back */
// /* 6: Completion Call Back - Executed on main thread, called after animation ends */
// TgEXTN TgAM_SKELETON_ANIM_INST_ID
// tgAM_SA_Play(
//     TgAM_SKELETON_ANIM_DATA_ID_C, TgUINT_F32_C, TgFLOAT32_C, TgFLOAT32_C, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgAM_SKELETON_ANIM_INST_ID_C) );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SA_Kill(
//     TgAM_SKELETON_ANIM_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SA_Stop(
//     TgAM_SKELETON_ANIM_INST_ID_C, TgFLOAT32_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SA_Set_Completion_Call_Back(
//     TgAM_SKELETON_ANIM_INST_ID_C, TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgAM_SKELETON_ANIM_INST_ID_C) );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SA_Set_Speed(
//     TgAM_SKELETON_ANIM_INST_ID_C, TgFLOAT32_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SA_Set_Time(
//     TgAM_SKELETON_ANIM_INST_ID_C, TgFLOAT32_C );  /* #IMPLEMENT */

// TgEXTN TgAM_SKELETON_ANIM_DATA_ID
// tgAM_SA_Query_Data(
//     TgAM_SKELETON_ANIM_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgFLOAT32
// tgAM_SA_Query_Duration(
//     TgAM_SKELETON_ANIM_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgFLOAT32
// tgAM_SA_Query_Speed(
//     TgAM_SKELETON_ANIM_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgFLOAT32
// tgAM_SA_Query_Time(
//     TgAM_SKELETON_ANIM_INST_ID_C );  /* #IMPLEMENT */


// /* -- State Machine -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

// TgEXTN TgAM_MACHINE_DATA_ID
// tgAM_Init_SM(
//     TgAM_FILE_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgUINT_F32
// tgAM_Free_SM(
//     TgAM_MACHINE_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgAM_MACHINE_VAR_ID
// tgAM_SM_Query_Variable_Id(
//     TgAM_MACHINE_DATA_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgAM_MACHINE_STATE_ID
// tgAM_SM_Query_State_Index(
//     TgAM_MACHINE_DATA_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */


// /* Instance Interface ---------------------------------------------------------------------------------------------------------------- */

// TgEXTN TgAM_MACHINE_INST_ID
// tgAM_SM_Init_Inst(
//     TgAM_MACHINE_DATA_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SM_Free_Inst(
//     TgAM_MACHINE_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SM_Set_Skeleton(
//     TgAM_MACHINE_INST_ID_C, TgAM_SKELETON_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SM_Set_Event_Call_Back(
//     TgUINT_PTR_C, TgVOID(*)( TgUINT_PTR_C, TgUINT_F32_C, TgAM_MACHINE_INST_ID_C) );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SM_Set_Variable(
//     TgAM_MACHINE_INST_ID_C, TgAM_MACHINE_VAR_ID_C, STg2_AM_Variable_Data_CPCU );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SM_Query_Variable(
//     STg2_AM_Variable_Data_PCU, TgAM_MACHINE_INST_ID_C, TgAM_MACHINE_VAR_ID_C );  /* #IMPLEMENT */


// /* Instance - State Interface -------------------------------------------------------------------------------------------------------- */

// TgEXTN TgRESULT
// tgAM_SM_Enter_State(
//     TgAM_MACHINE_INST_ID_C, TgAM_MACHINE_STATE_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgRESULT
// tgAM_SM_Exit_State(
//     TgAM_MACHINE_INST_ID_C, TgAM_MACHINE_STATE_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgBOOL
// tgAM_SM_Is_State_Active(
//     TgAM_MACHINE_INST_ID_C, TgAM_MACHINE_STATE_ID_C );  /* #IMPLEMENT */


// /* Instance - Motion Interface ------------------------------------------------------------------------------------------------------- */

// TgEXTN TgVOID
// tgAM_SM_Update_Desired_State(
//     TgAM_MACHINE_INST_ID_C, TgFLOAT32_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SM_Update_State(
//     TgAM_MACHINE_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVOID
// tgAM_SM_Set_Valid_Motion(
//     TgAM_MACHINE_INST_ID_C, TgVEC_F32_04_1_C );  /* #IMPLEMENT */

// /* 1: Frame Translation */
// /* 2: Frame Rotation */
// TgEXTN TgVOID
// tgAM_SM_Query_Desired_Motion(
//     TgVEC_F32_04_1_PCU, TgVEC_F32_04_1_PCU, TgAM_MACHINE_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVEC_F32_04_3_P
// tgAM_SM_Query_Key_Frame_Animation(
//     TgAM_MACHINE_INST_ID_C, TgUINT_F32_C );  /* #IMPLEMENT */

// TgEXTN TgVEC_F32_04_3_P
// tgAM_SM_Query_Morph_Target(
//     TgAM_MACHINE_INST_ID_C, tgAM_MESH_SET_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVEC_F32_04_3_P
// tgAM_SM_Query_Bone_List(
//     TgAM_MACHINE_INST_ID_C );  /* #IMPLEMENT */

// TgEXTN TgVEC_F32_04_3_P
// tgAM_SM_Query_Last_Bone_List(
//     TgAM_MACHINE_INST_ID_C );  /* #IMPLEMENT */


/* =============================================================================================================================================================================== */
#endif
