

using UnrealBuildTool;

public class ProjectFlumen : ModuleRules
{
	public ProjectFlumen(ReadOnlyTargetRules Target) : base(Target)
	{
		bUseRTTI = false;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "InputCore", "Networking", "Sockets", "HTTP",
            "OnlineSubsystem", "PlayFab", "PlayFabCpp", "PlayFabCommon" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemNull", "PlayFab", "PlayFabCpp", "PlayFabCommon" });
     	// DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemGooglePlay" });
            // DynamicallyLoadedModuleNames.Add("OnlineSubsystemGooglePlay");
        } else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemIOS" });
            // DynamicallyLoadedModuleNames.Add("OnlineSubsystemIOS");
        }

            if (Target.Type == global::UnrealBuildTool.TargetType.Server)
        {
            bEnableExceptions = true;

            // Add dynamic dlls required by all dedicated servers
            RuntimeDependencies.Add("$(TargetOutputDir)/xinput1_3.dll", "$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies/Win64/DirectX/xinput1_3.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/concrt140.dll", "$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies/Win64/Microsoft.VC.CRT/concrt140.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/msvcp140.dll", "$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies/Win64/Microsoft.VC.CRT/msvcp140.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/msvcp140_1.dll", "$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies/Win64/Microsoft.VC.CRT/msvcp140_1.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/msvcp140_2.dll", "$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies/Win64/Microsoft.VC.CRT/msvcp140_2.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/vccorlib140.dll", "$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies/Win64/Microsoft.VC.CRT/vccorlib140.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/vcruntime140.dll", "$(EngineDir)/Binaries/ThirdParty/AppLocalDependencies/Win64/Microsoft.VC.CRT/vcruntime140.dll", StagedFileType.SystemNonUFS);

            // Add dynamic dlls required by GSDK
            RuntimeDependencies.Add("$(TargetOutputDir)/GSDK_CPP_Windows.lib", "$(ProjectDir)/packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/lib/Windows/x64/Release/dynamic/GSDK_CPP_Windows.lib", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/libcurl.lib", "$(ProjectDir)/packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/lib/Windows/x64/Release/dynamic/libcurl.lib", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/libcurl.dll", "$(ProjectDir)/packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/lib/Windows/x64/Release/dynamic/libcurl.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/libssl-1_1-x64.dll", "$(ProjectDir)/packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/lib/Windows/x64/Release/dynamic/libssl-1_1-x64.dll", StagedFileType.SystemNonUFS);
            RuntimeDependencies.Add("$(TargetOutputDir)/libcrypto-1_1-x64.dll", "$(ProjectDir)/packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/lib/Windows/x64/Release/dynamic/libcrypto-1_1-x64.dll", StagedFileType.SystemNonUFS);

            // Add libraries required by GSDK
            PublicAdditionalLibraries.Add("$(ProjectDir)/packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/lib/Windows/x64/Release/dynamic/GSDK_CPP_Windows.lib");
            PublicAdditionalLibraries.Add("$(ProjectDir)/packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/lib/Windows/x64/Release/dynamic/libcurl.lib");
            PublicIncludePaths.Add("../packages/com.playfab.cppgsdk.v140.0.7.210520/build/native/include");
        }
    }
}
