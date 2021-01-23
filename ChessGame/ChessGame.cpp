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

void ChessGame::playerMoveCallback(Move move)
{
    waitingMoves.push(move);

    if (!stateMachineUpdating)
    {
        stateMachineUpdating = true;
        while (!waitingMoves.empty())
        {
            auto move = waitingMoves.front();
            waitingMoves.pop();

            if (!stateMachine.applyMove(move) || playerThatWon)
            {
                // game ended
                getPlayer(playerThatWon.value()).gameEndedCallback(true);
                getPlayer(negate(playerThatWon.value())).gameEndedCallback(false);

                break;
            }
            getCurrentPlayer().yourTurnCallback();
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
