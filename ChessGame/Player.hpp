#pragma once

#include <Observer/Observer.hpp>
#include <ChessGame/Enums.hpp>

class ChessGame;

class Player
{
public:
    Player(ChessGame& game, PlayerColor color);

    virtual void yourTurnSlot() = 0;
    virtual void gameEndedSlot(bool won) = 0;
    PlayerColor getPlayerColor() const;

protected:
    ChessGame& game_;
    PlayerColor color_;
};
