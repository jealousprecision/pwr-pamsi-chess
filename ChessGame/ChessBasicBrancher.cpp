#include "ChessBasicBrancher.hpp"

#include <vector>
#include <functional>
#include <ChessGame/ChessHelpers.hpp>

void ChessBasicBrancher::branch(
        const ChessGameState &source,
        GraphList<int, typename ChessGameState::MoveType> &valueGraph)
{
    // basic, depth is only 2
    for (int col = 0; col < 8; ++col)
    {
        for (int row = 0; row < 8; ++row)
        {
            if (source.matrix[col][row].owner == firstBranch_)
            {
                for (auto move : getPossibleMovesForPiece(source, col, row))
                {
                    auto newSource = source;
                    newSource.apply(move);

                    auto vert = valueGraph.addVertex(evalGameState(source, firstBranch_));
                    valueGraph.addEdge(0, vert, move);

                    subBranch_(vert, newSource, valueGraph);
                }
            }
        }
    }
}

void ChessBasicBrancher::subBranch_(
        unsigned srcVert,
        const ChessGameState &source,
        GraphList<int, typename ChessGameState::MoveType> &valueGraph)
{
    auto enemy = firstBranch_ == Ownership::White ? Ownership::Black : Ownership::White;

    for (int col = 0; col < 8; ++col)
    {
        for (int row = 0; row < 8; ++row)
        {
            if (source.matrix[col][row].owner == enemy)
            {
                for (auto move : getPossibleMovesForPiece(source, col, row))
                {
                    auto newSource = source;
                    newSource.apply(move);

                    auto vert = valueGraph.addVertex(evalGameState(source, firstBranch_));
                    valueGraph.addEdge(srcVert, vert, move);
                }
            }
        }
    }
}
