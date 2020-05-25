#pragma once

#include "IChessGameState.hpp"

class ChessGame;

class ChessGameEndState : public IChessGameState
{
public:
    ChessGameEndState(ChessGame& game) :
        game_(game)
    {}

    void update() override;
    std::vector<ChessGameState::MoveType> getPossibleMoves() const override;

protected:
    ChessGame& game_;
};
