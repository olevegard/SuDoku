#pragma once

#include "Vector2d.h"
#include "SuDokuCell.h"
#include "BoardStatus.h"

class CSuDokuSolver{
	public:
		CSuDokuSolver()
			:   m_oPossibleNumbers()
	{
	}

		// Set a position as solved, and update all related positions
		void insert( const vector2d &pos, short iDigit );

		// Try to solve a diigt.
		// First it will check if the position has been solved. If so, the value for this position will be returned.
		// Otherwise it will run every solve method
		// This method is meant as a way of trying to force the program to solve a position
		// For a method that solves everything, use solveEverything()

		// Return
		// 	0 if failed, nothing solved
		// 	otherwise it returns the new digit for pos.
		short solve( const vector2d &pos );

		// Tries to solve all by using the Solve() function in SuDokuCell.
		// The function will only check if there's only one possibilty for this cell.
		// In other words; this function will solve all cells with one positiblity;
		short sovleAll_Qucik( 
				bool bLoopSeveral, 		//!<< If true; loop til no cell was solved. If false; loop once. 
				std::vector< Digit > &vUsolved	//!<< List of all unsolved digits
		);

		// Will try to solve possiblities, but not insert any diigits.
		// Will try every solve possibility and return true if a possiblitiy was removed.
		// Should be used togehter will solveAll_Quick
		bool solveAll_Full( const BoardStatus &boardStatus);
		
		// Prints every possibilities in the following format :
		// 1  -  3
		// -  5  6
		// 7  8  -
		// if 1, 3, 5, 6, 7 and 8 are possible.
		// -  -  -
		// - |2| -
		// -  -  -
		// If the digit is solved witht 2 as the value
		void printAllPosibilities();

	private:

		// Removes a digit from m_oPossibleNumbers
		void removePossibilitiesInsert( const vector2d &pos, const short shDigit );


		// Solver methods...
		
		// Checks for a single digit on a columnt/row/square
		// If success : thtis digit can be removed from all other cells in column/row/square
		bool checkForHiddenSingle_Column( short iColumn );
		bool checkForHiddenSingle_Row   ( short iRow    );
		bool checkForHiddenSingle_Square( short iSquare );
	
		bool checkForNakedSingle_Row	( short iRow )
		{
			bool bFound = false;

			for ( short i = 0; i < 9 ; ++i)
			{
				printAllPosibilities();
				short digit = m_oPossibleNumbers[i][iRow].solve( );
				if ( digit != -1 )
				{
					bFound = true;
					std::cout << "Foudn naked single in " << i << " , " << iRow << " digit : " << digit + 1 << std::endl;
					printAllPosibilities();
					std::cin.ignore();
				}
			}

			return bFound;
		}
		// Checks for two cells with the same two digis.
		// NOTE 1 : these cells can have more than these two digits
		// NOTE 2 : the digit pair found must not be found anywhere else in this column/row/square
		// If success : all digits except the hidden pair can be removed from these two cells.
		bool checkForHiddenPairs_SingleRow ( short iRow );

		// Checks for two cells with only the same two digis.
		// If success : these two digits can be removed from all other cells in column/row/square
		bool checkForNakedPairs_SingleRow   ( short iRow    );
		bool checkForNakedPairs_SingleColumn( short iColumn );
		bool checkForNakedPairs_SingleSquare( short iSquare );

		short getCountOfDigitInRow ( short iRow, short iDigit );
		// Remove helper
		//	Removes digits from the row/column/sqaure specified in the first argument
		//	Removes only the two digits specified in argument two and three
		//	Does not remove the digits specified in the two last arguments
		bool RemovePossibilities_Row   ( short iRow              , short iHiddenDouble1, short iHiddenDOuble2, short iExcept1, short iExcept2 );
		bool RemovePossibilities_Column( short iColumn           , short iHiddenDouble1, short iHiddenDouble2, short iExcept1, short iExcept2 );
		bool RemovePossibilities_Square( const vector2d &posOrigo, short iHiddenDouble1, short iHiddenDouble2, short iExcept1, short iExcept2 );

		// Helper function to convert an int ( 0-9 identification of square ) into a vector2d
		void getPositionOfSquare ( short iSquare, vector2d& posOrigo ) const;

		// Variables
		// =======================================================================================
		// Keeps track of all possible numbers for all positions
		SuDokuCell::CSuDokuCell m_oPossibleNumbers[9][9];
};
