#include "SuDokuCell.h"


void CSuDokuCell::setAndMarkAsSolved( short iDigit )
{
	// Remove all digits and decrement count possible
	for ( short i = 0; i < 9; ++i )
	{
		removePossibleDigit(i);
	}

	m_bSolved = true;
	m_iDigit = iDigit + 1;

}

void  CSuDokuCell::addPossibleDigit( const short iDigit )
{
	m_bPossibleNumbers[ iDigit - 1] = true;
	++m_iCountPossible;
}

bool  CSuDokuCell::removePossibleDigit( const short iDigit )
{
	bool bRemoved = m_bPossibleNumbers[iDigit];
	m_bPossibleNumbers[iDigit] = false;

	if ( bRemoved )
		--m_iCountPossible;

	return bRemoved;
}

short  CSuDokuCell::tryToSolveCell()
{
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
		m_iDigit = ++iLast;
		m_bSolved = true;
		return iLast;
	} else
		return 0;
}
void  CSuDokuCell::removeAllExceptPair ( const short iDigit1, const short iDigit2 )
{
	for ( short iCurrentDigit = 1; iCurrentDigit < 9; ++iCurrentDigit )
	{
		if ( iCurrentDigit == iDigit1 || iCurrentDigit == iDigit2 )
			continue;

		m_bPossibleNumbers[iCurrentDigit - 1] = false;

	}
}

void  CSuDokuCell::resetHiddenDouble()
{
	m_iHiddenDouble1 = -1;
	m_iHiddenDouble2 = -1;
	m_iHiddenDouble3 = -1;
}


bool  CSuDokuCell::isPossible( short iDigit ) const
{
	return m_bPossibleNumbers[iDigit];
}

short CSuDokuCell::isPossible( const short iDigit1, const short iDigit2 ) const
{
	if ( m_bSolved )
		return 0;

	short iCount = 0;

	if ( m_bPossibleNumbers[iDigit1] )
		++iCount;

	if ( m_bPossibleNumbers[iDigit2] )
		++iCount;

	return iCount;
}

bool CSuDokuCell::isSolved() const
{
	return m_bSolved;
}
short  CSuDokuCell::getSolvedDigitP1() const
{
	return m_iDigit + 1;
}

std::string  CSuDokuCell::print( ) const
{
	std::stringstream stream;
	if ( m_bSolved )
		stream << " - Solved : " << m_iDigit;
	else
	{
		stream << " - Unsolved : ";

		for ( short i = 0; i < 9; ++i )
		{
			if ( isPossible(i) )
				stream << " " << ( i + 1);
		}

		stream << " possible : " << m_iCountPossible;
	}

	return stream.str();
}
