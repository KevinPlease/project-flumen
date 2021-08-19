

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectFlumenServerTarget : TargetRules
{
	public ProjectFlumenServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
        DefaultBuildSettings = BuildSettingsVersion.V2;

        ExtraModuleNames.AddRange( new string[] { "ProjectFlumen" } );
	}
}
