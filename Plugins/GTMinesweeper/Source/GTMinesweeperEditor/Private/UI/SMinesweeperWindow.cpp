// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SMinesweeperWindow.h"

#include "Misc/DefaultValueHelper.h"
#include "UI/Slate/SMinesweeperBoard.h"

#define LOCTEXT_NAMESPACE "SMinesweeperWindow"

void SMinesweeperWindow::Construct(const FArguments& InArgs)
{
	Rows = InArgs._DefaultRows;
	Columns = InArgs._DefaultColumns;
	Mines = InArgs._DefaultMines;
	SWindow::Construct(SWindow::FArguments()
		.Title(LOCTEXT("MinesweeperTitle", "Minesweeper"))
		.SupportsMaximize(false)
		.MinWidth(500)
		.MinHeight(500)
		.SizingRule(ESizingRule::Autosized)
		[
			SAssignNew(MainContainer, SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("RowsText", "Row Count: "))
				]
				+ SHorizontalBox::Slot()
				.MinWidth(25)
				[
					SAssignNew(RowsEditableText, SEditableTextBox)
					.Text(FText::AsNumber(Rows))
					.OnTextCommitted(this, &SMinesweeperWindow::OnChangeRows)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SSpacer)
					.Size(FVector2D(10, 0)) 
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("ColumnsText", "Column Count: "))
				]
				+ SHorizontalBox::Slot()
				.MinWidth(25)
				[
					SAssignNew(ColumnsEditableText, SEditableTextBox)
					.Text(FText::AsNumber(InArgs._DefaultColumns))
					.OnTextCommitted(this, &SMinesweeperWindow::OnChangeColumns)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SSpacer)
					.Size(FVector2D(10, 0)) 
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.Text(LOCTEXT("MinesText", "Mines Count: "))
				]
				+ SHorizontalBox::Slot()
				.MinWidth(25)
				[
					SAssignNew(MinesEditableText, SEditableTextBox)
					.Text(FText::AsNumber(InArgs._DefaultMines))
					.OnTextCommitted(this, &SMinesweeperWindow::OnChangeMines)
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSpacer)
				.Size(FVector2D(0, 10)) 
			]
			+SVerticalBox::Slot()
			.HAlign(HAlign_Center)
			.AutoHeight()
			[
				SNew(SButton)
				.OnClicked(this, &SMinesweeperWindow::AttemptToRefreshBoard)
				[
					SAssignNew(GenerateButtonText, STextBlock)
					.Text(LOCTEXT("StartGameText", "Start Game"))
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SSpacer)
				.Size(FVector2D(0, 10)) 
			]
		]);
}

FReply SMinesweeperWindow::AttemptToRefreshBoard()
{
	const EMinesweeperError& Error = FMinesweeper::VerifyMinesweeperData(Rows, Columns, Mines);
	switch (Error)
	{
	case EMinesweeperError::None:
		GenerateButtonText->SetText(LOCTEXT("RestartGameText", "Restart"));
		CreateMinesweeperBoard();
		break;
	case EMinesweeperError::InputMaxMines:
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("MaxMineErrorText", "You've reached the max mines that can be placed on the board."));
		break;
	case EMinesweeperError::InputRowCol:
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("RowColErrorText", "Invalid row and/ or column count"));
		break;
	case EMinesweeperError::InputZero:
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("ZeroErrorText", "Zeroes are not a valid input"));
		break;
	}
	return FReply::Handled();
}

void SMinesweeperWindow::CreateMinesweeperBoard()
{
	if (Board.IsValid())
	{
		MainContainer->RemoveSlot(Board.ToSharedRef());
	}
	Minesweeper = MakeShared<FMinesweeper>(Rows, Columns, Mines);
	Minesweeper->OnRevealCellDelegate.AddRaw(this, &SMinesweeperWindow::OnUpdateMinesweeperBoard);
	MainContainer->AddSlot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	.Padding(5)
	[
		SAssignNew(Board, SMinesweeperBoard)
		.Minesweeper(Minesweeper)
	];
}

void SMinesweeperWindow::OnUpdateMinesweeperBoard()
{
	if (!Minesweeper.IsValid())
	{
		return;
	}

	if (Minesweeper->IsGameOver())
	{
		GenerateButtonText->SetText(LOCTEXT("GameOverText", "Game Over: Retry"));
	}
}

void SMinesweeperWindow::OnChangeRows(const FText& Text, ETextCommit::Type CommitType)
{
	if (!FDefaultValueHelper::ParseInt(Text.ToString(), Rows))
	{
		RowsEditableText->SetText(FText::AsNumber(Rows));
	}
}

void SMinesweeperWindow::OnChangeColumns(const FText& Text, ETextCommit::Type CommitType)
{
	if (!FDefaultValueHelper::ParseInt(Text.ToString(), Columns))
	{
		ColumnsEditableText->SetText(FText::AsNumber(Columns));
	}
}

void SMinesweeperWindow::OnChangeMines(const FText& Text, ETextCommit::Type CommitType)
{
	if (!FDefaultValueHelper::ParseInt(Text.ToString(), Mines))
	{
		MinesEditableText->SetText(FText::AsNumber(Mines));
	}
}

#undef LOCTEXT_NAMESPACE /* SMinesweeperWindow */
