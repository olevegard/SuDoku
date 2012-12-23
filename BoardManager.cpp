#include "BoardManager.h"
#include <iomanip>
#include <cstring>


static const bool PRINT_DEBUG = true;

void CBoardManager::start()
{


}

//======================================================================================================
//=========================================== Loading Boards ===========================================
//======================================================================================================
void CBoardManager::loadBoard()
{

    /*
    // BOARD 5 - SOLVED
    insert(vector2d( 3, 0), 2, true);
    insert(vector2d( 7, 0), 6, true);
    insert(vector2d( 8, 0), 3, true);

    insert(vector2d( 0, 1), 3, true);
    insert(vector2d( 5, 1), 5, true);
    insert(vector2d( 6, 1), 4, true);
    insert(vector2d( 8, 1), 1, true);

    insert(vector2d( 2, 2), 1, true);
    insert(vector2d( 5, 2), 3, true);
    insert(vector2d( 6, 2), 9, true);
    insert(vector2d( 7, 2), 8, true);

    insert(vector2d( 7, 3), 9, true);

    insert(vector2d( 3, 4), 5, true);
    insert(vector2d( 4, 4), 3, true);
    insert(vector2d( 5, 4), 8, true);

    insert(vector2d( 1, 5), 3, true);

    insert(vector2d( 1, 6), 2, true);
    insert(vector2d( 2, 6), 6, true);
    insert(vector2d( 3, 6), 3, true);
    insert(vector2d( 6, 6), 5, true);

    insert(vector2d( 0, 7), 5, true);
    insert(vector2d( 2, 7), 3, true);
    insert(vector2d( 3, 7), 7, true);
    insert(vector2d( 8, 7), 8, true);

    insert(vector2d( 0, 8), 4, true);
    insert(vector2d( 1, 8), 7, true);
    insert(vector2d( 5, 8), 1, true);


    // BOARD 4 - SOLVED
    insert(vector2d( 0, 0), 3, true);
    insert(vector2d( 5, 0), 8, true);

    insert(vector2d( 0, 1), 7, true);
    insert(vector2d( 2, 1), 8, true);
    insert(vector2d( 3, 1), 3, true);
    insert(vector2d( 4, 1), 2, true);
    insert(vector2d( 8, 1), 5, true);

    insert(vector2d( 3, 2), 9, true);
    insert(vector2d( 7, 2), 1, true);

    insert(vector2d( 0, 3), 9, true);
    insert(vector2d( 5, 3), 4, true);
    insert(vector2d( 7, 3), 2, true);

    insert(vector2d( 4, 4), 1, true);

    insert(vector2d( 1, 5), 7, true);
    insert(vector2d( 3, 5), 8, true);
    insert(vector2d( 8, 5), 9, true);

    insert(vector2d( 1, 6), 5, true);
    insert(vector2d( 5, 6), 3, true);

    insert(vector2d( 0, 7), 8, true);
    insert(vector2d( 4, 7), 4, true);
    insert(vector2d( 5, 7), 7, true);
    insert(vector2d( 6, 7), 5, true);
    insert(vector2d( 8, 7), 3, true);

    insert(vector2d( 3, 8), 5, true);
    insert(vector2d( 8, 8), 6, true);

    // BOARD 3 - SOLVED
    insert( vector2d( 3, 0), 8, true);
    insert( vector2d( 4, 0), 4, true);
    insert( vector2d( 8, 0), 9, true);

    insert( vector2d( 2, 1), 1, true);
    insert( vector2d( 8, 1), 5, true);

    insert( vector2d( 0, 2), 8, true);
    insert( vector2d( 4, 2), 2, true);
    insert( vector2d( 5, 2), 1, true);
    insert( vector2d( 6, 2), 4, true);
    insert( vector2d( 7, 2), 6, true);

    insert( vector2d( 0, 3), 7, true);
    insert( vector2d( 2, 3), 8, true);
    insert( vector2d( 7, 3), 9, true);

    insert( vector2d( 1, 5), 5, true);
    insert( vector2d( 6, 5), 3, true);
    insert( vector2d( 8, 5), 1, true);

    insert( vector2d( 1, 6), 2, true);
    insert( vector2d( 2, 6), 4, true);
    insert( vector2d( 3, 6), 9, true);
    insert( vector2d( 4, 6), 1, true);
    insert( vector2d( 8, 6), 7, true);

    insert( vector2d( 0, 7), 9, true);
    insert( vector2d( 6, 7), 5, true);

    insert( vector2d( 0, 8), 3, true);
    insert( vector2d( 4, 8), 8, true);
    insert( vector2d( 5, 8), 4, true);
    // END BOARD 3

    // BOARD 2 - SOLVED
    insert( vector2d( 3, 0), 9, true);
    insert( vector2d( 5, 0), 1, true);

    insert( vector2d( 0, 1), 7, true);
    insert( vector2d( 2, 1), 1, true);
    insert( vector2d( 4, 1), 3, true);
    insert( vector2d( 6, 1), 4, true);

    insert( vector2d( 1, 2), 8, true);
    insert( vector2d( 4, 2), 6, true);
    insert( vector2d( 6, 2), 1, true);

    insert( vector2d( 0, 3), 1, true);
    insert( vector2d( 1, 3), 9, true);
    insert( vector2d( 2, 3), 5, true);
    insert( vector2d( 7, 3), 8, true);

    insert( vector2d( 1, 5), 4, true);
    insert( vector2d( 6, 5), 5, true);
    insert( vector2d( 7, 5), 6, true);
    insert( vector2d( 8, 5), 7, true);

    insert( vector2d( 2, 6), 3, true);
    insert( vector2d( 4, 6), 1, true);
    insert( vector2d( 7, 6), 9, true);

    insert( vector2d( 2, 7), 8, true);
    insert( vector2d( 4, 7), 5, true);
    insert( vector2d( 6, 7), 6, true);
    insert( vector2d( 8, 7), 2, true);

    insert( vector2d( 3, 8), 6, true);
    insert( vector2d( 5, 8), 2, true);
    // END BOARD 2

    // BOARD 1 - SOLVED
    insert( vector2d( 0, 0), 5, true);
    insert( vector2d( 3, 0), 3, true);
    insert( vector2d( 5, 0), 6, true);
    insert( vector2d( 8, 0), 2, true);

    insert( vector2d( 1, 1), 1, true);
    insert( vector2d( 3, 1), 2, true);
    insert( vector2d( 5, 1), 7, true);
    insert( vector2d( 7, 1), 4, true);

    insert( vector2d( 2, 2), 2, true);
    insert( vector2d( 4, 2), 9, true);
    insert( vector2d( 6, 2), 8, true);

    insert( vector2d( 0, 3), 2, true);
    insert( vector2d( 2, 3), 3, true);
    insert( vector2d( 6, 3), 1, true);
    insert( vector2d( 8, 3), 4, true);

    insert( vector2d( 3, 4), 4, true);
    insert( vector2d( 5, 4), 1, true);

    insert( vector2d( 0, 5), 9, true);
    insert( vector2d( 2, 5), 1, true);
    insert( vector2d( 6, 5), 2, true);
    insert( vector2d( 8, 5), 5, true);

    insert( vector2d( 2, 6), 5, true);
    insert( vector2d( 4, 6), 4, true);
    insert( vector2d( 6, 6), 6, true);

    insert( vector2d( 1, 7), 3, true);
    insert( vector2d( 3, 7), 8, true);
    insert( vector2d( 5, 7), 9, true);
    insert( vector2d( 7, 7), 2, true);

    insert( vector2d( 0, 8), 1, true);
    insert( vector2d( 3, 8), 5, true);
    insert( vector2d( 5, 8), 2, true);
    insert( vector2d( 8, 8), 8, true);
    // END BOARD 1


    */
}

