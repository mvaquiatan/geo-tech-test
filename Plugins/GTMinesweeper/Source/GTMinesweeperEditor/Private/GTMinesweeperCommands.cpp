// Copyright Epic Games, Inc. All Rights Reserved.

#include "GTMinesweeperCommands.h"

#define LOCTEXT_NAMESPACE "FGTMinesweeperModule"

void FGTMinesweeperCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Minesweeper", "Open editor minesweeper game", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
