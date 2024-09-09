#pragma once

#include <deque>
#include <iostream>
#include <string>

#include "Vector2.hpp"

class Graph {
    friend std::ostream& operator<<(std::ostream& os, Graph const& graph);

 public:
    Graph(void);
    ~Graph(void);
    // Graph(Graph const& rhs);
    // Graph& operator=(Graph const& rhs);

    void addPoint(Vector2 const& point);
    void addPoint(float x, float y);

 private:
    typedef std::deque<Vector2> points;

    Vector2 _size;
    points  _points;

    void        updateSize(float x, float y);
    char const* toString(void) const;
};
