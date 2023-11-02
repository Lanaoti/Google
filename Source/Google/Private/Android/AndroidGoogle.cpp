#include "AndroidGoogle.h"
#include "Android/AndroidJavaEnv.h"
#include "GoogleModule.h"

jmethodID FAndroidGoogle::GoogleInit;
jmethodID FAndroidGoogle::GoogleLogin;
jmethodID FAndroidGoogle::GoogleLogout;

//登录回调
JNI_METHOD void Java_com_epicgames_ue4_GameActivity_nativeGoogleLoginComplete(JNIEnv* jenv, jobject thiz, jstring jdata)
{
	FString Data = TEXT("");
	if (jenv != nullptr)
	{
		Data = FJavaHelper::FStringFromParam(jenv, jdata);
	}

	FGooglePtr Google = FGoogleModule::Get().GetGoogle();
	if (Google.IsValid())
	{
		Google->OnLoginCompleted.ExecuteIfBound(Data);
	}

	UE_LOG(LogGoogle, Log, TEXT("nativeGoogleLoginComplete: %s"), *Data);
}

//注销登录回调
JNI_METHOD void Java_com_epicgames_ue4_GameActivity_nativeGoogleLogoutComplete(JNIEnv* jenv, jobject thiz, jstring jdata)
{
	FString Data = TEXT("");
	if (jenv != nullptr)
	{
		Data = FJavaHelper::FStringFromParam(jenv, jdata);
	}

	UE_LOG(LogGoogle, Log, TEXT("nativeGoogleLogoutComplete: %s"), *Data);
}

FAndroidGoogle::FAndroidGoogle()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		GoogleInit = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Google_Init", "()V", false);
		GoogleLogin = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Google_Login", "()V", false);
		GoogleLogout = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Google_Logout", "()V", false);
	}
}

FAndroidGoogle::~FAndroidGoogle()
{

}

void FAndroidGoogle::OnStartup()
{

}

void FAndroidGoogle::OnShutdown()
{

}

void FAndroidGoogle::Init()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, GoogleInit);
	}
}

void FAndroidGoogle::Login()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, GoogleLogin);
	}
}

void FAndroidGoogle::Logout()
{
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, GoogleLogout);
	}
}