#pragma once

#include "Tool.hpp"
#include "ToolWorker.hpp"
#include "test_utils.hpp"

class Hammer : public Tool {
 public:
    Hammer(void) : Tool(HAMMER) { test::comment("Hammer constructor called"); }
    ~Hammer(void) { test::comment("Hammer destructor called"); }

 private:
    void use(void) {
        this->numberOfUses += 1;
        std::cout << GREEN << "Clang, clang, clang" << GREY << " - hammer used "
                  << this->numberOfUses << " times" << RESET << std::endl;
    }

    friend class Worker;
};
