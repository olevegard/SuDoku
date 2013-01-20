#pragma once

#include <vector>
#include <ostream>
#include <iostream>
#include <sys/time.h>

#include "Digit.h"
#include "Vector2d.h"

class CSuDokuBoard{
	public:
		CSuDokuBoard();
		// Initialisation
		// ==================================================================================


		// Printing
		// ==================================================================================

		// Printing functions....

		// Prints the entire board and highlights two cells.
		// Used when errors has been detected to highlight where the errors are
		void printBoard( const vector2d &pair1, const vector2d &pair2) const; // added

		// Prints the board without highlighting any cells
		void printBoard( ) const; // added

		// Displays all progress
		void printProgress() const;

		// Validate
		// ==================================================================================

		// Does all the three above validations for supplied position
		bool checkBoardValidity( const vector2d &pos ) const;
		bool checkBoardValidity(  ) const;

		bool checkMoveValidity ( const vector2d &pos, short digit ) const;    // added	// Checks if move is valid

		bool chekIfPositionIsLocked( const vector2d &pos ) const; // added

		// TODO : improve ( needs to check if a number is repeated )
		bool checkRowValidity( short iRow) const;
		bool checkColumnValidity( short iColumn) const;
		bool checkSquareValidity(const vector2d &pos) const; // needs testing

		// Insert
		// ==================================================================================

		// Generic insert method
		bool insert(
				const vector2d &pos, // Position to insert to
				short digit,       // The digit to inser ( 1-9 )
				bool lcoked = false // Lock position.
			   ); // added

		bool insert( const Digit &digit )
		{
			return insert( digit.getPosition(), digit.getDigit() );
		}

		// Resets the board by erasing all digits that aren't locked.
		void resetBoard();

		// Validate
		// ==================================================================================

		// Check if row has the digit in one of its spaces
		bool isDigitPlacedInRow( short iRow, short iDigit ) const;
		bool isDigitPlacedInColumn( short iColumn, short iDigit ) const;
		bool isDigitPlacedInSquare( const vector2d &pos, short iDigit ) const;//pos.x / 3 , pos.y / 3

		// Progress
		// ==================================================================================

		// Get numbers of digits filled out in row
		short getProgressRow(short iRow) const; // added
		short getProgressColumn(short iColumn) const;// added
		short getProgressSquare( const vector2d &pos ) const;// added

		short getTotatlProgress() const; // added

		// Returns value, or - if 0. Used for printing the board
		char getValueOfPosition( const vector2d &opos ) const;// added

		// Get a list of all unsolved positions
		//const std::vector<vector2d>& getUnsolvedPositions() const;// added

	private:


		// Removes a digit from m_vUnsolvedPositions
		//void removeFromListOfUnsolvedPositions( const vector2d &pos ); // added

		// Locks a position ( "hey man, trust me, I know this digit goes there" )
		// A locked position can't be changed, and won't be reset by reset board.
		// This should be done as much as possible
		bool lockPosition( const vector2d &pos );

		// The SuDoku board
		short m_shBoard[9][9];

		// Which positions can be changed?
		bool m_bLookedPositions[9][9];

		// Is guessing allowed?
		bool m_bGuessMode;

};
