// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GoogleModule.h"
#if PLATFORM_ANDROID
#include "Android/AndroidGoogle.h"
#endif

/** Logging definitions */
DEFINE_LOG_CATEGORY(LogGoogle);

#define LOCTEXT_NAMESPACE "FGoogleModule"

void FGoogleModule::StartupModule()
{
	UE_LOG(LogGoogle, Log, TEXT("FGoogleModule::StartupModule"));

#if PLATFORM_ANDROID
	Google = MakeShared<FAndroidGoogle>();
#endif

	if (Google.IsValid())
	{
		Google->OnStartup();
	}
}

void FGoogleModule::ShutdownModule()
{
	UE_LOG(LogGoogle, Log, TEXT("FGoogleModule::ShutdownModule"));

	if (Google.IsValid())
	{
		Google->OnShutdown();
	}
}

FGooglePtr FGoogleModule::GetGoogle()
{
	return Google;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGoogleModule, Google)