#pragma once

#include "Vector2d.h"
#include "SuDokuCell.h"
#include "BoardStatus.h"

class CSuDokuSolver{
public:
    CSuDokuSolver( BoardStatus* pStatus)
        :   m_oPossibleNumbers()
        ,   m_pBoardStatus(NULL)
    {
        m_pBoardStatus = pStatus;
    }

    // Set a position as solved, and update all related positions
    void insert( const vector2d &pos, short iDigit );

    // Try to solve a diigt.
    short solve( const vector2d &pos );

    void printAllPosibilities();
private:


    bool solveRow( const short shRow );                                         // Solvs a single row
    bool solveRow_SingleDigit( short shRow );                                   // Solves a row with a single digit missing ( helper method for solveRow )
    bool solveRow_Advanced (  short shRow );                                      // Solves a row with several digits missing ( helper method for solveRow )


    // Removes a digit from m_oPossibleNumbers
    void removePossibilitiesInsert( const vector2d &pos, const short shDigit );

    // Keeps track of all possible numbers for all positions
   SuDokuCell::CSuDokuCell m_oPossibleNumbers[9][9];


   BoardStatus* m_pBoardStatus;
};
