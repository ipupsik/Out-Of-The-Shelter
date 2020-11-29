// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FBPSteamGroupInfo;
struct FBPUniqueNetId;
enum class EBlueprintResultSwitch : uint8;
enum class ESteamUserOverlayType : uint8;
enum class EBlueprintAsyncResultSwitch : uint8;
enum class SteamAvatarSize : uint8;
class UTexture2D;
#ifdef ADVANCEDSTEAMSESSIONS_AdvancedSteamFriendsLibrary_generated_h
#error "AdvancedSteamFriendsLibrary.generated.h already included, missing '#pragma once' in AdvancedSteamFriendsLibrary.h"
#endif
#define ADVANCEDSTEAMSESSIONS_AdvancedSteamFriendsLibrary_generated_h

#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_289_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics; \
	ADVANCEDSTEAMSESSIONS_API static class UScriptStruct* StaticStruct();


template<> ADVANCEDSTEAMSESSIONS_API UScriptStruct* StaticStruct<struct FBPSteamGroupInfo>();

#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_SPARSE_DATA
#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetSteamGroups) \
	{ \
		P_GET_TARRAY_REF(FBPSteamGroupInfo,Z_Param_Out_SteamGroups); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedSteamFriendsLibrary::GetSteamGroups(Z_Param_Out_SteamGroups); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamFriendGamePlayed) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_ENUM_REF(EBlueprintResultSwitch,Z_Param_Out_Result); \
		P_GET_PROPERTY_REF(UIntProperty,Z_Param_Out_AppID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedSteamFriendsLibrary::GetSteamFriendGamePlayed(Z_Param_UniqueNetId,(EBlueprintResultSwitch&)(Z_Param_Out_Result),Z_Param_Out_AppID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetLocalSteamIDFromSteam) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FBPUniqueNetId*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetLocalSteamIDFromSteam(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateSteamIDFromString) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_SteamID64); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FBPUniqueNetId*)Z_Param__Result=UAdvancedSteamFriendsLibrary::CreateSteamIDFromString(Z_Param_SteamID64); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamPersonaName) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetSteamPersonaName(Z_Param_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFriendSteamLevel) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetFriendSteamLevel(Z_Param_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOpenSteamUserOverlay) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_ENUM(ESteamUserOverlayType,Z_Param_DialogType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::OpenSteamUserOverlay(Z_Param_UniqueNetId,ESteamUserOverlayType(Z_Param_DialogType)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRequestSteamFriendInfo) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_UBOOL(Z_Param_bRequireNameOnly); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::RequestSteamFriendInfo(Z_Param_UniqueNetId,Z_Param_bRequireNameOnly); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamFriendAvatar) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_ENUM_REF(EBlueprintAsyncResultSwitch,Z_Param_Out_Result); \
		P_GET_ENUM(SteamAvatarSize,Z_Param_AvatarSize); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UTexture2D**)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetSteamFriendAvatar(Z_Param_UniqueNetId,(EBlueprintAsyncResultSwitch&)(Z_Param_Out_Result),SteamAvatarSize(Z_Param_AvatarSize)); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetSteamGroups) \
	{ \
		P_GET_TARRAY_REF(FBPSteamGroupInfo,Z_Param_Out_SteamGroups); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedSteamFriendsLibrary::GetSteamGroups(Z_Param_Out_SteamGroups); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamFriendGamePlayed) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_ENUM_REF(EBlueprintResultSwitch,Z_Param_Out_Result); \
		P_GET_PROPERTY_REF(UIntProperty,Z_Param_Out_AppID); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		UAdvancedSteamFriendsLibrary::GetSteamFriendGamePlayed(Z_Param_UniqueNetId,(EBlueprintResultSwitch&)(Z_Param_Out_Result),Z_Param_Out_AppID); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetLocalSteamIDFromSteam) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FBPUniqueNetId*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetLocalSteamIDFromSteam(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execCreateSteamIDFromString) \
	{ \
		P_GET_PROPERTY(UStrProperty,Z_Param_SteamID64); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FBPUniqueNetId*)Z_Param__Result=UAdvancedSteamFriendsLibrary::CreateSteamIDFromString(Z_Param_SteamID64); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamPersonaName) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetSteamPersonaName(Z_Param_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetFriendSteamLevel) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(int32*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetFriendSteamLevel(Z_Param_UniqueNetId); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execOpenSteamUserOverlay) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_ENUM(ESteamUserOverlayType,Z_Param_DialogType); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::OpenSteamUserOverlay(Z_Param_UniqueNetId,ESteamUserOverlayType(Z_Param_DialogType)); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execRequestSteamFriendInfo) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_UBOOL(Z_Param_bRequireNameOnly); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::RequestSteamFriendInfo(Z_Param_UniqueNetId,Z_Param_bRequireNameOnly); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execGetSteamFriendAvatar) \
	{ \
		P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId); \
		P_GET_ENUM_REF(EBlueprintAsyncResultSwitch,Z_Param_Out_Result); \
		P_GET_ENUM(SteamAvatarSize,Z_Param_AvatarSize); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(UTexture2D**)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetSteamFriendAvatar(Z_Param_UniqueNetId,(EBlueprintAsyncResultSwitch&)(Z_Param_Out_Result),SteamAvatarSize(Z_Param_AvatarSize)); \
		P_NATIVE_END; \
	}


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAdvancedSteamFriendsLibrary(); \
	friend struct Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics; \
