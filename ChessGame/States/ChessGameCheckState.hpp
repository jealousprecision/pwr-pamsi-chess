#pragma once

#include <ChessGame/States/IChessGameState.hpp>

class ChessGame;

class ChessGameCheckState : public IChessGameState
{
public:
    ChessGameCheckState(ChessGame& game) :
        game_(game)
    {}

    void update() override;

protected:
    ChessGame& game_;
};
