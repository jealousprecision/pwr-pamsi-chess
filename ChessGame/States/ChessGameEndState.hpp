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
    const BoardPositionToPossibleMovesMap& getPossibleMoves() const override;

protected:
    ChessGame& game_;
};
