#pragma once

#include <memory>
#include <stack>
#include <queue>
#include <limits>
#include <list>
#include <optional>
#include <iostream>

#include <IBrancher.hpp>
#include <GraphList.hpp>

template<typename GameState>
class MinMax
{
public:
    MinMax(std::unique_ptr<IBrancher<GameState>> brancher) :
        brancher_(std::move(brancher))
    {}

    typename GameState::MoveType getOptimalMove(const GameState& gameState)
    {
        graph_.clear();
        auto src = graph_.addVertex(0);
        brancher_->branch(gameState, graph_);

        std::optional<typename GameState::MoveType> bestMove;
        int bestVal = std::numeric_limits<int>::min();
        for (auto edge : graph_.getEdgesOut(src))
        {
            auto val = minMaxImpl(graph_.getVertexTo(edge));
            if (val > bestVal)
            {
                bestVal = val;
                bestMove = graph_.getEdge(edge);
            }
        }

        if (bestVal == std::numeric_limits<int>::min())
            throw std::runtime_error("MinMax::getOptimalMove(): move not found?");

        std::cout << "MinMax::getOptimalMove(): move of value: " << bestVal << "; move: " << bestMove << std::endl;
    }

protected:    
    int minMaxImpl(unsigned vertex, bool isMax = false)
    {
        auto& edgesOut = graph_.getEdgesOut(vertex);

        if (edgesOut.size() == 0)
            return graph_.getVertex(vertex);

        auto result = isMax ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
        for (auto edge : edgesOut)
        {
            auto dest = graph_.getVertexTo(edge);
            if (isMax)
                result = std::max(result, minMaxImpl(dest, false));
            else
                result = std::min(result, minMaxImpl(dest, true));
        }

        return result;
    }

    GraphList<int, typename GameState::MoveType> graph_;
    std::unique_ptr<IBrancher<GameState>> brancher_;
};

