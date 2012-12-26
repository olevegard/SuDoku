#include "SuDokuSolver.h"
static const bool PRINT_DEBUG = true;


void CSuDokuSolver::insert( const vector2d &pos, short iDigit )
{
    // Update the possibilities for this position
    m_oPossibleNumbers[pos.x][pos.y].setAndMarkAsSolved( iDigit - 1 );
    removePossibilitiesInsert( pos, iDigit );
}

void CSuDokuSolver::removePossibilitiesInsert( const vector2d &pos, const short shDigit ) {

    short shDigitRem = shDigit - 1;
    if (PRINT_DEBUG)
        std::cout << "removePossibilitiesInsert: digit : " << shDigit << " pos : " << pos << std::endl;


    for ( int i = 0; i < 9; ++i )
    {
        if ( PRINT_DEBUG )
            std::cout << "removing ( " << pos.x << " , " << i << " ) and ( " << i << " , " << pos.y << " )\n";

        m_oPossibleNumbers[pos.x][i].remove(shDigitRem);
        m_oPossibleNumbers[i][pos.y].remove(shDigitRem);
    }

    short shXMod = pos.x % 3;
    short shYMod = pos.y % 3;

    short shX1 = 0;
    short shX2 = 0;
    short shX3 = 0;

    short shY1 = 0;
    short shY2 = 0;
    short shY3 = 0;

    if ( shXMod == 0 )
    {
        shX1 = pos.x;
        shX2 = pos.x + 1;
        shX3 = pos.x + 2;
    } else if ( shXMod == 1 )
    {
        shX1 = pos.x;
        shX2 = pos.x + 1;
        shX3 = pos.x - 1;

    }else if ( shXMod == 2 )
    {
        shX1 = pos.x;
        shX2 = pos.x - 1;
        shX3 = pos.x - 2;

    }

    if ( shYMod == 0 )
    {
        shY1 = pos.y;
        shY2 = pos.y + 1;
        shY3 = pos.y + 2;

    } else if ( shYMod == 1 )
    {
        shY1 = pos.y;
        shY2 = pos.y + 1;
        shY3 = pos.y - 1;

    } else if ( shYMod == 2 )
    {
        shY1 = pos.y;
        shY2 = pos.y - 1;
        shY3 = pos.y - 2;

    }

    m_oPossibleNumbers[shX1][shY1].remove(shDigitRem);
    m_oPossibleNumbers[shX2][shY1].remove(shDigitRem);
    m_oPossibleNumbers[shX3][shY1].remove(shDigitRem);

    m_oPossibleNumbers[shX1][shY2].remove(shDigitRem);
    m_oPossibleNumbers[shX2][shY2].remove(shDigitRem);
    m_oPossibleNumbers[shX3][shY2].remove(shDigitRem);

    m_oPossibleNumbers[shX1][shY3].remove(shDigitRem);
    m_oPossibleNumbers[shX2][shY3].remove(shDigitRem);
    m_oPossibleNumbers[shX3][shY3].remove(shDigitRem);

}

void CSuDokuSolver::printAllPosibilities()
{

    int iColumn = 0;
    int iRow = 0;
    for ( iRow = 0; iRow < 9; ++iRow )
    {
        for ( iColumn = 0; iColumn < 9; ++ iColumn)
        {
            if ( !m_oPossibleNumbers[iColumn][iRow].isSolved() )
            {
                for ( int i = 1; i <= 3; ++i )
                {
                    if ( m_oPossibleNumbers[iColumn][iRow].isPossible(i - 1))
                        std::cout << " " << i << " ";
                    else
                        std::cout << " - ";
                }
            } else
            {
                std::cout << " -  -  - ";
            }

            if ( iColumn == 2 || iColumn == 5)
                std::cout << " | ";
            else
                std::cout << "  ";

        }
        std::cout << std::endl;

        for ( int iColumn = 0; iColumn < 9; ++ iColumn)
        {
            if ( !m_oPossibleNumbers[iColumn][iRow].isSolved() )
            {
                for ( int i = 4; i <= 6; ++i )
                {
                    if ( m_oPossibleNumbers[iColumn][iRow].isPossible(i - 1))
                        std::cout << " " << i << " ";
                    else
                        std::cout << " - ";
                }
            } else
            {
                std::cout << " - |" << m_oPossibleNumbers[iColumn][iRow].getSolvedDigitP1() << "| - ";
            }


            if ( iColumn == 2 || iColumn == 5)
                std::cout << " | ";
            else
                std::cout << "  ";
        }
        std::cout << std::endl;

        for ( int iColumn = 0; iColumn < 9; ++ iColumn)
        {
            if ( !m_oPossibleNumbers[iColumn][iRow].isSolved() )
            {
                for ( int i = 7; i <= 9; ++i )
                {
                    if ( m_oPossibleNumbers[iColumn][iRow].isPossible(i - 1))
                        std::cout << " " << i << " ";
                    else
                        std::cout << " - ";
                }
            } else
            {
                std::cout << " -  -  - ";
            }


            if ( iColumn == 2 || iColumn == 5)
                std::cout << " | ";
            else
                std::cout << "  ";
        }

        if ( iRow == 2 || iRow == 5)
            std::cout << std::endl << std::endl << std::endl;
        else
            std::cout << std::endl << std::endl;

    }

}

short CSuDokuSolver::solve( const vector2d &pos )
{
    std::cout << "solving " << pos << std::endl;

    return 0;
}

