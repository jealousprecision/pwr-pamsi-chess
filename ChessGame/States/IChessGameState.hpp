#pragma once

#include <ChessGame/BoardPositionToPossibleMovesMap.hpp>

class Move;

class IChessGameState
{
public:
    virtual ~IChessGameState() = default;

    virtual void onInit() = 0;
    virtual bool applyMove(const Move& move) = 0;
    virtual void onExit() = 0;
    virtual const BoardPositionToPossibleMovesMap& getPossibleMoves() const = 0;
};
