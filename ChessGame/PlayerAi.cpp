#include "PlayerAi.hpp"

#include <memory>
#include <ChessGame/ChessGame.hpp>
#include <ChessGame/ChessBasicBrancher.hpp>

PlayerAi::PlayerAi(ChessGame& game, PlayerColor color) :
    Player(game, color),
    minMax(std::make_unique<ChessBasicBrancher>())
{}
