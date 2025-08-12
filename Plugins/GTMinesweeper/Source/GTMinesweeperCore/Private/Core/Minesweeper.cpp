// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Minesweeper.h"

#include "MinesweeperLogCategory.h"
#include "VerseVM/VVMValuePrinting.h"

FMinesweeper::FMinesweeper(int32 InRows, int32 InColumns, int32 InMines)
    : Rows(InRows), Columns(InColumns), MinesCount(InMines)
{
    ResetBoard();
}

const FMinesweeperCellInfo& FMinesweeper::GetCell(int32 Row, int32 Column) const
{
    return Board[Row][Column];
}

void FMinesweeper::ResetBoard()
{
    Board.SetNumZeroed(Rows);
    for (int32 r = 0; r < Rows; ++r)
    {
        Board[r].SetNumZeroed(Columns);
    }
    PlaceMines();
    CalculateNumbers();
    UE_LOG(LogMinesweeperCore, Display, TEXT("Reset board!"));
}

void FMinesweeper::Reveal(int32 Row, int32 Col, bool bFromInput/* = true*/)
{
    ON_SCOPE_EXIT{
        if (bFromInput)
        {
            UE_LOG(LogMinesweeperCore, Display, TEXT("Board updated!"));
            OnRevealCellDelegate.Broadcast();
        }
    };
    
    if (!IsValidCell(Row, Col) || Board[Row][Col].bRevealed)
    {
        return;
    }
    
    Board[Row][Col].bRevealed = true;

    if (Board[Row][Col].bHasMine)
    {
        UE_LOG(LogMinesweeperCore, Warning, TEXT("There's a bomb!"));
        bGameOver = true;
        return;
    }

    // Flood fill if empty
    if (Board[Row][Col].NeighborMines == 0)
    {
        for (int32 dr = -1; dr <= 1; ++dr)
        {
            for (int32 dc = -1; dc <= 1; ++dc)
            {
                if (dr != 0 || dc != 0)
                {
                    Reveal(Row + dr, Col + dc, false);
                }
            }
        }
    }
}

EMinesweeperError FMinesweeper::VerifyMinesweeperData(int32 InRows, int32 InColumns, int32 InMines)
{
    if (InMines == 0 || InRows == 0 || InColumns == 0)
    {
        return EMinesweeperError::InputZero;
    }
    int32 MaxMines = InRows * InColumns - 1;
    if (InMines > MaxMines)
    {
        return EMinesweeperError::InputMaxMines;
    }
    if (InRows <= 1 || InColumns <= 1)
    {
        return EMinesweeperError::InputRowCol;
    }
    return EMinesweeperError::None;
}

bool FMinesweeper::IsValidCell(int32 Row, int32 Col) const
{
    return Row >= 0 && Row < Rows && Col >= 0 && Col < Columns;
}

void FMinesweeper::PlaceMines()
{
    int32 Placed = 0;
    int32 MaxMines = Rows * Columns - 1;
    while (Placed < MinesCount && Placed < MaxMines)
    {
        int32 r = FMath::RandRange(0, Rows - 1);
        int32 c = FMath::RandRange(0, Columns - 1);

        if (!Board[r][c].bHasMine)
        {
            Board[r][c].bHasMine = true;
            Placed++;
        }
    }
}

void FMinesweeper::CalculateNumbers()
{
    for (int32 r = 0; r < Rows; ++r)
    {
        for (int32 c = 0; c < Columns; ++c)
        {
            if (Board[r][c].bHasMine)
                continue;

            int32 Count = 0;
            for (int32 dr = -1; dr <= 1; ++dr)
            {
                for (int32 dc = -1; dc <= 1; ++dc)
                {
                    if ((dr != 0 || dc != 0) && IsValidCell(r + dr, c + dc) && Board[r + dr][c + dc].bHasMine)
                    {
                        Count++;
                    }
                }
            }
            Board[r][c].NeighborMines = Count;
        }
    }
}