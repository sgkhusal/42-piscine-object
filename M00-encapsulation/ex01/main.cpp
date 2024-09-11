#include <iostream>
#include "Graph.hpp"

int main(void) {
    Graph graph = Graph();

    graph.addPoint(0, 0);
    graph.addPoint(2, 2);
    graph.addPoint(4, 2);
    graph.addPoint(2, 4);

    std::cout << "PDF example:" << std::endl;
    std::cout << graph << std::endl << std::endl;

    graph.addPoint(2, 8);
    graph.addPoint(8, 2);
    graph.addPoint(1, 1);
    graph.addPoint(3, 3);
    graph.addPoint(4, 4);
    graph.addPoint(5, 5);
    graph.addPoint(6, 6);
    graph.addPoint(7, 7);
    graph.addPoint(8, 8);
    graph.addPoint(9, 9);
    std::cout << "Max unit per axis:" << std::endl;
    std::cout << graph << std::endl << std::endl;

    graph.addPoint(10, 10);
    graph.addPoint(20, 20);
    graph.addPoint(100, 100);
    std::cout << "Bigger:" << std::endl;
    std::cout << graph << std::endl;
}
