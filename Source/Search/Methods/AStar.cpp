//
//  AStar.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "AStar.hpp"

namespace robo {


SearchResults AStar::search(const Environment& env)
{
    frontier_.clear();
    explored_.clear();

    Node node(env.start, -1, 0, Action::none);
    if ( env.goal_test(node.state) ) {
        return SearchResults(true, explored_, node);
    }

    frontier_.add(node);
    explored_.add(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.remove();

        if ( env.goal_test(node.state) ) {
            return SearchResults(true, explored_, node);
        }

        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node.state), a);
            if ( !explored_.contains(child) ) {
                explored_.add(child);

                if ( env.goal_test(child.state) ) {
                    return SearchResults(true, explored_, child);
                }

                frontier_.add(child);
            }
        }
    }

    return SearchResults(false, explored_, child);
}

Node AStar::get_child(const Environment& env, Node& parent, const Action action)
{
    auto child = SearchMethod::get_child(env, parent, action);
    auto g = parent.cost + env.step_cost;
    auto h = child.state.distance(env.goal);
    child.cost = g + h;
    return child;

}


}