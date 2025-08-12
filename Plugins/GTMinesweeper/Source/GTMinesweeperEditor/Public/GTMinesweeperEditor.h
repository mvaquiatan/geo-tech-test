// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class SMinesweeperWindow;
class FToolBarBuilder;
class FMenuBuilder;

class FGTMinesweeperEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void OnMinesweeperWindowClosed(const TSharedRef<SWindow>& Window);

	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> PluginCommands;
	TSharedPtr<SMinesweeperWindow> MinesweeperWindow;
};
