#include "PlayerAi.hpp"

#include <memory>
#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessBasicBrancher.hpp>

PlayerAi::PlayerAi(ChessGame& game) :
    Player(game),
    minMax(std::make_unique<ChessBasicBrancher>())
{}

void PlayerAi::updateObserver(
        const AbstractSubject& subject,
        const SubjectEvent& event)
{
    const auto& chessEvent = dynamic_cast<const ChessGameEvent&>(event);

    if (chessEvent.yourTurn)
    {

    }
}
