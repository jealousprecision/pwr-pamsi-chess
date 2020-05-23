#pragma once

#include <Observer/Observer.hpp>

class ChessGame;

enum class PlayerColor
{
    White,
    Black
};

class Player : public IObserver
{
public:
    Player(ChessGame& game, PlayerColor color);

    PlayerColor getPlayerColor();

protected:
    ChessGame& game_;
    PlayerColor color_;
};
