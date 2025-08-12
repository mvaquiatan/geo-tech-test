// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

DECLARE_DELEGATE_TwoParams(FOnCellClickedDelegate, int32/* Row */, int32/* Col */)

class SMinesweeperCell : public SBox
{

public:
	SLATE_BEGIN_ARGS(SMinesweeperCell){}
		SLATE_ARGUMENT(int32, NeighborMines)
		SLATE_ARGUMENT(bool, bIsMine)
		SLATE_ARGUMENT(int32, Row)
		SLATE_ARGUMENT(int32, Column)
		SLATE_EVENT(FOnCellClickedDelegate, OnCellClickedDelegate)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

	FReply OnCellClicked();

	void Reveal();

	void SetAsBombSource();

private:
	TSharedPtr<SButton> Button;
	TSharedPtr<STextBlock> TextBlock;
	int32 Row = -1, Column = -1, NeighborMines = 0;
	bool bIsMine = false;
	FOnCellClickedDelegate OnCellClickedDelegate;

};
