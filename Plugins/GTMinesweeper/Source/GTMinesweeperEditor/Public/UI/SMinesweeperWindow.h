// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Core/Minesweeper.h"

class SMinesweeperBoard;

class SMinesweeperWindow : public SWindow
{
public:

	SLATE_BEGIN_ARGS(SMinesweeperWindow):
		_DefaultRows(10),
		_DefaultColumns(10),
		_DefaultMines(10) {}
		SLATE_ARGUMENT(int32, DefaultRows)
		SLATE_ARGUMENT(int32, DefaultColumns)
		SLATE_ARGUMENT(int32, DefaultMines)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

protected:
	
	FReply AttemptToRefreshBoard();
	void CreateMinesweeperBoard();
	void OnUpdateMinesweeperBoard();
	void OnChangeRows(const FText& Text, ETextCommit::Type CommitType);
	void OnChangeColumns(const FText& Text, ETextCommit::Type CommitType);
	void OnChangeMines(const FText& Text, ETextCommit::Type CommitType);

	
private:

	TSharedPtr<FMinesweeper> Minesweeper;
	TSharedPtr<SMinesweeperBoard> Board;
	TSharedPtr<SVerticalBox> MainContainer;
	TSharedPtr<STextBlock> GenerateButtonText;
	TSharedPtr<SEditableTextBox> RowsEditableText;
	TSharedPtr<SEditableTextBox> ColumnsEditableText;
	TSharedPtr<SEditableTextBox> MinesEditableText;
	int32 Rows = 0, Columns = 0, Mines = 0;
};
