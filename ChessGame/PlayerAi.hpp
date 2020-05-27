#pragma once

#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameState.hpp>

class PlayerAi : public Player
{
public:
    PlayerAi(ChessGame& game, PlayerColor color);

    void yourTurnCallback() override;
    void gameEndedCallback(bool won) override;
    PieceType promotionResponse() override;
    void update();

protected:
    bool myTurn_ = false;
    bool isPlaying_ = true;
};
