// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedSteamSessions/Classes/AdvancedSteamFriendsLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAdvancedSteamFriendsLibrary() {}
// Cross Module References
	ADVANCEDSTEAMSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType();
	UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
	ADVANCEDSTEAMSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize();
	ADVANCEDSTEAMSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPSteamGroupInfo();
	ADVANCEDSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPUniqueNetId();
	ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary_NoRegister();
	ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	ADVANCEDSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSessions_EBlueprintAsyncResultSwitch();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed();
	ADVANCEDSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSessions_EBlueprintResultSwitch();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo();
// End Cross Module References
	static UEnum* ESteamUserOverlayType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("ESteamUserOverlayType"));
		}
		return Singleton;
	}
	template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<ESteamUserOverlayType>()
	{
		return ESteamUserOverlayType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESteamUserOverlayType(ESteamUserOverlayType_StaticEnum, TEXT("/Script/AdvancedSteamSessions"), TEXT("ESteamUserOverlayType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Hash() { return 2011888781U; }
	UEnum* Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_AdvancedSteamSessions();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESteamUserOverlayType"), 0, Get_Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESteamUserOverlayType::steamid", (int64)ESteamUserOverlayType::steamid },
				{ "ESteamUserOverlayType::chat", (int64)ESteamUserOverlayType::chat },
				{ "ESteamUserOverlayType::jointrade", (int64)ESteamUserOverlayType::jointrade },
				{ "ESteamUserOverlayType::stats", (int64)ESteamUserOverlayType::stats },
				{ "ESteamUserOverlayType::achievements", (int64)ESteamUserOverlayType::achievements },
				{ "ESteamUserOverlayType::friendadd", (int64)ESteamUserOverlayType::friendadd },
				{ "ESteamUserOverlayType::friendremove", (int64)ESteamUserOverlayType::friendremove },
				{ "ESteamUserOverlayType::friendrequestaccept", (int64)ESteamUserOverlayType::friendrequestaccept },
				{ "ESteamUserOverlayType::friendrequestignore", (int64)ESteamUserOverlayType::friendrequestignore },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "achievements.Comment", "/*Opens the overlay web browser to the specified user's achievements.*/" },
				{ "achievements.Name", "ESteamUserOverlayType::achievements" },
				{ "achievements.ToolTip", "Opens the overlay web browser to the specified user's achievements." },
				{ "BlueprintType", "true" },
				{ "chat.Comment", "/*Opens a chat window to the specified user, or joins the group chat.*/" },
				{ "chat.Name", "ESteamUserOverlayType::chat" },
				{ "chat.ToolTip", "Opens a chat window to the specified user, or joins the group chat." },
				{ "friendadd.Comment", "/*Opens the overlay in minimal mode prompting the user to add the target user as a friend.*/" },
				{ "friendadd.Name", "ESteamUserOverlayType::friendadd" },
				{ "friendadd.ToolTip", "Opens the overlay in minimal mode prompting the user to add the target user as a friend." },
				{ "friendremove.Comment", "/*Opens the overlay in minimal mode prompting the user to remove the target friend.*/" },
				{ "friendremove.Name", "ESteamUserOverlayType::friendremove" },
				{ "friendremove.ToolTip", "Opens the overlay in minimal mode prompting the user to remove the target friend." },
				{ "friendrequestaccept.Comment", "/*Opens the overlay in minimal mode prompting the user to accept an incoming friend invite.*/" },
				{ "friendrequestaccept.Name", "ESteamUserOverlayType::friendrequestaccept" },
				{ "friendrequestaccept.ToolTip", "Opens the overlay in minimal mode prompting the user to accept an incoming friend invite." },
				{ "friendrequestignore.Comment", "/*Opens the overlay in minimal mode prompting the user to ignore an incoming friend invite.*/" },
				{ "friendrequestignore.Name", "ESteamUserOverlayType::friendrequestignore" },
				{ "friendrequestignore.ToolTip", "Opens the overlay in minimal mode prompting the user to ignore an incoming friend invite." },
				{ "IsBlueprintBase", "true" },
				{ "jointrade.Comment", "/*Opens a window to a Steam Trading session that was started with the ISteamEconomy / StartTrade Web API.*/" },
				{ "jointrade.Name", "ESteamUserOverlayType::jointrade" },
				{ "jointrade.ToolTip", "Opens a window to a Steam Trading session that was started with the ISteamEconomy / StartTrade Web API." },
				{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
				{ "stats.Comment", "/*Opens the overlay web browser to the specified user's stats.*/" },
				{ "stats.Name", "ESteamUserOverlayType::stats" },
				{ "stats.ToolTip", "Opens the overlay web browser to the specified user's stats." },
				{ "steamid.Comment", "/*Opens the overlay web browser to the specified user or groups profile.*/" },
				{ "steamid.Name", "ESteamUserOverlayType::steamid" },
				{ "steamid.ToolTip", "Opens the overlay web browser to the specified user or groups profile." },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
				nullptr,
				"ESteamUserOverlayType",
				"ESteamUserOverlayType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* SteamAvatarSize_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("SteamAvatarSize"));
		}
		return Singleton;
	}
	template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<SteamAvatarSize>()
	{
		return SteamAvatarSize_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_SteamAvatarSize(SteamAvatarSize_StaticEnum, TEXT("/Script/AdvancedSteamSessions"), TEXT("SteamAvatarSize"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Hash() { return 3160318448U; }
	UEnum* Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_AdvancedSteamSessions();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("SteamAvatarSize"), 0, Get_Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "SteamAvatarSize::SteamAvatar_INVALID", (int64)SteamAvatarSize::SteamAvatar_INVALID },
				{ "SteamAvatarSize::SteamAvatar_Small", (int64)SteamAvatarSize::SteamAvatar_Small },
				{ "SteamAvatarSize::SteamAvatar_Medium", (int64)SteamAvatarSize::SteamAvatar_Medium },
				{ "SteamAvatarSize::SteamAvatar_Large", (int64)SteamAvatarSize::SteamAvatar_Large },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "IsBlueprintBase", "true" },
				{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
				{ "SteamAvatar_INVALID.Name", "SteamAvatarSize::SteamAvatar_INVALID" },
				{ "SteamAvatar_Large.Name", "SteamAvatarSize::SteamAvatar_Large" },
				{ "SteamAvatar_Medium.Name", "SteamAvatarSize::SteamAvatar_Medium" },
				{ "SteamAvatar_Small.Name", "SteamAvatarSize::SteamAvatar_Small" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
				nullptr,
				"SteamAvatarSize",
				"SteamAvatarSize",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::EnumClass,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FBPSteamGroupInfo::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ADVANCEDSTEAMSESSIONS_API uint32 Get_Z_Construct_UScriptStruct_FBPSteamGroupInfo_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FBPSteamGroupInfo, Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("BPSteamGroupInfo"), sizeof(FBPSteamGroupInfo), Get_Z_Construct_UScriptStruct_FBPSteamGroupInfo_Hash());
	}
	return Singleton;
}
template<> ADVANCEDSTEAMSESSIONS_API UScriptStruct* StaticStruct<FBPSteamGroupInfo>()
{
	return FBPSteamGroupInfo::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FBPSteamGroupInfo(FBPSteamGroupInfo::StaticStruct, TEXT("/Script/AdvancedSteamSessions"), TEXT("BPSteamGroupInfo"), false, nullptr, nullptr);
static struct FScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamGroupInfo
{
	FScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamGroupInfo()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("BPSteamGroupInfo")),new UScriptStruct::TCppStructOps<FBPSteamGroupInfo>);
	}
} ScriptStruct_AdvancedSteamSessions_StaticRegisterNativesFBPSteamGroupInfo;
	struct Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_numChatting_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_numChatting;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_numInGame_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_numInGame;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_numOnline_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_numOnline;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GroupTag_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_GroupTag;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GroupName_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_GroupName;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_GroupID_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_GroupID;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBPSteamGroupInfo>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numChatting_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numChatting = { "numChatting", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBPSteamGroupInfo, numChatting), METADATA_PARAMS(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numChatting_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numChatting_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numInGame_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numInGame = { "numInGame", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBPSteamGroupInfo, numInGame), METADATA_PARAMS(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numInGame_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numInGame_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numOnline_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numOnline = { "numOnline", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBPSteamGroupInfo, numOnline), METADATA_PARAMS(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numOnline_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numOnline_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupTag_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupTag = { "GroupTag", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBPSteamGroupInfo, GroupTag), METADATA_PARAMS(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupTag_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupTag_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupName_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "Comment", "// Uint64 representation\n" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Uint64 representation" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupName = { "GroupName", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBPSteamGroupInfo, GroupName), METADATA_PARAMS(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupName_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupID_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupID = { "GroupID", nullptr, (EPropertyFlags)0x0010000000000015, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FBPSteamGroupInfo, GroupID), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupID_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupID_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numChatting,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numInGame,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numOnline,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupTag,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupName,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupID,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
		nullptr,
		&NewStructOps,
		"BPSteamGroupInfo",
		sizeof(FBPSteamGroupInfo),
		alignof(FBPSteamGroupInfo),
		Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FBPSteamGroupInfo()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FBPSteamGroupInfo_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AdvancedSteamSessions();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("BPSteamGroupInfo"), sizeof(FBPSteamGroupInfo), Get_Z_Construct_UScriptStruct_FBPSteamGroupInfo_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FBPSteamGroupInfo_Hash() { return 2142335492U; }
	void UAdvancedSteamFriendsLibrary::StaticRegisterNativesUAdvancedSteamFriendsLibrary()
	{
		UClass* Class = UAdvancedSteamFriendsLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CreateSteamIDFromString", &UAdvancedSteamFriendsLibrary::execCreateSteamIDFromString },
			{ "GetFriendSteamLevel", &UAdvancedSteamFriendsLibrary::execGetFriendSteamLevel },
			{ "GetLocalSteamIDFromSteam", &UAdvancedSteamFriendsLibrary::execGetLocalSteamIDFromSteam },
			{ "GetSteamFriendAvatar", &UAdvancedSteamFriendsLibrary::execGetSteamFriendAvatar },
			{ "GetSteamFriendGamePlayed", &UAdvancedSteamFriendsLibrary::execGetSteamFriendGamePlayed },
			{ "GetSteamGroups", &UAdvancedSteamFriendsLibrary::execGetSteamGroups },
			{ "GetSteamPersonaName", &UAdvancedSteamFriendsLibrary::execGetSteamPersonaName },
			{ "OpenSteamUserOverlay", &UAdvancedSteamFriendsLibrary::execOpenSteamUserOverlay },
			{ "RequestSteamFriendInfo", &UAdvancedSteamFriendsLibrary::execRequestSteamFriendInfo },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms
		{
			FString SteamID64;
			FBPUniqueNetId ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SteamID64_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_SteamID64;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms, ReturnValue), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_SteamID64_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_SteamID64 = { "SteamID64", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms, SteamID64), METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_SteamID64_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_SteamID64_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_SteamID64,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "// Creates a unique steam id directly from a string holding a uint64 value, useful for testing\n" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Creates a unique steam id directly from a string holding a uint64 value, useful for testing" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "CreateSteamIDFromString", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms
		{
			FBPUniqueNetId UniqueNetId;
			int32 ReturnValue;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_UniqueNetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_UniqueNetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_UniqueNetId,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "// Gets the level of a friends steam account, STEAM ONLY, Returns -1 if the steam level is not known, might need RequestSteamFriendInfo called first.\n" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Gets the level of a friends steam account, STEAM ONLY, Returns -1 if the steam level is not known, might need RequestSteamFriendInfo called first." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetFriendSteamLevel", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventGetLocalSteamIDFromSteam_Parms
		{
			FBPUniqueNetId ReturnValue;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetLocalSteamIDFromSteam_Parms, ReturnValue), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "// Retreives the local steam ID from steam\n" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Retreives the local steam ID from steam" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetLocalSteamIDFromSteam", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventGetLocalSteamIDFromSteam_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms
		{
			FBPUniqueNetId UniqueNetId;
			EBlueprintAsyncResultSwitch Result;
			SteamAvatarSize AvatarSize;
			UTexture2D* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_AvatarSize;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_AvatarSize_Underlying;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Result;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Result_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize = { "AvatarSize", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, AvatarSize), Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, Result), Z_Construct_UEnum_AdvancedSessions_EBlueprintAsyncResultSwitch, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_UniqueNetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_UniqueNetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_UniqueNetId,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "// Get a texture of a valid friends avatar, STEAM ONLY, Returns invalid texture if the subsystem hasn't loaded that size of avatar yet\n" },
		{ "CPP_Default_AvatarSize", "SteamAvatar_Medium" },
		{ "ExpandEnumAsExecs", "Result" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Get a texture of a valid friends avatar, STEAM ONLY, Returns invalid texture if the subsystem hasn't loaded that size of avatar yet" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamFriendAvatar", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms
		{
			FBPUniqueNetId UniqueNetId;
			EBlueprintResultSwitch Result;
			int32 AppID;
		};
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_AppID;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_Result;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Result_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_AppID = { "AppID", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms, AppID), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms, Result), Z_Construct_UEnum_AdvancedSessions_EBlueprintResultSwitch, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_UniqueNetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_UniqueNetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_AppID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_UniqueNetId,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "/*, FString & GameName*/" },
		{ "ExpandEnumAsExecs", "Result" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", ", FString & GameName" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamFriendGamePlayed", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventGetSteamGroups_Parms
		{
			TArray<FBPSteamGroupInfo> SteamGroups;
		};
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_SteamGroups;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SteamGroups_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups = { "SteamGroups", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamGroups_Parms, SteamGroups), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups_Inner = { "SteamGroups", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FBPSteamGroupInfo, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups_Inner,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "Comment", "// Get a full list of steam groups\n" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Get a full list of steam groups" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamGroups", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventGetSteamGroups_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms
		{
			FBPUniqueNetId UniqueNetId;
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_UniqueNetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_UniqueNetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_UniqueNetId,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "// Gets the persona name of a steam ID, STEAM ONLY, Returns empty if no result, might need RequestSteamFriendInfo called first.\n" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Gets the persona name of a steam ID, STEAM ONLY, Returns empty if no result, might need RequestSteamFriendInfo called first." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamPersonaName", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms
		{
			FBPUniqueNetId UniqueNetId;
			ESteamUserOverlayType DialogType;
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FEnumPropertyParams NewProp_DialogType;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_DialogType_Underlying;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType = { "DialogType", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms, DialogType), Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_UniqueNetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_UniqueNetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType_Underlying,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_UniqueNetId,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "// Opens the steam overlay to go to the specified user dialog\n" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Opens the steam overlay to go to the specified user dialog" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "OpenSteamUserOverlay", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics
	{
		struct AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms
		{
			FBPUniqueNetId UniqueNetId;
			bool bRequireNameOnly;
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static void NewProp_bRequireNameOnly_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bRequireNameOnly;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms*)Obj)->ReturnValue = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly_SetBit(void* Obj)
	{
		((AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms*)Obj)->bRequireNameOnly = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly = { "bRequireNameOnly", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Bool | UE4CodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_UniqueNetId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_UniqueNetId_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_UniqueNetId,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
		{ "Comment", "// Preloads the avatar and name of a steam friend, return whether it is already available or not, STEAM ONLY, Takes time to actually load everything after this is called.\n" },
		{ "CPP_Default_bRequireNameOnly", "false" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "ToolTip", "Preloads the avatar and name of a steam friend, return whether it is already available or not, STEAM ONLY, Takes time to actually load everything after this is called." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "RequestSteamFriendInfo", nullptr, nullptr, sizeof(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary_NoRegister()
	{
		return UAdvancedSteamFriendsLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString, "CreateSteamIDFromString" }, // 3473515067
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel, "GetFriendSteamLevel" }, // 2660488992
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam, "GetLocalSteamIDFromSteam" }, // 3799441627
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar, "GetSteamFriendAvatar" }, // 2311000409
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed, "GetSteamFriendGamePlayed" }, // 3065766596
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups, "GetSteamGroups" }, // 2316481568
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName, "GetSteamPersonaName" }, // 195099480
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay, "OpenSteamUserOverlay" }, // 1990449338
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo, "RequestSteamFriendInfo" }, // 2518024643
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "AdvancedSteamFriendsLibrary.h" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAdvancedSteamFriendsLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::ClassParams = {
		&UAdvancedSteamFriendsLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAdvancedSteamFriendsLibrary, 1406920476);
	template<> ADVANCEDSTEAMSESSIONS_API UClass* StaticClass<UAdvancedSteamFriendsLibrary>()
	{
		return UAdvancedSteamFriendsLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAdvancedSteamFriendsLibrary(Z_Construct_UClass_UAdvancedSteamFriendsLibrary, &UAdvancedSteamFriendsLibrary::StaticClass, TEXT("/Script/AdvancedSteamSessions"), TEXT("UAdvancedSteamFriendsLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAdvancedSteamFriendsLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
