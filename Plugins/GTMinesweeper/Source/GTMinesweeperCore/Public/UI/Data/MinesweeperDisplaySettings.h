// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MinesweeperDisplaySettings.generated.h"

/**
 * 
 */
UCLASS(Config=GTMinesweeper, DefaultConfig)
class GTMINESWEEPERCORE_API UMinesweeperDisplaySettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	const FButtonStyle& GetCellButtonStyle() const { return CellButtonStyle; }
	const FLinearColor& GetCellNumberColor(int Index) const;
	float GetCellSize() const { return CellSize; }
	float GetCellPadding() const { return CellPadding; }
	
private:
	
	UPROPERTY(EditAnywhere, Config, Category="Cell")
	float CellSize = 32;

	UPROPERTY(EditAnywhere, Config, Category="Cell")
	float CellPadding = 2;
	
	UPROPERTY(EditAnywhere, Config, Category="Cell")
	FButtonStyle CellButtonStyle;
	
	UPROPERTY(EditAnywhere, Config, Category="Cell")
	TArray<FLinearColor> CellNumberColors;
};
