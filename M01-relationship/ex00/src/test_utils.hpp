#pragma once

#include <iostream>
#include <string>
#include <cstdarg>

namespace test {
#define ORANGE "\033[0;38;5;166m"
#define BLUE "\033[38;5;75m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define GREY "\033[38;5;244m"
#define RESET "\033[0m"

void title(std::string const title);
void subtitle(std::string const title);
void comment(std::string const comment);
void p(char const* text);
void error(char const* text);
void enter(void);
}  // namespace test
