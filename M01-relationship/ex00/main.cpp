#include <iostream>

#include "Hammer.hpp"
#include "Shovel.hpp"
#include "Tool.hpp"
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

    test::title("AGGREGATION & INHERENCE");
    test::subtitle(
        "The Worker can have a Tool that is not destroyed in case of Worker "
        "deletion");
    {
        test::subtitle("Create a Worker");
        Worker* worker = new Worker();
        std::cout << *worker << std::endl;
        test::enter();

        test::subtitle("Create a Shovel - Shovel is a Tool");
        Tool* shovel = new Shovel();
        std::cout << *shovel << std::endl;

        test::subtitle("The Worker can take a Shovel");
        worker->takeTool(shovel);
        std::cout << *worker << std::endl;
        std::cout << *shovel << std::endl;

        test::enter();
        // shovel.use(); // can't call private method
        worker->work(SHOVEL);
        worker->work();

        test::subtitle("deleting Worker");
        delete worker;

        test::subtitle("the shovel remains");
        std::cout << *shovel << std::endl;
        delete shovel;
    }

    try {
        test::subtitle("Worker without shovel tries to work");
        Worker worker = Worker();
        worker.work();
    } catch (Worker::NoTool& e) {
        test::error(e.what());
    }

    test::subtitle(
        "If the tool is already given to a worker, giving it to another worker"
        " removes it from the first");
    try {
        test::subtitle("Create 2 works");
        Worker worker1 = Worker();
        Worker worker2 = Worker();
        test::subtitle("Create a hammer - Hammer is a Tool");
        Hammer hammer = Hammer();

        test::subtitle("Worker 1 takes the tool");
        worker1.takeTool(&hammer);
        std::cout << "1: " << worker1 << std::endl;
        std::cout << "2: " << worker2 << std::endl;
        std::cout << hammer << std::endl;

        test::enter();
        worker1.work();

        test::subtitle("Worker 2 takes the same tool");
        worker2.takeTool(&hammer);
        std::cout << "1: " << worker1 << std::endl;
        std::cout << "2: " << worker2 << std::endl;
        std::cout << hammer << std::endl;

        test::enter();
        worker2.work();

        test::subtitle("Worker 1 tries to work again");
        worker1.work();
    } catch (Worker::NoTool& e) {
        test::error(e.what());
    }

    // Worker has a list of Tools, hammers and shovels

    test::title("ASSOCIATION ");
}
