#pragma once

#include <unordered_map>
#include <vector>

class Move;

struct BoardPosition
{
    unsigned col, row;
};

BoardPosition getBoardPosition_From(const Move& obj);

struct BoardPositionHash
{
    uint8_t operator()(BoardPosition pos) const;
};

bool operator==(BoardPosition lhs, BoardPosition rhs);

using BoardPositionToPossibleMovesMap = std::unordered_map<BoardPosition, std::vector<Move>, BoardPositionHash>;
