#pragma once

#include <ostream>
#include <vector>

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
