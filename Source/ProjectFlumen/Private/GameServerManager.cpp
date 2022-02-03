
#include "GameServerManager.h"

void UGameServerManager::ShutdownServer(bool force)
{
	#if UE_SERVER
	FGenericPlatformMisc::RequestExit(force);
	#endif
}
