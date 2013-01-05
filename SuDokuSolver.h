#pragma once

#include "Vector2d.h"
#include "SuDokuCell.h"
#include "BoardStatus.h"

class CSuDokuSolver{
	public:
		CSuDokuSolver( BoardStatus* pStatus)
			:   m_oPossibleNumbers()
			    ,   m_pBoardStatus(NULL)
	{
		m_pBoardStatus = pStatus;
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

		void printAllPosibilities();
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


		BoardStatus* m_pBoardStatus;
};
