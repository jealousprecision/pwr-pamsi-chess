#pragma once

#include <ChessGame/Player.hpp>
#include <ChessGame/GameState.hpp>
#include <MinMax.hpp>

class PlayerAi : public Player
{
public:
    PlayerAi(ChessGame& game);

    void updateObserver(
            const AbstractSubject& subject,
            const SubjectEvent& event) override;

protected:
    MinMax<ChessGameState> minMax;
};
