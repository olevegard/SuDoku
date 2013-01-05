#include "BoardManager.h"
#include <iomanip>
#include <cstring>


static const bool PRINT_DEBUG = false;

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
	short iLength =  strlen( czBoard );
	vector2d pos(0,0);

	short iDigit = 0;

	for ( int i = 0; i < iLength; ++i)
	{
		// If current char is space, skip.
		if ( czBoard[i] != '-' )
		{

			// Convert current char to a digit
			switch ( czBoard[i] )
			{
				case '0':
					iDigit = -1;
					break;
				case '1':
					iDigit = 0;
					break;
				case '2':
					iDigit = 1;
					break;
				case '3':
					iDigit = 2;
					break;
				case '4':
					iDigit = 3;
					break;
				case '5':
					iDigit = 4;
					break;
				case '6':
					iDigit = 5;
					break;
				case '7':
					iDigit = 6;
					break;
				case '8':
					iDigit = 7;
					break;
				case '9':
					iDigit = 8;
					break;
				default:
					iDigit = -1;
					break;
			}

			// Insert digit
			if ( iDigit >= 0 )
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
	}

	if ( m_oStatus.m_iUnsolvedPosCount== 0 )
		m_oBoard.printBoard();

	m_oSolver.printAllPosibilities();

}


void CBoardManager::insert( const vector2d &pos, short iDigit )
{
	if ( PRINT_DEBUG )
		std::cout << "inserting " << iDigit + 1 << " at : " << pos << std::endl;

	// Can iDigit be inserted to pos?
	if ( m_oBoard.insert( pos, iDigit, true ) )
	{

		// Update list of solved positions ( number of unsolved positions, solved in column/row/square )
		m_oStatus.UpdateSolveInformation( pos );
		//UpdateSolveInformation( pos );

		m_oSolver.insert( pos, iDigit );
	}

}

void CBoardManager::solveNext()
{
	if ( m_oSolver.solve( vector2d(0,0) ) != -1 )
	{
		std::cout << "Solved!\n";
		m_oSolver.printAllPosibilities();
	} else 
	{
		std::cout << "not solved\n";
	}
}
