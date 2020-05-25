#pragma once

#include <memory>
#include <optional>
#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameState.hpp>
#include <ChessGame/States/ChessGameStateMachine.hpp>

class ChessGame
{
    struct MoveEvent
    {
        Player& player;
        ChessGameState::MoveType moveType;
    };

public:
    ChessGame();

    void registerPlayer(Player& player);
    void playerMoveSlot(Player& player, ChessGameState::MoveType move);
    Player& getCurrentPlayer();
    Player& getPlayer(PlayerColor color);
    void start();
    void update();

    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;
    PlayerColor currentPlayerColor = PlayerColor::White;
    ChessGameState gameState;
    std::optional<MoveEvent> moveEvent;
    ChessGameStateMachine stateMachine;

    bool hasStarted = false;
};
