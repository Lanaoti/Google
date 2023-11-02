// Copyright 2022 CQUnreal. All Rights Reserved.

#include "GoogleBlueprintLibrary.h"
#include "GoogleModule.h"
#include "Serialization/JsonReader.h"


void UGoogleBlueprintLibrary::Init()
{
	FGooglePtr Google = FGoogleModule::Get().GetGoogle();
	if (Google.IsValid())
	{
		Google->Init();
	}
	else
	{
		UE_LOG(LogGoogle, Log, TEXT("Not supported"));
	}
}

void UGoogleBlueprintLibrary::Login(FGoogleLoginDelegate Delegate)
{
	FGooglePtr Google = FGoogleModule::Get().GetGoogle();
	if (Google.IsValid())
	{
		Google->OnLoginCompleted = FGoogleLoginCompleted::CreateLambda([Delegate](const FString& Data) {
			int32 Code = EGoogleResponse::Error;
						
			FGoogleLogin LoginData;

			TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(Data);
			TSharedPtr<FJsonObject> JsonObject;
			FJsonSerializer::Deserialize(JsonReader, JsonObject);
			if (JsonObject.IsValid())
			{
				JsonObject->TryGetNumberField(TEXT("Code"), Code);

				const TSharedPtr<FJsonObject>* DataObjectPtr = nullptr;
				if (JsonObject->TryGetObjectField(TEXT("Data"), DataObjectPtr))
				{
					TSharedPtr<FJsonObject> DataObject = *DataObjectPtr;
					if (DataObject.IsValid())
					{
						const TSharedPtr<FJsonObject>* UserObjectPtr = nullptr;
						if (DataObject->TryGetObjectField(TEXT("UserData"), UserObjectPtr))
						{
							TSharedPtr<FJsonObject> UserObject = *UserObjectPtr;

							UserObject->TryGetStringField(TEXT("Sub"), LoginData.UserData.Sub);
							UserObject->TryGetStringField(TEXT("GivenName"), LoginData.UserData.GivenName);
							UserObject->TryGetStringField(TEXT("FamilyName"), LoginData.UserData.FamilyName);
							UserObject->TryGetStringField(TEXT("Name"), LoginData.UserData.Name);
							UserObject->TryGetStringField(TEXT("Picture"), LoginData.UserData.Picture);
						}

						const TSharedPtr<FJsonObject>* AuthObjectPtr = nullptr;
						if (DataObject->TryGetObjectField(TEXT("AuthData"), AuthObjectPtr))
						{
							TSharedPtr<FJsonObject> AuthObject = *AuthObjectPtr;

							AuthObject->TryGetStringField(TEXT("ServerAuthCode"), LoginData.AuthData.ServerAuthCode);
							AuthObject->TryGetStringField(TEXT("IDToken"), LoginData.AuthData.IDToken);
						}
					}
				}
			}

			AsyncTask(ENamedThreads::GameThread, [Delegate, Code, LoginData]() {
				Delegate.ExecuteIfBound(Code, LoginData);
			});
		});
		Google->Login();
	}
	else
	{
		Delegate.ExecuteIfBound(EGoogleResponse::DeveloperError, FGoogleLogin());
	}
}

void UGoogleBlueprintLibrary::Logout()
{
	FGooglePtr Google = FGoogleModule::Get().GetGoogle();
	if (Google.IsValid())
	{
		Google->Logout();
	}
	else
	{
		UE_LOG(LogGoogle, Log, TEXT("Not supported"));
	}
}