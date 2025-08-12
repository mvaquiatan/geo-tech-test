// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slate/SMinesweeperBoard.h"

#include "Core/Minesweeper.h"
#include "UI/Slate/SMinesweeperCell.h"
#include "Widgets/Layout/SUniformGridPanel.h"

void SMinesweeperBoard::Construct(const FArguments& InArgs)
{
	Minesweeper = InArgs._Minesweeper;

	Minesweeper->OnRevealCellDelegate.AddRaw(this, &SMinesweeperBoard::OnRevealCell);

	const int32 Rows = Minesweeper->GetRows();
	const int32 Columns = Minesweeper->GetColumns();

	WidgetCells.Reserve(Rows * Columns);
	
	const TSharedRef<SUniformGridPanel>& Grid = SNew(SUniformGridPanel);
	for (int32 Row = 0; Row < Rows; ++Row)
	{
		for (int32 Col = 0; Col < Columns; ++Col)
		{
			const FMinesweeperCellInfo& CellInfo = Minesweeper->GetCell(Row, Col);
			const TSharedRef<SMinesweeperCell>& Cell = SNew(SMinesweeperCell)
				.Row(Row)
				.Column(Col)
				.bIsMine(CellInfo.bHasMine)
				.NeighborMines(CellInfo.NeighborMines)
				.OnCellClickedDelegate(this, &SMinesweeperBoard::OnCellClicked);
			Grid->AddSlot(Col, Row)[
				Cell
			];
			WidgetCells.Insert(Cell, Row * Columns + Col);
		}
	}

	ChildSlot
	[
		Grid
	];
}

void SMinesweeperBoard::OnCellClicked(int32 Row, int32 Col)
{
	Minesweeper->Reveal(Row, Col);
	if (Minesweeper->IsGameOver())
	{
		const int32 Columns = Minesweeper->GetColumns();
		const int32 Index = Row * Columns + Col;
		// The button clicked with the mine
		WidgetCells[Index]->SetAsBombSource();
	}
}

void SMinesweeperBoard::OnRevealCell()
{
	const bool bIsGameOver = Minesweeper->IsGameOver();
	const bool bIsCompleted = Minesweeper->IsCompleted();
	const int32 Rows = Minesweeper->GetRows();
	const int32 Columns = Minesweeper->GetColumns();
	for (int32 Row = 0; Row < Rows; ++Row)
	{
		for (int32 Col = 0; Col < Columns; ++Col)
		{
			const int32 Index = Row * Columns + Col;
			if (bIsCompleted || bIsGameOver || Minesweeper->GetCell(Row, Col).bRevealed)
			{
				WidgetCells[Index]->Reveal();
			}
		}
	}
}
