#include <cstring>

//#include "Board.h"
#include "BoardManager.h"

int main(int argc, char* argv[] )
{

    CBoardManager brdMan;

    std::cout << "loading...\n";
    if ( argc > 1 && argv[0] )
	{
        brdMan.loadBoard(argv[1]);
        //brd.printBoard();
	}


    //brd.insert()
   /*
    CBoard oBoard;

    if ( argc > 1 )
    {
        short shLength =  strlen(argv[1]);
        vector2d pos(0,0);
        //std::cout << "\n\n\n==========================================================\nBoard : \n";
        for ( int i = 0; i < shLength; ++i)
        {
            short shDigit = 0;
            switch (argv[1][i])
            {
                case '1':
                    shDigit = 1;
                    break;
                case '2':
                    shDigit = 2;
                    break;
                case '3':
                    shDigit = 3;
                    break;
                case '4':
                    shDigit = 4;
                    break;
                case '5':
                    shDigit = 5;
                    break;
                case '6':
                    shDigit = 6;
                    break;
                case '7':
                    shDigit = 7;
                    break;
                case '8':
                    shDigit = 8;
                    break;
                case '9':
                    shDigit = 9;
                    break;
                default:
                    shDigit = 0;
                    break;
            }
            if ( shDigit != 0 ) {
                std::cout << "inserting " << shDigit << " at : " << pos << std::endl;
                oBoard.insert( pos, shDigit, true );
            }

            pos.x++;

            if ( pos.x > 8)
            {
                pos.x = 0;
                pos.y++;
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "No board supplied as loading default\n";
        oBoard.loadBoard();
    }


	oBoard.printBoard();
	std::cin.ignore();

    if ( oBoard.validateEverything() ) {
        std::cout << "everything is valid!\n";
        //printBoard( );
    }

    oBoard.printBoard();

    oBoard.solveEverythingRepeat();

    //oBoard.printBoard();
*/
    return 0;
}
