#pragma once

#include <ChessGame/ChessGameData.hpp>

class IChessGameState
{
public:
    virtual ~IChessGameState() = default;

    virtual void onInit() {}
    virtual void update() = 0;
    virtual void onExit() {}
    virtual const BoardPositionToPossibleMovesMap& getPossibleMoves() const = 0;

    void checkIfPromotionAvalaibleAndHandleIt();
};
