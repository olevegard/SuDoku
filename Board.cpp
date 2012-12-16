#include "Board.h"

#include "Digit.h"
#include "PositionPair.h"

#include <stdio.h>
#include <signal.h>
#include <algorithm>


static const bool PRINT_TIME    = true; 	// Prints time status during the end
static const bool SPEED_ONLY    = true; 	// Disable checking features
static const bool PRINT_INFO    = false;	// Name of function
static const bool PRINT_BOARD   = false;	// Prints boards during inserts
static const bool PRINT_DEBUG   = false;	// Main debugging option.
static const bool FREEZE        = false;	// Flag for calling std::cin.ignore()

	CBoard::CBoard()
	:  m_iProgressRows     ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
	,  m_iProgressColumns  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
	,  m_iProgressSquares  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
	,  m_bGuessMode        ( false )
	,  m_bErrorFound       ( false )
	,  m_iUnsolvedPosCount ( 0 )
	,  m_vUnsolvedPositions( 0 )
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

CBoard::~CBoard()
{

}

bool CBoard::insert_Validate( const vector2d &pos, const short iDigit)
{

	return insert(pos, iDigit);

}

bool CBoard::insert_Lock( const vector2d &pos, const short iDigit)
{

	return insert(pos, iDigit, true);

}

bool CBoard::insert(const vector2d &pos, short shDigit, bool bLock)
{

    if ( PRINT_INFO)
		std::cout << "insert " << pos.x << " , " << pos.y << " digit : " << shDigit << std::endl;


    if ( PRINT_BOARD )
        printAllPosibilities();

    if ( FREEZE )
        std::cin.ignore();

	// Check if position is locekd.
	if ( !SPEED_ONLY )
	{
		if ( m_bLookedPositions[pos.x][pos.y] )
		{
			std::cout << "Can't insert " << pos.x << " , " << pos.y << " position is locked\n";
            std::cin.ignore();
			return false;
		}
	}
	// Insert digit into board
	m_shBoard[pos.x][pos.y] = shDigit;

	if ( !SPEED_ONLY )
	{
		if ( !validateEverything(pos))
		{
			m_bErrorFound = true;
			std::cout << "Could not place " << shDigit << " inside " << pos << std::endl;
			std::cin.ignore();
			return false;
		}
	}
	m_oPossibleNumbers[pos.x][pos.y].bSolved = true;
    //m_oPossibleNumbers[pos.x][pos.y].shDigit = shDigit;
    m_oPossibleNumbers[pos.x][pos.y].set( shDigit - 1 );

	if ( bLock  || !m_bGuessMode)
	{
		lockPosition( pos );
	}

	// Remove the possiblility ( it's not unsolved anymore ) and decrement the number of unsolved posititions
	removeFromListOfUnsolvedPositions(pos);
	m_iUnsolvedPosCount--;

	// Update list of solved colums
	m_iProgressColumns[pos.x]++;
	m_iProgressRows[pos.y]++;
	m_iProgressSquares[ pos.x / 3 + (( pos.y / 3) * 3 )]++;
	removePossibilitiesInsert(pos, shDigit);

	if ( PRINT_DEBUG )
	{
		for ( int i = 0; i < 9; ++i )
		{
			std::cout << "=====================================================================\n";
			std::cout << "column " << i << " has " << m_iProgressColumns[i]   << " solve digits\n";
			std::cout << "row    " << i << " has " << m_iProgressRows[i]      << " solve digits\n";
			std::cout << "square " << i << " has " << m_iProgressSquares[i]   << " solve digits\n";
			std::cout << "=====================================================================\n";
		}
	}

	return true;
}

char CBoard::getValue( const short shColumn, const short shRow)
{
	if ( m_shBoard[shColumn][shRow] > 0  )
	{
		// Return charter value of this digit
		return 48 + m_shBoard[shColumn][shRow];
	}
	else
		// No digit ( valid ) digit inserter, return -
		return '-';
}

bool CBoard::validateEverything(){

	for (  short i = 0; i < 9 ; ++i ) {
		if ( !validateRow(i) )
			return false;
		else if ( !validateCoumn(i) )
			return false;
	}

	if ( !validateSquare(0,0) )
		return false;
	if ( !validateSquare(0,1) )
		return false;
	if ( !validateSquare(0,2) )
		return false;
	if ( !validateSquare(1,0) )
		return false;
	if ( !validateSquare(1,1) )
		return false;
	if ( !validateSquare(1,2) )
		return false;
	if ( !validateSquare(2,0) )
		return false;
	if ( !validateSquare(2,1) )
		return false;
	if ( !validateSquare(2,2) )
		return false;

	return true;
}

bool CBoard::validateEverything(const vector2d &pos){

	if (!validateCoumn(pos.x)) {
		return false;
	}

	if (!validateRow(pos.y)) {
		return false;
	}

	if (!validateSquare( pos.x / 3, pos.y / 3)) {
		return false;
	}

	return true;
}

bool CBoard::validateSquare(const short shColumn, const short shRow){
	vector2d matchLocation[9];

	bool bDigitValid[9] = {
		false, false, false,
		false, false, false,
		false, false, false};

	short j = 0;
	for ( short i = 0; i < 3; ++i ) {
		for ( ; j < 3; j++ ) {

			short digit = m_shBoard[ shColumn * 3 + i][shRow * 3 + j];

			if ( digit > 0 ) {

				if ( bDigitValid[ digit - 1] ){
					printBoard( vector2d((shColumn * 3 + i), (shRow * 3 + j)),
							matchLocation[digit - 1]);
					return false;
				}

				bDigitValid[ digit - 1] = true;
				matchLocation[digit - 1].x = (shColumn * 3 + i);
				matchLocation[digit - 1].y = (shRow * 3 + j);

			}
		}

		j = 0;
	}

	return true;

}

bool CBoard::validateRow( const short shRow){

	vector2d matchLocation[9];

	bool bDigitValid[9] = {
		false, false, false,
		false, false, false,
		false, false, false
	};

	for ( short i = 0; i < 9; ++i ) {

		short digit = m_shBoard[i][shRow];

		if ( digit > 0 ) {

			if ( bDigitValid[ digit - 1] ){
				printBoard(vector2d(i, shRow), matchLocation[digit - 1]);

				return false;
			}

			bDigitValid[ digit - 1] = true;
			matchLocation[digit - 1].x = i;
			matchLocation[digit - 1].y = shRow;

		}
	}

	return true;

}

bool CBoard::validateCoumn( const short shColumn){

	vector2d matchLocation[9];

	bool bDigitValid[9] = {
		false, false, false,
		false, false, false,
		false, false, false};

	for ( short i = 0; i < 9; ++i ) {

		short digit = m_shBoard[shColumn][i];

		if ( digit > 0 ) {

			if ( bDigitValid[ digit - 1] ){
				printBoard(vector2d(shColumn, i), matchLocation[digit - 1]);
				return false;
			}

			bDigitValid[ digit - 1] = true;
			matchLocation[digit - 1].x = shColumn;
			matchLocation[digit - 1].y = i;
		}
	}
	return true;
}
bool CBoard::XWingHelper_Row(  )
{

    short iRow2 = 0;
    bool bSucces = false;

    for ( short iRow1 = 0; iRow1 < 9; ++iRow1 )
    {
        iRow2 = iRow1 + 1;

        for ( ; iRow2 < 9; ++iRow2 )
        {
            if ( checkForXWing_Rows( iRow1, iRow2 ) )
                bSucces = true;
        }
    }

    return bSucces;

}
bool CBoard::checkForXWing_Rows( short iRow1, short iRow2 )
{
	if (PRINT_INFO )
		std::cout << "Checking X Wing row " << iRow1 << " and " << iRow2 << std::endl;

	bool bSolved = false;

	for ( short iDigit = 0; iDigit  < 9; ++iDigit )
	{
		short iCount = 0;
		short iPairColumn1 = 0;
		short iPairColumn2 = 0;
		
		for ( short iColumn = 0; iColumn < 9; ++iColumn )
		{
			if (
				  ( !m_oPossibleNumbers[iColumn][iRow1].bSolved && m_oPossibleNumbers[iColumn][iRow1].isPossible(iDigit ))
				&&( !m_oPossibleNumbers[iColumn][iRow2].bSolved && m_oPossibleNumbers[iColumn][iRow2].isPossible(iDigit ))
			   )
			{
				if ( PRINT_DEBUG )
					std::cout << "\tFound in column " << iColumn << " digit : " << iDigit + 1 << " count : " << iCount << std::endl;

				if ( iCount == 0 )
					iPairColumn1 = iColumn;
				else if ( iCount == 1 )
					iPairColumn2 = iColumn;

				++iCount;
			} else if (
				  ( !m_oPossibleNumbers[iColumn][iRow1].bSolved && m_oPossibleNumbers[iColumn][iRow1].isPossible(iDigit ))
				||( !m_oPossibleNumbers[iColumn][iRow2].bSolved && m_oPossibleNumbers[iColumn][iRow2].isPossible(iDigit ))
				)
			{
				if (PRINT_DEBUG )
					std::cout << "\tColumn : " << iColumn << " found " << iDigit + 1 << " in one row, but not the other, skipping\n";

				iCount = 0; 
				break;
			}
		}

		if ( iCount == 2 )
		{
			if ( PRINT_DEBUG )
			{
				std::cout << "Found " << iDigit + 1
					<< "\n   in  " << iPairColumn1 << " , " << iRow1
					<< "\n   and " << iPairColumn2 << " , " << iRow1
					<< "\n   in  " << iPairColumn1 << " , " << iRow2
					<< "\n   and " << iPairColumn2 << " , " << iRow2
					<< std::endl;
			}

			// Remove iDigit from the rest of the columni
			for ( int iRowDelete = 0; iRowDelete < 9; ++iRowDelete )
			{
				if ( iRowDelete == iRow1 || iRowDelete  == iRow2  )
					continue;

				if (PRINT_DEBUG )
				{
					std::cout << "\t\tDeleting " << iDigit + 1
						<< "   \nfrom " << iPairColumn1  << " , " <<iRowDelete
						<< "   \nand  " << iPairColumn2  << " , " <<iRowDelete
						<< std::endl;
				}

				m_oPossibleNumbers[iPairColumn1][iRowDelete].remove( iDigit );
				m_oPossibleNumbers[iPairColumn2][iRowDelete].remove( iDigit );
			}
			bSolved = true;

			if ( PRINT_BOARD ) 
				printAllPosibilities();

			if ( FREEZE )
				std::cin.ignore();

		}
	}

	if ( !bSolved && PRINT_DEBUG )
		std::cout << "No XWing found!\n";

	return bSolved;

}

