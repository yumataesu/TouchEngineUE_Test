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

#include "TouchEngineVulkanRHI.h"

#include "ITouchEngineModule.h"
#include "Logging.h"
#include "TouchEngineVulkanResourceProvider.h"

#include "Modules/ModuleManager.h"
#include "Util/VulkanWindowsFunctions.h"
#include "Misc/App.h"

#define LOCTEXT_NAMESPACE "FTouchEngineVulkanRHI"

namespace UE::TouchEngine::Vulkan
{
	void FTouchEngineVulkanRHI::StartupModule()
	{
		// We are loaded in PostConfigInit so that we can hook up to Vulkan RHI and add some custom extensions
		// This is required so we can load the functions later in ConditionallyLoadVulkanFunctionsForWindows
		ConditionallySetupVulkanExtensions();

		// The rest of the setup needs to be done once the RHI has been initialised
		FCoreDelegates::OnPostEngineInit.AddStatic(&FTouchEngineVulkanRHI::LoadWindowsFunctions);
	}

	void FTouchEngineVulkanRHI::ShutdownModule()
	{
		if (ITouchEngineModule* Module = ITouchEngineModule::GetSafe())
		{
			Module->UnbindResourceProvider(TEXT("Vulkan"));
		}
	}

#if PLATFORM_WINDOWS
	void FTouchEngineVulkanRHI::LoadWindowsFunctions()
	{
		// Bypass graphics API check while cooking
		if (!FApp::CanEverRender())
		{
			return;
		}

		ITouchEngineModule::Get().BindResourceProvider(
			TEXT("Vulkan"),
			FResourceProviderFactory::CreateLambda([](const FResourceProviderInitArgs& Args)
			{
				return MakeVulkanResourceProvider(Args);
			})
		);
		
		ConditionallyLoadVulkanFunctionsForWindows();
		UE_CLOG(IsVulkanSelected() && !AreVulkanFunctionsForWindowsLoaded(), LogTouchEngineVulkanRHI, Error, TEXT("Failed to load Vulkan Windows functions."));
	}
#endif
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(UE::TouchEngine::Vulkan::FTouchEngineVulkanRHI, TouchEngineVulkanRHI);