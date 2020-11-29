// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FBPUniqueNetId;
#ifdef ADVANCEDSESSIONS_AdvancedVoiceLibrary_generated_h
#error "AdvancedVoiceLibrary.generated.h already included, missing '#pragma once' in AdvancedVoiceLibrary.h"
#endif
#define ADVANCEDSESSIONS_AdvancedVoiceLibrary_generated_h

#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_SPARSE_DATA
#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetNumLocalTalkers) \
	{ \
		P_GET_PROPERTY_REF(UIntProperty,Z_Param_Out_NumLocalTalkers); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::GetNumLocalTalkers(Z_Param_Out_NumLocalTalkers); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnMuteRemoteTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalUserNum); \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_GET_UBOOL(Z_Param_bIsSystemWide); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::UnMuteRemoteTalker(Z_Param_LocalUserNum,Z_Param_Out_UniqueNetId,Z_Param_bIsSystemWide); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMuteRemoteTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalUserNum); \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_GET_UBOOL(Z_Param_bIsSystemWide); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::MuteRemoteTalker(Z_Param_LocalUserNum,Z_Param_Out_UniqueNetId,Z_Param_bIsSystemWide); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsPlayerMuted) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalUserNumChecking); \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsPlayerMuted(Z_Param_LocalUserNumChecking,Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsRemotePlayerTalking) \
	{ \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsRemotePlayerTalking(Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsLocalPlayerTalking) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsLocalPlayerTalking(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveAllRemoteTalkers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::RemoveAllRemoteTalkers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnRegisterRemoteTalker) \
	{ \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::UnRegisterRemoteTalker(Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegisterRemoteTalker) \
	{ \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::RegisterRemoteTalker(Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnRegisterAllLocalTalkers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::UnRegisterAllLocalTalkers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnRegisterLocalTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::UnRegisterLocalTalker(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegisterAllLocalTalkers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::RegisterAllLocalTalkers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegisterLocalTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::RegisterLocalTalker(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStopNetworkedVoice) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::StopNetworkedVoice(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStartNetworkedVoice) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::StartNetworkedVoice(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsHeadsetPresent) \
	{ \
		P_GET_UBOOL_REF(Z_Param_Out_bHasHeadset); \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::IsHeadsetPresent(Z_Param_Out_bHasHeadset,Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetNumLocalTalkers) \
	{ \
		P_GET_PROPERTY_REF(UIntProperty,Z_Param_Out_NumLocalTalkers); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::GetNumLocalTalkers(Z_Param_Out_NumLocalTalkers); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnMuteRemoteTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalUserNum); \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_GET_UBOOL(Z_Param_bIsSystemWide); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::UnMuteRemoteTalker(Z_Param_LocalUserNum,Z_Param_Out_UniqueNetId,Z_Param_bIsSystemWide); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execMuteRemoteTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalUserNum); \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_GET_UBOOL(Z_Param_bIsSystemWide); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::MuteRemoteTalker(Z_Param_LocalUserNum,Z_Param_Out_UniqueNetId,Z_Param_bIsSystemWide); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsPlayerMuted) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalUserNumChecking); \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsPlayerMuted(Z_Param_LocalUserNumChecking,Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsRemotePlayerTalking) \
	{ \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsRemotePlayerTalking(Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsLocalPlayerTalking) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsLocalPlayerTalking(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRemoveAllRemoteTalkers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::RemoveAllRemoteTalkers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnRegisterRemoteTalker) \
	{ \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::UnRegisterRemoteTalker(Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegisterRemoteTalker) \
	{ \
		P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::RegisterRemoteTalker(Z_Param_Out_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnRegisterAllLocalTalkers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::UnRegisterAllLocalTalkers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execUnRegisterLocalTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::UnRegisterLocalTalker(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegisterAllLocalTalkers) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::RegisterAllLocalTalkers(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRegisterLocalTalker) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::RegisterLocalTalker(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStopNetworkedVoice) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::StopNetworkedVoice(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execStartNetworkedVoice) \
	{ \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::StartNetworkedVoice(Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execIsHeadsetPresent) \
	{ \
		P_GET_UBOOL_REF(Z_Param_Out_bHasHeadset); \
		P_GET_PROPERTY(UByteProperty,Z_Param_LocalPlayerNum); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedVoiceLibrary::IsHeadsetPresent(Z_Param_Out_bHasHeadset,Z_Param_LocalPlayerNum); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAdvancedVoiceLibrary(); \
	friend struct Z_Construct_UClass_UAdvancedVoiceLibrary_Statics; \
public: \
	DECLARE_CLASS(UAdvancedVoiceLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSessions"), NO_API) \
	DECLARE_SERIALIZER(UAdvancedVoiceLibrary)


#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_INCLASS \
private: \
	static void StaticRegisterNativesUAdvancedVoiceLibrary(); \
	friend struct Z_Construct_UClass_UAdvancedVoiceLibrary_Statics; \
public: \
	DECLARE_CLASS(UAdvancedVoiceLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSessions"), NO_API) \
	DECLARE_SERIALIZER(UAdvancedVoiceLibrary)


#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAdvancedVoiceLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAdvancedVoiceLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAdvancedVoiceLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAdvancedVoiceLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAdvancedVoiceLibrary(UAdvancedVoiceLibrary&&); \
	NO_API UAdvancedVoiceLibrary(const UAdvancedVoiceLibrary&); \
public:


#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAdvancedVoiceLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAdvancedVoiceLibrary(UAdvancedVoiceLibrary&&); \
	NO_API UAdvancedVoiceLibrary(const UAdvancedVoiceLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAdvancedVoiceLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAdvancedVoiceLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAdvancedVoiceLibrary)


#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_26_PROLOG
#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_SPARSE_DATA \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_RPC_WRAPPERS \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_INCLASS \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_SPARSE_DATA \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ADVANCEDSESSIONS_API UClass* StaticClass<class UAdvancedVoiceLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
