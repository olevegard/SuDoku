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

		bool checkForNakedPossibility_Column( short iColumn );
		bool checkForNakedPossibility_Row   ( short iRow );
	private:

		// This method is inteded to clean up the possibilities for the row.
		// It will mark a Cell as solved, and will remove all impossible digits for every positons.
		// This method is inteded to be used when trying to solve a single digit and you need extra information
		// Or when trying to solve the entire board.
		// Returns true whenever a something has been updated, if so update() needs to be run.
		bool solveRow( short shRow );

		// A helper method for solve row.
		// Will find count of every digit and the first position it was found in
		// Returns true if anything has been updated.
		bool solveRow_Helper( short shRow );

		// Removes a digit from m_oPossibleNumbers
		void removePossibilitiesInsert( const vector2d &pos, const short shDigit );

		// Keeps track of all possible numbers for all positions
		SuDokuCell::CSuDokuCell m_oPossibleNumbers[9][9];


		// Solver methods...
		bool checkForNakedPairs_SingleRow( short iRow );
		bool checkForNakedPairs_SingleColumn( short iColumn );

		// Remove helper
		bool RemovePossibilities_Row   ( short iRow   , short iHiddenDouble1, short iHiddenDOuble2, short iExcept1, short iExcept2 );
		bool RemovePossibilities_Column( short iColumn, short iHiddenDouble1, short iHiddenDouble2, short iExcept1, short iExcept2 );


};
