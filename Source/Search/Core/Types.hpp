//
//  GraphTypes.hpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include <functional>
#include <cmath>
#include <cstdlib>

namespace robo {


enum class Action {
    unknown = 0,
    none,
    up,
    left,
    down,
    right
};

enum class DistanceFunction {
    euclidean,
    manhattan
};


struct Point {
    Point()
        : x(0), y(0)
    {}

    Point(const int xpos, const int ypos)
        : x(xpos), y(ypos)
    {}

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    double distance(const Point& other,
                    const DistanceFunction distance_function) const
    {
        switch (distance_function) {

            case DistanceFunction::euclidean:
            {
                auto xsqr = (other.x - x) * (other.x - x);
                auto ysqr = (other.y - y) * (other.y - y);
                return sqrt(xsqr + ysqr);
            };
            case DistanceFunction::manhattan:
            {
                auto xresult = abs(x - other.x);
                auto yresult = abs(y - other.y);
                return xresult + yresult;
            };
        }
    }

    int x;
    int y;
};

struct PointHash {
    size_t operator() (const Point& point) const
    {
        return (60 + std::hash<int>()(point.y))
            * 60 + std::hash<int>()(point.x);
    }
};

struct Node {
    Node()
        : id(-1),
          parent_ptr(nullptr),
          cost(0),
          action(Action::unknown)
    {}

    Node(const Point& node_state, const Node* parent,
         const int path_cost, const Action direction)
        : parent_ptr(parent),
          cost(path_cost),
          action(direction),
          state(node_state)
    {}

    bool operator>(const Node& rhs) const
    {
        return cost > rhs.cost;
    }

    bool operator<(const Node& rhs) const
    {
        return cost < rhs.cost;
    }

    int id;
    const Node* parent_ptr;
    double cost;
    Action action;
    Point state;
};


}