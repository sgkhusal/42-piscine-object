#include "Graph.hpp"

Graph::Graph(void) : _size(Vector2(0, 0)), _points(points()) {}

Graph::~Graph(void) {}

void Graph::addPoint(Vector2 const& point) {
    // validate points
    _points.push_back(point);
    updateSize(point.getX(), point.getY());
}

void Graph::addPoint(float x, float y) {
    // validate points
    _points.push_back(Vector2(x, y));
    updateSize(x, y);
}

void Graph::updateSize(float x, float y) {
    if (x > _size.getX())
        _size.setX(x);
    if (y > _size.getY())
        _size.setY(y);
}

char const* Graph::toString(void) const {
    if (_size == 0) return "";

    return "";
}

std::ostream& operator<<(std::ostream& os, Graph const& graph) {
    os << graph.toString();
    return (os);
}
