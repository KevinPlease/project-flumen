

#include "ProjectFlumen.h"
#include "Modules/ModuleManager.h"

// Replace default game module with custom game module
// Found technique at https://forums.unrealengine.com/community/community-content-tools-and-tutorials/1547205-quick-c-tip-overriding-your-game-s-startupmodule-shutdownmodule-functions
//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, ProjectFlumen, "ProjectFlumen" );
IMPLEMENT_PRIMARY_GAME_MODULE(FProjectFlumenGameModuleImpl, ProjectFlumen, "ProjectFlumen");

#if UE_SERVER
#include "gsdk.h"
#include "string.h"
#endif

void FProjectFlumenGameModuleImpl::StartupModule()
{
#if UE_SERVER
	//UE_LOG(LogTemp, Display, TEXT("UE_SERVER StartupModule()"));
	bool _playFab = true;
	if (FParse::Param(FCommandLine::Get(), TEXT("NoPlayFab")))
	{
		_playFab = false;
	}
	if (_playFab) {
		ConnectToPlayFabAgent();
	}
#else
	//UE_LOG(LogTemp, Display, TEXT("Not UE_SERVER StartupModule()"))
#endif
}

void FProjectFlumenGameModuleImpl::ShutdownModule()
{
}

#if UE_SERVER
// This method will be called on every heartbeat to check if your game is healthy, as such, it should return very quickly
bool isHealthy()
{
    // Return whether your game server should be considered healthy
    return true;
}

// Callback function for GSDK
void OnShutdown()
{
	/* Perform any necessary cleanup and end the program */
	// Ask UE4 server to shutdown without force
	FGenericPlatformMisc::RequestExit(false);
}

// This method will be called in case #3, when Azure will perform maintenance on the virtual machine
void onMaintenanceScheduled(tm t)
{
#ifdef PLATFORM_WINDOWS
    time_t local = _mkgmtime(&t);
    double delta = difftime(local, time(NULL));
    struct tm buf;
    char str[26];
    gmtime_s(&buf, &local);
    asctime_s(str, sizeof str, &buf);
    printf("UTC:   %s", str);
    localtime_s(&buf, &local);
    asctime_s(str, sizeof str, &buf);
    printf("local: %s", str);
    printf("delta: %f", delta);
#else // Linux
    time_t local = timegm(&t);
    double delta = difftime(local, time(NULL));
    printf("UTC:   %s\n", asctime(gmtime(&local)));
    printf("local: %s\n", asctime(localtime(&local)));
    printf("delta: %f\n", delta);
#endif
    /* Perform any necessary cleanup, notify your players, etc. */
}

void FProjectFlumenGameModuleImpl::ConnectToPlayFabAgent()
{

	try {

		LogInfo("Connecting to PlayFab Agent.");

		// Call this while your game is initializing, it will start heartbeating to our agent and put the game server in an Initializing state
		Microsoft::Azure::Gaming::GSDK::start();
		Microsoft::Azure::Gaming::GSDK::registerHealthCallback(&isHealthy);
		Microsoft::Azure::Gaming::GSDK::registerShutdownCallback(&OnShutdown);
		Microsoft::Azure::Gaming::GSDK::registerMaintenanceCallback(&onMaintenanceScheduled);

		// Call this when your game is done initializing and players can connect
		// Note: This is a blocking call, and will return when this game server is either allocated or terminated
		if (Microsoft::Azure::Gaming::GSDK::readyForPlayers())
		{
			// readyForPlayers returns true when an allocation call has been done, a player is about to connect!
			LogInfo("Server is ready for players.");
		}
		else
		{
			// readyForPlayers returns false when the server is being terminated
			LogError("Server is getting terminated. Not ready for players.");
		}

	}
	catch (Microsoft::Azure::Gaming::GSDKInitializationException& e)
	{
		LogError("GSDK Initialization failed: " + FString(UTF8_TO_TCHAR(e.what())));
	}

}

void FProjectFlumenGameModuleImpl::LogInfo(FString message)
{
	UE_LOG(LogTemp, Display, TEXT("%s"), *message);
	Microsoft::Azure::Gaming::GSDK::logMessage(std::string(TCHAR_TO_UTF8(*message)));
}

void FProjectFlumenGameModuleImpl::LogError(FString message)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *message);
	Microsoft::Azure::Gaming::GSDK::logMessage(std::string(TCHAR_TO_UTF8(*message)));
}

#endif