#include "SuDokuCell.h"


void CSuDokuCell::setAndMarkAsSolved( short iDigit )
{
    // Remove all digits and decrement count possible
    for ( short i = 0; i < 9; ++i )
    {
        removePossibleDigit(i);
    }

    bSolved = true;
    shDigit = iDigit + 1;

}

void  CSuDokuCell::addPossibleDigit( const short shDigit )
{
    m_bPossibleNumbers[shDigit - 1] = true;
    ++m_shCountPossible;
}

bool  CSuDokuCell::removePossibleDigit( const short shDigit )
{
    bool bRemoved = m_bPossibleNumbers[shDigit];
    m_bPossibleNumbers[shDigit] = false;

    if ( bRemoved )
        --m_shCountPossible;

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
        shDigit = ++iLast;
        bSolved = true;
        return iLast;
    } else
        return 0;
}




void  CSuDokuCell::removeAllExceptPair ( const short shDigit1, const short shDigit2 )
{
    for ( short shCurrentDigit = 1; shCurrentDigit < 9; ++shCurrentDigit )
    {
        if ( shCurrentDigit == shDigit1 || shCurrentDigit == shDigit2 )
            continue;

        m_bPossibleNumbers[shCurrentDigit - 1] = false;

    }
}

void  CSuDokuCell::resetHiddenDouble()
{
    shHiddenDouble1 = -1;
    shHiddenDouble2 = -1;
    shHiddenDouble3 = -1;
}


bool  CSuDokuCell::isPossible( short shDigit ) const
{
    return m_bPossibleNumbers[shDigit];
}

short CSuDokuCell::isPossible( const short shDigit1, const short shDigit2 ) const
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

bool CSuDokuCell::isSolved() const
{
    return bSolved;
}
short  CSuDokuCell::getSolvedDigitP1() const
{
    return shDigit + 1;
}

std::string  CSuDokuCell::print( ) const
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
