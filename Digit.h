#pragma once

#include "Vector2d.h"

struct Digit
{
    Digit()
        :   m_vPositions({})
        ,   m_shCount(0)
    {

    }

    void addPosition( const vector2d &pos)
    {
        m_vPositions[m_shCount] = pos;
        ++m_shCount;

    }

    bool IsAlignedOnRow()
    {
        if ( m_shCount == 2 )
            return (m_vPositions[0].y == m_vPositions[1].y);
        else if ( m_shCount == 3 )
            return (
                (m_vPositions[0].y == m_vPositions[1].y) &&
                (m_vPositions[0].y == m_vPositions[2].y)
            );
        else
            return false;
    }

    bool IsAlignedOnColumn()
    {
        if ( m_shCount == 2 )
            return (m_vPositions[0].x == m_vPositions[1].x);
        else if ( m_shCount == 3 )
            return (
                (m_vPositions[0].x == m_vPositions[1].x) &&
                (m_vPositions[0].x == m_vPositions[2].x)
            );
        else
            return false;
    }

    bool isPair(){
        return m_shCount == 2;
    }

    short getCount(){
        return m_shCount;
    }

    bool compare( const Digit &digit )
    {

        std::cout << "positions 1 : " << m_vPositions[0]        << " and " << m_vPositions[1]       << std::endl;
        std::cout << "positions 2 : " << digit.m_vPositions[0]  << " and " << digit.m_vPositions[1] << std::endl;
        return ( ( m_vPositions[0] == digit.m_vPositions[0] )
              && ( m_vPositions[1] == digit.m_vPositions[1] ) );
    }

    vector2d m_vPositions[9];
    short m_shCount;

};

inline std::ostream& operator<<(std::ostream& stream, const Digit& digit){

    stream << "Positions : ";

    for ( short sh = 0; sh < digit.m_shCount; ++sh )
    {
        stream << digit.m_vPositions[sh] << " , ";
    }

    stream << std::endl;

    return stream;

}

