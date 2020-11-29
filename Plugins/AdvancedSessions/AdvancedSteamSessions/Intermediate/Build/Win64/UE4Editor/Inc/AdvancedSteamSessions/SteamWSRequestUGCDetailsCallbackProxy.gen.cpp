// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedSteamSessions/Classes/SteamWSRequestUGCDetailsCallbackProxy.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSteamWSRequestUGCDetailsCallbackProxy() {}
// Cross Module References
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
	ADVANCEDSTEAMSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails();
	ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister();
	ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy();
	ENGINE_API UClass* Z_Construct_UClass_UOnlineBlueprintCallProxyBase();
	ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails();
	ADVANCEDSTEAMSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopID();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics
	{
		struct _Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms
		{
			FBPSteamWorkshopItemDetails WorkShopDetails;
		};
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WorkShopDetails_MetaData[];
#endif
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WorkShopDetails;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::NewProp_WorkShopDetails_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::NewProp_WorkShopDetails = { "WorkShopDetails", nullptr, (EPropertyFlags)0x0010000008000182, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms, WorkShopDetails), Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails, METADATA_PARAMS(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::NewProp_WorkShopDetails_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::NewProp_WorkShopDetails_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::NewProp_WorkShopDetails,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_AdvancedSteamSessions, nullptr, "BlueprintWorkshopDetailsDelegate__DelegateSignature", nullptr, nullptr, sizeof(_Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms), Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	void USteamWSRequestUGCDetailsCallbackProxy::StaticRegisterNativesUSteamWSRequestUGCDetailsCallbackProxy()
	{
		UClass* Class = USteamWSRequestUGCDetailsCallbackProxy::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetWorkshopItemDetails", &USteamWSRequestUGCDetailsCallbackProxy::execGetWorkshopItemDetails },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics
	{
		struct SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms
		{
			UObject* WorldContextObject;
			FBPSteamWorkshopID WorkShopID;
			USteamWSRequestUGCDetailsCallbackProxy* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WorkShopID;
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms, ReturnValue), Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorkShopID = { "WorkShopID", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms, WorkShopID), Z_Construct_UScriptStruct_FBPSteamWorkshopID, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_ReturnValue,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorkShopID,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorldContextObject,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Online|AdvancedSteamWorkshop" },
		{ "Comment", "// Ends the current session\n" },
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
		{ "ToolTip", "Ends the current session" },
		{ "WorldContext", "WorldContextObject" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy, nullptr, "GetWorkshopItemDetails", nullptr, nullptr, sizeof(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms), Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister()
	{
		return USteamWSRequestUGCDetailsCallbackProxy::StaticClass();
	}
	struct Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnFailure_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnFailure;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OnSuccess_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSuccess;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UOnlineBlueprintCallProxyBase,
		(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails, "GetWorkshopItemDetails" }, // 2156590369
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SteamWSRequestUGCDetailsCallbackProxy.h" },
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnFailure_MetaData[] = {
		{ "Comment", "// Called when there is an unsuccessful results return\n" },
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
		{ "ToolTip", "Called when there is an unsuccessful results return" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnFailure = { "OnFailure", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USteamWSRequestUGCDetailsCallbackProxy, OnFailure), Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnFailure_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnFailure_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnSuccess_MetaData[] = {
		{ "Comment", "// Called when there is a successful results return\n" },
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
		{ "ToolTip", "Called when there is a successful results return" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnSuccess = { "OnSuccess", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(USteamWSRequestUGCDetailsCallbackProxy, OnSuccess), Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnSuccess_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnSuccess_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnFailure,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnSuccess,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USteamWSRequestUGCDetailsCallbackProxy>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::ClassParams = {
		&USteamWSRequestUGCDetailsCallbackProxy::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::PropPointers),
		0,
		0x008800A0u,
		METADATA_PARAMS(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USteamWSRequestUGCDetailsCallbackProxy, 386000732);
	template<> ADVANCEDSTEAMSESSIONS_API UClass* StaticClass<USteamWSRequestUGCDetailsCallbackProxy>()
	{
		return USteamWSRequestUGCDetailsCallbackProxy::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_USteamWSRequestUGCDetailsCallbackProxy(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy, &USteamWSRequestUGCDetailsCallbackProxy::StaticClass, TEXT("/Script/AdvancedSteamSessions"), TEXT("USteamWSRequestUGCDetailsCallbackProxy"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamWSRequestUGCDetailsCallbackProxy);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
