#pragma once

#include <algorithm>
#include "Digit.h"

struct BoardStatus
{

	BoardStatus()
#ifdef __unix__
		:  m_iProgressRows     ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
		,  m_iProgressColumns  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
		,  m_iProgressSquares  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
		,  m_iUnsolvedPosCount ( 0 )
#else
		:  m_iUnsolvedPosCount ( 0 )
#endif
		,  m_vUnsolvedPositions( 0 )
		{
			for ( int i = 0; i < ( 9 * 9 ); ++i)
			{
				int iX = i % 9;
				int iY = i / 9;

				m_vUnsolvedPositions.push_back( Digit( vector2d(iX, iY) ) );
				m_iUnsolvedPosCount++;
					
				m_bDigitFoundInRow[iX][iY] = false;
			}
		}

	void UpdateSolveInformation( const vector2d &pos)
	{
		removeFromListOfUnsolvedPositions(pos);

		++m_iProgressColumns[pos.x];
		++m_iProgressRows[pos.y];
		++m_iProgressSquares[ pos.x / 3 + (( pos.y / 3) * 3 )];
	}

	void removeFromListOfUnsolvedPositions( const vector2d &pos )
	{

		std::vector<Digit>::iterator p;

		p = std::find( m_vUnsolvedPositions.begin(), m_vUnsolvedPositions.end(), pos );

		if ( p != m_vUnsolvedPositions.end() )
		{
			m_vUnsolvedPositions.erase( p );

		}
		
		erasePosition( pos );

	}

	void erasePosition( const vector2d& pos )
	{
		--m_iUnsolvedPosCount;

		--m_iProgressRows[pos.x];
		--m_iProgressColumns[pos.y];
	}

	bool IsDigitFoundInRow( short iRow, short iDigit ) const
	{
		return m_bDigitFoundInRow[iRow][iDigit];
	}

	void SetDigitFoundInRow( short iRow, short iDigit )
	{
		m_bDigitFoundInRow[iRow][iDigit] = true;
	}
	// Arrays storiing progress for row/column/squares
	// Used for optimization purposes
	int m_iProgressRows[9];
	int m_iProgressColumns[9];
	int m_iProgressSquares[9];

	// The number of unsolved positions.
	int m_iUnsolvedPosCount;

	// All unsolved positions
	std::vector<Digit> m_vUnsolvedPositions;
private:
	bool m_bDigitFoundInRow[9][9];
};



