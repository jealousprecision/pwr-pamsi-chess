#pragma once

#include <string>

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

enum class PlayerColor
{
    White,
    Black
};

Ownership toOwnership(PlayerColor color);
PlayerColor negate(PlayerColor color);
std::string toString(PlayerColor color);
