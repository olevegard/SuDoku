#include "SuDokuBoard.h"
#include <cstring>

static const bool PRINT_TIME    = true; 	// Prints time status during the end
static const bool SPEED_ONLY    = true; 	// Disable checking features
static const bool PRINT_INFO    = false;	// Name of function
static const bool PRINT_BOARD   = false;	// Prints boards during inserts
static const bool PRINT_DEBUG   = false;	// Main debugging option.
static const bool FREEZE        = false;	// Flag for calling std::cin.ignore()

//======================================================================================================
//=========================================== Loading Boards ===========================================
//======================================================================================================
void CSuDokuBoard::loadBoard()
{

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

/*
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

void CSuDokuBoard::loadBoard( const char* board )
{
    short length =  strlen( board );
    vector2d pos(0,0);

    short shDigit = 0;
    for ( int i = 0; i < length; ++i)
    {
        // Convert current char to a digit
        switch ( board[i] )
        {
            case '1':
                shDigit = 1;
                break;
            case '2':
                shDigit = 2;
                break;
            case '3':
                shDigit = 3;
                break;
            case '4':
                shDigit = 4;
                break;
            case '5':
                shDigit = 5;
                break;
            case '6':
                shDigit = 6;
                break;
            case '7':
                shDigit = 7;
                break;
            case '8':
                shDigit = 8;
                break;
            case '9':
                shDigit = 9;
                break;
            default:
                shDigit = 0;
                break;
        }

        // Insert digit
        if ( shDigit != 0 )
        {
            std::cout << "inserting " << shDigit << " at : " << pos << std::endl;
            //insert( pos, shDigit, true );
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

}

//======================================================================================================
//============================================== Inserting =============================================
//======================================================================================================
bool CSuDokuBoard::insert(const vector2d &pos, short digit, bool lock )
{

    if ( PRINT_INFO)
        std::cout << "insert " << pos << " digit : " << digit << std::endl;

    // Need to know if the move is valid
    if ( !checkMoveValidity( pos, digit ) )
        return false;

    // Need to check if position is locked ( if something has been inserted into this position allready )
    if ( chekIfPositionIsLocked(pos) )
        return false;

    // Insert digit into board
    m_shBoard[pos.x][pos.y] = digit;

    // Check row/column/square that intersects with this position for errors.
   if ( !checkBoardValidity(pos) )
       return false;

    if ( lock  || !m_bGuessMode)
    {
        //lockPosition( pos );
    }

    // Update list of solved positions ( number of unsolved positions, solved in column/row/square )
    UpdateSolveInformation( pos );

    // Need to remove digit from CellsS set pos as solved and set its value
    // TODO: move to solver
    m_oPossibleNumbers[pos.x][pos.y].bSolved = true;
    m_oPossibleNumbers[pos.x][pos.y].set( digit - 1 );

    // TODO; seperate function
    // Freezes terminal so that ouput can be read.
    if ( FREEZE )
        std::cin.ignore();

    return true;
}
//============================================================================================================
//============================================== Status updating =============================================
//============================================================================================================
void CSuDokuBoard::UpdateSolveInformation( const vector2d &pos)
{
    // Remove the possiblility ( it's not unsolved anymore ) and decrement the number of unsolved posititions
    removeFromListOfUnsolvedPositions(pos);

    ++m_iProgressColumns[pos.x];
    ++m_iProgressRows[pos.y];
    ++m_iProgressSquares[ pos.x / 3 + (( pos.y / 3) * 3 )];


}

void CSuDokuBoard::removeFromListOfUnsolvedPositions( const vector2d &pos )
{

    int i = 0;

    // Todo: use std::find?
    for ( ; i < m_iUnsolvedPosCount; ++i )
    {
        if ( m_vUnsolvedPositions[i].x == pos.x && m_vUnsolvedPositions[i].y == pos.y )
        {
            m_vUnsolvedPositions.erase( m_vUnsolvedPositions.begin() + i);
            break;
        }
    }

    --m_iUnsolvedPosCount;

}
//==============================================================================================================
//============================================== Validity checking =============================================
//==============================================================================================================
bool CSuDokuBoard::checkMoveValidity ( const vector2d &pos, short digit )
{

    if ( SPEED_ONLY )
        return false;

    if ( PRINT_DEBUG )
        std::cout << "isValidMove " << digit << " into " << pos << " ?";

    if ( !isDigitPlacedInColumn( pos.x, digit )
         && !isDigitPlacedInRow( pos.y, digit )
         && !isDigitPlacedInSquare( pos,  digit ) )
    {
        if ( PRINT_DEBUG )
            std::cout << " Yes!\n";

        return true;
    }

    else
    {
        if ( PRINT_DEBUG )
            std::cout << " No!\n";

        return false;
    }
}

bool CSuDokuBoard::checkBoardValidity(const vector2d &pos)
{

    if ( SPEED_ONLY )
        return true;

    bool valid = true;

    if (!validateCoumn(pos.x))
    {
        std::cout << "Error found in column " << pos.x << std::endl;
        valid = false;
    }

    if (!validateRow(pos.y))
    {
        std::cout << "Error found in row " << pos.y << std::endl;
        valid = false;
    }

    if (!validateSquare( pos.x / 3, pos.y / 3))
    {
        std::cout << "Error found in square " << pos  << std::endl;
        valid = false;
    }

    // Should be informed asap if something is not valid
    if ( !valid )
        std::cin.ignore();

    return valid;
}

bool CSuDokuBoard::chekIfPositionIsLocked(const vector2d &pos)
{
    // Check if position is locekd.
    if ( SPEED_ONLY )
        return false;

    if ( m_bLookedPositions[pos.x][pos.y] )
    {
        std::cout << "Can't insert " << pos << " position is locked\n";
        std::cin.ignore();  // Since locks aren't implemented yet -> pause
        return true;
    }

}

