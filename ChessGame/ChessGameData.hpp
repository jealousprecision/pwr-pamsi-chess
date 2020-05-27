#pragma once

#include <ostream>
#include <vector>
#include <unordered_map>

#include <ChessGame/Enums.hpp>

struct Field
{
    Ownership owner = Ownership::None;
    PieceType piece = PieceType::Unused;
};

using GameMatrix = std::vector<std::vector<Field>>;

struct ChessGameData
{
    struct MoveType
    {
        unsigned colFrom, rowFrom;
        unsigned colTo, rowTo;
    };

    ChessGameData();

    void apply(MoveType move);

    GameMatrix matrix;
};

std::ostream& operator<<(std::ostream& os, const ChessGameData::MoveType& obj);
std::string toString(const ChessGameData::MoveType& obj);
bool operator==(ChessGameData::MoveType lhs, ChessGameData::MoveType rhs);

struct BoardPosition
{
    unsigned col, row;
};

BoardPosition getBoardPosition_From(const ChessGameData::MoveType& obj);

struct BoardPositionHash
{
    uint16_t operator()(BoardPosition pos) const;
};

bool operator==(BoardPosition lhs, BoardPosition rhs);

using BoardPositionToPossibleMovesMap = std::unordered_map<
    BoardPosition, std::vector<ChessGameData::MoveType>, BoardPositionHash>;
