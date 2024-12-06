// Copyright 2023 - 2024 Leartes Studios. All Rights Reserved.

#include "Style/MToolStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

FName FMAToolStyle::ToolStyleName = FName("MAToolStyle");
TSharedPtr<FSlateStyleSet> FMAToolStyle::CreatedToolSlateStyleSet = nullptr;

void FMAToolStyle::InitializeToolStyle()
{	
	if(!CreatedToolSlateStyleSet.IsValid())
	{
		CreatedToolSlateStyleSet = CreateToolSlateStyleSet();
		FSlateStyleRegistry::RegisterSlateStyle(*CreatedToolSlateStyleSet);
	}
}

TSharedRef<FSlateStyleSet> FMAToolStyle::CreateToolSlateStyleSet()
{	
	TSharedRef<FSlateStyleSet> CustomStyleSet = MakeShareable(new FSlateStyleSet(ToolStyleName));

	const FString IconDirectory = 
	IPluginManager::Get().FindPlugin(TEXT("MaterialAssignment"))->GetBaseDir() /"Resources";
	
	CustomStyleSet->SetContentRoot(IconDirectory);
	
	const FVector2D Icon32x32 (32.f,32.f);
	
	CustomStyleSet->Set("LevelEditor.MaterialAssignmentIcon",
	new FSlateImageBrush(IconDirectory/"Material_Assignment.png",Icon32x32));
	
	return CustomStyleSet;
}

void FMAToolStyle::ShutDownStyle()
{
	if(CreatedToolSlateStyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*CreatedToolSlateStyleSet);
		CreatedToolSlateStyleSet.Reset();
	}
}
