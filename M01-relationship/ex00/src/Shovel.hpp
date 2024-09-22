#pragma once

#include "Tool.hpp"
#include "ToolWorker.hpp"
#include "test_utils.hpp"

class Shovel : public Tool {
 public:
    Shovel(void) : Tool(SHOVEL) { test::comment("Shovel constructor called"); }
    ~Shovel(void) { test::comment("Shovel destructor called"); }

 private:
    void use(void) {
        this->numberOfUses += 1;
        std::cout << GREEN << "Shovel used " << this->numberOfUses << " times" << RESET
                  << std::endl;
    }

    friend class Worker;
};
