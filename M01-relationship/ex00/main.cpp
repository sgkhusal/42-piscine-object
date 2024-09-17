#include <iostream>

#include "Worker.hpp"
#include "test_utils.hpp"

int main(void) {
    test::title("COMPOSITION");
    test::subtitle(
        "A Position and a Statistic are part of a Worker and are destroyed when "
        "the Worker is destroyed");

    {
        test::subtitle("1. Default constructor");
        Worker* worker = new Worker();
        std::cout << *worker << std::endl;
        delete worker;

        test::subtitle("2. Passing Position and Statistic");
        Statistic stat = Statistic(5, 2);
        Position  pos  = Position(1, 2, 3);
        worker         = new Worker(pos, stat);
        std::cout << *worker << std::endl;
        delete worker;

        test::subtitle("3. with parameters");
        worker = new Worker(5, 5, 5, 10, 5);
        std::cout << *worker << std::endl;
        delete worker;

        test::enter();
        test::comment("remaining stack variables destructor:");
    }
}
