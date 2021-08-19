

#pragma once

#include "CoreMinimal.h"
//#include "Engine/GameEngine.h"

class FProjectFlumenGameModuleImpl : public IModuleInterface
{
public:
	// IModuleInterface Methods
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool IsGameModule() const override
	{
		return true;
	}
#if UE_SERVER
private:
	// Methods added to support GSDK
	void ConnectToPlayFabAgent();
	void LogInfo(FString message);
	void LogError(FString message);
#endif
};
