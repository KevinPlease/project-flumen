


#include "GameModeMaster.h"

void AGameModeMaster::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, FUniqueNetIdRepl(), ErrorMessage);
}

APlayerController* AGameModeMaster::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, FUniqueNetIdRepl(), ErrorMessage);
}