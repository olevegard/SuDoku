#pragma once

#include "SuDokuCell.h"
#include "SuDokuBoard.h"


class CBoardManager{


public:
    CBoardManager()
        :   m_oBoard()
        ,   m_oPossibleNumbers()
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




private:

    // Removes a digit from m_oPossibleNumbers
    void removePossibilitiesInsert( const vector2d &pos, const short shDigit );

    void printAllPosibilities();

    void insert( const vector2d &pos, short iDigit );
    CSuDokuBoard m_oBoard;

    // Keeps track of all possible numbers for all positions
   SuDokuCell::CSuDokuCell m_oPossibleNumbers[9][9];
};
