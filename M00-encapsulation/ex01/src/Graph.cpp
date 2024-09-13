#include "Graph.hpp"

Graph::Graph(void) : _size(Vector2(0, 0)), _points(points()) {}

Graph::Graph(std::string const& filename) : _size(Vector2(0, 0)), _points(points()) {
    getFilePoints(filename);
}

Graph::~Graph(void) {}

void Graph::addPoint(Vector2 const& point) {
    _points.push_back(point);
    updateSize(point.getX(), point.getY());
}

void Graph::addPoint(float x, float y) {
    _points.push_back(Vector2(x, y));
    updateSize(x, y);
}

void Graph::updateSize(float x, float y) {
    if (x > _size.getX()) _size.setX(std::ceil(x));
    if (y > _size.getY()) _size.setY(std::ceil(y));
}

void Graph::getFilePoints(std::string const& filename) {
    std::ifstream     file;
    std::stringstream ss;
    std::string       line;
    float             x;
    float             y;

    file.open(filename.c_str());
    if (file.fail()) {
        std::string msg = "Error reading ";
        msg += filename;
        throw std::runtime_error(msg.c_str());
    }

    while (std::getline(file, line)) {
        if (line == "") continue;

        for (std::string::const_iterator it = line.begin(); it != line.end(); it++) {
            if (!std::isdigit(*it) && *it != '.' && *it != ',') {
                std::string msg = "Wrong character at <";
                msg += line;
                msg.append(">");
                throw std::runtime_error(msg.c_str());
            }
        }

        size_t comma = line.find(',');
        if (comma == std::string::npos)
            throw std::runtime_error("missing comma separator");
        ss << line.substr(0, comma);
        ss >> x;
        ss.clear();
        ss << line.substr(comma + 1);
        ss >> y;
        ss.clear();
        this->addPoint(x, y);
    }

    file.close();
}

std::string Graph::toString(void) const {
    int  col_size = 2;
    int  x_max    = _size.getX() + 1;
    int  y_max    = _size.getY() + 1;
    bool x_bigger = false;
    bool y_bigger = false;

    if (x_max > 9) {
        x_max    = 9;
        x_bigger = true;
    }
    if (y_max > 9) {
        y_max    = 9;
        y_bigger = true;
    }

    int x_size     = (x_max + ZERO_LINE + AXES_LINE) * col_size + NEW_LINE;
    int y_size     = y_max + ZERO_LINE + AXES_LINE;
    int graph_size = x_size * y_size;

    std::string graph(graph_size, ' ');
    int         id = graph_size;
    int         i, j, x, y;
    for (std::string::iterator it = graph.end(); it != graph.begin(); it--) {
        i = id / x_size;
        j = id % x_size;
        x = (j - 2) / 2;
        y = y_max - i;

        if (i == y_size - 1) {
            if (j > 2 && (j - 2) % 2) *it = x + 48;
        } else if (j == 1) {
            *it = y + 48;
        } else if (j % 2) {
            *it = '.';
        } else if (j == x_size - 1) {
            *it = '\n';
        }

        id--;
    }

    for (points::const_iterator it = _points.begin(); it != _points.end(); it++) {
        x = round(it->getX());
        y = round(it->getY());
        if (x > 9 || y > 9) continue;
        i         = y_max - y;
        j         = x * 2 + 2;
        id        = x_size * i + j + 1;
        graph[id] = 'X';
    }

    if (y_bigger && _size.getX() > 9) graph.insert(--graph.end(), 3, '.');
    if (x_bigger && _size.getY() > 9) graph.insert(0, " .\n .\n .\n");

    return graph;
}

std::ostream& operator<<(std::ostream& os, Graph const& graph) {
    os << graph.toString();
    return (os);
}
