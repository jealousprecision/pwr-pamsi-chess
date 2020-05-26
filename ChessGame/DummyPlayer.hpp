#pragma once

#include <ChessGame/Player.hpp>

class DummyPlayer : public Player
{
public:
    DummyPlayer(ChessGame& game, PlayerColor color) :
        Player(game, color)
    {}

    void yourTurnSlot() override;
    void gameEndedSlot(bool) override;
    PieceType promotionSlot() override;
    void update();


protected:
    bool yourTurn_ = false;
    bool isPlaying = true;
};