int CBoard::finCountOfDigitInRow( short iDigit, short iRow)
{

	short iCount = 0;
	for ( short i = 0; i < 9; ++i )
	{
		if ( !m_oPossibleNumbers[i][iRow].bSolved && m_oPossibleNumbers[i][iRow].isPossible(iDigit ))
			++iCount;
	}

	return iCount;

}
void CBoard::findPossibleNumbersForAllPositions( const bool bAdd ){

	if ( PRINT_DEBUG)
		std::cout << "findPossibleNumbersForAllPositions\n";

	int iSize = m_vUnsolvedPositions.size();

	// Check all unsolved positionas and add all numbers for all of them
	//  Loop through all the unsoled posiions.
	for ( int iPosition = 0; iPosition < iSize; ++iPosition ) {
		vector2d pos = m_vUnsolvedPositions[iPosition];
		//if ( PRINT_DEBUG ) std::cout << "checking : " << pos << std::endl;

		// Loop through all digits
		for (int iDigit = 1; iDigit <= 9; ++iDigit ) {

			if ( PRINT_DEBUG )
				std::cout << "  digit : " << iDigit;

			// Check if the digit can go    in this pos.
			if ( isValidMove(pos, iDigit) ) {
				if ( bAdd ) {
					m_oPossibleNumbers[pos.x][pos.y].add( iDigit );

					if ( PRINT_DEBUG )
						std::cout << " addded\n";
				}
			} else {
				if ( FREEZE )
				{
					std::cout << "removing : " << iDigit << " from  " << pos << std::endl;
					std::cin.ignore();
				}
				m_oPossibleNumbers[pos.x][pos.y].remove( iDigit - 1);

				if ( PRINT_DEBUG )
					std::cout << " removed\n";
			}
		}
	}
}
bool CBoard::checkForNakedPairs_SingleSquare( const short shSquare ) {

	if ( PRINT_DEBUG)
		std::cout << "checkForHiddenDoubles_SingleSquare " << shSquare << std::endl;

	vector2d posOrigo;

	switch ( shSquare) {
		case 0:
			posOrigo.x = 0;
			posOrigo.y = 0;
			break;
		case 1:
			posOrigo.x = 3;
			posOrigo.y = 0;
			break;
		case 2:
			posOrigo.x = 6;
			posOrigo.y = 0;
			break;
		case 3:
			posOrigo.x = 0;
			posOrigo.y = 3;
			break;
		case 4:
			posOrigo.x = 3;
			posOrigo.y = 3;
			break;
		case 5:
			posOrigo.x = 6;
			posOrigo.y = 3;
			break;
		case 6:
			posOrigo.x = 0;
			posOrigo.y = 6;
			break;
		case 7:
			posOrigo.x = 3;
			posOrigo.y = 6;
			break;
		case 8:
			posOrigo.x = 6;
			posOrigo.y = 6;
			break;
		default:
			break;
	}
	short shSquareIndex2 = 0;
	bool bFound = false;

	for ( short shSquareIndex = 0; shSquareIndex < 9; ++shSquareIndex )
	{
		shSquareIndex2 = shSquareIndex + 1;
		for ( ; shSquareIndex2 < 9; ++shSquareIndex2 )
		{

			vector2d pos1( posOrigo.x + ( shSquareIndex % 3 ),
					posOrigo.y + ( shSquareIndex / 3 ));

			vector2d pos2( posOrigo.x + ( shSquareIndex2 % 3 ),
					posOrigo.y + ( shSquareIndex2 / 3 ));

			Cell cell1 = m_oPossibleNumbers[pos1.x][pos1.y];
			Cell cell2 = m_oPossibleNumbers[pos2.x][pos2.y];

			// Checkinf for naked pair two cell with only the two same numbers..
			if ( cell1.isNakedPair(cell2) )
			{
				bFound = true;

				if ( PRINT_DEBUG )
				{
					std::cout << "...HiddenPair!" << pos1 << " and " << pos2
						<< " : " << cell1.shHiddenDouble1 << " & " << cell1.shHiddenDouble2 << std::endl;
					std::cin.ignore();
				}
				// Remove all other instance of the found numbers in this column
				// TODO : Make this into a function
				// ...removePosibilities_Column( const short shColum, const short shExcept1, const short shExcept2, const short shDigit1, const short shDigit2)
				// Where shExcept1 and shExcept1 are the columns that make up the matching pairs ( should not have shDigit1 and shDigit2 removed
				// TODO2 : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )

				for ( int i = 0; i < 9; ++i)
				{
					if ( i != shSquareIndex && i != shSquareIndex2)
					{
						if ( PRINT_DEBUG )
						{
							std::cout << posOrigo.x + ( i % 3 ) << " , " << posOrigo.y + ( i / 3 )
								<< " Removing : " << cell1.shHiddenDouble1 << " and " << cell1.shHiddenDouble2 << std::endl;

							if ( PRINT_BOARD )
								printAllPosibilities();

							if ( FREEZE )
								std::cin.ignore();
							
						}
						m_oPossibleNumbers
							[ posOrigo.x + ( i % 3 )]
							[ posOrigo.y + ( i / 3 )]
							.remove(cell1.shHiddenDouble1 - 1);

						m_oPossibleNumbers
							[ posOrigo.x + ( i % 3 )]
							[ posOrigo.y + ( i / 3 )]
							.remove(cell1.shHiddenDouble2 - 1);

					}

				}
			} // End check for naked pair

			// Check for hidden pair
		}
	}

	return bFound;
}

bool CBoard::checkForPointingPairs(const short shSquareID)
{
	if ( PRINT_DEBUG)
		std::cout << "checkForPointingPairs : " << shSquareID << std::endl;

	vector2d posSquare;

	switch ( shSquareID) {
		case 0:
			posSquare.x = 0;
			posSquare.y = 0;
			break;
		case 1:
			posSquare.x = 3;
			posSquare.y = 0;
			break;
		case 2:
			posSquare.x = 6;
			posSquare.y = 0;
			break;
		case 3:
			posSquare.x = 0;
			posSquare.y = 3;
			break;
		case 4:
			posSquare.x = 3;
			posSquare.y = 3;
			break;
		case 5:
			posSquare.x = 6;
			posSquare.y = 3;
			break;
		case 6:
			posSquare.x = 0;
			posSquare.y = 6;
			break;
		case 7:
			posSquare.x = 3;
			posSquare.y = 6;
			break;
		case 8:
			posSquare.x = 6;
			posSquare.y = 6;
			break;
		default:
			break;

	}
	// Pointing pair
	// ==============================================================================================================
	// A Pair or Triple in a box    - if they are aligned on a row   , n can be removed from the rest of the row
	// A Pair or Triple in a box    - if they are aligned on a column, n can be removed from the rest of the column.

	// 1a. Find a digit with two or three occurances within the box.
	//    1b. Comopare the locations. Are they all on the same colum or row? If yes, we have a pointing pair/triple
	//       1c. Remove all occurances for this digit on that row/column
	Digit digits[9];
	bool bSuccess = false;

	for ( short shDigit = 0;shDigit < 9; ++shDigit)
	{
		if ( PRINT_DEBUG)
			std::cout << "   checking digit " << shDigit + 1 << std::endl;
		for ( int i = 0; i < 3; ++i )
		{

			for (int j = 0 ; j < 3; ++j ) {

				vector2d posDigit(posSquare.x + i, posSquare.y + j);

				if ( !m_oPossibleNumbers[posDigit.x][posDigit.y].bSolved && m_oPossibleNumbers[posDigit.x][posDigit.y].isPossible(shDigit) )
				{

					digits[shDigit].addPosition(posDigit);
					if ( PRINT_DEBUG)
						std::cout << "      added digit : " << shDigit +1  << " pos : " <<posDigit << " count : " << digits[shDigit].m_shCount << std::endl;
				}
			}
		}
		if ( PRINT_DEBUG)
			std::cout << "\n   all added for digit : " << shDigit +1  << std::endl;

		// Pointing pairs only works for 2 or 3 occuranses of digit in row.
		if ( digits[shDigit].m_shCount < 2 || digits[shDigit].m_shCount > 3)
		{
			if ( PRINT_DEBUG)
				std::cout << "      Too many / few occurances ( " << digits[shDigit].m_shCount << " ) , skipping to next...\n"
					<<"==================================================================\n\n";
			continue;
		}

		if ( PRINT_DEBUG)
			std::cout << "      " << digits[shDigit].m_shCount << " occurances\n";



		if ( digits[shDigit].IsAlignedOnRow() ) {
			if ( PRINT_DEBUG)
				std::cout << "   aligned on row!\n";



			bSuccess = true;
			short shPosY = digits[shDigit].m_vPositions[0].y;
			if ( ( shSquareID % 3 ) == 0 )
			{
				for ( int i = 3; i < 9; ++i ) {
					if ( PRINT_DEBUG)
						std::cout << "      removing digit : " << shDigit + 1 << " from : " << i << " , " << shPosY << std::endl;
					m_oPossibleNumbers[i][shPosY].remove(shDigit);
				}

			} else if ( ( shSquareID % 3 ) == 1 )
			{
				for ( int i = 0; i < 9; ++i ) {
					if ( i > 2 && i < 6)
						continue;
					if ( PRINT_DEBUG)
						std::cout << "      removing digit : " << shDigit + 1 << " from : " << i << " , " << shPosY << std::endl;
					m_oPossibleNumbers[i][shPosY].remove(shDigit);
				}

			} else
			{
				for ( int i = 0; i < 6; ++i ) {
					if ( PRINT_DEBUG)
						std::cout << "      removing digit : " << shDigit + 1 << " from : " << i << " , " << shPosY << std::endl;
					m_oPossibleNumbers[i][shPosY].remove(shDigit);
				}
			}


		}

		else  if ( digits[shDigit].IsAlignedOnColumn() )
		{
			if ( PRINT_DEBUG)
				std::cout << "      aligned on column!\n";


			bSuccess = true;
			short shPosX = digits[shDigit].m_vPositions[0].x;
			if ( ( shSquareID / 3 ) == 0 )
			{
				for ( int i = 3; i < 9; ++i ) {
					if ( PRINT_DEBUG)
						std::cout << "      removing digit left : " << shDigit + 1 << " from : " << shPosX << " , " << i << std::endl;
					m_oPossibleNumbers[shPosX][i].remove(shDigit);
				}

			} else if ( ( shSquareID / 3 ) == 1 )
			{
				for ( int i = 0; i < 9; ++i ) {
					if ( i > 2 && i < 6)
						continue;
					if ( PRINT_DEBUG)
						std::cout << "      removing digit middle : " << shDigit + 1 << " from : " << shPosX << " , " << i << std::endl;
					m_oPossibleNumbers[shPosX][i].remove(shDigit);
				}

			} else
			{
				for ( int i = 0; i < 6; ++i ) {
					if ( PRINT_DEBUG)
						std::cout << "      removing digit right : " << shDigit + 1 << " from : " << shPosX << " , " << i << std::endl;
					m_oPossibleNumbers[shPosX][i].remove(shDigit);
				}

			}


		}
		else if ( PRINT_DEBUG)
			std::cout << "      not aligned\n";

		if ( PRINT_DEBUG)
		{
			std::cout << "   ==================================================================\n\n";
			if ( FREEZE )
				std::cin.ignore();
		}
	}

	// Box line intersection ( if step 1 fails )
	// ==============================================================================================================
	// A Pair or Triple on a row    - if they are all in the same box, n can be removed from the rest of the box.
	// A Pair or Triple on a column - if they are all in the same box, n can be removed from the rest of the box.

	// 2a. Try to find a digit that's locked to this square either by column or row ( box line intersection )
	//    2b Remove all occurances of that digits that's not on the row/column in 2a
	return bSuccess;

}
void CBoard::removePosibilities_Column( const short shColumn, const short shExcept1, const short shExcept2, const short shDigit1, const short shDigit2) {
	if ( PRINT_DEBUG )
		std::cout << "Remove possibiliteis Column ( shColumn )\n";
	for ( int i = 0; i < 9; ++i)
	{
		if ( i != shExcept1 && i != shExcept2) {
			if ( PRINT_DEBUG )
				std::cout << shColumn << " , " << i << "\n   Removing : " << shDigit1 << "\n   Removing : " << shDigit2 << std::endl;
			m_oPossibleNumbers[shColumn][i].remove(shDigit1 - 1);
			m_oPossibleNumbers[shColumn][i].remove(shDigit2 - 1);
		}
	}
}

