#pragma once

#include <memory>
#include <ChessGame/States/IChessGameState.hpp>

class ChessGame;

class ChessGameStateMachine
{
public:
    enum class State
    {
        Default,
        Check,
        End
    };

    ChessGameStateMachine(ChessGame& game);

    void changeState(State state);
    void update();

protected:
    std::unique_ptr<IChessGameState> defaultState_;
    std::unique_ptr<IChessGameState> checkState_;
    std::unique_ptr<IChessGameState> endState_;

    IChessGameState* currentState;
};
