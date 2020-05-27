#pragma once

#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameState.hpp>

class PlayerAi : public Player
{
public:
    PlayerAi(ChessGame& game, PlayerColor color);

    void yourTurnSlot() override;
    void gameEndedSlot(bool won) override;
    PieceType promotionSlot() override;
    void update();

protected:
    bool myTurn_ = false;
    bool isPlaying_ = true;
};
