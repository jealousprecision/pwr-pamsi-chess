#pragma once

#include <ChessGame/States/IChessGameState.hpp>

class ChessGame;

class ChessGameDefaultState : public IChessGameState
{
public:
    ChessGameDefaultState(ChessGame& game) :
        game_(game)
    {}

    void onInit() override;
    void update() override;
    void onExit() override;
    const BoardPositionToPossibleMovesMap& getPossibleMoves() const override;

protected:
    void initPossibleMoves_();

    ChessGame& game_;
    BoardPositionToPossibleMovesMap possibleMoves_;
};
