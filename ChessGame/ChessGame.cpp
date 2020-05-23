#include "ChessGame.hpp"

#include <stdexcept>

ChessGame::ChessGame() :
    stateMachine(*this)
{}

void ChessGame::registerPlayer(Player& player)
{
    if (player.getPlayerColor() == PlayerColor::White)
        whitePlayer = &player;
    else
        blackPlayer = &player;
}

void ChessGame::playerMoveSlot(Player& player, ChessGameState::MoveType move)
{
    if (moveEvent.has_value())
        throw std::runtime_error("ChessGame::playerMoveSlot(): called when already holding a player move signal");

    moveEvent.emplace(MoveEvent{player, move});
}

void ChessGame::start()
{
    if (!whitePlayer && !blackPlayer)
        throw std::runtime_error("ChessGame::start(): white and/or black player not defined!");

    whitePlayer->yourTurnSlot();
    hasStarted = true;
}

void ChessGame::update()
{
    if (hasStarted)
        stateMachine.update();
}
