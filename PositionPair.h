#pragma once

#include "Vector2d.h"

struct PositionPair{
    PositionPair()

        :   shDigit1(0)
        ,   m_oPairPos1()
        ,   m_oPairPos2()
    {

    }

     bool operator==( const PositionPair &pair )
     {

         return (
                 ( m_oPairPos1 == pair.m_oPairPos1 )
              && ( m_oPairPos2 == pair.m_oPairPos2 )
            );

     }

    short shDigit1;


    vector2d m_oPairPos1;
    vector2d m_oPairPos2;

};

inline std::ostream& operator<<(std::ostream& stream, const PositionPair& pair){
    stream << "Digit : " << pair.shDigit1 + 1
           << "\n      pos 1 : " << pair.m_oPairPos1
           << "\n      pos 2 : " << pair.m_oPairPos2;

    return stream;
}
