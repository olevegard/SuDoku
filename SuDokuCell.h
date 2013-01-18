#pragma once


#include "Vector2d.h"
#include <sstream>
#include <iostream>



namespace SuDokuCell
{
struct CSuDokuCell
{

	
	static const bool PRINT_DEBUG   = false;	// Main debugging option.
CSuDokuCell()
	: m_bSolved(false)

	, m_iHiddenDouble1(0)
	, m_iHiddenDouble2(0)
	, m_iHiddenDouble3(0)

	, m_iCountPossible(9)
	, m_iDigit(0)
#ifdef __unix__
	, m_bPossibleNumbers({true,true,true,true,true,true,true,true,true})
#endif
{


}
bool remove( const short shDigit ) {
	bool bRemoved = m_bPossibleNumbers[shDigit];
	m_bPossibleNumbers[shDigit] = false;

	if ( bRemoved )
		--m_iCountPossible;

	return bRemoved;
}

// Sets the digit and marks as solved
void setAndMarkAsSolved( short iDigit );
void addPossibleDigit( const short shDigit );

void removeAllPosibilities();
bool removePossibleDigit( const short shDigit );

short tryToSolveCell();

void removeAllExceptPair ( const short shDigit1, const short shDigit2 );

void resetHiddenDouble();

short solve()
{
	if ( PRINT_DEBUG )
		std::cout << "Solving cell---" << std::endl;

	if (m_bSolved )
	{
		if ( PRINT_DEBUG )
			std::cout << "   Allready solved" << std::endl;

		return -1;
	}

	if ( m_iCountPossible == 1 )
	{
		for ( short i = 0; i < 9; ++i )
		{
			if ( PRINT_DEBUG )
				std::cout << "   Solving digit : " << i << std::endl;

			if ( m_bPossibleNumbers[i] )
			{
				setAndMarkAsSolved( i );
				return i;
			}
		}
	}

	return -1;
}

// Gets
short isPossible( const short shDigit1, const short shDigit2 ) const;
bool  isPossible( short shDigit ) const;

bool  isSolved() const;

// Returns solved digit + 1 so that it will be between 1 and 9
short getSolvedDigitP1() const;

// Used by << operator
std::string print( ) const;

short getHiddenDouble1() const
{
	return m_iHiddenDouble1;
}

short getHiddenDouble2() const
{
	return m_iHiddenDouble2;
}

short getHiddenDouble3() const
{
	return m_iHiddenDouble3;
}

void setHiddenDouble1( short iDigit )
{
	m_iHiddenDouble1 = iDigit;
}

void setHiddenDouble2( short iDigit )
{
	m_iHiddenDouble2 = iDigit;
}

void setHiddenDouble3( short iDigit )
{
	m_iHiddenDouble3 = iDigit;
}

short getCountPossible()
{
	return m_iCountPossible;
}

short checkIsHiddenDouble( short iPossibleDouble ) const
{
	return ( iPossibleDouble == m_iHiddenDouble1
			|| iPossibleDouble == m_iHiddenDouble2
			|| iPossibleDouble == m_iHiddenDouble3 );
}

short getCountPossible() const
{
	return m_iCountPossible;
}

// Variables
private:
bool m_bSolved;

short m_iHiddenDouble1;
short m_iHiddenDouble2;
short m_iHiddenDouble3;

short m_iCountPossible;

short m_iDigit;
bool m_bPossibleNumbers[9];
};// End of Cell struct...

}
