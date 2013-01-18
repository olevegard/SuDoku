#pragma once


#include "SuDokuBoard.h"
#include "SuDokuSolver.h"
#include "BoardStatus.h"


class CBoardManager{


	public:
		CBoardManager()
			:   m_oBoard()
			,   m_oStatus()
			,   m_oSolver()

	{

	}

		void start();


		// Loads the board TODO: load from file or args

		// Load a random board with desired skill level
		void loadBoard( /*int skillLevel*/); // not implemented yet

		// Load a bored stored in file
		//void loadBoard( const char* fileName); // not implemented yet

		// Load a board from cmd line
		void loadBoard( const char* board );

		void solveNext( );




	private:

		void insert( const vector2d &pos, short iDigit );
		CSuDokuBoard m_oBoard;

		BoardStatus m_oStatus;

		CSuDokuSolver m_oSolver;

};
