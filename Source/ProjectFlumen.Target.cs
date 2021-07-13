

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectFlumenTarget : TargetRules
{
	public ProjectFlumenTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ProjectFlumen" } );
	}
}