bool CBoard::checkForNakedPairs_SingleRow( const short shRow ){
	if ( PRINT_DEBUG )
		std::cout << "checkForHiddenDoubles_SingleRow " << shRow << std::endl;

	short shColumnIndex2 = 0;
	bool bFound = false;

	for ( short shColumnIndex1 = 0; shColumnIndex1 < 9; ++shColumnIndex1 )
	{
		shColumnIndex2 = shColumnIndex1 + 1;
		for ( ; shColumnIndex2 < 9; ++shColumnIndex2 )
		{
			Cell cell1 = m_oPossibleNumbers[shColumnIndex1][shRow];
			Cell cell2 = m_oPossibleNumbers[shColumnIndex2][shRow];

			if ( PRINT_DEBUG )
				std::cout   << "Compairing " << shColumnIndex1 << " , " << shRow << cell1 << std::endl
					<< "And        " << shColumnIndex2 << " , " << shRow << cell2 << std::endl;

			if ( cell1.isNakedPair(cell2) ) {
				bFound = true;
				if ( PRINT_DEBUG )
					std::cout << "...HiddenPair!" << shColumnIndex1 << " , " << shRow << " and " << shColumnIndex2 << " , " << shRow << std::endl;

				// Remove all other instance of the found numbers in this column
				// TODO : Make this into a function
				// ...removePosibilities_Column( const short shColum, const short shExcept1, const short shExcept2, const short shDigit1, const short shDigit2)
				// Where shExcept1 and shExcept1 are the columns that make up the matching pairs ( should not have shDigit1 and shDigit2 removed
				// TODO2 : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )
				for ( int i = 0; i < 9; ++i)
				{
					if ( i != shColumnIndex1 && i != shColumnIndex2) {
						if ( PRINT_DEBUG )
							std::cout << i << " , " << shRow << "\nRemoving : " << cell1.shHiddenDouble1 << "\nRemoving : " << cell1.shHiddenDouble2 << std::endl;
						m_oPossibleNumbers[i][shRow].remove(cell1.shHiddenDouble1 - 1);
						m_oPossibleNumbers[i][shRow].remove(cell1.shHiddenDouble2 - 1);

					}

				}
			}
		}
	}
	return bFound;
}

void CBoard::checkForNakedTriplets_SingleRow( const short shRow )
{
	if ( PRINT_DEBUG )
		std::cout << "CheckForakedTriplets_SingleRow" << shRow << std::endl;

	short shColumnIndex2 = 0;

	// Compare all cells with each other
	for ( short shColumnIndex1 = 0; shColumnIndex1 < 9; ++shColumnIndex1 )
	{
		shColumnIndex2 = shColumnIndex1 + 1;
		for ( ; shColumnIndex2 < 9; ++shColumnIndex2 )
		{
			// Find object for the two cells
			Cell cell1 = m_oPossibleNumbers[shColumnIndex1][shRow];
			Cell cell2 = m_oPossibleNumbers[shColumnIndex2][shRow];

			for ( short shColumnIndex3 = 0; shColumnIndex3 < 9; ++shColumnIndex3)
			{

				Cell cell3 = m_oPossibleNumbers[shColumnIndex3][shRow];

				 if ( PRINT_DEBUG )
					std::cout   << "Compairing " 
						<< shColumnIndex1 << " , " << shRow << cell1 
						<< std::endl
						
						<< "And        " 
						<< shColumnIndex2 << " , " << shRow << cell2 
						<< std::endl
					
						<< "And        " 
						<< shColumnIndex3 << " , " << shRow << cell2 
						<< std::endl;

				// Check if they are naked pairs
				if ( isNakedTriplets(cell1, cell2, cell3 ))
				{
					if ( PRINT_DEBUG )
						std::cout << "...NakedTriplets!" 
							<< shColumnIndex1 << " , " << shRow 
							<< " and " 
							<< shColumnIndex2 << " , " << shRow << std::endl
							<< " and " 
							<< shColumnIndex3 << " , " << shRow << std::endl;
					printAllPosibilities();
					// Remove all other instance of the found numbers in this column
					// TODO : Make this into a function
					// ...removePosibilities_Column( const short shColum, const short shExcept1, const short shExcept2, const short shDigit1, const short shDigit2)
					// Where shExcept1 and shExcept1 are the columns that make up the matching pairs ( should not have shDigit1 and shDigit2 removed
					// TODO2 : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )
					for ( int i = 0; i < 9; ++i)
					{
						if (       i != shColumnIndex1
							&& i != shColumnIndex2
							&& i != shColumnIndex3
						) 
						{
					}	
							short shPossible1 = cell1.shHiddenDouble1;
							short shPossible2 = cell1.shHiddenDouble2;
							short shPossible3 = cell1.shHiddenDouble3;

							if ( cell1.shHiddenDouble3 >= 0)
							{
								shPossible1 = cell1.shHiddenDouble1;
								shPossible2 = cell1.shHiddenDouble1;
								shPossible3 = cell1.shHiddenDouble3;
							} else if ( cell2.shHiddenDouble3 >= 0)
							{
								shPossible1 = cell2.shHiddenDouble1;
								shPossible2 = cell2.shHiddenDouble1;
								shPossible3 = cell2.shHiddenDouble3;
							} else if ( cell3.shHiddenDouble3 >= 0)
							{
								shPossible1 = cell3.shHiddenDouble1;
								shPossible2 = cell3.shHiddenDouble1;
								shPossible3 = cell3.shHiddenDouble3;
							}
							
							m_oPossibleNumbers[i][shRow].remove(shPossible1);
							m_oPossibleNumbers[i][shRow].remove(shPossible2);
							m_oPossibleNumbers[i][shRow].remove(shPossible3);

							if ( PRINT_DEBUG )
							{
								printAllPosibilities();
								std::cout << i << " , " << shRow
									<< "\nRemoving : " << shPossible1
									<< "\nRemoving : " << shPossible2
									<< "\nRemoving : " << shPossible3
									<< std::endl;
								//std::cin.ignore();

							}
					}
				}
			}
		}
	}
}

