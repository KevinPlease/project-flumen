#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameServerManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTFLUMEN_API UGameServerManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game Server")
	static void ShutdownServer(bool force = false);

};
