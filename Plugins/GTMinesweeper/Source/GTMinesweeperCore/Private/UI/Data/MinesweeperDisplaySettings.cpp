// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Data/MinesweeperDisplaySettings.h"

const FLinearColor& UMinesweeperDisplaySettings::GetCellNumberColor(int Index) const
{
	if (CellNumberColors.IsValidIndex(Index))
	{
		return CellNumberColors[Index];
	}
	return FLinearColor::Black;
}
