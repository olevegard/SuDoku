#pragma once
#include "Vector2d.h"
#include <sstream>
#include <iostream>

struct CSuDokuCell
{
CSuDokuCell()
    : bSolved(false)


    , shHiddenDouble1(0)
    , shHiddenDouble2(0)
    , shHiddenDouble3(0)

    , m_shCountPossible(9)
    , shDigit(0)
    , m_bPossibleNumbers({true,true,true,true,true,true,true,true,true})
    {
    }


    // Sets the digit and marks as solved
    void setAndMarkAsSolved( short iDigit );
    void addPossibleDigit( const short shDigit );
    bool removePossibleDigit( const short shDigit );

    short tryToSolveCell();

    void removeAllExceptPair ( const short shDigit1, const short shDigit2 );


    void resetHiddenDouble();


    // Gets
    short isPossible( const short shDigit1, const short shDigit2 ) const;
    bool isPossible( short shDigit ) const;
    bool isSolved() const;
    short getSolvedDigitP1() const;
    std::string print( ) const;

    short getHiddenDouble1() const
    {
        return shHiddenDouble1;
    }

    short getHiddenDouble2() const
    {
        return shHiddenDouble2;
    }

    short getHiddenDouble3() const
    {
        return shHiddenDouble3;
    }

    void setHiddenDouble1( short iDigit )
    {
        shHiddenDouble1 = iDigit;
    }

    void setHiddenDouble2( short iDigit )
    {
        shHiddenDouble2 = iDigit;
    }

    void setHiddenDouble3( short iDigit )
    {
        shHiddenDouble3 = iDigit;
    }

    short getCountPossible()
    {
        return m_shCountPossible;
    }

// Variables
private:
    bool bSolved;

    short shHiddenDouble1;
    short shHiddenDouble2;
    short shHiddenDouble3;

    short m_shCountPossible;

    short shDigit;
    bool m_bPossibleNumbers[9];
};// End of Cell struct...


