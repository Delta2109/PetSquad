// Copyright 2023 - 2024 Leartes Studios. All Rights Reserved.

#include "MaterialAssignmentManager.h"
#include "Editor.h"
#include "EditorUtilitySubsystem.h" 
#include "EditorUtilityWidgetBlueprint.h"
#include "LevelEditor.h"
#include "MToolAssetData.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Style/MToolStyle.h"

#define LOCTEXT_NAMESPACE "FMaterialAssignmentManagerModule"

void FMaterialAssignmentManagerModule::StartupModule()
{
	FMAToolStyle::InitializeToolStyle();
	
	SetupPluginToolbarEntry();
}

void FMaterialAssignmentManagerModule::SetupPluginToolbarEntry()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> Extenders = LevelEditorModule.GetToolBarExtensibilityManager()->GetAllExtenders();

	const TSharedPtr<FExtender> MyExtender = MakeShareable(new FExtender);
	MyExtender->AddToolBarExtension("Play", EExtensionHook::After, NULL, FToolBarExtensionDelegate::CreateRaw(this, &FMaterialAssignmentManagerModule::AddToolbarExtension));

	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(MyExtender);
}

void FMaterialAssignmentManagerModule::AddToolbarExtension(FToolBarBuilder& ToolBarBuilder)
{
	ToolBarBuilder.AddToolBarButton
	(
	FUIAction(
		FExecuteAction::CreateRaw(this, &FMaterialAssignmentManagerModule::ToolbarButtonClicked)),
		NAME_None,
		FText::FromString(TEXT("Material Assignment")), //Title text
		FText::FromString(TEXT("Material Assignment")), // Tooltip  text
		FSlateIcon(FMAToolStyle::GetToolStyleName(),"LevelEditor.MaterialAssignmentIcon")
	);
	
}

void FMaterialAssignmentManagerModule::ToolbarButtonClicked()
{
	if (!GEditor){return;}

	if(	UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>())
	{
		if(EditorUtilitySubsystem->DoesTabExist(ToolTabID))
		{
			EditorUtilitySubsystem->CloseTabByID(ToolTabID);
		}
		else
		{
			if(UObject* ToolWindowObject = MTToolAssetData::MAToolWindowPath.TryLoad())
			{
				if(const auto ToolWindowBlueprint = Cast<UEditorUtilityWidgetBlueprint>(ToolWindowObject))
				{
					EditorUtilitySubsystem->SpawnAndRegisterTabAndGetID(ToolWindowBlueprint,ToolTabID);

					//Fix Window Size
					const FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
					const TSharedPtr<FTabManager> LevelEditorTabManager = LevelEditorModule.GetLevelEditorTabManager();
					if (const TSharedPtr<SDockTab> FoundTab = LevelEditorTabManager->FindExistingLiveTab(ToolTabID))
					{
						FoundTab->SetTabIcon(FSlateIcon(FMAToolStyle::GetToolStyleName(),"LevelEditor.MaterialAssignmentIcon").GetIcon());

						/*FWindowSizeLimits SizeLimits;
						SizeLimits.SetMaxHeight(800.0f);
						SizeLimits.SetMaxWidth(820.0f);*/

						if(FoundTab->GetParentWindow().IsValid())
						{
							//FoundTab->GetParentWindow()->SetSizeLimits(SizeLimits);
							FoundTab->GetParentWindow()->Resize(FVector2D(850.0f,500.0f));
						}
					}
				}
			}
		}
	}
}


void FMaterialAssignmentManagerModule::ShutdownModule()
{
	FMAToolStyle::ShutDownStyle();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FMaterialAssignmentManagerModule, MaterialAssignmentManager)