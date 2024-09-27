#pragma once

#include <set>

#include "Worker.hpp"
#include "Tool.hpp"

template<typename T>
class Workshop {
 public:
    Workshop(void): workers(WorkshopWorkers()) {
        test::comment("Workshop constructor called");
    }
    ~Workshop(void) { test::comment("Workshop destructor called"); }

    void signUp(Worker* worker) {
        // if (!worker->getTool<T>()) throw Worker::NoTool();
        if (!worker->getTool<T>()) throw std::runtime_error("Worker has no Tool");
        if (this->workers.find(worker) != this->workers.end()) {
            test::comment("Worker already registered at this workshop");
            return;
        }

        this->workers.insert(worker);
        std::cout << GREEN << "Worker registered to workshop" << RESET << std::endl;
    }

    void leave(Worker* worker) {
        if (this->workers.find(worker) == this->workers.end()) {
            test::comment("Worker not registered at this workshop");
            return;
        }
        this->workers.erase(worker);
        std::cout << GREEN << "Worker leaves the workshop" << RESET << std::endl;
    }

    void executeWorkDay(void) {
        std::set<Worker*>::iterator it, end = this->workers.end();
        Worker* worker;

        std::cout << GREEN << "Calling works to work on workshop" << RESET << std::endl;
        for (it = this->workers.begin(); it != end; it++) {
            worker = *it;
            worker->work<T>();
        }
    }

 private:
    typedef std::set<Worker*> WorkshopWorkers;

    WorkshopWorkers workers;
    static T        toolType;
};
