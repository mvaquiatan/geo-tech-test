// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slate/SMinesweeperCell.h"

#include "UI/Data/MinesweeperDisplaySettings.h"

void SMinesweeperCell::Construct(const FArguments& InArgs)
{
	Column = InArgs._Column;
	Row = InArgs._Row;
	OnCellClickedDelegate = InArgs._OnCellClickedDelegate;
	NeighborMines = InArgs._NeighborMines;
	bIsMine = InArgs._bIsMine;

	const UMinesweeperDisplaySettings* MinesweeperDisplaySettings = GetDefault<UMinesweeperDisplaySettings>();
	const FButtonStyle& ButtonStyle = MinesweeperDisplaySettings->GetCellButtonStyle();
	
	SBox::Construct(
		SBox::FArguments()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(MinesweeperDisplaySettings->GetCellPadding())
		.WidthOverride(MinesweeperDisplaySettings->GetCellSize())
		.HeightOverride(MinesweeperDisplaySettings->GetCellSize())
		[
			SAssignNew(Button, SButton)
			.ButtonStyle(&ButtonStyle)
			.Cursor(EMouseCursor::Hand)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked(this, &SMinesweeperCell::OnCellClicked)
			[
				SAssignNew(TextBlock, STextBlock)
				.Text(bIsMine ? FText::FromString("*") : FText::AsNumber(NeighborMines))
				.Visibility(EVisibility::Hidden)
				.ColorAndOpacity(MinesweeperDisplaySettings->GetCellNumberColor(NeighborMines))
			]
		]
	);
}

FReply SMinesweeperCell::OnCellClicked()
{
	OnCellClickedDelegate.ExecuteIfBound(Row, Column);
	return FReply::Handled();
}

void SMinesweeperCell::Reveal()
{
	TextBlock->SetVisibility(bIsMine || NeighborMines > 0 ? EVisibility::Visible : EVisibility::Hidden);
	SetEnabled(false);
}

void SMinesweeperCell::SetAsBombSource()
{
	Button->SetBorderBackgroundColor(FLinearColor::Red);
}
