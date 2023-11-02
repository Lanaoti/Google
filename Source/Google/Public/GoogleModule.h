// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "GenericGoogle.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGoogle, Log, All);

typedef TSharedPtr<FGenericGoogle> FGooglePtr;

class FGoogleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static inline FGoogleModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FGoogleModule>("Google");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("Google");
	}

	FGooglePtr GetGoogle();

private:
	FGooglePtr Google;
};
