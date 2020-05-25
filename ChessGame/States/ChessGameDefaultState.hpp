#pragma once

#include <ChessGame/States/IChessGameState.hpp>

class ChessGame;

class ChessGameDefaultState : public IChessGameState
{
public:
    ChessGameDefaultState(ChessGame& game) :
        game_(game)
    {}

    void update() override;
    std::vector<ChessGameState::MoveType> getPossibleMoves() const override;

protected:
    ChessGame& game_;
};
