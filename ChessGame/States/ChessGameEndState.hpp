#pragma once

#include "IChessGameState.hpp"

class ChessGameEndState : public IChessGameState
{
public:
    void onInit() override {};
    bool applyMove(const Move& move) override;
    void onExit() override {};
    const BoardPositionToPossibleMovesMap& getPossibleMoves() const override;
};
