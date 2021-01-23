#include "BoardPositionToPossibleMovesMap.hpp"

#include <ChessGame/ChessGameData.hpp>

BoardPosition getBoardPosition_From(const Move& obj)
{
    return BoardPosition{obj.colFrom, obj.rowFrom};
}

uint8_t BoardPositionHash::operator()(BoardPosition pos) const
{
    return static_cast<uint8_t>(pos.col) * 8 + static_cast<uint8_t>(pos.row);
}

bool operator==(BoardPosition lhs, BoardPosition rhs)
{
    return lhs.col == rhs.col && lhs.row == rhs.row;
}
