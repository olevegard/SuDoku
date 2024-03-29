#include "SuDokuBoard.h"
#include <cstring>
#include <iomanip>

static const bool PRINT_TIME    = true; 	// Prints time status during the end
static const bool SPEED_ONLY    = false; 	// Disable checking features
static const bool PRINT_INFO    = false;	// Name of function
static const bool PRINT_BOARD   = false;	// Prints boards during inserts
static const bool PRINT_DEBUG   = false;	// Main debugging option.
static const bool FREEZE        = false;	// Flag for calling std::cin.ignore()

CSuDokuBoard::CSuDokuBoard()

	:  m_bGuessMode        ( false )
{
	for ( int i = 0; i < ( 9 * 9 ); ++i)
	{
		int iX = i % 9;
		int iY = i / 9;

		m_shBoard[iX][iY] = -1;
		m_bLookedPositions[iX][iY] = false;

	}
}

//======================================================================================================
//============================================== Inserting =============================================
//======================================================================================================
bool CSuDokuBoard::insert(const vector2d &pos, short iDigit, bool bLock )
{

	if ( PRINT_INFO)
		std::cout << "insert " << pos << " digit : " << iDigit + 1 << std::endl;

	if ( m_shBoard[pos.x][pos.y] != -1 )
	{
		std::cout << "pos : " << pos << " allready filled!\n";
		return ( m_shBoard[pos.x][pos.y] == iDigit );
	}

	// Need to know if the move is valid
	// Need to check if position is locked ( if something has been inserted into this position allready )
	if ( chekIfPositionIsLocked(pos) || !checkMoveValidity( pos, iDigit ) )
	{
		std::cout << "Board@" << __LINE__ << " ERROR INSERTING " << iDigit + 1  << " at : " << pos << std::endl;
		std::cin.ignore();
		return false;
	}

	// Insert digit into board
	m_shBoard[pos.x][pos.y] = iDigit;

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
	///UpdateSolveInformation( pos );


	return true;
}
//============================================================================================================
//============================================== Status updating =============================================
//============================================================================================================



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
		std::cout << "isValidMove " << iDigit + 1 << " into " << pos << " ? " << std::boolalpha << isValid << std::endl;

	if ( !isValid )
		printBoard(pos, vector2d(-1,-1));

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
		{
			std::cout << "Line : " << __LINE__ << " Digit " << iDigit + 1 << " found in " << iColumn << " , " << i << std::endl;
			return true;
		}
	}

	return false;
}

bool CSuDokuBoard::isDigitPlacedInRow( short iRow, short iDigit ) const
{
	for ( short i = 0; i < 9; ++i ) {

		if ( m_shBoard[i][iRow] == iDigit)
		{
			std::cout << "Line : " << __LINE__ << " Digit " << iDigit + 1 << " found in " << i << " , " << iRow << std::endl;
			return true;
		}
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
			{
				std::cout << "Line : " << __LINE__  << " Digit " << iDigit + 1 << " found in " << posOrigo.x + i << " , " << posOrigo.y + i << std::endl;
				return true;
			}
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
	return ( 9 * 9 );// - m_iUnsolvedPosCount;
}

char CSuDokuBoard::getValueOfPosition( const vector2d &pos ) const
{
	short iValue = m_shBoard[pos.x][pos.y];

	if ( iValue >= 0  )
	{
		// Return charter value of this digit
		return '1' + iValue;
	}
	else
		// No digit ( valid ) digit inserter, return -
		return '-';
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
