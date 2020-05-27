#pragma once

#include <ChessGame/Player.hpp>

class DummyPlayer : public Player
{
public:
    DummyPlayer(ChessGame& game, PlayerColor color) :
        Player(game, color)
    {}

    void yourTurnCallback() override;
    void gameEndedCallback(bool) override;
    PieceType promotionResponse() override;
    void update();


protected:
    bool yourTurn_ = false;
    bool isPlaying = true;
};
