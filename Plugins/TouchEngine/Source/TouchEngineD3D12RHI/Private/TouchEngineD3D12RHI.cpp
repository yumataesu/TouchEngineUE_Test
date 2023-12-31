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

#include "TouchEngineD3D12RHI.h"

#include "ITouchEngineModule.h"
#include "TouchEngineD3D12ResourceProvider.h"

#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FTouchEngineD3D12RHI"

namespace UE::TouchEngine::D3DX12
{
	void FTouchEngineD3D12RHI::StartupModule()
	{
		ITouchEngineModule::Get().BindResourceProvider(
			TEXT("D3D12"),
			FResourceProviderFactory::CreateLambda([](const FResourceProviderInitArgs& Args)
			{
				return MakeD3DX12ResourceProvider(Args);
			})
		);
	}

	void FTouchEngineD3D12RHI::ShutdownModule()
	{
		ITouchEngineModule::Get().UnbindResourceProvider(TEXT("D3D12"));
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(UE::TouchEngine::D3DX12::FTouchEngineD3D12RHI, TouchEngineD3D12RHI);