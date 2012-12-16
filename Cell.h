#pragma once
#include "Vector2d.h"
#include <sstream>

struct Cell
{
Cell()
    : bSolved(false)


    , shHiddenDouble1(0)
    , shHiddenDouble2(0)
    , shHiddenDouble3(0)

    , m_shCountPossible(9)
    , shDigit(0)
    , m_bPossibleNumbers({true,true,true,true,true,true,true,true,true})
    {
    }

// Compare two rows.
// Returns true if hidden pair.
bool operator==( const Cell &cell ){

    // Don't consider cell pairs where on of them is solved.
    if ( bSolved || cell.bSolved)
        return false;

    int iCount = 0;

    for ( int i = 0; i < 9; ++i ) {

        if ( m_bPossibleNumbers[i] && cell.m_bPossibleNumbers[i] )
            ++iCount;

        if (m_bPossibleNumbers[i] != cell.m_bPossibleNumbers[i] )
            return false;
    }

    return (iCount == 2);
}

void set( short iDigit )
{
    // Remove all digits and decrement count possible
    for ( short i = 0; i < 9; ++i )
    {
        remove(i);
    }

    shDigit = iDigit + 1;

}

void add( const short shDigit ) {
    m_bPossibleNumbers[shDigit - 1] = true;
    ++m_shCountPossible;
}

bool remove( const short shDigit ) {
    bool bRemoved = m_bPossibleNumbers[shDigit];
    m_bPossibleNumbers[shDigit] = false;

    if ( bRemoved )
        --m_shCountPossible;

    return bRemoved;
}

short solve(){
    int iCount = 0;
    int iLast = 0;

    for ( int i = 0; i < 9; ++i )
    {

        if ( m_bPossibleNumbers[i]  )
        {
            ++iCount;
            if ( iLast == 0)
                iLast = i;

        }

    }

    if ( iCount == 1) {
        m_bPossibleNumbers[iLast] = false;
        shDigit = ++iLast;
        bSolved = true;
        return iLast;
    } else
        return 0;

}
// Returns true if shDigit is possible in this Cell and in the argument cell.
// Returns false otherwise
bool isPairingPossibleDigit ( const Cell &cell, const short shDigit ) {
    if ( m_bPossibleNumbers[shDigit] && cell.m_bPossibleNumbers[shDigit] )
        return true;
    else
        return false;
}

short countPossibleOfPair( const short shDigit1, const short shDigit2)
{
    if ( bSolved )
        return 0;

    short shCount = 0;

    if ( m_bPossibleNumbers[shDigit1] )
        ++shCount;

    if ( m_bPossibleNumbers[shDigit2] )
        ++shCount;

    return shCount;
}
void removeAllExceptPair ( const short shDigit1, const short shDigit2 )
{
    for ( short shCurrentDigit = 1; shCurrentDigit < 9; ++shCurrentDigit )
    {
        if ( shCurrentDigit == shDigit1 || shCurrentDigit == shDigit2 )
            continue;

        m_bPossibleNumbers[shCurrentDigit - 1] = false;

    }
}


bool isPossibleTriplet( const short shCellNr )
{
    short shCount = 0;

    for ( short sh = 0; sh < 9; ++sh )
    {
        if ( m_bPossibleNumbers[sh] )
            ++shCount;

        if ( shCount < 3 )
            return true;

    }

    return ( shCount > 0 && shCount <= 3 );

}
bool isNakedPair( const Cell &cell )
{
    short shCountPossible = 0;

    if ( bSolved || cell.bSolved)
        return false;

    for ( short i = 0; i < 9; ++i)
    {
        if ( m_bPossibleNumbers[i] != cell.m_bPossibleNumbers[i])
            return false;

        if ( m_bPossibleNumbers[i])
        {
            if ( shCountPossible == 0)
            {
                shHiddenDouble1 = i + 1;
            } else
            {
                shHiddenDouble2 = i + 1;
            }

            ++shCountPossible;
        }
    }

    return ( shCountPossible == 2 );
}

void resetHiddenDouble()
{
    shHiddenDouble1 = -1;
    shHiddenDouble2 = -1;
    shHiddenDouble3 = -1;
}
bool isPossiblePair( const Cell &cell )
{
    if ( bSolved || cell.bSolved)
        return false;

    short shCountPossible = 0;

    for ( short i = 0; i < 9; ++i)
    {
        // if the two are matching
        if ( m_bPossibleNumbers[i] == cell.m_bPossibleNumbers[i] && m_bPossibleNumbers[i])
        {
            if ( shCountPossible == 0)
            {
                shHiddenDouble1 = i + 1;
            } else
            {
                shHiddenDouble2 = i + 1;
            }

            ++shCountPossible;
        }
    }

    return ( shCountPossible == 2 );
}

bool isPossible( short shDigit ) const
{
    return m_bPossibleNumbers[ shDigit];
}

inline bool operator[](const short shDigit )
{
    return m_bPossibleNumbers[shDigit];
}
short getSolvedDigitP1()
{
    return shDigit + 1;
}

std::string print( ) const
{
    std::stringstream stream;
    if ( bSolved )
        stream << " - Solved : " << shDigit;
	else {
		stream << " - Unsolved : ";

		for ( short i = 0; i < 9; ++i ) {
			if ( isPossible(i) )
				stream << " " << ( i + 1);
		}

		stream << " possible : " << m_shCountPossible;
	}
    return stream.str();
}