public: \
	DECLARE_CLASS(UAdvancedSteamFriendsLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSteamSessions"), NO_API) \
	DECLARE_SERIALIZER(UAdvancedSteamFriendsLibrary)


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_INCLASS \
private: \
	static void StaticRegisterNativesUAdvancedSteamFriendsLibrary(); \
	friend struct Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics; \
public: \
	DECLARE_CLASS(UAdvancedSteamFriendsLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSteamSessions"), NO_API) \
	DECLARE_SERIALIZER(UAdvancedSteamFriendsLibrary)


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAdvancedSteamFriendsLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAdvancedSteamFriendsLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAdvancedSteamFriendsLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAdvancedSteamFriendsLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAdvancedSteamFriendsLibrary(UAdvancedSteamFriendsLibrary&&); \
	NO_API UAdvancedSteamFriendsLibrary(const UAdvancedSteamFriendsLibrary&); \
public:


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAdvancedSteamFriendsLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAdvancedSteamFriendsLibrary(UAdvancedSteamFriendsLibrary&&); \
	NO_API UAdvancedSteamFriendsLibrary(const UAdvancedSteamFriendsLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAdvancedSteamFriendsLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAdvancedSteamFriendsLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAdvancedSteamFriendsLibrary)


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_308_PROLOG
#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_SPARSE_DATA \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_RPC_WRAPPERS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_INCLASS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_SPARSE_DATA \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h_311_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ADVANCEDSTEAMSESSIONS_API UClass* StaticClass<class UAdvancedSteamFriendsLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h


#define FOREACH_ENUM_ESTEAMUSEROVERLAYTYPE(op) \
	op(ESteamUserOverlayType::steamid) \
	op(ESteamUserOverlayType::chat) \
	op(ESteamUserOverlayType::jointrade) \
	op(ESteamUserOverlayType::stats) \
	op(ESteamUserOverlayType::achievements) \
	op(ESteamUserOverlayType::friendadd) \
	op(ESteamUserOverlayType::friendremove) \
	op(ESteamUserOverlayType::friendrequestaccept) \
	op(ESteamUserOverlayType::friendrequestignore) 

enum class ESteamUserOverlayType : uint8;
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<ESteamUserOverlayType>();

#define FOREACH_ENUM_STEAMAVATARSIZE(op) \
	op(SteamAvatarSize::SteamAvatar_INVALID) \
	op(SteamAvatarSize::SteamAvatar_Small) \
	op(SteamAvatarSize::SteamAvatar_Medium) \
	op(SteamAvatarSize::SteamAvatar_Large) 

enum class SteamAvatarSize : uint8;
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<SteamAvatarSize>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
