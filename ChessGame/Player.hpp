#pragma once

#include <ChessGame/Enums.hpp>

class ChessGame;

class Player
{
public:
    virtual ~Player() = default;

    Player(ChessGame& game, PlayerColor color);

    virtual void yourTurnSlot() = 0;
    virtual void gameEndedSlot(bool won) = 0;
    virtual PieceType promotionSlot() = 0;
    PlayerColor getPlayerColor() const;

protected:
    ChessGame& game_;
    PlayerColor color_;
};
