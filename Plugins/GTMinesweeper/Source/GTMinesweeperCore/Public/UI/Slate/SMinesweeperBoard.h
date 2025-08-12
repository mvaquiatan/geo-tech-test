// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class SMinesweeperCell;
class FMinesweeper;

class GTMINESWEEPERCORE_API SMinesweeperBoard : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMinesweeperBoard){}
		SLATE_ARGUMENT(TSharedPtr<FMinesweeper>, Minesweeper)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void OnCellClicked(int32 Row, int32 Col);

	void OnRevealCell();
	
private:
	TArray<TSharedPtr<SMinesweeperCell>> WidgetCells;
	TSharedPtr<FMinesweeper> Minesweeper;
};
