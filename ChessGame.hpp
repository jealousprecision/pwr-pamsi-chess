#pragma once

#include <memory>
#include "GameState.hpp"
#include "MinMax.hpp"
#include "ChessBasicBrancher.hpp"

#include "Observer/Subject.hpp"

class ChessGame;

namespace chessgamestates
{

class ChessGameAbstractState
{
public:
    ChessGameAbstractState(ChessGame& parent) :
        parent_(parent)
    {}
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

class ChessGame : public AbstractSubject
{
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
