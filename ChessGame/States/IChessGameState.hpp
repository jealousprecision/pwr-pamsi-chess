#pragma once

#include <ChessGame/ChessGameState.hpp>

class IChessGameState
{
public:
    virtual void onInit() {}
    virtual void update() = 0;
    virtual void onExit() {}
    virtual std::vector<ChessGameState::MoveType> getPossibleMoves() const = 0;
};
