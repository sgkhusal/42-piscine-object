#pragma once

#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Vector2.hpp"

#define AXES_LINE 1
#define ZERO_LINE 1
#define NEW_LINE 1

class Graph {
    friend std::ostream& operator<<(std::ostream& os, Graph const& graph);

 public:
    Graph(void);
    explicit Graph(std::string const& filename);
    ~Graph(void);

    void addPoint(Vector2 const& point);
    void addPoint(float x, float y);

 private:
    typedef std::deque<Vector2> points;

    Vector2 _size;
    points  _points;

    void        updateSize(float x, float y);
    void        getFilePoints(std::string const& filename);
    std::string toString(void) const;
};
