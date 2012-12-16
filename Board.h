#pragma once
#include <vector>
#include <ostream>
#include <iostream>
#include <sys/time.h>

#include "Box.h"
#include "Cell.h"
#include "Vector2d.h"

class CBoard{
	public:

		CBoard();
		~CBoard();

		void printBoard( );                                             // Prints the board without highlighting any cells
		void printProgress();

		void loadBoard();   // Loads the board TODO: load from file or args

		// Does all the three validations ( validateRow(), validateColumn(), validateSquare() for values 0-8 )
		bool validateEverything(  );

		// Does all the three above validations for supplied position
		bool validateEverything( const vector2d &pos );

		// Inserts and validates a single digit
		bool insert_Validate( const vector2d &pos, const short iDigit);

		// Inserts a locked digit
		bool insert_Lock( const vector2d &pos, const short iDigit);

		// Get numbers filled in of a particular digit
		short getProgressDigit(short shDigit);

		// Get numbers of digits filled out in total
		short getTotatlProgress();

		// Solves everything ( or as far as possible )
		int solveEverythingRepeat();
        void solveLoop();

		bool insert(const vector2d &pos, short shDigit, bool bLocked = false );


	private:
		// Returns value, or - if 0. Used for printing the board
		char getValue( const short shColumn, const short shRow);

		// Helper solve methods - Rows
		//===============================================================================
		bool solveRow( const short shRow );                                         // Solvs a single row
		bool solveRow_SingleDigit( short shRow );                                   // Solves a row with a single digit missing ( helper method for solveRow )
		bool solveRow_Advanced ( short shRow);                                      // Solves a row with several digits missing ( helper method for solveRow )

		// Checks
		bool isDigitPlacedInRow( short shRow, short shDigit );                      // Check if row has the digit in one of its spaces
		short getProgressRow(short shRow);                                          // Get numbers of digits filled out in row
		bool validateRow( const short shRow);                                       // Validates an entire row ( left to right )

		// Possibility checks..
		bool checkForNakedPairs_SingleRow   ( const short shRow );                  // Checks an entire column for naked pairs
		void checkForNakedTriplets_SingleRow( const short shRow );
		bool checkForHiddenPairs_SingleRow  ( const short shRow );                  // Checks an entire column for hidden pairs
		bool checkForXWing_Rows		    ( short iRow1, short iRow2 );			// Checks the two rows for XWing

		// Helpers
		int finCountOfDigitInRow( short iDigit, short iRow ); 					// Find how many celles iDigit can be place in withinn this row

		// Possibility removal...
		bool findUniqueInRow                ( const short shRow );                  // Tries to find an unique digit in row.
		bool findHiddenPairRow              ( const short shRow );

		// Helper solve methods - Columns
		//===============================================================================
		bool solveColumn( const short shColumn );                                   // Solvs a single column
		bool solveColumn_SingleDigit( short shColumn );                             // Solves a column with a single digit missing ( helper method for solveColumn )
		bool solveColumn_Advanced( const short shColumn );                          // Solves a column with several digits missing ( helper method for solveColumn )

		// Checks
		bool isDigitPlacedInColumn( short shColumn, short shDigit );                // Check if column has the digit in one of its spaces
		short getProgressColumn(short shColumn);                                    // Get numbers of digits filled out in column
		bool validateCoumn( const short shColumn);                                  // Validates an entire colum ( top to bottom )

		// Possibility checks..
		bool checkForNakedPairs_SingleColumn    ( const short shColumn);                // Checks an entire column for hidden pairs
		bool checkForNakedTriplets_SingleColumn ( const short iColumn );
		bool checkForHiddenPairs_SingleColumn   ( const short shColumn);
		bool findUniqueInColumn                 ( const short shColumn);               // Tries to find an unique digit in column.
		bool findHiddenPairColumn               ( const short shColumn);

		// Helperers
		int finCountOfDigitInColumn( short iDigit, short iColumn ); 					// Find how many celles iDigit can be place in withinn this column
		void removePosibilities_Column(
			const short shColumn,   // The column to remove possibilities for
			const short shExcept1,  // The first position to ignore
			const short shExcept2,  // The second position to ignore
			const short shDigit1,   // The first digit to remove
			const short shDigit2    // The second digit to remove
		);

		// Helper solve methods - Squares
		//===============================================================================
		bool solveSquare( const short & shSquareID );                               // Calls solveSquare with the coordinates for shSquareID
		bool solveSquare( short shColumn, short shRow );                            // Solvs a single square
		bool solveSquare_SingleDigit( const short shColumn, const short shRow );    // Solves a square with a single digit missing ( helper method for solveSquare )
		short solveSquare_Advanced( const short shColumn, const short shRow );      // Solves a square with several digits missing ( helper method for solveSquare )

		// Checks
		bool isDigitPlacedInSquare(short shColumn, short shRow, short shDigit);     // Check if square has the digit in one of its spaces
		short getProgressSquare(const short shColumn, const short shRow );          // Get numbers of digits filled out in square
		bool validateSquare(const short shColumn, const short shRow);               // Validates an entire square

		// Possibility checks..
		bool checkForNakedPairs_SingleSquare( const short shSquare );			// Checks an entire square for hidden pairs
		bool checkForPointingPairs          ( const short shSquare );			// Check shSquare for pointing pairs
		bool findUniqueInSquare             ( const short shSquare );			// Check if there are any numbers than only occurs once witinn this square
		// General solve methods
		// Go through all cells and find all possible digits
		//===============================================================================
		void findPossibleNumbersForAllPositions(const bool bAdd  );     // Goes through all positions and looks for possibilities

		bool solvePossibilities();                                      // Goes throug all possibilities looks for singles and insert the singles to the board.

		// Printing functions....
		void printAllPosibilities();
		void printBoard( const short shColumn, const short shRow);      // Prints the board and highlights a single cell
		void printBoard( const vector2d &pair1, const vector2d &pair2); // Prints the entire board and highlights two cells.

		// Helper functions for insert
		bool isValidMove ( const vector2d &pos, short shDigit );    	// Checks if move is valid
		bool lockPosition( const vector2d &pos );

		void removeFromListOfUnsolvedPositions( const vector2d &pos );			// Removes a digit from m_vUnsolvedPositions
		void removePossibilitiesInsert( const vector2d &pos, const short shDigit );	// Removes a digit from m_oPossibleNumbers


		void resetBoard();		// Resets the board by erasing all digits that aren't locked. 

		Cell m_oPossibleNumbers[9][9];	// Keeps track of all possible numbers for all positions

		int m_iProgressRows[9];     // How many unsolved cells remains in row
		int m_iProgressColumns[9];  // How many unsolved cells remains in column
		int m_iProgressSquares[9];  // How many unsolved cells remains in square

		bool m_bLookedPositions[9][9];  // Which positions can be changed?
		bool m_bGuessMode;
		bool m_bErrorFound;
		short m_shBoard[9][9];          // The SuDoku board

		int m_iUnsolvedPosCount;        		// The number of unsolved positions.
		std::vector<vector2d> m_vUnsolvedPositions; 	// All unsolved positions

};
