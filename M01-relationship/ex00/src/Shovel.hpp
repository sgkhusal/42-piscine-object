#pragma once

#include "test_utils.hpp"
#include "ShovelWorker.hpp"

class Shovel {
 public:
    Shovel(void) : numberOfUses(0) { test::comment("Shovel constructor called"); }
    ~Shovel(void) {
        test::comment("Shovel destructor called");
        ShovelWorker::remove(this);
    }

 private:
    int numberOfUses;

    void use(void) {
        this->numberOfUses += 1;
        std::cout << GREEN << "Shovel used " << this->numberOfUses << " times" << RESET
                  << std::endl;
    }

    friend class Worker;

    friend std::ostream& operator<<(std::ostream& os, Shovel const& rhs) {
        os << "Shovel used " << rhs.numberOfUses << " times";
        return os;
    }
};
