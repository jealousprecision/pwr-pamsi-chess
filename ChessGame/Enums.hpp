#pragma once

#include <string>

enum class PieceType
{
    Unused,
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};

enum class Ownership
{
    None,
    White,
    Black
};

enum class PlayerColor
{
    White,
    Black
};

Ownership toOwnership(PlayerColor color);
PlayerColor negate(PlayerColor color);
std::string toString(PlayerColor color);
