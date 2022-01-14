#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#if UE_SERVER
#include "gsdk.h"
#include <vector>
#endif

#include "GameServerManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTFLUMEN_API UGameServerManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create Game Server Manager", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Game Server")
	static UGameServerManager* CreateGameServerManager(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game Server")
	void PlayerConnected(FString playfabId);

	UFUNCTION(BlueprintCallable, Category = "Game Server")
	void PlayerDisconnected(FString playfabId);

	UFUNCTION(BlueprintCallable, Category = "Game Server")
	void ShutdownServer(bool force = false);

private:
	#if UE_SERVER
	static std::vector<Microsoft::Azure::Gaming::ConnectedPlayer> players;
	#endif
};
