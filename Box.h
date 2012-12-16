#pragma once
#include "Vector2d.h"
struct Box{
    Box()
        // Set all of bRowX and bColumnX to false.
        :   bRow1   ({false,false,false,false,false,false,false,false,false})
        ,   bRow2   ({false,false,false,false,false,false,false,false,false})
        ,   bRow3   ({false,false,false,false,false,false,false,false,false})
        ,   bColumn1({false,false,false,false,false,false,false,false,false})
        ,   bColumn2({false,false,false,false,false,false,false,false,false})
        ,   bColumn3({false,false,false,false,false,false,false,false,false})

    {
        //std::cout << "Box initialized\n";
    }
    // Adds a position to the box.
    void add(const vector2d &pos, short shDigit){
        // 1 : 0,1,2
        // 2 : 3,4,5
        // 3 : 6,7,8

        short shColumn = pos.x % 3;
        short shRow = pos.y % 3;
        --shDigit;
       // --shDigit;

        if ( shColumn == 0 )
           bColumn1[shDigit] = true;

        else if ( shColumn == 1 )
           bColumn2[shDigit] = true;

        else if ( shColumn == 2 )
            bColumn3[shDigit] = true;

        if ( shRow == 0 )
            bRow1[shDigit] = true;

        else if ( shRow == 1 )
            bRow2[shDigit] = true;

        else if ( shRow == 2 )
            bRow3[shDigit] = true;


        //std::cout << shDigit + 1 << " added for " << shColumn << " , " << shRow << std::endl;

    }
    // Remove a digit from the list of posible locations
    void remove( const vector2d &pos, short shDigit ) {
        short shColumn = pos.x % 3;
        short shRow = pos.y % 3;
        --shDigit;

        if ( shColumn == 0 )
           bColumn1[shDigit] = false;

        else if ( shColumn == 1 )
           bColumn2[shDigit] = false;

        else if ( shColumn == 2 )
            bColumn3[shDigit] = false;

        if ( shRow == 0 )
            bRow1[shDigit] = false;

        else if ( shRow == 1 )
            bRow2[shDigit] = false;

        else if ( shRow == 2 )
            bRow3[shDigit] = false;

    }
    // Checks all pbRowositions again.
    void recheck(){
        std::cout << "Rows : \n";
        for ( int i = 0; i < 9; ++i ){
            if ( !bRow1[i])
                std::cout << i + 1 << " , can't be placed in row 1\n";
            else
                std::cout << i + 1 << " , can be placed in row 1\n";

            if ( !bRow2[i])
                std::cout << i + 1 << " , can't be placed in row 2\n";
            else
                std::cout << i + 1 << " , can be placed in row 2\n";

            if ( !bRow3[i])
                std::cout << i + 1 << " , can't be placed in row 3\n";
            else
                std::cout << i + 1 << " , can be placed in row 3\n";

            std::cout << std::endl;

        }

        //std::cout << "Column : \n";
        for ( int i = 0; i < 9; ++i ){
            if ( !bColumn1[i])
                std::cout << i + 1 << " , can't be placed in column 1\n";
            else
                std::cout << i + 1 << " , can be placed in column 1\n";

            if ( !bColumn2[i])
                std::cout << i + 1 << " , can't be placed in column 2\n";
            else
                std::cout << i + 1 << " , can be placed in column 2\n";

            if ( !bColumn3[i])
                std::cout << i + 1 << " , can't be placed in column 3\n";
            else
                std::cout << i + 1 << " , can be placed in column 3\n";

            //std::cout << std::endl;

        }

        //std::cout << std::endl << std::endl;

    }

    short shDigits[3][3]; // Contains the possible digits for all positions within this box 3 x 3 box.

    bool bRow1[9];      // Can digit x be placed in this row? Initialized to false
    bool bRow2[9];      // Can digit x be placed in this row? Initialized to false
    bool bRow3[9];      // Can digit x be placed in this row? Initialized to false

    bool bColumn1[9];   // Can digit x be placed in this column? Initialized to false
    bool bColumn2[9];   // Can digit x be placed in this column? Initialized to false
    bool bColumn3[9];   // Can digit x be placed in this column? Initialized to false

};
