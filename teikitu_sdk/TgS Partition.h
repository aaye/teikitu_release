/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PARTITION_H)
#define TGS_PARTITION_H
#pragma once

#define TGS_PLATFORM_PARTITION_H

#include "TgS PARTITION/TgS Partition - Constants.h"
#include "TgS PARTITION/TgS Partition - Type.h"
#include "TgS PARTITION/TgS Partition - Data.h"


/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Partition Interface                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* -- Prune and Sweep ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

                                            /** @brief Initialize a prune and sweep object
                                                @param [in,out] ARG0 Pointer to the prune and sweep system. */
TgEXTN TgVOID                               tgPA_PnS_Init( STg2_PA_PnS_PCU ARG0 );

                                            /** @brief Initialize a prune and sweep object
                                                @param [in] ARG0 Pointer to the prune and sweep system.
                                                @param [in] ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter. */
TgEXTN TgRESULT                             tgPA_PnS_Exe_Func( STg2_PA_PnS_PCU ARG0, TgVOID(*ARG1)( TgUINT_MAX_C, TgUINT_MAX_C ) );

                                            /** @brief Insert a bounding box into the system.
                                                @param [in] ARG0 Pointer to the prune and sweep system.
                                                @param [in] ARG1 Integer user data field.
                                                @param [in] ARG2 Integer category field.
                                                @param [in] ARG3 Integer collide bitmask.
                                                @param [in] ARG4 Pointer to axis aligned bounding box to be added to the system.
                                                @return Unique identifier for the object inserted. */
TgEXTN TgPNS_OBJECT_ID                      tgPA_PnS_Insert_Object( STg2_PA_PnS_PCU ARG0, TgUINT_MAX_C ARG1, TgUINT_F64_C ARG2, TgUINT_F64_C ARG3, TgBOXAA_F32_04_CPCU ARG4 );

                                            /** @brief Remove an object from the system.
                                                @param [in] ARG0 Pointer to the prune and sweep system.
                                                @param [in] ARG1 Unique identifier for the object.
                                                @return Result Code. */
TgEXTN TgRESULT                             tgPA_PnS_Remove_Object( STg2_PA_PnS_PCU ARG0, TgPNS_OBJECT_ID_C ARG1 );

                                            /** @brief Initialize a prune and sweep object
                                                @param [in] ARG0 Pointer to the prune and sweep system.
                                                @param [in] ARG1 Integer category bitfield.
                                                @param [in] ARG2 Integer collision bitfield.
                                                @param [in] ARG3 Pointer to an axis aligned bounding box for testing.
                                                @return True if the objects collide and false otherwise. */
TgEXTN TgBOOL                               tgPA_PnS_Test_AABB( STg2_PA_PnS_PCU ARG0, TgUINT_F64_C ARG1, TgUINT_F64_C ARG2, TgBOXAA_F32_04_CPCU ARG3 );

                                            /** @brief Update the axis aligned bounding box for the given object.
                                                @param [in] ARG0 Pointer to the prune and sweep system.
                                                @param [in] ARG1 Unique identifier for the object.
                                                @param [in] ARG2 Pointer to axis aligned bounding box to be added to the system.
                                                @return Result Code. */
TgEXTN TgRESULT                             tgPA_PnS_Object_Update( STg2_PA_PnS_PCU ARG0, TgPNS_OBJECT_ID_C ARG1, TgBOXAA_F32_04_CPCU ARG2 );

                                            /** @brief Initialize a prune and sweep object
                                                @param [in] ARG0 Pointer to the prune and sweep system.
                                                @param [in] ARG1 Unique identifier for the object.
                                                @param [in] ARG2 ARG1 Function pointer to execute on contact/collision between two objects using the user data as the parameter.
                                                @return Result Code. */
TgEXTN TgRESULT                             tgPA_PnS_Object_Exe_Func( STg2_PA_PnS_PCU ARG0, TgPNS_OBJECT_ID_C ARG1, TgVOID(*ARG2)( TgUINT_MAX_C, TgUINT_MAX_C ) );


/* =============================================================================================================================================================================== */
#endif
