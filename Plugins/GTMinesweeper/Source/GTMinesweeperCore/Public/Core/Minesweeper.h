// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_MULTICAST_DELEGATE(FOnMinesweeperBoardUpdateDelegate);

enum class GTMINESWEEPERCORE_API EMinesweeperError
{
    None,
    InputZero,
    InputRowCol,
    InputMaxMines,
};

struct GTMINESWEEPERCORE_API FMinesweeperCellInfo
{
    bool bHasMine = false;
    bool bRevealed = false;
    int32 NeighborMines = 0;
};

class GTMINESWEEPERCORE_API FMinesweeper
{
public:
    FMinesweeper(){}
    FMinesweeper(int32 InRows, int32 InColumns, int32 InMines);

    int32 GetRows() const { return Rows; }
    int32 GetColumns() const { return Columns; }
    const FMinesweeperCellInfo& GetCell(int32 Row, int32 Column) const;
    
    void ResetBoard();
    void Reveal(int32 Row, int32 Col, bool bFromInput = true);
    bool IsGameOver() const { return bGameOver; }

    static EMinesweeperError VerifyMinesweeperData(int32 InRows, int32 InColumns, int32 InMines);

private:

    bool IsValidCell(int32 Row, int32 Col) const;
    void PlaceMines();
    void CalculateNumbers();
    
private:
    int32 Rows = 0;
    int32 Columns = 0;
    int32 MinesCount = 0;
    bool bGameOver = false;

    TArray<TArray<FMinesweeperCellInfo>> Board;

public:
    FOnMinesweeperBoardUpdateDelegate OnRevealCellDelegate;
};
