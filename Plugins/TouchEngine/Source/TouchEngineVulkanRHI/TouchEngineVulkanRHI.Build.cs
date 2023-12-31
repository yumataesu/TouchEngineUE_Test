/* Shared Use License: This file is owned by Derivative Inc. (Derivative)
* and can only be used, and/or modified for use, in conjunction with
* Derivative's TouchDesigner software, and only if you are a licensee who has
* accepted Derivative's TouchDesigner license or assignment agreement
* (which also govern the use of this file). You may share or redistribute
* a modified version of this file provided the following conditions are met:
*
* 1. The shared file or redistribution must retain the information set out
* above and this list of conditions.
* 2. Derivative's name (Derivative Inc.) or its trademarks may not be used
* to endorse or promote products derived from this file without specific
* prior written permission from Derivative.
*/

using System.IO;
using UnrealBuildTool;

public class TouchEngineVulkanRHI : ModuleRules
{
	public TouchEngineVulkanRHI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PrivateDefinitions.Add("VULKAN_SUPPORTS_MAINTENANCE_LAYER2");

		PublicDependencyModuleNames.AddRange(new string[] 
			{ 
				"Core",
				"CoreUObject",
				"Engine"
			});
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"TouchEngine",
				"TouchEngineAPI",
				"RenderCore",
				"RHI", 
				"RHICore",
				"Vulkan",
				"VulkanRHI"
			});
		
		var EngineDir = Path.GetFullPath(Target.RelativeEnginePath);
		PrivateIncludePaths.AddRange(
			new string[] {
				Path.Combine(EngineDir, "Source", "Runtime", "VulkanRHI", "Private"),
				Path.Combine(EngineDir, "Source", "ThirdParty", "Vulkan", "Include", "vulkan")
			});
		
		if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Android)
		{
			AddEngineThirdPartyPrivateStaticDependencies(Target, "Vulkan");
		}
		
		if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			PrivateIncludePaths.Add(
				Path.Combine(EngineDir, "Source", "Runtime", "VulkanRHI", "Private", "Linux")
			);
		}
		if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PrivateIncludePaths.Add(
				Path.Combine(EngineDir, "Source", "Runtime", "VulkanRHI", "Private", "Mac")
			);
		}
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PrivateIncludePaths.Add(
				Path.Combine(EngineDir, "Source", "Runtime", "VulkanRHI", "Private", "Windows")
				);
		}
	}
}