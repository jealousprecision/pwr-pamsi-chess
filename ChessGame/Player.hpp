#pragma once

#include <ChessGame/Enums.hpp>

class ChessGame;

class Player
{
public:
    virtual ~Player() = default;

    Player(ChessGame& game, PlayerColor color);

    virtual void yourTurnCallback() = 0;
    virtual void gameEndedCallback(bool won) = 0;
    virtual PieceType promotionResponse() = 0;

    PlayerColor getPlayerColor() const;

protected:
    ChessGame& game_;
    PlayerColor color_;
};
