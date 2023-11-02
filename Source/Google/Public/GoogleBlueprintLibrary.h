// Copyright 2022 CQUnreal. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GoogleBlueprintLibrary.generated.h"

UENUM(BlueprintType)
namespace EGoogleResponse
{
	enum Type
	{
		Success = 0,				// 成功
		Canceled = 1,				// 取消
		Error = 2,					// 错误
		DeveloperError = 3			// 开发者错误
	};
}

USTRUCT(BlueprintType)
struct FGoogleUser
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = Google)
	FString Sub;

	UPROPERTY(BlueprintReadWrite, Category = Google)
	FString GivenName;

	UPROPERTY(BlueprintReadWrite, Category = Google)
	FString FamilyName;

	UPROPERTY(BlueprintReadWrite, Category = Google)
	FString Name;

	UPROPERTY(BlueprintReadWrite, Category = HYKB)
	FString Picture;
};

USTRUCT(BlueprintType)
struct FGoogleAuthToken
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = Google)
	FString ServerAuthCode;

	UPROPERTY(BlueprintReadWrite, Category = Google)
	FString IDToken;
};

USTRUCT(BlueprintType)
struct FGoogleLogin
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, Category = HYKB)
	FGoogleUser UserData;

	UPROPERTY(BlueprintReadWrite, Category = HYKB)
	FGoogleAuthToken AuthData;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FGoogleLoginDelegate, int32, Code, const FGoogleLogin&, LoginData);

UCLASS()
class GOOGLE_API UGoogleBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = HYKB, meta = (DisplayName = "HYKBInit"))
	static void Init();

	UFUNCTION(BlueprintCallable, Category = HYKB, meta = (DisplayName = "HYKBLogin"))
	static void Login(FGoogleLoginDelegate Delegate);

	UFUNCTION(BlueprintCallable, Category = HYKB, meta = (DisplayName = "HYKBLogout"))
	static void Logout();
};
