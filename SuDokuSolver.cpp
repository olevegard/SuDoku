#include "SuDokuSolver.h"
#include "LogTool.h"
#include "Digit.h"

static const bool PRINT_DEBUG = false;


bool CSuDokuSolver::solveRow( short iRow, short &iProgress )
{

	// Check if only one digit is missing for this row
	int iProgress = m_pBoardStatus->m_iProgressRows[iRow];


	if ( PRINT_DEBUG )
	{
		std::cout << "Trying to solve row " << iRow << std::endl;
	}

	// Nothing to do if 8 or more digits has been placed in row allready.
	if ( iProgress >= 8 )
	{

		if ( PRINT_DEBUG )
		{
			std::cout <<  "      Allready solved ( 8 or more digits present in row)" << iRow << std::endl;
		}

		return false;
	}

	// Try to solve row
	return solveRow_Helper( iRow );
}

bool CSuDokuSolver::solveRow_Helper( short iRow  )
{
	short iPossible[] =
	{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0
	};

	vector2d firstPositions[] = 
	{
		vector2d(-1, -1), vector2d(-1, -1), vector2d(-1, -1),
		vector2d(-1, -1), vector2d(-1, -1), vector2d(-1, -1),
		vector2d(-1, -1), vector2d(-1, -1), vector2d(-1, -1)
	};

	bool bSuccess = false;
	// Iterate through all digits ( 0 - 9 )
	for ( short iDigit = 0; iDigit < 9; ++iDigit)
	{
		// Iterate trhough all columns ( 0 - 9 )
		for ( short i = 0; i < 9; ++i )
		{

			// Is digit possilbe in this position?
			if ( m_oPossibleNumbers[i][iRow].isPossible( i ) )
			{
				iPossible[i]++;
				
				// Is this the first instance of this digit in this row?
				if ( iPossible[i] == 1 )
				{
					// Save position of this digit
					firstPositions[i] = vector2d( i, iRow);
				}
			}

		}
	}

					/*
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
	*/

	return bSuccess;
}

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


void CSuDokuSolver::sovleAll_Qucik( bool bLoopSeveral, std::vector< Digit > &v )
{
	vector2d pos(-1,-1);
	bool bContinue = true;
	//std::vector< Digit > &v = m_pBoardStatus->m_vUnsolvedPositions;
	
	int iSolvedDigit = -1;
	timespec startTime;
	timespec stopTime;
	std::vector< Digit >::iterator p;
	clock_gettime( CLOCK_REALTIME, &startTime );

	while ( bContinue )
	{
		bContinue = false;

		for ( p = v.begin(); p != v.end(); )
		{
			pos = (*p).getPosition();

			if ( PRINT_DEBUG )
				std::cout << "Solving : " << pos << std::endl;
			
			iSolvedDigit = solve( pos );

			if ( iSolvedDigit != -1 )
			{
				if ( PRINT_DEBUG )
					std::cout << "   Erasing : " << (*p).getPosition() << std::endl;

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
	
	clock_gettime( CLOCK_REALTIME, &stopTime );
	CLogTool::LogTime( startTime, stopTime );
}
