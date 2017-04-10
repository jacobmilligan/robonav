//
//  IDAStar.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  06/04/2017
//

#pragma once

#include "Search/Core/SearchMethod.hpp"

namespace robo {

/// @brief AStar is an implementation of iterative A* search method for graph-based
/// environments
class IDAStar : public SearchMethod {
public:
    /// @brief Executes A* on an environment
    /// @param env The environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
private:
    struct IDAStarResults {
        double limit;
        Solution solution;
    };

    IDAStarResults astar(const Environment& env, const Node& node,
                         const double limit);

    Frontier<std::set> frontier_;
};


}