	bool bSolved;


	short shHiddenDouble1;
	short shHiddenDouble2;
	short shHiddenDouble3;

	short m_shCountPossible;
private:
    short shDigit;
    bool m_bPossibleNumbers[9];
};// End of Cell struct... 

// opeator << defined outside of namespace as it should be
inline std::ostream& operator<<(std::ostream& stream, const Cell& cell)
{

	stream << cell.print();
	return stream;
}

inline bool isNakedTriplets( Cell &cell1, Cell &cell2, Cell &cell3  ) 
{
	if ( false )
		std::cout << "   Cell.h@" << __LINE__ << ": Checking for naked triplets....\n";

	// If any of the three positions are solved allready
	if ( cell1.bSolved || cell2.bSolved || cell3.bSolved )
		return false;

	// If any of the three Cells have less than two or more than three possible digits
	if (
		   cell1.m_shCountPossible > 3 || cell1.m_shCountPossible < 2
		|| cell2.m_shCountPossible > 3 || cell2.m_shCountPossible < 2
		|| cell3.m_shCountPossible > 3 || cell3.m_shCountPossible < 2
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
				cell1.shHiddenDouble1 = i;
			else if ( shCountPossibleCell1 == 2 )
				cell1.shHiddenDouble2 = i;
			else if ( shCountPossibleCell1 == 3 )
				cell1.shHiddenDouble3 = i;
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
				cell2.shHiddenDouble1 = i;
			else if ( shCountPossibleCell2 == 2 )
				cell2.shHiddenDouble2 = i;
			else if ( shCountPossibleCell2 == 3 )
				cell2.shHiddenDouble3 = i;
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
				cell3.shHiddenDouble1 = i;
			else if ( shCountPossibleCell3 == 2 )
				cell3.shHiddenDouble2 = i;
			else if ( shCountPossibleCell3 == 3 )
				cell3.shHiddenDouble3 = i;
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

	// Print all possible numbers
        if ( false )
        std::cout
            << "Cell 1 : " << cell1.shHiddenDouble1 + 1 << " , " << cell1.shHiddenDouble2 + 1 << " , " << cell1.shHiddenDouble3 + 1
            << "\nCell 2 : " << cell2.shHiddenDouble1 + 1 << " , " << cell2.shHiddenDouble2 + 1 << " , " << cell2.shHiddenDouble3 + 1
            << "\nCell 3 : " << cell3.shHiddenDouble1 + 1 << " , " << cell3.shHiddenDouble2 + 1 << " , " << cell3.shHiddenDouble3 + 1 << std::endl;

	// Cell 1 - hidden triple 1
	if (
		   cell1.shHiddenDouble1 != cell2.shHiddenDouble1
		&& cell1.shHiddenDouble1 != cell2.shHiddenDouble2
		&& cell1.shHiddenDouble1 != cell2.shHiddenDouble3
		&& cell1.shHiddenDouble1 != cell3.shHiddenDouble1
		&& cell1.shHiddenDouble1 != cell3.shHiddenDouble2
		&& cell1.shHiddenDouble1 != cell3.shHiddenDouble3
		
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
	}	

	return true;
/*
	if (       shHiddenDouble2 == cell1.shHiddenDouble1
		|| shHiddenDouble2 == cell1.shHiddenDouble2
		|| shHiddenDouble2 == cell1.shHiddenDouble3
	)
		
	if (       shHiddenDouble3 == cell1.shHiddenDouble1
		|| shHiddenDouble3 == cell1.shHiddenDouble2
		|| shHiddenDouble3 == cell1.shHiddenDouble3
	)
		bTriplet = true;

	if ( !bTriplet ) 
		return false;

	// Cell 1 pair in cell 3
	bTriplet = false;
	
	if (       shHiddenDouble1 == cell2.shHiddenDouble1
		|| shHiddenDouble1 == cell2.shHiddenDouble2
		|| shHiddenDouble1 == cell2.shHiddenDouble3
	)
		bTriplet = true;

	if (       shHiddenDouble2 == cell2.shHiddenDouble1
		|| shHiddenDouble2 == cell2.shHiddenDouble2
		|| shHiddenDouble2 == cell2.shHiddenDouble3
	)
		
	if (       shHiddenDouble3 == cell2.shHiddenDouble1
		|| shHiddenDouble3 == cell2.shHiddenDouble2
		|| shHiddenDouble3 == cell2.shHiddenDouble3
	)
		bTriplet = true;

	if ( !bTriplet ) 
		return false;

	// Cell 2 pair in cell 3
	bTriplet = false;
	
	if (       cell1.shHiddenDouble1 == cell2.shHiddenDouble1
		|| cell1.shHiddenDouble1 == cell2.shHiddenDouble2
		|| cell1.shHiddenDouble1 == cell2.shHiddenDouble3
	)
		bTriplet = true;

	if (       cell1.shHiddenDouble2 == cell2.shHiddenDouble1
		|| cell1.shHiddenDouble2 == cell2.shHiddenDouble2
		|| cell1.shHiddenDouble2 == cell2.shHiddenDouble3
	)
		
	if (       cell1.shHiddenDouble3 == cell2.shHiddenDouble1
		|| cell1.shHiddenDouble3 == cell2.shHiddenDouble2
		|| cell1.shHiddenDouble3 == cell2.shHiddenDouble3
	)
		bTriplet = true;

	if ( !bTriplet ) 
		return false;
	
	return true;
*
	// Check if shHiddenDouble1 exists in cell 2
	if (  shHiddenDouble1 == cell1.shHiddenDouble1 && shHiddenDouble1 > 0)
		std::cout << "found in cell 1 and 2 : " << shHiddenDouble1 + 1 << " = " << cell1.shHiddenDouble1 + 1 << std::endl;
	if (  shHiddenDouble1 == cell1.shHiddenDouble2 && shHiddenDouble1 > 0)
		std::cout << "found in cell 1 and 2 : " << shHiddenDouble1 + 1 << " = " << cell1.shHiddenDouble2 + 1 << std::endl;
	if (  shHiddenDouble1 == cell1.shHiddenDouble3 && shHiddenDouble1 > 0)
		std::cout << "found in cell 1 and 2 : " << shHiddenDouble1 + 1 << " = " << cell1.shHiddenDouble3 + 1 << std::endl;

	// Check if shHiddenDouble1 exists in cell 3
	if (  shHiddenDouble1 == cell2.shHiddenDouble1 && shHiddenDouble1 > 0)
		std::cout << "found in cell 1 and 3 : " << shHiddenDouble1 + 1 << " = " << cell2.shHiddenDouble1 + 1 << std::endl;
	if (  shHiddenDouble1 == cell2.shHiddenDouble2 && shHiddenDouble1 > 0)
		std::cout << "found in cell 1 and 3 : " << shHiddenDouble1 + 1 << " = " << cell2.shHiddenDouble2 + 1 << std::endl;
	if (  shHiddenDouble1 == cell2.shHiddenDouble3 && shHiddenDouble1 > 0)
		std::cout << "found in cell 1 and 3 : " << shHiddenDouble1 + 1 << " = " << cell2.shHiddenDouble3 + 1 << std::endl;

	// Check if shHiddenDouble2 exists in cell 2
	if (  shHiddenDouble2 == cell1.shHiddenDouble1 && shHiddenDouble2 > 0)
		std::cout << "found in cell 1 and 2 : " << shHiddenDouble2 + 1 << " = " << cell1.shHiddenDouble1 + 1 << std::endl;
	if (  shHiddenDouble2 == cell1.shHiddenDouble2 && shHiddenDouble2 > 0)
		std::cout << "found in cell 1 and 2 : " << shHiddenDouble2 + 1 << " = " << cell1.shHiddenDouble2 + 1 << std::endl;
	if (  shHiddenDouble2 == cell1.shHiddenDouble3 && shHiddenDouble2 > 0)
		std::cout << "found in cell 1 and 2 : " << shHiddenDouble2 + 1 << " = " << cell1.shHiddenDouble3 + 1 << std::endl;

	// Check if shHiddenDouble2 exists in cell 3
	if (  shHiddenDouble2 == cell2.shHiddenDouble1 && shHiddenDouble2 > 0)
		std::cout << "found in cell 1 and 3 : " << shHiddenDouble2 + 1 << " = " << cell2.shHiddenDouble1 + 1 << std::endl;
	if (  shHiddenDouble2 == cell2.shHiddenDouble2 && shHiddenDouble2 > 0)
		std::cout << "found in cell 1 and 3 : " << shHiddenDouble2 + 1 << " = " << cell2.shHiddenDouble2 + 1 << std::endl;
	if (  shHiddenDouble2 == cell2.shHiddenDouble3 && shHiddenDouble2 > 0)
		std::cout << "found in cell 1 and 3 : " << shHiddenDouble2 + 1 << " = " << cell2.shHiddenDouble3 + 1 << std::endl;

	return
		(  ( shHiddenDouble1 == cell1.shHiddenDouble1 ) && ( shHiddenDouble1 == cell2.shHiddenDouble1 )
		&& ( shHiddenDouble2 == cell1.shHiddenDouble2 ) && ( shHiddenDouble2 == cell2.shHiddenDouble2 )
		&& ( shHiddenDouble3 == cell1.shHiddenDouble3 ) && ( shHiddenDouble3 == cell2.shHiddenDouble3 )
	); **/
}
