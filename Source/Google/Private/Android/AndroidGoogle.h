#pragma once

#include "CoreMinimal.h"
#include "GenericGoogle.h"

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"

class FAndroidGoogle : public FGenericGoogle
{
public:
	FAndroidGoogle();
	virtual ~FAndroidGoogle();

	virtual void OnStartup() override;
	virtual void OnShutdown() override;
	virtual void Init()override;
	virtual void Login() override;
	virtual void Logout() override;

	// JNI Methods
	static jmethodID GoogleInit;
	static jmethodID GoogleLogin;
	static jmethodID GoogleLogout;
};