// opeator << defined outside of namespace as it should be
inline std::ostream& operator<<(std::ostream& stream, const CSuDokuCell& cell)
{

    stream << cell.print();
    return stream;
}
inline bool isNakedPair( CSuDokuCell &cell1, CSuDokuCell &cell2 )
{
    short shCountPossible = 0;

    if ( cell1.isSolved() || cell2.isSolved() )
        return false;

    for ( short i = 0; i < 9; ++i)
    {
        if ( cell1.isPossible(i) != cell2.isPossible(i) )
            return false;

        if ( cell1.isPossible(i) )
        {
            if ( shCountPossible == 0)
            {
                cell1.setHiddenDouble1( i + 1);
                cell2.setHiddenDouble1( i + 1);
            } else
            {
                cell1.setHiddenDouble2( i + 1 );
                cell2.setHiddenDouble2( i + 1 );
            }

            ++shCountPossible;
        }
    }

    return ( shCountPossible == 2 );
}
inline bool isNakedTriplets( CSuDokuCell &cell1, CSuDokuCell &cell2, CSuDokuCell &cell3  )
{
    if ( false )
        std::cout << "   Cell.h@" << __LINE__ << ": Checking for naked triplets....\n";

    // If any of the three positions are solved allready
    if ( cell1.isSolved() || cell2.isSolved() || cell3.isSolved() )
        return false;

    // If any of the three Cells have less than two or more than three possible digits
    if (
           cell1.getCountPossible() > 3 || cell1.getCountPossible() < 2
        || cell2.getCountPossible() > 3 || cell2.getCountPossible() < 2
        || cell3.getCountPossible() > 3 || cell3.getCountPossible() < 2
    )
    {
        //std::cout << "One or more colums has more than 3 or less than two possibilities!\n";
        return false;
    }
    if ( false )
        std::cout << "=====================Checking tirplet===============================\n"
            << "Cell 1 : " << cell1.print() << std::endl
            << "Cell 2 : " << cell2.print() << std::endl
            << "Cell 3 : " << cell3.print() << std::endl;

    short shCountPossibleCell1 = 0;
    short shCountPossibleCell2 = 0;
    short shCountPossibleCell3 = 0;
    bool bFound[] = {
        false, false, false,
        false, false, false,
        false, false, false
    };
    cell1.resetHiddenDouble();
    cell2.resetHiddenDouble();
    cell3.resetHiddenDouble();

    // Put all possible triplets in the struct member values...
    for ( short i = 0; i < 9; ++i)
    {
        if ( cell1.isPossible(i) )
        {
            ++shCountPossibleCell1;
            bFound[i] = true;

            if ( false )
                std::cout << "possible in cell 1 : " << i + 1 << " Count : " << shCountPossibleCell1 << std::endl;

            if ( shCountPossibleCell1 == 1 )
                cell1.setHiddenDouble1( i );

            else if ( shCountPossibleCell1 == 2 )
                cell1.setHiddenDouble2( i );

            else if ( shCountPossibleCell1 == 3 )
                cell1.setHiddenDouble3( i );

            else
            {
                if ( false )
                    std::cout << "   Too many digits in cell 1...\n";
                return false;
            }
        }
        if ( cell2.isPossible(i) )
        {
            ++shCountPossibleCell2;

            bFound[i] = true;

            if ( false )
                std::cout << "possible in cell 2 : " << i + 1 << std::endl;

            if ( shCountPossibleCell2 == 1 )
                cell2.setHiddenDouble1( i );

            else if ( shCountPossibleCell2 == 2 )
                cell2.setHiddenDouble2( i );

            else if ( shCountPossibleCell2 == 3 )
                cell2.setHiddenDouble3( i );

            else
            {
                if ( false )
                    std::cout << "   Too many digits in cell 2...\n";
                return false;
            }

        }
        if ( cell3.isPossible(i) )
        {
            ++shCountPossibleCell3;

            bFound[i] = true;

            if ( false )
                std::cout << "possible in cell 3 : " << i + 1 << std::endl;

            if ( shCountPossibleCell3 == 1 )
                cell3.setHiddenDouble1( i );

            else if ( shCountPossibleCell3 == 2 )
                cell3.setHiddenDouble2( i );

            else if ( shCountPossibleCell3 == 3 )
                cell3.setHiddenDouble3( i );

            else
            {
                if ( false )
                    std::cout << "   Too many digits in cell 3...\n";
                return false;
            }
        }
    }

    // Make sure obly 3 unique numbers exists...
    int iCountUnique = 0;
    for ( int i = 0; i < 9; ++i)
    {
        if ( bFound[i] )
            ++iCountUnique;
    }

    if ( iCountUnique > 3 )
        return false;



}
bool CompareHiddehDoubles_3( /*const CSodukCell &cell1, const CSuDokuCell &cell2, const CSuDokuCell &cell3 */)
{

    /* TODO malke this into a generic function!
    if (
           iCell1Double1 != cell2.shHiddenDouble1
        && iCell1Double1 != cell2.shHiddenDouble2
        && iCell1Double1 != cell2.shHiddenDouble3
        && iCell1Double1 != cell3.shHiddenDouble1
        && iCell1Double1 != cell3.shHiddenDouble2
        && iCell1Double1 != cell3.shHiddenDouble3

    )
        return false;


      */

    /*
    short iCell1Double1 = cell1.getHiddenDouble1();
    short iCell1Double2 = cell1.getHiddenDouble2();
    short iCell1Double3 = cell1.getHiddenDouble3();

    short iCell2Double1 = cell2.getHiddenDouble1();
    short iCell2Double2 = cell2.getHiddenDouble2();
    short iCell2Double3 = cell2.getHiddenDouble3();

    short iCell3Double1 = cell3.getHiddenDouble1();
    short iCell3Double2 = cell3.getHiddenDouble2();
    short iCell3Double3 = cell3.getHiddenDouble3();
*/

    /*
    // Print all possible numbers
    if ( false )
        std::cout
            << "Cell 1 : " << iCell1Double1 + 1 << " , " << cell1.shHiddenDouble2 + 1 << " , " << cell1.shHiddenDouble3 + 1
            << "\nCell 2 : " << cell2.shHiddenDouble1 + 1 << " , " << cell2.shHiddenDouble2 + 1 << " , " << cell2.shHiddenDouble3 + 1
            << "\nCell 3 : " << cell3.shHiddenDouble1 + 1 << " , " << cell3.shHiddenDouble2 + 1 << " , " << cell3.shHiddenDouble3 + 1 << std::endl;


    // Cell 1 - hidden triple 1
    if (
           iCell1Double1 != cell2.shHiddenDouble1
        && iCell1Double1 != cell2.shHiddenDouble2
        && iCell1Double1 != cell2.shHiddenDouble3
        && iCell1Double1 != cell3.shHiddenDouble1
        && iCell1Double1 != cell3.shHiddenDouble2
        && iCell1Double1 != cell3.shHiddenDouble3

    )
        return false;
    //
    // Cell 1 - hidden triple 2
    if (
           cell1.shHiddenDouble2 != cell2.shHiddenDouble1
        && cell1.shHiddenDouble2 != cell2.shHiddenDouble2
        && cell1.shHiddenDouble2 != cell2.shHiddenDouble3
        && cell1.shHiddenDouble2 != cell3.shHiddenDouble1
        && cell1.shHiddenDouble2 != cell3.shHiddenDouble3
        && cell1.shHiddenDouble2 != cell3.shHiddenDouble3
    )
        return false;

    // Cell 1 - hidden triple 3
    if ( cell1.m_shCountPossible == 3)
    {
        if (
               cell1.shHiddenDouble3 != cell2.shHiddenDouble1
            && cell1.shHiddenDouble3 != cell2.shHiddenDouble2
            && cell1.shHiddenDouble3 != cell2.shHiddenDouble3
            && cell1.shHiddenDouble3 != cell3.shHiddenDouble1
            && cell1.shHiddenDouble3 != cell3.shHiddenDouble2
            && cell1.shHiddenDouble3 != cell3.shHiddenDouble3

        )
            return false;
    }

    // Cell 2 - hidden triple 1
    if (
           cell2.shHiddenDouble1 != cell1.shHiddenDouble1
        && cell2.shHiddenDouble1 != cell1.shHiddenDouble2
        && cell2.shHiddenDouble1 != cell1.shHiddenDouble3
        && cell2.shHiddenDouble1 != cell3.shHiddenDouble1
        && cell2.shHiddenDouble1 != cell3.shHiddenDouble2
        && cell2.shHiddenDouble1 != cell3.shHiddenDouble3

    )
        return false;
    // Cell 2 - hidden triple 2
    if (
           cell2.shHiddenDouble2 != cell1.shHiddenDouble1
        && cell2.shHiddenDouble2 != cell1.shHiddenDouble2
        && cell2.shHiddenDouble2 != cell1.shHiddenDouble3
        && cell2.shHiddenDouble2 != cell3.shHiddenDouble1
        && cell2.shHiddenDouble2 != cell3.shHiddenDouble3
        && cell2.shHiddenDouble2 != cell3.shHiddenDouble3
    )
        return false;

    // Cell 2 - hidden triple 3
    if ( cell2.m_shCountPossible == 3)
    {
        if (
               cell2.shHiddenDouble3 != cell1.shHiddenDouble1
            && cell2.shHiddenDouble3 != cell1.shHiddenDouble2
            && cell2.shHiddenDouble3 != cell1.shHiddenDouble3
            && cell2.shHiddenDouble3 != cell3.shHiddenDouble1
            && cell2.shHiddenDouble3 != cell3.shHiddenDouble2
            && cell2.shHiddenDouble3 != cell3.shHiddenDouble3

        )
            return false;
    }

    // Cell 3 - hidden triple 1
    if (
           cell3.shHiddenDouble1 != cell1.shHiddenDouble1
        && cell3.shHiddenDouble1 != cell1.shHiddenDouble2
        && cell3.shHiddenDouble1 != cell1.shHiddenDouble3
        && cell3.shHiddenDouble1 != cell2.shHiddenDouble1
        && cell3.shHiddenDouble1 != cell2.shHiddenDouble2
        && cell3.shHiddenDouble1 != cell2.shHiddenDouble3

    )
        return false;
    // Cell 3 - hidden triple 2
    if (
           cell3.shHiddenDouble2 != cell1.shHiddenDouble1
        && cell3.shHiddenDouble2 != cell1.shHiddenDouble2
        && cell3.shHiddenDouble2 != cell1.shHiddenDouble3
        && cell3.shHiddenDouble2 != cell2.shHiddenDouble1
        && cell3.shHiddenDouble2 != cell2.shHiddenDouble3
        && cell3.shHiddenDouble2 != cell2.shHiddenDouble3
    )
        return false;

    // Cell 3 - hidden triple 3
    if ( cell3.m_shCountPossible == 3)
    {
        if (
               cell3.shHiddenDouble3 != cell1.shHiddenDouble1
            && cell3.shHiddenDouble3 != cell1.shHiddenDouble2
            && cell3.shHiddenDouble3 != cell1.shHiddenDouble3
            && cell3.shHiddenDouble3 != cell2.shHiddenDouble1
            && cell3.shHiddenDouble3 != cell2.shHiddenDouble2
            && cell3.shHiddenDouble3 != cell2.shHiddenDouble3

        )
            return false;
    }*/

    return true;
}

// Returns true if shDigit is possible in this Cell and in the argument cell.
// Returns false otherwise
bool isPairingPossibleDigit ( const CSuDokuCell &cell1, const CSuDokuCell &cell2, const short shDigit ) {
    if ( cell1.isPossible( shDigit ) && cell2.isPossible( shDigit ) )
        return true;
    else
        return false;
}
