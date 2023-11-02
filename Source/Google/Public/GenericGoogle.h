#pragma once

#include "CoreMinimal.h"
#include "Templates/SharedPointer.h"

DECLARE_DELEGATE_OneParam(FGoogleLoginCompleted, const FString&);

class GOOGLE_API FGenericGoogle
{
public:
	FGenericGoogle();
	virtual ~FGenericGoogle();

	virtual void OnStartup();
	virtual void OnShutdown();

	//初始化
	virtual void Init() = 0;

	//好游快爆登录
	virtual void Login() = 0;

	//好游快爆登出
	virtual void Logout() = 0;

	//登录完成的回调
	FGoogleLoginCompleted OnLoginCompleted;
};
