#pragma once

#include <ChessGame/States/IChessGameState.hpp>

class ChessGame;

class ChessGameCheckState : public IChessGameState
{
public:
    ChessGameCheckState(ChessGame& game);

    void onInit() override;
    bool applyMove(const Move& move) override;
    void onExit() override;
    const BoardPositionToPossibleMovesMap& getPossibleMoves() const override;

private:
    void initPossibleMovesMap_();

    ChessGame& game_;
    BoardPositionToPossibleMovesMap possibleMoves_;
};
