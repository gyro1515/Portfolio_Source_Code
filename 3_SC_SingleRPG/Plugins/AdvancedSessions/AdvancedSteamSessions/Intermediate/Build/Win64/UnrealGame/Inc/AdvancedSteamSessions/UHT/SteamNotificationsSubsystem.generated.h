// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SteamNotificationsSubsystem.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef ADVANCEDSTEAMSESSIONS_SteamNotificationsSubsystem_generated_h
#error "SteamNotificationsSubsystem.generated.h already included, missing '#pragma once' in SteamNotificationsSubsystem.h"
#endif
#define ADVANCEDSTEAMSESSIONS_SteamNotificationsSubsystem_generated_h

#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_16_DELEGATE \
struct _Script_AdvancedSteamSessions_eventOnSteamOverlayActivated_Parms \
{ \
	bool bOverlayState; \
}; \
static inline void FOnSteamOverlayActivated_DelegateWrapper(const FMulticastScriptDelegate& OnSteamOverlayActivated, bool bOverlayState) \
{ \
	_Script_AdvancedSteamSessions_eventOnSteamOverlayActivated_Parms Parms; \
	Parms.bOverlayState=bOverlayState ? true : false; \
	OnSteamOverlayActivated.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_SPARSE_DATA
#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_RPC_WRAPPERS
#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_ACCESSORS
#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUSteamNotificationsSubsystem(); \
	friend struct Z_Construct_UClass_USteamNotificationsSubsystem_Statics; \
public: \
	DECLARE_CLASS(USteamNotificationsSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSteamSessions"), NO_API) \
	DECLARE_SERIALIZER(USteamNotificationsSubsystem)


#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_INCLASS \
private: \
	static void StaticRegisterNativesUSteamNotificationsSubsystem(); \
	friend struct Z_Construct_UClass_USteamNotificationsSubsystem_Statics; \
public: \
	DECLARE_CLASS(USteamNotificationsSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSteamSessions"), NO_API) \
	DECLARE_SERIALIZER(USteamNotificationsSubsystem)


#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API USteamNotificationsSubsystem(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(USteamNotificationsSubsystem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamNotificationsSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamNotificationsSubsystem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamNotificationsSubsystem(USteamNotificationsSubsystem&&); \
	NO_API USteamNotificationsSubsystem(const USteamNotificationsSubsystem&); \
public: \
	NO_API virtual ~USteamNotificationsSubsystem();


#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API USteamNotificationsSubsystem(USteamNotificationsSubsystem&&); \
	NO_API USteamNotificationsSubsystem(const USteamNotificationsSubsystem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, USteamNotificationsSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(USteamNotificationsSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(USteamNotificationsSubsystem) \
	NO_API virtual ~USteamNotificationsSubsystem();


#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_18_PROLOG
#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_SPARSE_DATA \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_RPC_WRAPPERS \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_ACCESSORS \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_INCLASS \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_SPARSE_DATA \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_ACCESSORS \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_INCLASS_NO_PURE_DECLS \
	FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h_21_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ADVANCEDSTEAMSESSIONS_API UClass* StaticClass<class USteamNotificationsSubsystem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_12SteamSessions_AggroTest2_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamNotificationsSubsystem_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
