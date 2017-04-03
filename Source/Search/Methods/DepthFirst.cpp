//
//  DepthFirst.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "Search/Methods/DepthFirst.hpp"

namespace robo {


SearchResults DepthFirst::search(const Environment& env)
{
    frontier_.clear();
    explored_.clear();

    Node node(env.start, -1, 0, Action::none);
    if ( env.goal_test(env.start) ) {
        return SearchResults(true, explored_, node);
    }

    frontier_.add(node);
    explored_.add(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.remove();

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


}