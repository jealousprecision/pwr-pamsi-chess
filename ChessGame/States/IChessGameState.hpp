#pragma once

#include <ChessGame/ChessGameState.hpp>

class IChessGameState
{
public:
    virtual void onInit() {}
    virtual void update() = 0;
    virtual void onExit() {}
    virtual const BoardPositionToPossibleMovesMap& getPossibleMoves() const = 0;

    void checkIfPromotionAvalaibleAndHandleIt();
};
