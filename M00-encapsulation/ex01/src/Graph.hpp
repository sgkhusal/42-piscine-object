#pragma once

#include <cmath>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "Vector2.hpp"

#define AXES_LINE 1
#define ZERO_LINE 1
#define NEW_LINE 1

class Graph {
    friend std::ostream& operator<<(std::ostream& os, Graph const& graph);

 public:
    Graph(void);
    ~Graph(void);

    void addPoint(Vector2 const& point);
    void addPoint(float x, float y);

 private:
    typedef std::deque<Vector2> points;
    Vector2 _size;
    points  _points;

    void        updateSize(float x, float y);
    std::string toString(void) const;
};
