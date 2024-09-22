#pragma once

#include "test_utils.hpp"

class Worker;

class Shovel {
 public:
    Shovel(void) : numberOfUses(0), worker(NULL) {
        test::comment("Shovel constructor called");
    }
    ~Shovel(void) {
        test::comment("Shovel destructor called");
        // if (this->worker) this->worker->releaseShovel();  // TODO: table
    }

    Worker* getOwner(void) { return this->worker; }
    void    resetWorker(void) {
        this->worker = NULL;
        std::cout << GREEN << "Shovel now is not with any worker" << RESET << std::endl;
    }
    void setWorker(Worker* newWorker) {
        this->worker = newWorker;
        std::cout << GREEN << "Shovel worker updated to " << this->worker << RESET
                  << std::endl;
    }

 private:
    int     numberOfUses;
    Worker* worker;

    void use(void) {
        this->numberOfUses += 1;
        std::cout << GREEN << "Shovel used " << this->numberOfUses << " times" << RESET
                  << std::endl;
    }

    friend class Worker;

    friend std::ostream& operator<<(std::ostream& os, Shovel const& rhs) {
        os << "Shovel used " << rhs.numberOfUses
           << " times - worker pointer at: " << rhs.worker;
        return os;
    }
};
