#include "SuDokuBoard.h"
#include <cstring>
#include <algorithm>
#include <iomanip>

static const bool PRINT_TIME    = true; 	// Prints time status during the end
static const bool SPEED_ONLY    = false; 	// Disable checking features
static const bool PRINT_INFO    = false;	// Name of function
static const bool PRINT_BOARD   = false;	// Prints boards during inserts
static const bool PRINT_DEBUG   = true;	// Main debugging option.
static const bool FREEZE        = false;	// Flag for calling std::cin.ignore()

CSuDokuBoard::CSuDokuBoard()
    :  m_iProgressRows     ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
    ,  m_iProgressColumns  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
    ,  m_iProgressSquares  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
    ,  m_iUnsolvedPosCount ( 0 )
    ,  m_vUnsolvedPositions( 0 )
    ,  m_bGuessMode        ( false )
{
    for ( int i = 0; i < ( 9 * 9 ); ++i)
    {
        int iX = i % 9;
        int iY = i / 9;

        m_shBoard[iX][iY] = 0;
        m_bLookedPositions[iX][iY] = false;

        m_vUnsolvedPositions.push_back( vector2d(iX, iY));
        m_iUnsolvedPosCount++;
    }
}

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

void CSuDokuBoard::loadBoard( const char* czBoard )
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
            std::cout << "inserting " << iDigit << " at : " << pos << std::endl;
            insert( pos, iDigit, true );
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
bool CSuDokuBoard::insert(const vector2d &pos, short digit, bool bLock )
{

    if ( PRINT_INFO)
        std::cout << "insert " << pos << " digit : " << digit << std::endl;

    // Need to know if the move is valid
    // Need to check if position is locked ( if something has been inserted into this position allready )
    if ( chekIfPositionIsLocked(pos) || !checkMoveValidity( pos, digit ) )
    {
        std::cin.ignore();
        return false;
    }

    // Insert digit into board
    m_shBoard[pos.x][pos.y] = digit;

    /*
    // Check row/column/square that intersects with this position for errors.
   if ( !checkBoardValidity(pos) )
        bSucces = false;
*/

    if ( bLock  || !m_bGuessMode)
    {
        //lockPosition( pos );
    }

    // Update list of solved positions ( number of unsolved positions, solved in column/row/square )
    UpdateSolveInformation( pos );


    return true;
}
//============================================================================================================
//============================================== Status updating =============================================
//============================================================================================================
void CSuDokuBoard::UpdateSolveInformation( const vector2d &pos)
{

    removeFromListOfUnsolvedPositions(pos);

    ++m_iProgressColumns[pos.x];
    ++m_iProgressRows[pos.y];
    ++m_iProgressSquares[ pos.x / 3 + (( pos.y / 3) * 3 )];


}

void CSuDokuBoard::removeFromListOfUnsolvedPositions( const vector2d &pos )
{

    std::vector<vector2d>::iterator p;

    p = std::find( m_vUnsolvedPositions.begin(), m_vUnsolvedPositions.end(), pos );

    if ( p != m_vUnsolvedPositions.end() )
    {
        m_vUnsolvedPositions.erase( p );

        --m_iUnsolvedPosCount;
    }

}
//==============================================================================================================
//============================================== Validity checking =============================================
//==============================================================================================================
bool CSuDokuBoard::checkMoveValidity ( const vector2d &pos, short iDigit ) const
{

    if ( SPEED_ONLY )
        return true;

    bool isValid = ( !isDigitPlacedInColumn( pos.x, iDigit )
         && !isDigitPlacedInRow( pos.y, iDigit )
         && !isDigitPlacedInSquare( pos,  iDigit )
    );

    if ( PRINT_DEBUG )
        std::cout << "isValidMove " << iDigit << " into " << pos << " ? " << std::boolalpha << isValid << std::endl;

    if ( !isValid )
        printBoard();

    return isValid;
}

bool CSuDokuBoard::chekIfPositionIsLocked(const vector2d &pos) const
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

    return false;

}

