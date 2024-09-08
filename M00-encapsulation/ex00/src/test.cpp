#include "test.hpp"

namespace test {
void title(std::string const title) {
    size_t size = title.length();

    if (size > 77) {
        std::cout << std::endl << BLUE << title << RESET << std::endl;
    } else {
        size_t c_size = (80 - size - 2) / 2;
        char   c      = '*';

        std::cout << std::endl
                  << BLUE << std::string(c_size, c) << " " << title << " "
                  << std::string(c_size, c) << RESET << std::endl;
    }
}

void p(char const* text) { std::cout << text << std::endl; }

void error(char const* text) { std::cout << ORANGE << text << RESET << std::endl; }

}  // namespace test
