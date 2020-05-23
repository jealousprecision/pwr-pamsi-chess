#include "ChessGame.hpp"

namespace chessgamestates
{

ChessGameAbstractState::ChessGameAbstractState(ChessGame& parent) :
    parent_(parent)
{}

}  // namespace chessgamestates