bool CBoard::findHiddenPairColumn( const short shColumn )
{
	if ( PRINT_DEBUG )
		std::cout << "findHiddenPairColum: " << shColumn << std::endl;

	short shDigit2 = 0; 

	for ( short shDigit1 = 1; shDigit1 < 10; ++shDigit1)
	{
		if ( isDigitPlacedInColumn( shColumn, shDigit1 ))
		{
			if ( PRINT_DEBUG )
				std::cout << shDigit1 << " is allready placed in this row\n";
			continue;
		}

		shDigit2 = shDigit1 + 1;

		for ( ; shDigit2 < 10; ++shDigit2 )
		{

			if ( PRINT_DEBUG )
				std::cout << "Digit pair : " << shDigit1 << " , " << shDigit2 << std::endl;

			if ( isDigitPlacedInColumn( shColumn, shDigit1 ))
			{
				if ( PRINT_DEBUG )
					std::cout << shDigit2 << " is allready placed in this row\n";
				continue;
			}

			vector2d pos1;
			vector2d pos2;
			short shCountPairs = 0;

			// If the neither shDigit1 or shDigit2 has been palced in this row, check all positions. 
			for ( short shRowIndex = 0;shRowIndex  < 9; shRowIndex++)
			{
				short shCount = m_oPossibleNumbers[shColumn][shRowIndex].countPossibleOfPair( shDigit1 - 1, shDigit2 - 1 );

				if ( PRINT_DEBUG )
					std::cout << "\tCount of digit pair ( " << shDigit1 << " , " << shDigit2 << " ) in " << shColumn << " , " << shRowIndex << " count = " << shCount << std::endl;

				if ( shCount == 2)
				{
					++shCountPairs;

					if ( shCountPairs == 1 )
						pos1 = vector2d( shColumn, shRowIndex );
					else
						pos2 = vector2d( shColumn, shRowIndex );

				} else if ( shCount == 1 ){
					shCountPairs = 0;
					break;
				}
			}
			if ( shCountPairs == 2 ) 
			{
				if ( PRINT_DEBUG )
					std::cout << "Pair found\n"
						<< "\tPos 1   : " << pos1 << std::endl
						<< "\tPos 2   : " << pos2 << std::endl
						<< "\tDigit 1 : " << shDigit1 << std::endl
						<< "\tDigit 2 : " << shDigit2 << std::endl;

				// Remove all digits except thoose that make up the hidden pair
				m_oPossibleNumbers[pos1.x][pos1.y].removeAllExceptPair( shDigit1, shDigit2 );
				m_oPossibleNumbers[pos2.x][pos2.y].removeAllExceptPair( shDigit1, shDigit2 );
			}
		}
	}
	return true;
}

bool CBoard::findHiddenPairRow( const short shRow )
{
	if ( PRINT_DEBUG )
		std::cout << "findHiddenPairRo: " << shRow << std::endl;

	short shDigit2 = 0; 
	bool bSuccess = false;

	for ( short shDigit1 = 1; shDigit1 < 10; ++shDigit1)
	{
		if ( isDigitPlacedInRow(shRow, shDigit1 ) )
		{
			if ( PRINT_DEBUG )
				std::cout << shDigit1 << " is allready placed in this row\n";
			continue;
		}

		shDigit2 = shDigit1 + 1;

		for ( ; shDigit2 < 10; ++shDigit2 )
		{

			if ( PRINT_DEBUG )
				std::cout << "Digit pair : " << shDigit1 << " , " << shDigit2 << std::endl;

			if ( isDigitPlacedInRow( shRow, shDigit2 ))
			{
				if ( PRINT_DEBUG )
					std::cout << shDigit2 << " is allready placed in this row\n";
				continue;
			}

			vector2d pos1;
			vector2d pos2;
			short shCountPairs = 0;

			// If the neither shDigit1 or shDigit2 has been palced in this row, check all positions. 
			for ( short shColumnIndex = 0; shColumnIndex < 9; ++shColumnIndex)
			{
				short shCount = m_oPossibleNumbers[shColumnIndex][shRow].countPossibleOfPair( shDigit1 - 1, shDigit2 - 1 );

				if ( PRINT_DEBUG )
					std::cout << "\tCount of digit pair ( " << shDigit1 << " , " << shDigit2 << " ) in " << shColumnIndex << " , " << shRow << " count = " << shCount << std::endl; 

				if ( shCount == 2)
				{
					++shCountPairs;

					if ( shCountPairs == 1 )
						pos1 = vector2d(shColumnIndex, shRow );
					else
						pos2 = vector2d(shColumnIndex, shRow );

				} else if ( shCount == 1 ){
					shCountPairs = 0;
					break;
				}
			}
			if ( shCountPairs == 2 ) 
			{
				if ( PRINT_DEBUG )
					std::cout << "Pair found\n"
						<< "\tPos 1   : " << pos1 << std::endl
						<< "\tPos 2   : " << pos2 << std::endl
						<< "\tDigit 1 : " << shDigit1 << std::endl
						<< "\tDigit 2 : " << shDigit2 << std::endl;

				// Remove all digits except thoose that make up the hidden pair
				m_oPossibleNumbers[pos1.x][pos1.y].removeAllExceptPair( shDigit1, shDigit2 );
				m_oPossibleNumbers[pos2.x][pos2.y].removeAllExceptPair( shDigit1, shDigit2 );

				bSuccess = true; 
			}
		}
	}
	return bSuccess;
}

bool CBoard::checkForHiddenPairs_SingleRow( const short shRow )
{
	if ( PRINT_DEBUG )
		std::cout << "checkForHiddenPairs_SingleRow " << shRow << std::endl;

	// Algorith first finds all digits that occur in two places in this column in a PositionPair
	// Then it compares all PositionPairs and looks for two position pairs where two digit pairs occurs in the same positions

	// A pair is any digit that occurs exactly twice in this column.

	// If pair 1 is located in x1, y1 and pair 2 in x2, y2
	// Then this methed will look for instances where x1 == x2 and y1 == y2

	short shPairCount = 0;
	std::vector<PositionPair> vPositionPair;

	// 1. Go through all possible digits
	for ( short shDigit1 = 0; shDigit1 < 9; ++shDigit1)
	{
		if ( isDigitPlacedInRow(shRow, shDigit1 + 1))
			continue;

		// This struct holds a pair ( two positions + a digit )
		PositionPair pair;

		// 2. See if this digit exists in any of the cells in this column
		for ( short shColumnIndex = 0; shColumnIndex < 9; ++shColumnIndex)
		{
			//if ( PRINT_DEBUG )
				//std::cout << "comparing : " << shColumn << " , " << shRow << " and : " << shColumnIndex << " , " << shRow << std::endl;
			// 3. If it add it to the temp Pair struct
			if ( m_oPossibleNumbers[shColumnIndex][shRow].isPossible(shDigit1) )
			{
				++shPairCount;

				if ( shPairCount == 1 )
				{

					// This is the first occurance of this digit, add it to the struct along with the digit found.
					pair.shDigit1 = shDigit1;
					pair.m_oPairPos1 = vector2d( shColumnIndex, shRow);
				}else if ( shPairCount == 2 )
				{
					// This is the second occurance of the digit, add it to the struct
					pair.m_oPairPos2 = vector2d( shColumnIndex, shRow);
				}

			}

		}
		// If we found to occurances of the pair, at the pair struct to the list of pairs
		if ( shPairCount == 2 )
		{
			vPositionPair.push_back(pair);
		}

		shPairCount = 0;


	}

	short shSize = vPositionPair.size();
	short j = 0;
	bool bMatchFound = false;

	// 4. Loop through all pairs and compare them all.
	for ( short i = 0; i < shSize; ++i)
	{
		PositionPair currentPair = vPositionPair.at(i);
		j = i + 1;

		for (; j < shSize; ++j)
		{
			PositionPair secondPair = vPositionPair.at(j);

			// A match was found, this means that there are two numbers tha only occurs in the same two locations.
			// Meaning we have a double pair ( hidden or naked doubles )
			if ( secondPair == currentPair)
			{
				if ( PRINT_DEBUG )
					std::cout << "=====MATCH FOUND=====\n" << secondPair << std::endl << currentPair << std::endl;

				bMatchFound = true;

				// Remove digits affected by hidden pair
				for ( short shDigit  = 0; shDigit < 9; ++shDigit )
				{
					if ( shDigit == currentPair.shDigit1 || shDigit == secondPair.shDigit1)
						continue;

					if ( PRINT_DEBUG )
					{
						std::cout << "removing digit : " << shDigit << std::endl;
						std::cout << "pos 1 : " << currentPair.m_oPairPos1 << std::endl;
						std::cout << "pos 2 : " << currentPair.m_oPairPos2 << std::endl;
					}

					// Since these two numbers only occures in these two positions, we can erase every other digit from these positions.
					m_oPossibleNumbers[currentPair.m_oPairPos1.x][currentPair.m_oPairPos1.y].remove(shDigit);
					m_oPossibleNumbers[currentPair.m_oPairPos2.x][currentPair.m_oPairPos2.y].remove(shDigit);


				}

			}
		}
	}

	return bMatchFound;

}

