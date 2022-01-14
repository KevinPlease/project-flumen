
#include "GameServerManager.h"

UGameServerManager* UGameServerManager::CreateGameServerManager(UObject* WorldContextObject)
{
	return NewObject<UGameServerManager>();
}

void UGameServerManager::PlayerConnected(FString playfabId)
{
	#if UE_SERVER
	// When a new player connects, let PlayFab know by adding it to the vector of players and calling updateConnectedPlayers
	std::string id = std::string(TCHAR_TO_UTF8(*playfabId));
	players.push_back(Microsoft::Azure::Gaming::ConnectedPlayer(id));
	Microsoft::Azure::Gaming::GSDK::updateConnectedPlayers(players);
	#endif
}

void UGameServerManager::PlayerDisconnected(FString playfabId)
{
	#if UE_SERVER
	for (auto it = players.begin(); it != players.end(); ++it)
	{
		Microsoft::Azure::Gaming::ConnectedPlayer player = *it;
		FString PlayfabIdString(player.m_playerId.c_str());
		if (PlayfabIdString == playfabId)
		{
			players.erase(it);
			it--;
			break;
		}
	}
	Microsoft::Azure::Gaming::GSDK::updateConnectedPlayers(players);
	#endif
}

void UGameServerManager::ShutdownServer(bool force)
{
	#if UE_SERVER
	players.clear();
	FGenericPlatformMisc::RequestExit(force);
	#endif
}
