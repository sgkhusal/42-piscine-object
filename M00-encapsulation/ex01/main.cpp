#include <iostream>
#include "Graph.hpp"

int main(void) {
    Graph graph = Graph();

    graph.addPoint(0, 0);
    graph.addPoint(2, 2);
    graph.addPoint(4, 2);
    graph.addPoint(2, 4);
    graph.addPoint(10, 10);

    std::cout << graph << std::endl;
}