bool CBoard::findUniqueInRow(const short shRow)
{
	if ( PRINT_DEBUG )
		std::cout << "findUniqueInRow : " << shRow << std::endl;
	bool bUniqueFound = false;

	for ( short shDigit = 0; shDigit < 9; ++shDigit )
	{
		short shCounter = 0;
		short shPrevFoundColumn = 0;

		for ( short shColumnIndex = 0; shColumnIndex < 9; ++shColumnIndex )
		{
			if ( !m_oPossibleNumbers[shColumnIndex][shRow].bSolved && m_oPossibleNumbers[shColumnIndex][shRow].isPossible(shDigit) )
			{
				shCounter++;
				shPrevFoundColumn = shColumnIndex;
			}
		}
		if ( PRINT_DEBUG )
			std::cout << "   Counter for : " << shDigit + 1  << " : " << shCounter <<std::endl;

		if ( shCounter == 1)
		{

			if ( PRINT_DEBUG )
			{
				std::cout << "      " << shDigit + 1 << " is unique in " << shPrevFoundColumn << " , " << shRow << std::endl;
				printAllPosibilities();
			}
			bUniqueFound = true;

			// Insert found digit
			insert( vector2d(shPrevFoundColumn, shRow), shDigit + 1, true);
		}

	}
	return bUniqueFound;
}
bool CBoard::checkForNakedPairs_SingleColumn( const short shColumn){
	if ( PRINT_DEBUG )
		std::cout << "checkForHiddenDoubles_SingleColumn " << shColumn << std::endl;

	short shRowIndex2 = 0;
	bool bFound = true;

	for ( short shRowIndex1 = 0; shRowIndex1 < 9; ++shRowIndex1 )
	{
		shRowIndex2 = shRowIndex1 + 1;

		for ( ; shRowIndex2 < 9; ++shRowIndex2 )
		{
			Cell cell1 = m_oPossibleNumbers[shColumn][shRowIndex1];
			Cell cell2 = m_oPossibleNumbers[shColumn][shRowIndex2];

			if ( PRINT_DEBUG )
				std::cout   << "Compairing " << shColumn << " , " << shRowIndex1 << cell1 << std::endl
					<< "And        " << shColumn << " , " << shRowIndex2 << cell2 << std::endl;

			if ( cell1.isNakedPair(cell2) )
			{
				if ( PRINT_DEBUG )
					std::cout << "...HiddenPair!" << shColumn << " , " << shRowIndex1 << " and " << shColumn << " , " << shRowIndex2
						<< " : " << cell1.shHiddenDouble1 << " & " << cell1.shHiddenDouble2 << std::endl;

				// Remove all other instance of the found numbers in this column
				// TODO : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )
				removePosibilities_Column( shColumn, shRowIndex1, shRowIndex2, cell1.shHiddenDouble1, cell1.shHiddenDouble2);
				bFound = true;
			} else
				if ( PRINT_DEBUG )
				{
					std::cout << "...Not HiddenPair!\n";
					std::cout << "=============================================\n";
				}
		}
	}
	return bFound;
}
bool CBoard::checkForNakedTriplets_SingleColumn( short shColumn )
{
	if ( PRINT_DEBUG )
		std::cout << "CheckForNakedTriplets_SingleColumn" << shColumn << std::endl;

	short shRowIndex2 = 0;
	//short shRowIndex3 = 0;
	bool bSolved = false; 

	// Compare all cells with each other
	for ( short shRowIndex1 = 0; shRowIndex1 < 9; ++shRowIndex1 )
	{
		shRowIndex2 = shRowIndex1 + 1;
		for ( ;shRowIndex2 < 9; ++shRowIndex2 )
		{
			// Find object for the two cells
			Cell cell1 = m_oPossibleNumbers[shColumn][shRowIndex1];
			Cell cell2 = m_oPossibleNumbers[shColumn][shRowIndex2];
			
			//shRowIndex3 = shRowIndex2 + 1;

			for (short shRowIndex3 = 0 ; shRowIndex3 < 9; ++shRowIndex3 )
			{
				if ( shRowIndex3 == shRowIndex1 || shRowIndex3 == shRowIndex2 )
					continue;

				Cell cell3 = m_oPossibleNumbers[shColumn][shRowIndex3];

				 if ( PRINT_DEBUG )
					std::cout << std::endl
						<< "=========================== Checking column " << shColumn <<  " ==========================================\n"
						<< "Compairing : " << shRowIndex1 << " , " << shRowIndex2 << " , " << shRowIndex3 << std::endl
						<< "Celll 1 ( " << shRowIndex1 << " ) : " << cell1 << std::endl
						<< "Celll 2 ( " << shRowIndex2 << " ) : " << cell2 << std::endl
						<< "Celll 3 ( " << shRowIndex3 << " ) : " << cell3 << std::endl
						<< "=====================================================================\n";
				// Check if they are naked pairs
				if ( isNakedTriplets(cell1, cell2, cell3 ))
				{
					if ( PRINT_DEBUG )	
                    {
                        std::cout << "Cell 1 : " << cell1 << std::endl
                            << "Cell 2 : " << cell2 << std::endl
                            << "Cell 3 : " << cell3 << std::endl;

						std::cout 
							<< "...HiddenPair!" << shColumn << " , " << shRowIndex1 << std::endl
							<< " and          " << shColumn << " , " << shRowIndex2 << std::endl
							<< " and          " << shColumn << " , " << shRowIndex3 << std::endl;

                        if ( PRINT_BOARD )
                            printAllPosibilities();
                    }
					// Remove all other instance of the found numbers in this column
					// TODO : Make this into a function
					// ...removePosibilities_Column( const short shColum, const short shExcept1, const short shExcept2, const short shDigit1, const short shDigit2)
					// Where shExcept1 and shExcept1 are the columns that make up the matching pairs ( should not have shDigit1 and shDigit2 removed
					// TODO2 : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )
					for ( int i = 0; i < 9; ++i)
					{
						if ( 
							   i != shRowIndex1 
							&& i != shRowIndex2 
							&& i != shRowIndex3 )
						{
							short shPossible1 = cell1.shHiddenDouble1;
							short shPossible2 = cell1.shHiddenDouble2;
							short shPossible3 = cell1.shHiddenDouble3;
							
							if ( cell1.shHiddenDouble3 >= 0 )
							{
								shPossible1 = cell1.shHiddenDouble1;
								shPossible2 = cell1.shHiddenDouble2;
								shPossible3 = cell1.shHiddenDouble3;
							} else if ( cell2.shHiddenDouble3 >= 0 )
							{
								shPossible1 = cell2.shHiddenDouble1;
								shPossible2 = cell2.shHiddenDouble2;
								shPossible3 = cell2.shHiddenDouble3;
							} else if ( cell3.shHiddenDouble3 >= 0 )
							{
								shPossible1 = cell3.shHiddenDouble1;
								shPossible2 = cell3.shHiddenDouble2;
								shPossible3 = cell3.shHiddenDouble3;
							}
							if ( PRINT_DEBUG )
                            {
								std::cout <<  shColumn << " , " << i
									<< "\nRemoving : " << shPossible1 + 1
									<< "\nRemoving : " << shPossible2 + 1
									<< "\nRemoving : " << shPossible3 + 1 << std::endl;
                            }
							m_oPossibleNumbers[shColumn][i].remove(shPossible1);
							m_oPossibleNumbers[shColumn][i].remove(shPossible2);
							m_oPossibleNumbers[shColumn][i].remove(shPossible3);
						}

					}
					bSolved = true;
                    if ( PRINT_BOARD )
                        printAllPosibilities();

                    if ( FREEZE )
                        std::cin.ignore();
				}
			}
		}
	}
	return bSolved;
}
bool CBoard::checkForHiddenPairs_SingleColumn(const short shColumn )
{

	// Algorith first finds all digits that occur in two places in this column in a PositionPair
	// Then it compares all PositionPairs and looks for two position pairs where two digit pairs occurs in the same positions

	// A pair is any digit that occurs exactly twice in this column.

	// If pair 1 is located in x1, y1 and pair 2 in x2, y2
	// Then this methed will look for instances where x1 == x2 and y1 == y2
	if ( PRINT_DEBUG )
		std::cout << "checkForHiddenPairs_SingleColumn : " << shColumn << std::endl;

	short shPairCount = 0;
	std::vector<PositionPair> vPositionPair;

	// 1. Go through all possible digits
	for ( short shDigit1 = 0; shDigit1 < 9; ++shDigit1)
	{
		if ( isDigitPlacedInColumn(shColumn, shDigit1 + 1))
			continue;
		// This struct holds a pair ( two positions + a digit )
		PositionPair pair;

		// 2. See if this digit exists in any of the cells in this column
		for ( short shRowIndex = 0; shRowIndex < 9; ++shRowIndex)
		{

			// 3. If it deos, add it to the temp Pair struct
			if ( m_oPossibleNumbers[shColumn][shRowIndex].isPossible(shDigit1) )
			{
				++shPairCount;

				if ( shPairCount == 1 )
				{
					// This is the first occurance of this digit, add it to the struct along with the digit found.
					pair.shDigit1 = shDigit1;
					pair.m_oPairPos1 = vector2d( shColumn, shRowIndex);
				}else if ( shPairCount == 2 )
				{
					// This is the second occurance of the digit, add it to the struct
					pair.m_oPairPos2 = vector2d( shColumn, shRowIndex);
				}

			}

		}
		// If we found to occurances of the pair, at the pair struct to the list of pairs
		if ( shPairCount == 2 )
		{
			vPositionPair.push_back(pair);
		}
		shPairCount = 0;


	}


	bool bMatchFound = false;
	short shSize = vPositionPair.size();
	short j = 0;

	// 4. Loop through all pairs and compare them all.
	for ( short i = 0; i < shSize; ++i)
	{
		PositionPair currentPair = vPositionPair.at(i);
		j = i + 1;

		for (; j < shSize; ++j)
		{
			PositionPair secondPair = vPositionPair.at(j);

			// A match was found, this means that there are two numbers tha only occurs in the same two locations.
			// Meaning we have a double pair ( hidden or naked doubles )
			if ( secondPair == currentPair)
			{

				if ( PRINT_DEBUG )
					std::cout << "=====MATCH FOUND=====\n" << secondPair << std::endl << currentPair << std::endl;
				bMatchFound = true;
				for ( short shDigit  = 0; shDigit < 9; ++shDigit )
				{
					if ( shDigit == currentPair.shDigit1 || shDigit == secondPair.shDigit1)
						continue;


					if ( PRINT_DEBUG )
					{
						std::cout << "removing digit : " << shDigit << std::endl;
						std::cout << "pos 1 : " << currentPair.m_oPairPos1 << std::endl;
						std::cout << "pos 2 : " << currentPair.m_oPairPos2 << std::endl;
					}

					// Since these two numbers only occures in these two positions, we can erase every other digit from these positions.
					m_oPossibleNumbers[currentPair.m_oPairPos1.x][currentPair.m_oPairPos1.y].remove(shDigit);
					m_oPossibleNumbers[currentPair.m_oPairPos2.x][currentPair.m_oPairPos2.y].remove(shDigit);


				}

			}
		}
	}
	return bMatchFound;
	/*
	   clock_gettime(CLOCK_REALTIME, &ts_end);

	   unsigned long iTimeStart = ts_start.tv_sec * 1000000000 + ts_start.tv_nsec;

	// End
	unsigned long iTimeStop = ts_end.tv_sec * 1000000000 + ts_end.tv_nsec;
	int iDeltaEnd = iTimeStop - iTimeStart;

	// Loop 1
	iTimeStop = ts_loop1.tv_sec * 1000000000 + ts_loop1.tv_nsec;
	int iDeltaLoop1 = iTimeStop - iTimeStart;
	std::cout << "===============================checkForHiddenPairs_SingleColumn===============================\n"
	<< "  delta loop 1   : " << static_cast<double> (iDeltaLoop1 / 1000.0f) << " µs\n"
	<< "  delta time_end : " << static_cast<double> (iDeltaEnd / 1000.0f) << " µs\n"
	<< "==============================================================================================\n";
	*/



}
bool CBoard::findUniqueInColumn( const short shColumn )
{
	if ( PRINT_DEBUG )
		std::cout << "findUniqueInColumn : " << shColumn << std::endl;



	bool bUniqueFound = false;

	for ( short shDigit = 0; shDigit < 9; ++shDigit )
	{

		short shCounter = 0;
		short shPrevFoundRow = 0;

		for ( short shRowIndex = 0; shRowIndex < 9; ++shRowIndex )
		{
			if ( !m_oPossibleNumbers[shColumn][shRowIndex].bSolved && m_oPossibleNumbers[shColumn][shRowIndex].isPossible(shDigit) )
			{
				shCounter++;
				shPrevFoundRow = shRowIndex;
			}
		}
		if ( PRINT_DEBUG )
			std::cout << "   Counter for : " << shDigit + 1  << " : " << shCounter <<std::endl;

		if ( shCounter == 1)
		{
			if ( PRINT_DEBUG ){
			
				std::cout << "      " << shDigit + 1 << " is unique in " << shColumn << " , " << shPrevFoundRow << std::endl;
				printAllPosibilities( );
			}


			bUniqueFound = true;

			// Insert found digit
			insert( vector2d(shColumn, shPrevFoundRow), shDigit + 1, true);
		}

	}

	return bUniqueFound;

}
bool CBoard::solvePossibilities()
{

	if (PRINT_DEBUG )
		std::cout << "solvePossibilities\n";

	bool bSolved = false;

	for (unsigned int i = 0; i < m_vUnsolvedPositions.size(); ++i)
	{

		vector2d pos = m_vUnsolvedPositions.at(i);

		// if ( m_oPossibleNumbers[ pos.x ][pos.y].bSolved )continue;

		short shSolvedDigit = m_oPossibleNumbers[ pos.x ][pos.y].solve();

		if ( shSolvedDigit ) {
			if ( PRINT_DEBUG )
				std::cout << "   solved : " << shSolvedDigit << " pos : " << pos << std::endl;

			insert( pos, shSolvedDigit, true);

			bSolved = true;
		}
	}
	return bSolved;
}
bool CBoard::findUniqueInSquare( const short shSquare )
{
    if ( PRINT_INFO )
		std::cout << "findUniqueInSquare : " << shSquare << std::endl;


	vector2d posOrigo;

	switch ( shSquare) {
		case 0:
			posOrigo.x = 0;
			posOrigo.y = 0;
			break;
		case 1:
			posOrigo.x = 3;
			posOrigo.y = 0;
			break;
		case 2:
			posOrigo.x = 6;
			posOrigo.y = 0;
			break;
		case 3:
			posOrigo.x = 0;
			posOrigo.y = 1;
			break;
		case 4:
			posOrigo.x = 3;
			posOrigo.y = 3;
			break;
		case 5:
			posOrigo.x = 6;
			posOrigo.y = 3;
			break;
		case 6:
			posOrigo.x = 0;
			posOrigo.y = 6;
			break;
		case 7:
			posOrigo.x = 3;
			posOrigo.y = 6;
			break;
		case 8:
			posOrigo.x = 6;
			posOrigo.y = 6;
			break;
		default:
			break;
	}

	short shCounter = 0;
	short shPrevFoundSquare = 0;
	bool bFound = false;

	for ( short shDigit = 0; shDigit <9; ++shDigit)
	{
		bool bIsSolved = false;

		for ( short shSquareIndex = 0; shSquareIndex < 9 ; ++shSquareIndex )
		{
            if ( PRINT_DEBUG )
                std::cout << "checking " << posOrigo.x + shSquareIndex % 3 << " , " << posOrigo.y + shSquareIndex / 3 << std::endl;
			
			if ( m_oPossibleNumbers[posOrigo.x + shSquareIndex % 3 ][posOrigo.y + shSquareIndex / 3 ].bSolved )
			{
				bIsSolved = true;
				break;
			}

			if ( m_oPossibleNumbers[posOrigo.x + shSquareIndex % 3 ][posOrigo.y + shSquareIndex / 3 ].isPossible(shDigit))
			{
				shCounter++;
				shPrevFoundSquare = shSquareIndex;
			}

			if ( PRINT_DEBUG )
				std::cout << "   Counter for : " << shDigit + 1  << " : " << shCounter <<std::endl;

		}
		if ( bIsSolved )
		{
            if ( PRINT_DEBUG )
                std::cout << "   Digit : " << shDigit << " is allready placed in this square!\n";
			continue;
		}
		if ( shCounter == 1)
		{
			if ( true || PRINT_DEBUG ){
			
				std::cout << "      " << shDigit + 1 << " is unique in " << posOrigo.x + shPrevFoundSquare % 3 << " , " <<  posOrigo.y + shPrevFoundSquare / 3 << std::endl;
				printAllPosibilities( );
				std::cin.ignore();
			}


			bFound  = true;

			// Insert found digit
			insert( vector2d(posOrigo.x + shPrevFoundSquare % 3, posOrigo.y + shPrevFoundSquare / 3 ), shDigit + 1, true);
		}
	}
	
	return bFound;

}
void CBoard::printAllPosibilities(){
	std::cout << "Printing all positions\n";

	int iColumn = 0;
	int iRow = 0;
	for ( iRow = 0; iRow < 9; ++iRow ) {
		for ( iColumn = 0; iColumn < 9; ++ iColumn) {
			if ( !m_oPossibleNumbers[iColumn][iRow].bSolved ){
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
			if ( !m_oPossibleNumbers[iColumn][iRow].bSolved ){
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
			if ( !m_oPossibleNumbers[iColumn][iRow].bSolved ){
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

void CBoard::printBoard( ){
	printBoard( vector2d(-1,-1), vector2d(-1,-1));
}

void CBoard::printBoard( const short shColumn, const short shRow ){
	printBoard( vector2d(shColumn,shRow), vector2d(-1,-1));
}

void CBoard::printBoard( const vector2d &pair1, const vector2d &pair2){
	std::cout << "   =====================BOARD STATUS====================\n";
	short j = 0;
	for ( short i = 0; i < 9; ++i ){
		std::cout << "   || ";
		for ( ; j < 9; j++) {
			if ( j == 3 || j == 6)
				std::cout << "     ";
			// else if ( j == 8)
			//   std::cout << "||";

			if ( ( j == pair1.x && i == pair1.y ) || ( j == pair2.x && i == pair2.y ) )
				std::cout << " |" << getValue( j, i) << "|";
			else
				std::cout << "  " << getValue( j, i) << " ";
		}

		j = 0;

		if ( i == 2 || i == 5 )
			std::cout << "  ||\n\n\n";
		else
			std::cout << "  ||\n\n";
	}
	std::cout << "   =====================================================\n";


}

void CBoard::printProgress() {

	std::cout << "\n======================================\n";

	for ( int i = 0; i < 9; i ++)
		std::cout << "Column    : " << i << " | " << getProgressColumn(i) << " / 9 filled out!\n";

	for ( int i = 0; i < 9; i ++)
		std::cout << "Row       : " << i << " | " << getProgressRow(i) << " / 9 filled out!\n";

	for ( int i = 0; i < 9; i ++) {
		std::cout << "Square    : " << i << " | " << getProgressSquare(i % 3, i / 3) << " / 9 filled out!\n";
	}

	for ( int i = 1; i < 10; i ++) {
		std::cout << "Digit    : " << i << " | " << getProgressDigit(i) << " / 9 filled out!\n";
	}

	std::cout << "Total progress : " << getTotatlProgress() << std::endl;
	std::cout << "======================================\n";
}

short CBoard::getProgressRow(short shRow)
{
	short shNumbersFilledIn = 0;

	for ( short i = 0; i < 9; ++i ) {

		if ( m_shBoard[i][shRow] != 0)
			shNumbersFilledIn++;
	}

	return shNumbersFilledIn;
}

short CBoard::getProgressColumn(short shColumn)
{
	short shNumbersFilledIn = 0;

	for ( short i = 0; i < 9; ++i ) {

		if ( m_shBoard[shColumn][i] != 0)
			shNumbersFilledIn++;
	}

	return shNumbersFilledIn;
}

short CBoard::getProgressSquare(const short shColumn,const short shRow)
{

	short shNumbersFilledIn = 0;
	short j = 0;

	for ( short i = 0; i < 3; ++i ) {
		for ( ; j < 3; j++ ) {

			if ( m_shBoard[ shColumn * 3 + i][shRow * 3 + j] != 0)
				shNumbersFilledIn++;
		}

		j = 0;
	}

	return shNumbersFilledIn;
}

short CBoard::getProgressDigit(short shDigit ){
	short shNumbersFilledIn = 0;
	short j = 0;

	for ( short i = 0; i < 9; ++i ) {
		for ( ; j < 9; j++ ) {

			if ( m_shBoard[ i ][ j ] == shDigit)
				shNumbersFilledIn++;
		}

		j = 0;
	}

	return shNumbersFilledIn;
}

short CBoard::getTotatlProgress(){
	short shNumbersFilledIn = 0;

	for ( int i = 0; i < 9; ++i)
		shNumbersFilledIn += getProgressRow(i);

	return shNumbersFilledIn;
}


bool CBoard::isDigitPlacedInRow( short shRow, short shDigit ) {

	for ( short i = 0; i < 9; ++i ) {

		if ( m_shBoard[i][shRow] == shDigit)
			return true;
	}

	return false;
}

bool CBoard::isDigitPlacedInColumn( short shColumn, short shDigit )
{

	for ( short i = 0; i < 9; ++i ) {

		if ( m_shBoard[shColumn][i] == shDigit)
			return true;
	}

	return false;
}


bool CBoard::isDigitPlacedInSquare(short shColumn,short shRow, short shDigit)
{
	short j = 0;

	for ( short i = 0; i < 3; ++i ) {
		for ( ; j < 3; j++ ) {

			if ( m_shBoard[ shColumn * 3 + i][shRow * 3 + j] == shDigit)
				return true;
		}

		j = 0;
	}

	return false;
}

void  CBoard::solveLoop()
{

    for (int i = 0; i < 9; ++i )
    {

        /*
        if ( solveRow( i ) || solveColumn(i ) || solveSquare( i ) )
        {
            bContinue = true;

        }*/


        if ( checkForNakedPairs_SingleSquare(i) )
        {
            findUniqueInSquare( i );
        }

        if ( checkForNakedPairs_SingleRow(i) )
        {
            findUniqueInRow( i );
        }

        if ( checkForNakedPairs_SingleColumn(i) )
        {
            findUniqueInColumn( i );
        }

        if ( checkForNakedTriplets_SingleColumn( i ) )
        {
            findUniqueInColumn( i );
        }
        if ( checkForXWing_Rows(1, 5))
        {

            findUniqueInColumn( 1 );
            findUniqueInColumn( 7 );
        }


    }


    for (int i = 0; i < 9; ++i )
    {
        if ( findHiddenPairColumn(i) )
        {
            if ( findUniqueInColumn(i) )
            {
                //bContinue = true;
                break;
            }
        }

        if ( findHiddenPairRow(i) )
        {

            if ( findUniqueInRow(i) )
            {
                //bContinue = true;
                break;
            }
        }
    }

  solvePossibilities();




    for (int i = 0; i < 9; ++i )
    {

        if ( checkForPointingPairs(i) )
        {
            findUniqueInRow(i);
            findUniqueInColumn(i);

            /*
            if ( findUniqueInRow(i) )
                bContinue = true;

            if ( findUniqueInColumn(i) )
                bContinue = true;
*/
        }
    }

    XWingHelper_Row();
}


int CBoard::solveEverythingRepeat()
{
	timespec ts_start;
	timespec ts_stop;
	unsigned long iTimeStart = 0;
    //bool bContinue = true;
	std::cout << "Trying to solve every position..." << std::endl;
	short shTries = 0;

	clock_gettime(CLOCK_REALTIME, &ts_start);

    while ( /*bContinue &&*/ m_iUnsolvedPosCount && shTries < 100)
	{
        solveLoop();
        ++shTries;
	}

	clock_gettime(CLOCK_REALTIME, &ts_stop);
	
	//checkForNakedTriplets_SingleColumn( 2 );

	iTimeStart = ts_start.tv_sec * 1000000000 + ts_start.tv_nsec;

	if ( PRINT_TIME ) 
	{
		unsigned long iTimeStop = ts_stop.tv_sec * 1000000000 + ts_stop.tv_nsec;
		int iDelta = iTimeStop - iTimeStart;

        std::cout << "===============================Solving done ===============================\n"
			<< "  status     : "    << getTotatlProgress() << " of  " <<  ( 9 * 9) << " solved = " << m_iUnsolvedPosCount << " unsolved\n"
            << "  used       : "    << shTries << " iterations\n"
            << "  delta time : "    << static_cast<double> (iDelta / 1000000.0f)    << " ms"
			<< " = "                << static_cast<double> (iDelta / 1000.0f)       << " µs"
			<< " = "                << iDelta                                       << " ns\n"
			<< "==========================================================================\n";
	}
	if ( m_iUnsolvedPosCount == 0 )
		printBoard();
	else
		printAllPosibilities();

	return true;
}

bool CBoard::lockPosition( const vector2d &pos ) 
{
	if ( PRINT_DEBUG )
		std::cout << "_Locking column " << pos.x << " , " << pos.y << std::endl;

	if ( !validateEverything())
	{
        std::cin.ignore();
        std::cout << "Can't lock, board is not valid\n";
		return false;
	}

	m_bLookedPositions[pos.x][pos.y] = true;
	return true;
}


bool CBoard::solveRow( const short shRow ) {

	// Check if only one digit is missing for this row
	int iProgress = m_iProgressRows[shRow];

	// Allready solved
	if ( iProgress == 9 )
	{
		return false;
	}

	if ( PRINT_INFO )
	{
		std::cout << "  Trying to solve row " << shRow << std::endl;
	}


	if ( !SPEED_ONLY )
	{
		// Check that row conatins no errors
		if ( !validateRow(shRow))
		{
			if ( PRINT_DEBUG )
				std::cout << "  Could not complete row " << shRow << ", row is invalid!\n";
			return false;
		}
	}

	if ( iProgress == 8 ) {
		if ( solveRow_SingleDigit(shRow) )
		{
			if ( PRINT_INFO )
			{
				std::cout << "Success! (row_single digit solve) Line : " << __LINE__ << std::endl;
				std::cout << "================================================================================\n";
			}
			return true;
		}
	}
	else
	{
		if ( solveRow_Advanced(shRow) )
		{
			if ( PRINT_INFO )
			{
				std::cout << "Success! (row_advanced solve) Line : " << __LINE__ << std::endl;
				std::cout << "================================================================================\n";
			}

			return true;
		}
	}

	if ( PRINT_DEBUG ) 
		std::cout << "  Could not complete row " << shRow << "!\n";
	return false;


}

bool CBoard::solveRow_SingleDigit( short shRow ){
	// Store all inserted digits for this row in a bool array
	bool bDigitValid[9] = {
		false, false, false,
		false, false, false,
		false, false, false
	};

	short shMissingDigitPos = -1;


	for ( short i = 0; i < 9; ++i ) {

		short digit = m_shBoard[i][shRow];

		if ( digit > 0 ) {
			bDigitValid[ digit - 1] = true;
		} else
			shMissingDigitPos = i;
	}

	// Find the one element in the bool array that is set to false ( the digit that hasn't been used )
	// Insert it into the row and validate the row to make sure everything is valid.
	for ( int i = 0; i < 9; ++i )
	{
		if ( bDigitValid[i] != true)
		{

			insert( vector2d(shMissingDigitPos, shRow), i + 1 );
			if ( !SPEED_ONLY )
				if ( validateRow(0) )
				{
					if ( PRINT_DEBUG )
						std::cout << "  Row solved!\n";
					if ( PRINT_BOARD )
						printBoard();
					return true;
				}

		}
	}

	return false;

}

bool CBoard::solveRow_Advanced ( const short shRow){

	std::vector<vector2d> vEmptyPositions;
	vector2d prevPossibleMovePos;
	short possibleMoveCount = 0;

	for ( short i = 0; i < 9; ++i )
	{
		// Find all and empty positions digits in shRow
		if ( m_shBoard[i][shRow] == 0 )
		{
			vEmptyPositions.push_back(vector2d(i, shRow));
		}
	}

	short shSize = vEmptyPositions.size();
	short shSolvedPositions = 0;
	for ( int j = 1; j < 10; j++ )
	{
		int i = 0;

		for (; i < shSize; ++i  )
		{
			if ( isValidMove( vEmptyPositions[i], j) )
			{
				possibleMoveCount++;
				prevPossibleMovePos = vEmptyPositions[i];
			}
		}

		if ( possibleMoveCount == 1)
		{
			if ( insert( prevPossibleMovePos, j ) )
			{
				return 1;
				//++shSolvedPositions;
			}
		}

		possibleMoveCount = 0;

	}
	return shSolvedPositions > 0;

}


bool CBoard::solveColumn( const short shColumn ) {

	// Check if only one digit is missing for this row
	int iProgress = m_iProgressColumns[shColumn];

	// Allready solved
	if ( iProgress == 9 )
	{
		return false;
	}

	if ( PRINT_INFO )
	{
		std::cout << "  Trying to solve column " << shColumn << std::endl;
	}

	if ( !SPEED_ONLY )
	{
		// Check that row conatins no errors
		if ( !validateCoumn(shColumn))
		{
			if ( PRINT_DEBUG )
				std::cout << "  Could not complete column " << shColumn << ", column is invalid!\n";
			return false;
		}
	}


	// Check that only one digit is missing for this column
	if ( iProgress == 8 )
	{

		if ( solveColumn_SingleDigit(shColumn) )
		{
			if ( PRINT_INFO )
			{
				std::cout << "Success! (row_single digit solve) Line : " << __LINE__ << std::endl
					<< "\n================================================================================\n";
			}
		}

	} else
	{

		if ( solveColumn_Advanced(shColumn) )
		{
			if ( PRINT_INFO )
			{
				std::cout << "Success! (row_advanced solve) Line : " << __LINE__
					<< "\n================================================================================\n";
			}
			return true;
		}

		return false;
	}



	return false;


}

bool CBoard::solveColumn_SingleDigit( short shColumn ) {
	if ( PRINT_INFO )
		std::cout << "Solving columnt single digit\n";

	// Store all inserted digits for this column in a bool array
	bool bDigitValid[9] =
	{
		false, false, false,
		false, false, false,
		false, false, false
	};

	short shMissingDigitPos = -1;


	for ( short i = 0; i < 9; ++i ) {

		short digit = m_shBoard[shColumn][i];

		// Is a digit place in shColumn, i?
		if ( digit > 0 )
		{
			// Yes - set this digit position as valid
			bDigitValid[ digit - 1] = true;
		} else
			// No - set this position as the missing position
			shMissingDigitPos = i;
	}

	// Find the one element in the bool array that is set to false ( the digit that hasn't been used )
	// Insert it into the row and validate the column to make sure everything is valid.

	// Loop through the list and find the digit that hasn't been placed.
	for ( int i = 0; i < 9; ++i )
	{
		if ( bDigitValid[i] != true)
		{
			insert( vector2d(shColumn, shMissingDigitPos), i + 1);

			if ( !SPEED_ONLY )
				if ( validateCoumn(shColumn) )
				{
					if ( PRINT_DEBUG )
						std::cout << "  Column solved!\n";
					if ( PRINT_BOARD )
						printBoard();
					return true;
				}

		}
	}

	// The method failed, this should never hapen since this method wil only be called when only one digit is missing
	return false;
}


bool CBoard::solveColumn_Advanced ( const short shColumn){
	if ( PRINT_INFO )
		std::cout << "   Solving column advanced\n";


	std::vector<vector2d> vEmptyPositions;
	vector2d prevPossibleMovePos;
	short possibleMoveCount = 0;


	// Finds all empty pos
	// Checks to see if any number can only go in one of them

	for ( short i = 0; i < 9; ++i ) {

		// Find all and empty positions digits in shRow
		if ( m_shBoard[shColumn][i] == 0 ) {
			vEmptyPositions.push_back(vector2d(shColumn, i));
		}
	}
	short shSolvedPositions = 0;
	short shSize = vEmptyPositions.size();
	for ( int j = 1; j < 10; j++ )
	{
		int i = 0;

		for (; i < shSize; ++i  )
		{
			if ( isValidMove( vEmptyPositions[i], j) )
			{

				possibleMoveCount++;
				prevPossibleMovePos = vEmptyPositions[i];

			}
		}

		if ( possibleMoveCount == 1)
		{
			if ( insert( prevPossibleMovePos, j ) )
				return 1;//shSolvedPositions++;
		}

		possibleMoveCount = 0;
	}

	return shSolvedPositions > 0;

}
bool CBoard::solveSquare( const short &shSquareID ) {
	bool bSolved = false;
	switch ( shSquareID) {
		case 0:
			bSolved = solveSquare(0,0);
			break;
		case 1:
			bSolved = solveSquare(1,0);
			break;
		case 2:
			bSolved = solveSquare(2,0);
			break;
		case 3:
			bSolved = solveSquare(0,1);
			break;
		case 4:
			bSolved = solveSquare(1,1);
			break;
		case 5:
			bSolved = solveSquare(2,1);
			break;
		case 6:
			bSolved = solveSquare(0,2);
			break;
		case 7:
			bSolved = solveSquare(1,2);
			break;
		case 8:
			bSolved = solveSquare(2,2);
			break;
		default:
			bSolved = false;
			break;
	}
	return bSolved;
}
bool CBoard::solveSquare( short shColumn, short shRow ){

	// Check for complete column
	// =======================================================================
	int iProgress = m_iProgressSquares[ shColumn  + ( shRow  * 3)];

	if ( iProgress == 9)
	{
		return false;
	}

	if ( PRINT_INFO )
	{
		std::cout << "  Trying to solve square " << shColumn << " , " << shRow << std::endl;
	}

	// Validate
	// =======================================================================
	if ( !SPEED_ONLY)
	{

		// Check that square conatins no errors
		if ( !validateSquare(shColumn, shRow)) {
			if ( PRINT_DEBUG )
				std::cout << "  Could not complete square " << shColumn << " , " << shRow << ", square is invalid!\n";
			return false;
		}
	}

	// Check if only one digit is missing for this square
	// =======================================================================
	if ( iProgress == 8 )
	{
		if ( solveSquare_SingleDigit(shColumn, shRow) )
		{
			if ( PRINT_INFO ) {
				std::cout << "Success! (square single digit solve) Line : " << __LINE__ << std::endl;
				std::cout << "================================================================================\n";
			}

			return true;

		}
		// More than one digit missing
		// =======================================================================
	} else
	{
		if ( solveSquare_Advanced(shColumn, shRow) )
		{
			if ( PRINT_INFO ) {
				std::cout << "Success! (square advanced solve) Line : " << __LINE__ << std::endl;
				std::cout << "================================================================================\n";
			}

			return true;

		}
	}

	return false;
}

bool CBoard::solveSquare_SingleDigit( const short shColumn, const short shRow ) {
	bool bDigitValid[9] = {
		false, false, false,
		false, false, false,
		false, false, false};

	vector2d missingDigitPos;

	short j = 0;

	for ( short i = 0; i < 3; ++i ) {
		for ( ; j < 3; j++ ) {

			short digit = m_shBoard[ shColumn * 3 + i][shRow * 3 + j];

			if ( digit > 0 ) {
				bDigitValid[ digit - 1] = true;
			} else {
				missingDigitPos = vector2d(shColumn * 3 + i, shRow * 3 + j);
			}

		}

		j = 0;

	}

	// Find the one element in the bool array that is set to false ( the digit that hasn't been used )
	// Insert it into the row and validate the column to make sure everything is valid.
	for ( int i = 0; i < 9; ++i ) {
		if ( bDigitValid[i] != true) {
			if ( PRINT_DEBUG )
				std::cout << "  inserting " << missingDigitPos.x << " , " << missingDigitPos.y << " digit = " << i + 1 << std::endl;
			//m_shBoard[missingDigitPos.first][missingDigitPos.second] = i +1;
			insert_Validate(missingDigitPos, i +1 );
			if ( !SPEED_ONLY ) {
				if ( validateSquare(shColumn, shRow) ) {
					if ( PRINT_DEBUG )
						std::cout << "  Square solved!\n";
					if ( PRINT_BOARD )
						printBoard();
					return true;
				} else {
					if ( PRINT_DEBUG )
						std::cout << "  Square solved resulting in error!\n";
					return false;
				}
			}
		}
	}

	return true;
}

short CBoard::solveSquare_Advanced( const short shColumn, const short shRow ){

	if ( PRINT_INFO )
		std::cout << "   Solving square_advanced " << shColumn << " , " << shRow << std::endl;

	// short shSquareX = shColumn / 3;
	//short shSquareY = shRow / 3;
	short shPossibleMoveCount = 0;
	vector2d prevPossibleMovePos;

	std::vector<vector2d> vEmptyPositions;

	// Determing a square digit - Way 2
	// 1. Find all free squares ( except the one supplied )
	// 2. Check if placing digit in any of them is a valid move
	// 3. If digit is not valid in any of the digit, place in the originally suplied digit

	short j = 0;
	for ( short i = 0; i < 3; ++i )
	{
		for ( ; j < 3; j++ )
		{

			short shCurrentX = shColumn * 3 + i;
			short shCurrentY = shRow * 3 + j;

			if ( PRINT_DEBUG )
				std::cout << "    Position : " << shCurrentX << " , " << shCurrentY;

			if ( m_shBoard[ shCurrentX ][shCurrentY] == 0 )
			{
				if ( PRINT_DEBUG )
					std::cout << " added to list";
				vEmptyPositions.push_back(vector2d(shCurrentX, shCurrentY));

			}

			if ( PRINT_DEBUG )
				std::cout << std::endl;

		}
		j = 0;
	}
	// short shDigitsSolved = 0;
	short shSize = vEmptyPositions.size();

	for ( int j = 1; j < 10; j++ ){
		if ( isDigitPlacedInSquare(shColumn, shRow, j))
			continue;


		int i = 0;

		for (; i < shSize; ++i  ) {
			if ( isValidMove( vEmptyPositions[i], j) )
			{

				shPossibleMoveCount++;
				prevPossibleMovePos = vEmptyPositions[i];

			}
		}

		if ( shPossibleMoveCount == 1)
		{
			if ( insert( prevPossibleMovePos, j ) )
				return 1;
			//++shDigitsSolved;
		}

		shPossibleMoveCount = 0;
	}

	return /*shDigitsSolved >*/ 0;
}

bool CBoard::isValidMove ( const vector2d &pos, short shDigit ) {

	if ( PRINT_DEBUG )
		std::cout << "isValidMove " << shDigit << " into " << pos << " ?";

	if (
			!isDigitPlacedInColumn  ( pos.x     , shDigit             )
			&& !isDigitPlacedInRow     ( pos.y     , shDigit             )
			&& !isDigitPlacedInSquare  ( pos.x / 3 , pos.y / 3,  shDigit )

	   )
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


void CBoard::removeFromListOfUnsolvedPositions( const vector2d &pos ){


	int i = 0;
	for ( ; i < m_iUnsolvedPosCount; ++i )
	{

		if ( m_vUnsolvedPositions[i].x == pos.x &&
				m_vUnsolvedPositions[i].y == pos.y
		   )
		{

			m_vUnsolvedPositions.erase(m_vUnsolvedPositions.begin() + i);
			break;
		}
	}

}
void CBoard::removePossibilitiesInsert( const vector2d &pos, const short shDigit ) {

	short shDigitRem = shDigit - 1;
	if (PRINT_DEBUG)
		std::cout << "removePossibilitiesInsert: digit : " << shDigit << " pos : " << pos << std::endl;


	for ( int i = 0; i < 9; ++i )
	{
		if ( PRINT_DEBUG )
			std::cout << "removing ( " << pos.x << " , " << i << " ) and ( " << i << " , " << pos.y << std::endl;

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
void CBoard::resetBoard() {

	if (m_bGuessMode ) {
		short j = 0;
		for ( short i = 0; i < 9; ++i ) {
			for ( ; j < 9; j++ ) {
				if ( !m_bLookedPositions[i][j])
				{
					m_iUnsolvedPosCount++;
					m_shBoard[i][j] = 0;
				}
			}
			j = 0;
		}
	}
}
void CBoard::loadBoard()
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
