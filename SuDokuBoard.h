#pragma once
#include <vector>
#include <ostream>
#include <iostream>
#include <sys/time.h>

#include "Box.h"
#include "Cell.h"
#include "Vector2d.h"

class CSuDokuBoard{
    public:
        // Initialisation
        // ==================================================================================

        // Loads the board TODO: load from file or args

        // Load a random board with desired skill level
        void loadBoard( /*int skillLevel*/);

        // Load a bored stored in file
        void loadBoard( const char* fileName);

        // Load a board from cmd line ( only implemented way )
        void loadBoard( const char* board[] );

        // Printing
        // ==================================================================================

        // Prints the board without highlighting any cells
        void printBoard( );

        // Displays all progress
        void printProgress();

        // Extract values
        // ==================================================================================

        // Returns value, or - if 0. Used for printing the board
        char getValue( short shColumn, short shRow);


        // Validate
        // ==================================================================================

        // Does all the three above validations for supplied position
        bool checkBoardValidity( const vector2d &pos );

         // Does all the three validations ( validateRow(), validateColumn(), validateSquare() for values 0-8 )
        bool validateEverything(  );

         // Validates an entire row ( left to right )
        bool validateRow( short row);

        // Validates an entire colum ( top to bottom )
        bool validateCoumn( short col);

         // Validates an entire square
        bool validateSquare(short col, short row);

        // Insert
        // ==================================================================================

        // Generic insert method
        bool insert(
                const vector2d &pos, // Position to insert to
                short digit,       // The digit to inser ( 1-9 )
                bool lcoked = false // Lock position.
        );

        bool checkMoveValidity ( const vector2d &pos, short digit );    	// Checks if move is valid

        bool chekIfPositionIsLocked( const vector2d &pos );

        // Resets the board by erasing all digits that aren't locked.
        void resetBoard();

        // Validate
        // ==================================================================================

        // Check if row has the digit in one of its spaces
        bool isDigitPlacedInRow( short row, short digit );

        // Check if column has the digit in one of its spaces
        bool isDigitPlacedInColumn( short col, short digit );

        // Check if square has the digit in one of its spaces
        bool isDigitPlacedInSquare( const vector2d &pos, short digit);//pos.x / 3 , pos.y / 3

        // Progress
        // ==================================================================================

        // Get numbers of digits filled out in row
        short getProgressRow(short shRow);

        // Get numbers of digits filled out in column
        short getProgressColumn(short shColumn);

         // Get numbers of digits filled out in square
        short getProgressSquare( const vector2d &pos );

        // Get numbers filled in of a particular digit
        short getProgressDigit(short shDigit);

        // Get numbers of digits filled out in total
        short getTotatlProgress();


        // Get a list of all unsolved positions
        const std::vector<vector2d>& getUnsolvedPositions()
        {
            return m_vUnsolvedPositions;
        }

        void UpdateSolveInformation( const vector2d &pos );

    private:
        // Printing functions....
        void printBoard( const vector2d &pair1, const vector2d &pair2); // Prints the entire board and highlights two cells.

        // Insertion helpers
        // =====================================================================================

        // Removes a digit from m_vUnsolvedPositions
        void removeFromListOfUnsolvedPositions( const vector2d &pos );

        // Removes a digit from m_oPossibleNumbers
        void removePossibilitiesInsert( const vector2d &pos, const short shDigit );

        // Locks a position ( "hey man, trust me, I know this digit goes there" )
        // A locked position can't be changed, and won't be reset by reset board.
        bool lockPosition( const vector2d &pos );

        // Keeps track of all possible numbers for all positions
        // TODO: move to solver
        Cell m_oPossibleNumbers[9][9];

        int m_iProgressRows[9];     // How many unsolved cells remains in row   ( used for quicker solving for rows   )
        int m_iProgressColumns[9];  // How many unsolved cells remains in column( used for quicker solving for column )
        int m_iProgressSquares[9];  // How many unsolved cells remains in square( used for quicker solving for square )

        bool m_bLookedPositions[9][9];  // Which positions can be changed?
        bool m_bGuessMode;
        bool m_bErrorFound;
        short m_shBoard[9][9];          // The SuDoku board

        int m_iUnsolvedPosCount;        		// The number of unsolved positions.
        std::vector<vector2d> m_vUnsolvedPositions; 	// All unsolved positions
};
