#include "Graph.hpp"

Graph::Graph(void) : _size(Vector2(1, 1)), _points(points()) {}

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
    if (x > _size.getX()) _size.setX(std::ceil(x));
    if (y > _size.getY()) _size.setY(std::ceil(y));
}

std::string Graph::toString(void) const {
    int col_size = 2;
    int x_size     = (_size.getX() + 3) * col_size + 1;
    int y_size     = _size.getY() + 3;
    int graph_size = x_size * y_size;

    std::string graph(graph_size, ' ');
    int id = graph_size;
    int i, j, x, y;
    for (std::string::iterator it = graph.end(); it != graph.begin(); it--) {
        i = id / x_size;
        j = id % x_size;
        x = (j - 2) / 2;
        y = _size.getY() + 1 - i;

        if (i == y_size - 1) {
            if (j > 2 && (j - 2) % 2)
                *it = x + 48;
        } else if (j == 1) {
            *it = y + 48;
        } else if (j % 2) {
            *it = '.';
        } else if (j == x_size - 1) {
            *it = '\n';
        }

        if (x == 2 && y == 2 && j % 2) *it = 'X';
        id--;
    }

    return graph;
}

std::ostream& operator<<(std::ostream& os, Graph const& graph) {
    os << graph.toString();
    return (os);
}
