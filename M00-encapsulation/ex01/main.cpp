#include <iostream>

#include "Graph.hpp"
#include "test_utils.hpp"

int main(void) {
    Graph graph = Graph();

    test::subtitle("Empty graph:");
    std::cout << graph << std::endl << std::endl;

    test::subtitle("Adding point (0,0):");
    graph.addPoint(0, 0);
    std::cout << graph << std::endl << std::endl;

    graph.addPoint(2, 2);
    graph.addPoint(4, 2);
    graph.addPoint(2, 4);

    test::subtitle("PDF example:");
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
    test::subtitle("More points:");
    std::cout << graph << std::endl << std::endl;

    graph.addPoint(10, 10);
    graph.addPoint(20, 20);
    graph.addPoint(100, 100);
    test::subtitle("Bigger:");
    std::cout << graph << std::endl << std::endl;

    graph.addPoint(6.4, 1.6);  // rounds to 6, 2
    graph.addPoint(2.1, 5.5);  // rounds to 2, 6
    test::subtitle("With some floats:");
    std::cout << graph << std::endl << std::endl;

    test::title("FILE TESTS");
    test::subtitle("Reading from unexistent file:");
    try {
        Graph graphFile = Graph("wrong_name");
    } catch (std::exception &e) {
        test::error(e.what());
    }

    test::subtitle("File with wrong input format:");
    try {
        Graph graphFile = Graph("./sample/error");
        std::cout << graphFile << std::endl << std::endl;
    } catch (std::exception &e) {
        test::error(e.what());
    }

    test::subtitle("Reading from empty file:");
    try {
        Graph graphFile = Graph("./sample/empty");
        std::cout << graphFile << std::endl << std::endl;
    } catch (std::exception &e) {
        test::error(e.what());
    }

    test::subtitle("Reading from a file:");
    try {
        Graph graphFile = Graph("./sample/points");
        std::cout << graphFile << std::endl << std::endl;
    } catch (std::exception &e) {
        test::error(e.what());
    }

}
