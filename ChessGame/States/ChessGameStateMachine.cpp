#include "ChessGameStateMachine.hpp"

#include <ChessGame/ChessGame.hpp>
#include <ChessGame/States/ChessGameDefaultState.hpp>
#include <ChessGame/States/ChessGameCheckState.hpp>
#include <ChessGame/States/ChessGameEndState.hpp>

ChessGameStateMachine::ChessGameStateMachine(ChessGame& game) :
    defaultState_(std::make_unique<ChessGameDefaultState>(game)),
    checkState_(std::make_unique<ChessGameCheckState>(game)),
    endState_(std::make_unique<ChessGameEndState>(game)),
    currentState(defaultState_.get())
{}

void ChessGameStateMachine::changeState(ChessGameStateMachine::State state)
{
    currentState->onExit();

    switch (state)
    {
    case ChessGameStateMachine::State::Default:
        currentState = defaultState_.get();
        break;
    case ChessGameStateMachine::State::Check:
        currentState = checkState_.get();
        break;
    case ChessGameStateMachine::State::End:
        currentState = endState_.get();
        break;
    }

    currentState->onInit();
}

void ChessGameStateMachine::update()
{
    currentState->update();
}
