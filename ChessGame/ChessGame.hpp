#pragma once

#include <memory>
#include <optional>
#include <ChessGame/Player.hpp>
#include <ChessGame/ChessGameData.hpp>
#include <ChessGame/States/ChessGameStateMachine.hpp>

class ChessGame
{
public:
    struct MoveEvent
    {
        Player& player;
        ChessGameData::MoveType moveType;
    };

    ChessGame();

    void registerPlayer(Player& player);
    Player& getCurrentPlayer();
    Player& getPlayer(PlayerColor color);
    void start();
    void update();
    void playerMoveCallback(Player& player, ChessGameData::MoveType move);

    PlayerColor currentPlayerColor = PlayerColor::White;
    ChessGameData gameState;
    ChessGameStateMachine stateMachine;

    std::optional<MoveEvent> moveEvent;
    std::optional<ChessGameData::MoveType> lastMove;


private:
    Player* whitePlayer = nullptr;
    Player* blackPlayer = nullptr;
    bool hasStarted = false;
};
