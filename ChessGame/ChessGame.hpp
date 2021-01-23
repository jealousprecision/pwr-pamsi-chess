#pragma once

#include <memory>
#include <optional>
#include <queue>
#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameData.hpp>
#include <ChessGame/States/ChessGameStateMachine.hpp>

class ChessGame
{
public:
    ChessGame();

    void registerPlayer(Player& player);
    Player& getCurrentPlayer();
    Player& getPlayer(PlayerColor color);
    void start();
    void playerMoveCallback(Move move);

    PlayerColor currentPlayerColor = PlayerColor::White;
    ChessGameData gameState;
    ChessGameStateMachine stateMachine;

    std::queue<Move> waitingMoves;
    std::optional<Move> lastMove;
    std::optional<PlayerColor> playerThatWon;


private:
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;
    bool stateMachineUpdating = false;
};
