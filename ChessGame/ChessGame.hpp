#pragma once

#include <memory>
#include "GameState.hpp"
#include "MinMax.hpp"
#include "ChessBasicBrancher.hpp"

#include "Observer/Subject.hpp"

class ChessGame;

namespace chessgamestates
{

class ChessGameStateMachine
{
public:
    void parseMove(Player& player, ChessGameState::MoveType type);
};

class ChessGameAbstractState
{
public:
    ChessGameAbstractState(ChessGame& parent);
    virtual ~ChessGameAbstractState() = default;

    virtual void onInit() {}
    virtual void onExit() {}

    virtual void playerMoveSlot(ChessGameState::MoveType move) = 0;

protected:
    ChessGame& parent_;
};

class ChessGameDefaultState : ChessGameAbstractState
{
    ChessGameDefaultState(ChessGame& parent) :
        ChessGameAbstractState(parent)
    {}

    virtual void playerMoveSlot(ChessGameState::MoveType move) override;
};

}  // namespace chessgamestates

class ChessGameEvent : SubjectEvent
{
public:
    bool gameEnded = false;
    bool yourTurn = false;
};

class ChessGame : public AbstractSubject
{
    struct Event
    {
        bool playerMoveEvent;

    };

public:
    ChessGame(Ownership playerColor = Ownership::Black) :
        ai(std::make_unique<ChessBasicBrancher>(negate(playerColor)))
    {

    }

    void playerMoveSlot(ChessGameState::MoveType move)
    {
        state.apply(move);

        auto aiMove = ai.getOptimalMove(state);
        state.apply(aiMove);
    }

    const ChessGameState& getState() const { return state; }

protected:
    Ownership player = Ownership::White;
    ChessGameState state;
    MinMax<ChessGameState> ai;
};
