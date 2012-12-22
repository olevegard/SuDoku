#pragma once

#include "SuDokuCell.h"
#include "SuDokuBoard.h"


class CBoardManager{


public:
    CBoardManager()
        :   m_oBoard()
        ,   m_oCells()
    {

    }
    // Loads the board TODO: load from file or args

    // Load a random board with desired skill level
    void loadBoard( /*int skillLevel*/); // not implemented yet

    // Load a bored stored in file
    void loadBoard( const char* fileName); // not implemented yet

    // Load a board from cmd line
    void loadBoard( const char* board[] );

private:
    CSuDokuBoard m_oBoard;
    SuDokuCell::CSuDokuCell m_oCells;

};