bool CSuDokuBoard::checkBoardValidity(const vector2d &pos) const
{

    if ( SPEED_ONLY )
        return true;

    bool valid = true;

    if (!checkColumnValidity( pos.x ) )
    {
        std::cout << "Error found in column " << pos.x << std::endl;
        valid = false;
    }

    if (!checkRowValidity( pos.y ) )
    {
        std::cout << "Error found in row " << pos.y << std::endl;
        valid = false;
    }

    if (!checkSquareValidity( pos ) )
    {
        std::cout << "Error found in square " << pos  << std::endl;
        valid = false;
    }

    // Should be informed asap if something is not valid
    if ( !valid )
        std::cin.ignore();

    return valid;
}

bool CSuDokuBoard::checkBoardValidity(  ) const
{
    bool bValid = true;

    vector2d pos( 0, 0);
    for ( short i = 0; i < 9; ++i )
    {
        if ( !checkRowValidity( i ) || !checkColumnValidity(i) || !checkSquareValidity(pos))
            bValid = false;


        // Increment pos
        if ( pos.x == 6 )
        {
            pos.x = 0;
            pos.y += 3;
        } else
            pos.x += 3;
    }

    // If something is wrong, it will have been printed once allready.
    // But freezing should only be done once, hence it's done here
    if ( !bValid )
        std::cin.ignore();

    return bValid;

}

bool CSuDokuBoard::checkRowValidity( short iRow ) const
{
    vector2d matchLocation[9];

    bool bDigitValid[9] = {
        false, false, false,
        false, false, false,
        false, false, false
    };

    for ( short i = 0; i < 9; ++i ) {

        short iDigit = m_shBoard[i][iRow];

        if ( iDigit > 0 ) {

            if ( bDigitValid[ iDigit - 1] )
            {
                printBoard(vector2d(i, iRow), matchLocation[iDigit - 1]);

                if ( PRINT_DEBUG )
                        std::cout << "Error found in " << vector2d(i, iRow) << " and " << matchLocation[iDigit - 1] << " : " << iDigit << std::endl;

                return false;
            }

            bDigitValid[ iDigit - 1] = true;
            matchLocation[iDigit - 1].x = i;
            matchLocation[iDigit - 1].y = iRow;

        }
    }

    return true;
}

bool CSuDokuBoard::checkSquareValidity( const vector2d &pos ) const
{
    vector2d matchLocation[9];
    vector2d origo = pos.GetOrigo();

    bool bDigitValid[9] =
    {
        false, false, false,
        false, false, false,
        false, false, false
    };

    short j = 0;
    for ( short i = 0; i < 3; ++i )
    {
        for ( ; j < 3; j++ )
        {

            short iDigit = m_shBoard[ pos.x * 3 + i][pos.y * 3 + j];

            if ( iDigit > 0 )
            {

                if ( bDigitValid[ iDigit - 1] )
                {
                    printBoard( vector2d( origo.x + i, origo.y + j ), matchLocation[iDigit - 1]);

                    if ( PRINT_DEBUG )
                        std::cout << "Error found in " << vector2d( origo.x + i, origo.y + j ) << " and " << matchLocation[iDigit - 1] << " : " << iDigit << std::endl;

                    return false;
                }

                bDigitValid[ iDigit - 1] = true;
                matchLocation[iDigit - 1].x = (origo.x + i);
                matchLocation[iDigit - 1].y = (origo.y + j);

            }
        }

        j = 0;


    }
    return true;
}

bool CSuDokuBoard::checkColumnValidity( short iColumn ) const
{
    vector2d matchLocation[9];

    bool bDigitValid[9] =
    {
        false, false, false,
        false, false, false,
        false, false, false
    };

    for ( short i = 0; i < 9; ++i )
    {

        short iDigit = m_shBoard[iColumn][i];

        if ( iDigit > 0 ) {

            if ( bDigitValid[ iDigit - 1] )
            {
                printBoard(vector2d(iColumn, i), matchLocation[iDigit - 1]);

                if ( PRINT_DEBUG )
                    std::cout << "Error found in " << vector2d(iColumn, i) << " and " << matchLocation[iDigit - 1] << " : " << iDigit << std::endl;

                return false;
            }

            bDigitValid[ iDigit - 1] = true;
            matchLocation[iDigit - 1].x = iColumn;
            matchLocation[iDigit - 1].y = i;
        }
    }

    return true;
}

