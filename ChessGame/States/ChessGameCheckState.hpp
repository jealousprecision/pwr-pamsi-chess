#pragma once

#include <ChessGame/States/IChessGameState.hpp>
#include <ChessGame/ChessGameData.hpp>

class ChessGame;

class ChessGameCheckState : public IChessGameState
{
public:
    ChessGameCheckState(ChessGame& game) :
        game_(game)
    {}

    void onInit() override;
    void update() override;
    void onExit() override;
    const BoardPositionToPossibleMovesMap& getPossibleMoves() const override;

protected:
    void initPossibleMovesMap_();

    ChessGame& game_;
    BoardPositionToPossibleMovesMap possibleMovesMap_;
};
