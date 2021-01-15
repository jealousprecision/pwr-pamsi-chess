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
    waitingMoves.push(MoveEvent{player, move});
    if (!stateMachineUpdating)
    {
        stateMachineUpdating = true;
        while (!waitingMoves.empty())
        {
            stateMachine.update();
        }
        stateMachineUpdating = false;
    }
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
}
