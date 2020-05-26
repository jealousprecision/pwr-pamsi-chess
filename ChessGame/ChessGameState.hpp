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

struct ChessGameState
{
    struct MoveType
    {
        unsigned colFrom, rowFrom;
        unsigned colTo, rowTo;
    };

    ChessGameState();

    void apply(MoveType move)
    {
        matrix[move.colTo][move.rowTo] = matrix[move.colFrom][move.rowFrom];
        matrix[move.colFrom][move.rowFrom] = Field();
    }

    GameMatrix matrix;
};

std::ostream& operator<<(std::ostream& os, const ChessGameState::MoveType& obj);
std::string toString(const ChessGameState::MoveType& obj);
bool operator==(ChessGameState::MoveType lhs, ChessGameState::MoveType rhs);

struct BoardPosition
{
    unsigned col, row;
};

BoardPosition getBoardPosition_From(const ChessGameState::MoveType& obj);

struct BoardPositionHash
{
    uint16_t operator()(BoardPosition pos) const;
};

bool operator==(BoardPosition lhs, BoardPosition rhs);

using BoardPositionToPossibleMovesMap = std::unordered_map<
    BoardPosition, std::vector<ChessGameState::MoveType>, BoardPositionHash>;
