#include <iostream>

#include "Graph.hpp"

int main(void) {
    Graph graph = Graph();

    std::cout << "Empty graph:" << std::endl;
    std::cout << graph << std::endl << std::endl;

    graph.addPoint(0, 0);
    std::cout << "With point(0,0):" << std::endl;
    std::cout << graph << std::endl << std::endl;

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
    std::cout << "More points:" << std::endl;
    std::cout << graph << std::endl << std::endl;

    graph.addPoint(10, 10);
    graph.addPoint(20, 20);
    graph.addPoint(100, 100);
    std::cout << "Bigger:" << std::endl;
    std::cout << graph << std::endl;

    graph.addPoint(6.4, 1.6);  // rounds to 6, 2
    graph.addPoint(2.1, 5.5);  // rounds to 2, 6
    std::cout << "With some floats:" << std::endl;
    std::cout << graph << std::endl;
}
