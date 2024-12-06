// Copyright 2023 - 2024 Leartes Studios. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FMaterialAssignmentManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	FName ToolTabID;

	void SetupPluginToolbarEntry();
	void AddToolbarExtension(class FToolBarBuilder& ToolBarBuilder);

public:
	void ToolbarButtonClicked();
};