bool CSuDokuBoard::isDigitPlacedInColumn( short iColumn, short iDigit ) const
{
    for ( short i = 0; i < 9; ++i ) {

        if ( m_shBoard[iColumn][i] == iDigit)
            return true;
    }

    return false;
}

bool CSuDokuBoard::isDigitPlacedInRow( short iRow, short iDigit ) const
{
    for ( short i = 0; i < 9; ++i ) {

        if ( m_shBoard[i][iRow] == iDigit)
            return true;
    }

    return false;
}

bool CSuDokuBoard::isDigitPlacedInSquare( const vector2d &pos, short iDigit) const
{
    vector2d posOrigo = pos.GetOrigo();
    short j = 0;

    for ( short i = 0; i < 3; ++i ) {
        for ( ; j < 3; j++ ) {

            if ( m_shBoard[ posOrigo.x + i][posOrigo.y + j] == iDigit)
                return true;
        }

        j = 0;
    }

    return false;
}
//=====================================================================================================
//============================================== Progress =============================================
//=====================================================================================================
short CSuDokuBoard::getProgressRow(short iRow) const
{
    short iNumbersFilledIn = 0;

    for ( short i = 0; i < 9; ++i )
    {
        if ( m_shBoard[i][iRow] != 0)
            iNumbersFilledIn++;
    }

    return iNumbersFilledIn;
}

short CSuDokuBoard::getProgressColumn(short iColumn) const
{
    short iNumbersFilledIn = 0;

    for ( short i = 0; i < 9; ++i )
    {
        if ( m_shBoard[iColumn][i] != 0)
            iNumbersFilledIn++;
    }

    return iNumbersFilledIn;
}

short CSuDokuBoard::getProgressSquare( const vector2d &pos ) const
{
    short iNumbersFilledIn = 0;
    short j = 0;

    for ( short i = 0; i < 3; ++i )
    {
        for ( ; j < 3; j++ )
        {
            if ( m_shBoard[ pos.x * 3 + i][pos.y * 3 + j] != 0)
                iNumbersFilledIn++;
        }

        j = 0;
    }

    return iNumbersFilledIn;
}

short CSuDokuBoard::getTotatlProgress() const
{
    return ( 9 * 9 ) - m_iUnsolvedPosCount;
}


char CSuDokuBoard::getValueOfPosition( const vector2d &pos ) const
{
    short iValue = m_shBoard[pos.x][pos.y];

    if ( iValue > 0  )
    {
        // Return charter value of this digit
        return 48 + iValue;
    }
    else
        // No digit ( valid ) digit inserter, return -
        return '-';
}




const std::vector<vector2d>& CSuDokuBoard::getUnsolvedPositions() const
{
    return m_vUnsolvedPositions;
}


void CSuDokuBoard::printBoard( const vector2d &pos1, const vector2d &pos2) const
{
    std::cout << "   =====================BOARD STATUS====================\n";

    vector2d currentPos(0,0);

    for ( ;currentPos.y < 9; ++ currentPos.y )
    {

        std::cout << "   || ";

        for ( ; currentPos.x < 9; currentPos.x++)
        {

            // Add space between every three columns...
            if ( currentPos.x == 3 || currentPos.x == 6)
                std::cout << "     ";

            // If ( i, j ) is the same as pos1 or pos2, surround this digit by |
            // Otherwise, use spaces
            if ( currentPos == pos1 || currentPos == pos2)
                std::cout << " |" << getValueOfPosition( currentPos ) << "|";
            else
                std::cout << "  " << getValueOfPosition( currentPos ) << " ";
        }

        currentPos.x = 0;

        // And spacing lines between every three rows
        if ( currentPos.y == 2 || currentPos.y == 5 )
            std::cout << "  ||\n\n\n";
        else
            std::cout << "  ||\n\n";
    }

    std::cout << "   =====================================================\n";
}

void CSuDokuBoard::printBoard( ) const
{
    printBoard( vector2d(-1,-1), vector2d(-1,-1));
}