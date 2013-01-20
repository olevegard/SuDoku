#pragma once

#include "Vector2d.h"

class Digit
{
	public:
		Digit()
			:	m_oPosition( -1, -1 )
			,	m_iDigit(-1)
			,	m_bSolved( false )
		{
		}
		Digit( vector2d pos )
			:	m_oPosition( -1, -1 )
			,	m_iDigit(-1)
			,	m_bSolved( false )
		{
			m_oPosition = pos;
		}
		Digit( vector2d pos, short iDigit, bool bSolved)
			:	m_oPosition( -1, -1 )
			,	m_iDigit(-1)
			,	m_bSolved( false )
		{
			m_oPosition = pos;
			m_iDigit = iDigit;
			m_bSolved = bSolved;
		}

		vector2d getPosition() const
		{
			return m_oPosition;
		}

		short getDigit() const
		{
			return m_iDigit;
		}

		bool isSolved() const
		{
			return m_bSolved;
		}
		
		bool operator==( const Digit &digit ) const
		{
			return digit.getPosition() == m_oPosition;
		}

		void setAsSolved( short iDigit )
		{
			m_iDigit = iDigit;
			m_bSolved = true;
		}
	private:
		vector2d m_oPosition;
		short m_iDigit;
		bool m_bSolved;
};


inline std::ostream& operator<<(std::ostream& stream, const Digit& digit )
{
	stream << "Digit ( " << digit.getPosition() << " ) | Solved : ";

	if ( digit.isSolved() )
		stream << "Yes | Value : " << digit.getDigit() + 1 ;
	else 
		stream << "No";

	return stream;
}

inline bool operator<<( const Digit &digit1, const Digit &digit2 )
{
	return digit1.getPosition() ==  digit2.getPosition(); 
}

