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

#include "ToxAssetFactoryNew.h"
#include "TouchEngineEditorModule.h"

#include "ToxAsset.h"

UClass* FToxAssetTypeActions::GetSupportedClass() const
{
	return UToxAsset::StaticClass();
}

FText FToxAssetTypeActions::GetName() const
{
	return INVTEXT("Tox Asset");
}

FColor FToxAssetTypeActions::GetTypeColor() const
{
	return FColor::Yellow;
}

uint32 FToxAssetTypeActions::GetCategories()
{
	return FTouchEngineEditorModule::TouchEngineAssetCategoryBit;
}

UToxAssetFactoryNew::UToxAssetFactoryNew(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UToxAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
	bEditorImport = false;
}

UObject* UToxAssetFactoryNew::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UToxAsset* NewAsset = NewObject<UToxAsset>(InParent, InClass, InName, Flags);

	return NewAsset;
}

uint32 UToxAssetFactoryNew::GetMenuCategories() const
{
	return FTouchEngineEditorModule::TouchEngineAssetCategoryBit;
}