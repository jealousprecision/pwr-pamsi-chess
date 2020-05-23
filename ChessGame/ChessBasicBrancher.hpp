#pragma once

#include <ChessGame/IBrancher.hpp>
#include <ChessGame/ChessGameState.hpp>

#include <stdexcept>

class ChessBasicBrancher : public IBrancher<ChessGameState>
{
public:
    ChessBasicBrancher(Ownership firstBranch) :
        firstBranch_(firstBranch)
    {
        if (firstBranch_ == Ownership::None)
            throw std::runtime_error("ChessBasicBrancher::ChessBasicBrancher(): Can't branch Ownership::None");
    }

    void branch(
            const ChessGameState& source,
            GraphList<int, typename ChessGameState::MoveType>& valueGraph) override;

protected:
    void subBranch_(
            unsigned srcVert,
            const ChessGameState& source,
            GraphList<int, typename ChessGameState::MoveType>& valueGraph);

    Ownership firstBranch_;
};
