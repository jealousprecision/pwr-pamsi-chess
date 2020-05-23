#include "ChessBasicBrancher.hpp"

#include <vector>
#include <functional>
#include <ChessGame/ChessHelpers.hpp>

namespace
{

int getPieceValue(PieceType piece)
{
    switch(piece)
    {
    case PieceType::Pawn:
        return 1;
    case PieceType::Rook:
        return 5;
    case PieceType::Knight:
        return 5;
    case PieceType::Bishop:
        return 5;
    case PieceType::Queen:
        return 20;
    case PieceType::King:
        return 100;
    default:
        throw std::runtime_error("getPossibleMovesForPiece(): bad enum value");
    }
}

int evalGameState(const ChessGameState& source, Ownership player)
{
    int value = 0;

    for (int col = 0; col < 8; ++col)
    {
        for (int row = 0; row < 8; ++row)
        {
            if (source.matrix[col][row].owner == Ownership::None)
                continue;

            if (source.matrix[col][row].owner == player)
                value += getPieceValue(source.matrix[col][row].piece);
            else
                value -= getPieceValue(source.matrix[col][row].piece);
        }
    }

    return value;
}

}  // namespace

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
