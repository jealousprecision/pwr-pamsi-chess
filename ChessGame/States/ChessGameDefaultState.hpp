#pragma once

#include <ChessGame/States/IChessGameState.hpp>

class ChessGame;

class ChessGameDefaultState : public IChessGameState
{
public:
    ChessGameDefaultState(ChessGame& chessGame);

    void onInit() override;
    bool applyMove(const Move& move) override;
    void onExit() override;
    const BoardPositionToPossibleMovesMap& getPossibleMoves() const override;

private:
    void initPossibleMoves_();

    ChessGame& game_;
    BoardPositionToPossibleMovesMap possibleMoves_;
};