void CBoardManager::loadBoard( const char* czBoard )
{
    short length =  strlen( czBoard );
    vector2d pos(0,0);

    short iDigit = 0;
    for ( int i = 0; i < length; ++i)
    {
        // Convert current char to a digit
        switch ( czBoard[i] )
        {
            case '1':
                iDigit = 1;
                break;
            case '2':
                iDigit = 2;
                break;
            case '3':
                iDigit = 3;
                break;
            case '4':
                iDigit = 4;
                break;
            case '5':
                iDigit = 5;
                break;
            case '6':
                iDigit = 6;
                break;
            case '7':
                iDigit = 7;
                break;
            case '8':
                iDigit = 8;
                break;
            case '9':
                iDigit = 9;
                break;
            default:
                iDigit = 0;
                break;
        }

        // Insert digit
        if ( iDigit != 0 )
        {
            insert( pos, iDigit );
        }

        // Increment x position of current digit
        pos.x++;

        // Update y position of digit
        if ( pos.x > 8)
        {
            pos.x = 0;
            pos.y++;
        }
    }
    m_oBoard.printBoard();
    printAllPosibilities();

}

void CBoardManager::removePossibilitiesInsert( const vector2d &pos, const short shDigit ) {

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

void CBoardManager::printAllPosibilities()
{
    std::cout << "Printing all positions\n";

    int iColumn = 0;
    int iRow = 0;
    for ( iRow = 0; iRow < 9; ++iRow ) {
        for ( iColumn = 0; iColumn < 9; ++ iColumn) {
            if ( !m_oPossibleNumbers[iColumn][iRow].isSolved() ){
                for ( int i = 1; i <= 3; ++i ) {
                    if ( m_oPossibleNumbers[iColumn][iRow].isPossible(i - 1))
                        std::cout << " " << i << " ";
                    else
                        std::cout << " - ";
                }
            } else {
                std::cout << " -  -  - ";
            }

            if ( iColumn == 2 || iColumn == 5)
                std::cout << " | ";
            else
                std::cout << "  ";

        }
        std::cout << std::endl;

        for ( int iColumn = 0; iColumn < 9; ++ iColumn) {
            if ( !m_oPossibleNumbers[iColumn][iRow].isSolved() ){
                for ( int i = 4; i <= 6; ++i ) {
                    if ( m_oPossibleNumbers[iColumn][iRow].isPossible(i - 1))
                        std::cout << " " << i << " ";
                    else
                        std::cout << " - ";
                }
            } else {
                std::cout << " - |" << m_oPossibleNumbers[iColumn][iRow].getSolvedDigitP1() << "| - ";
            }


            if ( iColumn == 2 || iColumn == 5)
                std::cout << " | ";
            else
                std::cout << "  ";
        }
        std::cout << std::endl;

        for ( int iColumn = 0; iColumn < 9; ++ iColumn) {
            if ( !m_oPossibleNumbers[iColumn][iRow].isSolved() ){
                for ( int i = 7; i <= 9; ++i ) {
                    if ( m_oPossibleNumbers[iColumn][iRow].isPossible(i - 1))
                        std::cout << " " << i << " ";
                    else
                        std::cout << " - ";
                }
            } else {
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

void CBoardManager::insert( const vector2d &pos, short iDigit )
{
    std::cout << "inserting " << iDigit << " at : " << pos << std::endl;

    // Can iDigit be inserted to pos?
    if ( m_oBoard.insert( pos, iDigit, true ) )
    {
        // Update the possibilities for this position
        m_oPossibleNumbers[pos.x][pos.y].setAndMarkAsSolved( iDigit - 1 );
        removePossibilitiesInsert( pos, iDigit );
    }

}
