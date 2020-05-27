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

void ChessGame::playerMoveCallback(Player& player, ChessGameData::MoveType move)
{
    if (moveEvent.has_value())
        throw std::runtime_error("ChessGame::playerMoveCallback(): called when already holding a player move signal");

    moveEvent.emplace(MoveEvent{player, move});
}

Player& ChessGame::getPlayer(PlayerColor color)
{
    return color == PlayerColor::White ? *whitePlayer : *blackPlayer;
}

Player& ChessGame::getCurrentPlayer()
{
    return getPlayer(currentPlayerColor);
}

void ChessGame::start()
{
    if (!whitePlayer || !blackPlayer)
        throw std::runtime_error("ChessGame::start(): white and/or black player not defined!");

    whitePlayer->yourTurnCallback();
    hasStarted = true;
}

void ChessGame::update()
{
    if (hasStarted)
        stateMachine.update();
}
