#pragma once

#include <vector>

enum class PieceType
{
    Unused,
    King,
    Queen,
    Rook,  // tower
    Bishop,
    Knight, // horse
    Pawn
};

enum class Ownership
{
    None, // When field is empty
    White,
    Black
};

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
        state[move.colTo][move.rowTo] = state[move.colFrom][move.rowFrom];
        state[move.colFrom][move.rowFrom] = Field();
    }

    GameMatrix state;
};
