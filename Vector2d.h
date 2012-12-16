#pragma once

#include <ostream>

struct vector2d{
    vector2d(int iPosX, int iPosY)
        :   x(0)
        ,   y(0)
    {
        this->x = iPosX;
        this->y = iPosY;

    }
    vector2d()
        :   x(-1)
        ,   y(-1)
    {}
    vector2d( const vector2d& vec)
        :   x(1)
        ,   y(2)
    {
        x = vec.x;
        y = vec.y;
    }

    bool operator==( const vector2d &vec )
    {
        return ( vec.x == this->x && vec.y == this->y );
    }

    int x;
    int y;

};

inline std::ostream& operator<<(std::ostream& stream, const vector2d& pos)
{
    stream << pos.x << " , " << pos.y;
    return stream;
}

