#pragma once

#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameState.hpp>
#include <MinMax.hpp>

class PlayerAi : public Player
{
public:
    PlayerAi(ChessGame& game);

protected:
    MinMax<ChessGameState> minMax;
};
