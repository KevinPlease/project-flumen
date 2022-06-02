// Mobile Utils Plugin
// Created by Patryk Stepniewski
// Copyright (c) 2014-2019 gameDNA Ltd. All Rights Reserved.

#include "MobileUtilsPlatform.h"

#import <Reachability/Reachability.h>
#include "OnlineIdentityInterfaceIOS.h"
#include "OnlineSubsystemIOS.h"
#include "OnlineSubsystem.h"
//#import <SAMKeychain/SAMKeychain.h>


FMobileUtilsPlatform::FMobileUtilsPlatform()
{
}

FMobileUtilsPlatform::~FMobileUtilsPlatform()
{
}

bool FMobileUtilsPlatform::CheckInternetConnection()
{
	Reachability *reachability = [Reachability reachabilityForInternetConnection];
	NetworkStatus networkStatus = [reachability currentReachabilityStatus];
	return networkStatus != NotReachable;
}

bool FMobileUtilsPlatform::CheckGooglePlayServices()
{
	return false;
}

FString FMobileUtilsPlatform::GetPersistentUniqueDeviceId()
{
	/*NSString *AppName = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString*)kCFBundleNameKey];
	NSString *PersistentUUID = [SAMKeychain passwordForService : AppName account : @"incoding"];

	if (PersistentUUID == nil)
	{
		PersistentUUID = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
		[SAMKeychain setPassword : PersistentUUID forService : AppName account : @"incoding"];
	}

	return FString(PersistentUUID);*/
	return FString("");
}

FString FMobileUtilsPlatform::GetDeviceId()
{
	return GetPersistentUniqueDeviceId();
}

void FMobileUtilsPlatform::LaunchAppStore()
{
	NSString* simple = @"itms-apps://itunes.apple.com/app/id361309726";
	UIApplication* application = [UIApplication sharedApplication];
	NSURL* URL = [NSURL URLWithString:simple];
	[application openURL:URL
		options:@{}
		completionHandler:^(BOOL success) {
		  if (success)
		  {
			  NSLog(@"Opened url");
		  }
		}];
	

}

FString FMobileUtilsPlatform::GetGameCenterPlayerId()
{
#if PLATFORM_ANDROID
	return FString("");
#endif

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::GetByPlatform();
	FOnlineIdentityIOS* IdentityInterface = static_cast<FOnlineIdentityIOS*>(OnlineSubsystem->GetIdentityInterface().Get());
	
	check(IdentityInterface != nullptr);

	if ([GKLocalPlayer localPlayer] == nil)
	{
		UE_LOG_ONLINE_EXTERNALUI(Log, TEXT("Game Center localPlayer is null."));
		return FString("");
	}

	if ([GKLocalPlayer localPlayer].isAuthenticated)
	{
		return FString("");
	}

	const FString PlayerId(FOnlineSubsystemIOS::GetPlayerId(IdentityInterface->GetLocalGameCenterUser()));
	return PlayerId;
}