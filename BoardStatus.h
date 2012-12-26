struct BoardStatus
{

    BoardStatus()
        :  m_iProgressRows     ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
        ,  m_iProgressColumns  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
        ,  m_iProgressSquares  ( {0, 0, 0, 0, 0, 0, 0, 0, 0} )
        ,  m_iUnsolvedPosCount ( 0 )
        ,  m_vUnsolvedPositions( 0 )
    {
        for ( int i = 0; i < ( 9 * 9 ); ++i)
        {
            int iX = i % 9;
            int iY = i / 9;

            m_vUnsolvedPositions.push_back( vector2d(iX, iY));
            m_iUnsolvedPosCount++;
        }
    }

    void CSuDokuBoard::UpdateSolveInformation( const vector2d &pos)
    {
        removeFromListOfUnsolvedPositions(pos);

        ++m_iProgressColumns[pos.x];
        ++m_iProgressRows[pos.y];
        ++m_iProgressSquares[ pos.x / 3 + (( pos.y / 3) * 3 )];
    }


    // Arrays storiing progress for row/column/squares
    // Used for optimization purposes
    int m_iProgressRows[9];
    int m_iProgressColumns[9];
    int m_iProgressSquares[9];

    // The number of unsolved positions.
    int m_iUnsolvedPosCount;

    // All unsolved positions
    std::vector<vector2d> m_vUnsolvedPositions;


};
