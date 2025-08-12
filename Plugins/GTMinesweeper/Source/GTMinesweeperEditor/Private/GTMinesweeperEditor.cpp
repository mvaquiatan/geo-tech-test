// Copyright Epic Games, Inc. All Rights Reserved.

#include "GTMinesweeperEditor.h"
#include "GTMinesweeperStyle.h"
#include "GTMinesweeperCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "UI/SMinesweeperWindow.h"

static const FName GTMinesweeperTabName("GTMinesweeper");

#define LOCTEXT_NAMESPACE "FGTMinesweeperModule"

void FGTMinesweeperEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FGTMinesweeperStyle::Initialize();
	FGTMinesweeperStyle::ReloadTextures();

	FGTMinesweeperCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FGTMinesweeperCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FGTMinesweeperEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGTMinesweeperEditorModule::RegisterMenus));
}

void FGTMinesweeperEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	if (MinesweeperWindow.IsValid())
	{
		MinesweeperWindow->RequestDestroyWindow();
		MinesweeperWindow.Reset();
	}
	
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FGTMinesweeperStyle::Shutdown();

	FGTMinesweeperCommands::Unregister();
}

void FGTMinesweeperEditorModule::PluginButtonClicked()
{
	if (MinesweeperWindow.IsValid())
	{
		return;
	}
	
	MinesweeperWindow = SNew(SMinesweeperWindow);
	MinesweeperWindow->SetOnWindowClosed(FOnWindowClosed::CreateRaw(this, &FGTMinesweeperEditorModule::OnMinesweeperWindowClosed));
	FSlateApplication::Get().AddWindow(MinesweeperWindow.ToSharedRef());
}

void FGTMinesweeperEditorModule::OnMinesweeperWindowClosed(const TSharedRef<SWindow>& Window)
{
	MinesweeperWindow.Reset();
}

void FGTMinesweeperEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGTMinesweeperCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGTMinesweeperCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGTMinesweeperEditorModule, GTMinesweeper)