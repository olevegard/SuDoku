#include "SuDokuCell.h"

namespace SuDokuCell
{
	void CSuDokuCell::setAndMarkAsSolved( short iDigit )
	{
		// Remove all digits and decrement count possible
		removeAllPosibilities();

		m_bSolved = true;
		m_iDigit = iDigit;

	}

	void CSuDokuCell::removeAllPosibilitiesExcept( short iDigit )
	{
		for ( short i = 0; i < 9; ++i )
		{
			if ( i != iDigit )
				removePossibleDigit(i);
		}
	}
/*
	void  CSuDokuCell::addPossibleDigit( const short iDigit )
	{
		m_bPossibleNumbers[ iDigit - 1] = true;
		++m_iCountPossible;
	}
*/
	bool  CSuDokuCell::removePossibleDigit( const short iDigit )
	{
		bool bRemoved = m_bPossibleNumbers[iDigit];
		m_bPossibleNumbers[iDigit] = false;

		if ( bRemoved )
			--m_iCountPossible;

		return bRemoved;
	}

	void CSuDokuCell::removeAllPosibilities()
	{
		for ( short i = 0; i < 9; ++i )
		{
			removePossibleDigit(i);
		}
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
		for ( short iCurrentDigit = 0; iCurrentDigit < 9; ++iCurrentDigit )
		{
			if ( iCurrentDigit == iDigit1 || iCurrentDigit == iDigit2 )
				continue;
			
			remove( iCurrentDigit );
			//m_bPossibleNumbers[iCurrentDigit] = false;
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
		return m_iDigit;
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

	short CSuDokuCell::solve()
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
					//removeAllPosibilitiesExcept(i);
					//removeAllPosibilities(
					setAndMarkAsSolved( i );
					return i;
				}
			}
		}

		return -1;
	} // End struct Cell
	// opeator << defined as a non-member function as it shouold be
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
	// Returns true if shDigit is possible in this Cell and in the argument cell.
	// Returns false otherwise
	bool isPairingPossibleDigit ( const CSuDokuCell &cell1, const CSuDokuCell &cell2, const short shDigit ) {
		if ( cell1.isPossible( shDigit ) && cell2.isPossible( shDigit ) )
			return true;
		else
			return false;
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

	bool compareHelper( const CSuDokuCell &cell, const CSuDokuCell &cell2, const CSuDokuCell &cell3  )
	{
		// Number of digits forund in cell 2 and 3
		short iHitsInCell2 = 0;
		short iHitsInCell3 = 0;

		// Look for a pair that's in either cell2 or cell3
		short iCell1Double1 =  cell.getHiddenDouble1();

		if ( cell2.checkIsHiddenDouble( iCell1Double1 ) )
			++iHitsInCell2;

		if ( cell3.checkIsHiddenDouble( iCell1Double1 ) )
			++iHitsInCell3;

		// Look for a pair that's in either cell2 or cell3
		short iCell1Double2 = cell.getHiddenDouble2();

		if ( cell2.checkIsHiddenDouble( iCell1Double2 ) )
			++iHitsInCell2;

		if ( cell3.checkIsHiddenDouble( iCell1Double2 ) )
			++iHitsInCell3;

		if ( cell.getCountPossible() > 2 )
		{

			short iCell1Double3 = cell.getHiddenDouble3();

			if ( cell2.checkIsHiddenDouble( iCell1Double3 ) )
				++iHitsInCell2;

			if ( cell3.checkIsHiddenDouble( iCell1Double3 ) )
				++iHitsInCell3;

			return ( iHitsInCell2 > 0 && iHitsInCell3 > 0 ) && iHitsInCell2 + iHitsInCell3 == 3;
		} else
			return ( iHitsInCell2 > 0 && iHitsInCell3 > 0 );
	}

	bool CompareHiddehDoubles_3( const CSuDokuCell &cell1, const CSuDokuCell &cell2, const CSuDokuCell &cell3 )
	{
		if ( !compareHelper( cell1, cell2, cell3 ) )
			return false;

		if ( !compareHelper( cell2, cell1, cell3 ) )
			return false;

		if ( !compareHelper( cell3, cell1, cell2 ) )
			return false;

		return true;

		/*l
		// TODO malke this into a generic function!
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
					&& cell2.shitHiddenDouble3 != cell3.shHiddenDouble2
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


}
