// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "GTMinesweeperStyle.h"

class FGTMinesweeperCommands : public TCommands<FGTMinesweeperCommands>
{
public:

	FGTMinesweeperCommands()
		: TCommands<FGTMinesweeperCommands>(TEXT("GTMinesweeper"), NSLOCTEXT("Contexts", "GTMinesweeper", "GTMinesweeper Plugin"), NAME_None, FGTMinesweeperStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
