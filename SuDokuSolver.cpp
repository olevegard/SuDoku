#include "SuDokuSolver.h"
#include "LogTool.h"
#include "Digit.h"

static const bool PRINT_DEBUG = false;


void CSuDokuSolver::insert( const vector2d &pos, short iDigit )
{
	// Update the possibilities for this position
	m_oPossibleNumbers[pos.x][pos.y].setAndMarkAsSolved( iDigit );
	removePossibilitiesInsert( pos, iDigit );
}


void CSuDokuSolver::removePossibilitiesInsert( const vector2d &pos, const short iDigit ) {

	short iDigitRem = iDigit;

	if (PRINT_DEBUG)
		std::cout << "removePossibilitiesInsert: digit : " << iDigit + 1 << " pos : " << pos << std::endl;


	for ( int i = 0; i < 9; ++i )
	{
		if ( PRINT_DEBUG )
			std::cout << "removing ( " << pos.x << " , " << i << " ) and ( " << i << " , " << pos.y << " )\n";

		m_oPossibleNumbers[pos.x][i].remove(iDigitRem);
		m_oPossibleNumbers[i][pos.y].remove(iDigitRem);
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

	m_oPossibleNumbers[shX1][shY1].remove(iDigitRem);
	m_oPossibleNumbers[shX2][shY1].remove(iDigitRem);
	m_oPossibleNumbers[shX3][shY1].remove(iDigitRem);

	m_oPossibleNumbers[shX1][shY2].remove(iDigitRem);
	m_oPossibleNumbers[shX2][shY2].remove(iDigitRem);
	m_oPossibleNumbers[shX3][shY2].remove(iDigitRem);

	m_oPossibleNumbers[shX1][shY3].remove(iDigitRem);
	m_oPossibleNumbers[shX2][shY3].remove(iDigitRem);
	m_oPossibleNumbers[shX3][shY3].remove(iDigitRem);

}

void CSuDokuSolver::printAllPosibilities()
{

	std::cout << "=======================================PRITING POSSIBILITIES=======================================\n";
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
				std::cout << " - |" << m_oPossibleNumbers[iColumn][iRow].getSolvedDigitP1() + 1  << "| - ";
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

	std::cout << "==================================================================================================\n";
}

short CSuDokuSolver::solve( const vector2d &pos )
{
	if ( PRINT_DEBUG)
		std::cout << "solving " << pos << std::endl;
	
	short iDigit = m_oPossibleNumbers[pos.x][pos.y].solve( );

	if ( iDigit != -1 ) 
	{
		removePossibilitiesInsert( pos, iDigit ); 
	}

	return iDigit;
}

short CSuDokuSolver::sovleAll_Qucik( bool bLoopSeveral, std::vector< Digit > &v )
{

	vector2d pos(-1,-1);
	std::vector< Digit >::iterator p;
	int iSolvedDigit = -1;

	short iSolveCount = 0;
	bool bContinue = true;

	while ( bContinue )
	{
		bContinue = false;
		p = v.begin(); 

		for ( ;p != v.end(); )
		{
			pos = (*p).getPosition();

			if ( PRINT_DEBUG )
				std::cout << "Solving : " << pos << std::endl;

			iSolvedDigit = solve( pos );

			if ( iSolvedDigit != -1 )
			{
				if ( PRINT_DEBUG )
					std::cout << "   Solve : " << (*p).getPosition() << " is " << iSolvedDigit + 1 <<  std::endl;

				++iSolveCount;
				// Set this digit as solved...
				(*p).setAsSolved( iSolvedDigit );

				// For looping more than once
				if ( bLoopSeveral )
				{
					bContinue = true;
					break;
				}
			} else 
				++p;
		}
	}

	return iSolveCount;
}
bool CSuDokuSolver::solveAll_Full( const BoardStatus &boardStatus)
{
	bool bSuccess = false;

	for ( short i = 0; i < 9; ++i )
	{

		if ( boardStatus.m_iProgressColumns[i] < 8 )
		{
			if ( checkForHiddenSingle_Column( i ) )
				bSuccess = true;

			if ( checkForNakedPairs_SingleRow( i ) )
				bSuccess = true;
		}

		if ( boardStatus.m_iProgressRows[i] <= 8 )
		{
			if ( checkForHiddenSingle_Row( i ) )
				bSuccess = true;

			if ( checkForNakedPairs_SingleColumn( i ) )
				bSuccess = true;

			if ( checkForHiddenPairs_SingleRow( i ) )
				bSuccess = true;
		
			//checkForNakedSingle_Row( i );
		}

		if ( boardStatus.m_iProgressSquares[i] < 8 )
		{
			if ( checkForHiddenSingle_Square( i ) )
				bSuccess = true;
				
			if ( checkForNakedPairs_SingleSquare( i ) )
				bSuccess = true;
		}
		
	}

	return bSuccess;
	// Loop i 0 -> 9
	// 	If ColumnProgress != 9
	// 		Solve columnt
	// 		*
	// 	if row Progress != 9
	// 		solve row
	// 		*
	// 	if squareProgress != 9
	// 		solve square
	// 		*
	//
	// 	pointing pairs
	// 		*
	//
	// 	box/line reduction
	// 		*
	//
	// 	x-wing
	// 		*
	//
	// next


	// * == if successfull and new possibilities removed, return true, otherwise contitnue
}
bool CSuDokuSolver::checkForHiddenSingle_Row ( short iRow )
{

	bool bFound = false;
	for ( short iDigit = 0; iDigit < 9; ++iDigit )
	{
//		if ( boardStatus.IsDigitFoundInRow( iRow, iDigit ) )
//			continue;

		short iCount = 0;
		short iPos = 0;
		for ( short i = 0; i < 9; ++i )
		{
			if ( m_oPossibleNumbers[i][iRow].isPossible( iDigit ) )
			{
				if ( PRINT_DEBUG )
					std::cout << iDigit + 1 << " found at " << i << " , " << iRow << std::endl;
				++iCount;
				iPos = i;
			}
		}

		if ( iCount == 1 )
		{
			if ( PRINT_DEBUG )
				std::cout << "single pos : " << iPos << " , " << iRow << " digit : " << iDigit + 1 << std::endl;

			bFound = true;
			m_oPossibleNumbers[iPos][iRow].removeAllPosibilitiesExcept(iDigit);
		}
	}
	return bFound;
}
bool CSuDokuSolver::checkForHiddenSingle_Column( short iColumn )
{
	bool bFound = false;
	for ( short iDigit = 0; iDigit < 9; ++iDigit )
	{
		short iCount = 0;
		short iPos = 0;
		for ( short i = 0; i < 9; ++i )
		{
			if ( m_oPossibleNumbers[iColumn][i].isPossible( iDigit ) )
			{
				if ( PRINT_DEBUG )
					std::cout << iDigit + 1 << " found at " << iColumn << " , " << i<< std::endl;
				++iCount;
				iPos = i;
			}
		}

		if ( iCount == 1 )
		{

			if ( PRINT_DEBUG )
				std::cout << "single pos : " << iColumn << " , " << iPos << " digit : " << iDigit + 1 << std::endl;
			bFound = true;
			m_oPossibleNumbers[iColumn][iPos].removeAllPosibilitiesExcept(iDigit);
		}
	}
	return bFound;
}
bool CSuDokuSolver::checkForHiddenSingle_Square( short iSquare )
{
	if ( PRINT_DEBUG )
		std::cout << "checkForNakePossibility_SingleSquare " << iSquare << std::endl;

	vector2d posOrigo;
	getPositionOfSquare( iSquare, posOrigo);

	bool bFound = false;

	for ( short iDigit = 0; iDigit < 9; ++iDigit )
	{
		short iCount = 0;
		vector2d pos;
		vector2d posFound;

		for ( short i = 0; i < 9; ++i )
		{
			pos.x = posOrigo.x + ( i % 3 );
			pos.y = posOrigo.y + ( i / 3 );
			if ( m_oPossibleNumbers[pos.x][pos.y].isPossible( iDigit ) )
			{
				if ( PRINT_DEBUG )
					std::cout << iDigit + 1 << " found at " << pos << std::endl;

				if ( iCount == 0 )
					posFound = pos;
				++iCount;
			}
		}

		if ( iCount == 1 )
		{
			if ( PRINT_DEBUG )
				std::cout << "single pos : " << posFound << " digit : " << iDigit + 1 << std::endl;

			bFound = true;
			m_oPossibleNumbers[posFound.x][posFound.y].removeAllPosibilitiesExcept(iDigit);
		}
	}
	return bFound;
}
bool CSuDokuSolver::checkForNakedPairs_SingleRow( short iRow )
{
	if ( PRINT_DEBUG )
		std::cout << "checkForHiddenDoubles_SingleRow " << iRow << std::endl;

	short iColumnIndex2 = 0;
	bool bFound = false;

	for ( short iColumnIndex1 = 0; iColumnIndex1 < 9; ++iColumnIndex1 )
	{
		iColumnIndex2 = iColumnIndex1 + 1;
		for ( ; iColumnIndex2 < 9; ++iColumnIndex2 )
		{
			SuDokuCell::CSuDokuCell cell1 = m_oPossibleNumbers[iColumnIndex1][iRow];
			SuDokuCell::CSuDokuCell cell2 = m_oPossibleNumbers[iColumnIndex2][iRow];

			//if ( PRINT_DEBUG )
			//	std::cout   << "Compairing " << iColumnIndex1 << " , " << iRow << cell1 << std::endl
			//		<< "And        " << iolumnIndex2 << " , " << iRow << cell2 << std::endl;

			if ( cell1.isNakedPair(cell2) )
			{
				if ( PRINT_DEBUG )
					std::cout << "...HiddenPair! " << iColumnIndex1 << " , " << iRow << " and " << iColumnIndex2 << " , " << iRow << std::endl;

				// Remove all other instance of the found numbers in this column
				// TODO : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )
				bFound = RemovePossibilities_Row( iRow, cell1.getHiddenDouble1(), cell1.getHiddenDouble2(), iColumnIndex1, iColumnIndex2 );
			}
		}
	}
	return bFound;
}

bool CSuDokuSolver::checkForNakedPairs_SingleColumn( short iColumn )
{
	if ( PRINT_DEBUG )
		std::cout << "checkForHiddenDoubles_SingleColumn " << iColumn << std::endl;

	short iRowIndex2 = 0;
	bool bFound = true;

	for ( short iRowIndex1 = 0; iRowIndex1 < 9; ++iRowIndex1 )
	{
		iRowIndex2 = iRowIndex1 + 1;

		for ( ; iRowIndex2 < 9; ++iRowIndex2 )
		{
			SuDokuCell::CSuDokuCell cell1 = m_oPossibleNumbers[iColumn][iRowIndex1];
			SuDokuCell::CSuDokuCell cell2 = m_oPossibleNumbers[iColumn][iRowIndex2];

			//if ( PRINT_DEBUG )
			//	std::cout   << "Compairing " << iColumn << " , " << iRowIndex1 << cell1 << std::endl
			//		<< "And        " << iColumn << " , " << iRowIndex2 << cell2 << std::endl;

			if ( cell1.isNakedPair(cell2) )
			{
				//if ( PRINT_DEBUG )
				//	std::cout << "...HiddenPair!" << iColumn << " , " << iRowIndex1 << " and " << iColumn << " , " << iRowIndex2
				//		<< " : " << cell1.shHiddenDouble1 << " & " << cell1.shHiddenDouble2 << std::endl;
				if ( PRINT_DEBUG )
					std::cout << "...HiddenPair! " << iColumn << " , " << iRowIndex1 << " and " << iColumn << " , " << iRowIndex2 
						<< " digit : " << cell1.getHiddenDouble1() << " and " << cell1.getHiddenDouble2() << std::endl;

				// Remove all other instance of the found numbers in this column
				// TODO : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )
				bFound = RemovePossibilities_Column( iColumn, cell1.getHiddenDouble1(), cell1.getHiddenDouble2(), iRowIndex1, iRowIndex2 );
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
bool CSuDokuSolver::checkForNakedPairs_SingleSquare( short iSquare ) {

	if ( PRINT_DEBUG)
		std::cout << "checkForHiddenDoubles_SingleSquare " << iSquare << std::endl;

	vector2d posOrigo;
	getPositionOfSquare( iSquare, posOrigo);

	short iSquareIndex2 = 0;
	bool bFound = false;

	for ( short iSquareIndex = 0; iSquareIndex < 9; ++iSquareIndex )
	{
		iSquareIndex2 = iSquareIndex + 1;
		for ( ; iSquareIndex2 < 9; ++iSquareIndex2 )
		{

			vector2d pos1( posOrigo.x + ( iSquareIndex % 3 ),
					posOrigo.y + ( iSquareIndex / 3 ));

			vector2d pos2( posOrigo.x + ( iSquareIndex2 % 3 ),
					posOrigo.y + ( iSquareIndex2 / 3 ));

			SuDokuCell::CSuDokuCell cell1 = m_oPossibleNumbers[pos1.x][pos1.y];
			SuDokuCell::CSuDokuCell cell2 = m_oPossibleNumbers[pos2.x][pos2.y];

			// Checkinf for naked pair two cell with only the two same numbers..
			if ( cell1.isNakedPair(cell2) )
			{
				

				if ( PRINT_DEBUG )
				{
					std::cout << "...HiddenPair!" << pos1 << " and " << pos2
						<< " : " << cell1.getHiddenDouble1() << " & " << cell1.getHiddenDouble2() << std::endl;
				}
				// Remove all other instance of the found numbers in this column
				// TODO : Make this into a function
				// ...removePosibilities_Column( const short shColum, const short shExcept1, const short shExcept2, const short iDigit1, const short iDigit2)
				// Where shExcept1 and shExcept1 are the columns that make up the matching pairs ( should not have iDigit1 and iDigit2 removed
				// TODO2 : Make a MatchingPair struct that holds the positions, and the matchin digits ( ? )
				bFound = RemovePossibilities_Square( posOrigo, cell1.getHiddenDouble1(), cell1.getHiddenDouble2(), iSquareIndex, iSquareIndex2 );
			} // End check for naked pair

			// Check for hidden pair
		}
	}

	return bFound;
}

bool CSuDokuSolver::RemovePossibilities_Row( short iRow, short iHiddenDouble1, short iHiddenDouble2, short iExcept1, short iExcept2 )
{
	bool bNewlyErased = false;

	for ( int i = 0; i < 9; ++i)
	{
		if ( i != iExcept1 && i != iExcept2 ) {
			
			if ( PRINT_DEBUG )
				std::cout << "   " << " Removing : " << iHiddenDouble1 << ", " << iHiddenDouble2 << std::endl;

			bool bRemoveResult1 = m_oPossibleNumbers[i][iRow].remove( iHiddenDouble1 );
			bool bRemoveResult2 = m_oPossibleNumbers[i][iRow].remove( iHiddenDouble2 );

			if ( bRemoveResult1 || bRemoveResult2 )
				bNewlyErased = true;

		}

	}

	return bNewlyErased;
}

bool CSuDokuSolver::RemovePossibilities_Column( short iColumn, short iHiddenDouble1, short iHiddenDouble2, short iExcept1, short iExcept2 )
{
	bool bNewlyErased = false;

	for ( int i = 0; i < 9; ++i)
	{
		if ( i != iExcept1 && i != iExcept2 ) {

			if ( PRINT_DEBUG )
				std::cout << "   " << iColumn << " , " << i << " Removing : " << iHiddenDouble1 << ", " << iHiddenDouble2 << std::endl;

			bool bRemoveResult1 = m_oPossibleNumbers[iColumn][i].remove( iHiddenDouble1 );
			bool bRemoveResult2 = m_oPossibleNumbers[iColumn][i].remove( iHiddenDouble2 );

			if ( bRemoveResult1 || bRemoveResult2 )
				bNewlyErased = true;


		}

	}

	return bNewlyErased;
}

bool CSuDokuSolver::RemovePossibilities_Square( const vector2d &posOrigo, short iHiddenDouble1, short iHiddenDouble2, short iExcept1, short iExcept2 )
{
	bool bNewlyErased = false;

	for ( int i = 0; i < 9; ++i)
	{
		if ( i != iExcept1 && i != iExcept2 ) {

			if ( PRINT_DEBUG )
				std::cout << "   " << posOrigo << " , " << i << " Removing : " << iHiddenDouble1 << ", " << iHiddenDouble2 << std::endl;

			vector2d pos( posOrigo.x + ( i% 3 ),
					posOrigo.y + ( i/ 3 ));

			bool bRemoveResult1 = m_oPossibleNumbers[pos.x][pos.y].remove( iHiddenDouble1 );
			bool bRemoveResult2 = m_oPossibleNumbers[pos.x][pos.y].remove( iHiddenDouble2 );
			

			if ( bRemoveResult1 || bRemoveResult2 )
				bNewlyErased = true;
		}

	}

	return bNewlyErased;
}




bool CSuDokuSolver::checkForHiddenPairs_SingleRow ( short iRow )
{
	//std::cout << "Check for hidden pairs [ ROW ] " << iRow << std::endl;

	//printAllPosibilities();
	short iDigit2 = 0;
	bool bFound = false;
	bool bPairFound = false;

	short iPairingDigit1 = -1;
	short iPairingDigit2 = -1;

	for ( short iDigit1 = 0; iDigit1 < 9; ++iDigit1 )
	{
		//getCountOfDigitInRow( iRow, iDigit1 );

	
		//std::cout << "Checking " << iDigit1 + 1 << std::endl;

		// Check if there is less or more than two instances of iDigit1 in this row
		if ( getCountOfDigitInRow( iRow, iDigit1 ) != 2 )
		{
			//std::cout << "   Count possible of " << iDigit1 + 1 << " in row " << iRow  << " is too small, skipping...\n";
			continue;
		}
		
		
		//std::cout << "Don checking " << iDigit1 + 1 << std::endl;

		for ( iDigit2 = iDigit1 + 1 ; iDigit2 < 9; ++iDigit2 )
		{
			// Check if there is less or more than two instances of iDigit2 in this row
			if ( getCountOfDigitInRow( iRow, iDigit2 ) != 2 )
			{
				//std::cout << "      Count possible of " << iDigit2 + 1 << " in row " << iRow << " is too small, skipping...\n";
				continue;
			}

			// At this point there exist exactly two instances of both iDigit1 and iDigit2 in this row
			//std::cout << "      " << iDigit1 + 1 << " and " << iDigit2 + 1 << " is a possible hidden pair!\n";

			iPairingDigit1 = iDigit1;
			iPairingDigit2 = iDigit2;
			bPairFound = true;
		}
	}

	if ( !bPairFound )
		return false;

	bool bFound1 = false;
	bool bFound2 = false;
	short iPairingColumn1 = 0;
	short iPairingColumn2 = 0;
	for ( short i = 0; i < 9; ++i )
	{
		if ( m_oPossibleNumbers[i][iRow].isSolved() )
			continue;

		// Check if i, iRow has both possibilities
		if ( m_oPossibleNumbers[i][iRow].isPossible( iPairingDigit1 ) && m_oPossibleNumbers[i][iRow].isPossible( iPairingDigit2 ) )
		{
			if ( bFound1 )
			{
				iPairingColumn2 = i;
				bFound2 = true;
			}
			else 
			{
				iPairingColumn1 = i;
				bFound1 = true;
			}
		}
	}

	if ( bFound1 && bFound2 )
	{
		if ( PRINT_DEBUG ) 
			std::cout << "Hidden paur foud! " << iPairingDigit1 + 1 << " and " << iPairingDigit2 + 1 << " in column pos " << iPairingColumn1 << " and " << iPairingColumn2 << std::endl;
		m_oPossibleNumbers[iPairingColumn1][iRow].removeAllExceptPair( iPairingDigit1, iPairingDigit2 );
		m_oPossibleNumbers[iPairingColumn2][iRow].removeAllExceptPair( iPairingDigit1, iPairingDigit2 );
		bFound = true;
	}

	return bFound;
}


void CSuDokuSolver::getPositionOfSquare ( short iSquare, vector2d& posOrigo ) const
{
	switch ( iSquare) {
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
}
short CSuDokuSolver::getCountOfDigitInRow ( short iRow, short iDigit )
{
	if ( PRINT_DEBUG )
		std::cout << "Finding possible of " << iDigit + 1 << " in row " << iRow << std::endl;

	short iCountPossible = 0;
	for ( int iColumn = 0; iColumn < 9; ++iColumn )
	{
		if ( m_oPossibleNumbers[iColumn][iRow].getSolvedDigitP1() ==  iDigit   ) 
		{
			if ( PRINT_DEBUG )
				std::cout << "   " <<  iColumn << " , " << iRow << " is allready solved with digit " << iDigit + 1 << std::endl;

			return 0;
		}

		if ( m_oPossibleNumbers[iColumn][iRow].isPossible( iDigit ) )
		{
			if ( PRINT_DEBUG )
				std::cout << "   Found possible of " << iDigit + 1 << " in " << iColumn << " , " << iRow << std::endl;
			++iCountPossible;
		}
	}

	if ( PRINT_DEBUG )
		std::cout << "   Count possible of " << iDigit + 1 << " in row " << iRow << " is " << iCountPossible << std::endl;

	return iCountPossible;
}
