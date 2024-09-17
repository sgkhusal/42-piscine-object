#include "test_utils.hpp"

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

void subtitle(std::string const title) {
    std::cout << std::endl << YELLOW << title << RESET << std::endl;
}

void comment(std::string const comment) {
    std::cout << GREY << comment << RESET << std::endl;
}

void p(char const* text) { std::cout << text << std::endl; }

void error(char const* text) { std::cout << ORANGE << text << RESET << std::endl; }

void enter(void)  { std::cout << std::endl; }

}  // namespace test
