#pragma once

#include <ostream>
#include <vector>
#include <unordered_map>

#include <ChessGame/Enums.hpp>
#include <ChessGame/Player.hpp>

struct Move
{
    unsigned colFrom, rowFrom;
    unsigned colTo, rowTo;
};

std::ostream& operator<<(std::ostream& os, const Move& obj);
std::string toString(const Move& obj);
bool operator==(Move lhs, Move rhs);

struct MoveEvent
{
    Player& player;
    Move moveType;
};

struct Field
{
    Ownership owner = Ownership::None;
    PieceType piece = PieceType::Unused;
};

using GameMatrix = std::vector<std::vector<Field>>;

struct ChessGameData
{
    ChessGameData();

    void apply(Move move);

    GameMatrix matrix;
};


