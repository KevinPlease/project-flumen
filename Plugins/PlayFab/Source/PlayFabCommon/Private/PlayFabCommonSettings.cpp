//////////////////////////////////////////////////////
// Copyright (C) Microsoft. 2018. All rights reserved.
//////////////////////////////////////////////////////


#include "PlayFabCommonSettings.h"

namespace PlayFabCommon
{
    const FString PlayFabCommonSettings::sdkVersion = "1.86.220523";
    const FString PlayFabCommonSettings::buildIdentifier = "adobuild_unrealmarketplaceplugin_142";
    const FString PlayFabCommonSettings::versionString = "UE4MKPL-1.86.220523";

    FString PlayFabCommonSettings::clientSessionTicket;
    FString PlayFabCommonSettings::entityToken;
    FString PlayFabCommonSettings::connectionString;

    FString PlayFabCommonSettings::photonRealtimeAppId;
    FString PlayFabCommonSettings::photonTurnbasedAppId;
    FString PlayFabCommonSettings::photonChatAppId;
}
