#pragma once

#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameData.hpp>

class PlayerAi : public Player
{
public:
    PlayerAi(ChessGame& game, PlayerColor color);

    void yourTurnCallback() override;
    void gameEndedCallback(bool won) override;
    PieceType promotionResponse() override;

protected:
    bool isPlaying_ = true;
};
