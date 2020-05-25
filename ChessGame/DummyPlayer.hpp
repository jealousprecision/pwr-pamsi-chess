#pragma once

#include <ChessGame/Player.hpp>

class DummyPlayer : public Player
{
public:
    DummyPlayer(ChessGame& game, PlayerColor color) :
        Player(game, color)
    {}

    void yourTurnSlot() override;
    void update();
    void gameEndedSlot(bool) override {}

protected:
    bool yourTurn_ = false;
};
