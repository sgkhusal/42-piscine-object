#pragma once

#include "test_utils.hpp"

class Statistic {
 public:
    Statistic(void) : level(0), exp(0) {
        test::comment("Statistic constructor called");
    }
    Statistic(int level, int exp) : level(level), exp(exp) {
        test::comment("Statistic constructor called");
    }
    Statistic(Statistic const& stat) : level(stat.getLevel()), exp(stat.getExp()) {
        test::comment("Statistic copy constructor called");
    }
    ~Statistic(void) { test::comment("Statistic destructor called"); }

    int const& getLevel(void) const { return level; }
    int const& getExp(void) const { return exp; }

 private:
    int level;
    int exp;

    friend class Worker;

    friend std::ostream& operator<<(std::ostream& os, Statistic const& rhs) {
        os << "level: " << rhs.level << " - exp: " << rhs.exp;
        return os;
    }
};
