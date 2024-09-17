#pragma once

#include "Position.hpp"
#include "Statistic.hpp"

class Worker {
 public:
    Worker(void) : coordonnee(Position()), stat(Statistic()) {
        test::comment("Worker constructor called");
    }
    Worker(Position const& p, Statistic const& s) : coordonnee(p), stat(s) {
        test::comment("Worker constructor called");
    }
    Worker(int x, int y, int z, int level, int exp)
        : coordonnee(Position(x, y, z)), stat(Statistic(level, exp)) {
        test::comment("Worker constructor called");
    }
    ~Worker(void) { test::comment("Worker destructor called"); }

 private:
    Position  coordonnee;
    Statistic stat;

    friend std::ostream& operator<<(std::ostream& os, Worker const& rhs) {
        os << "Worker:\n"
           << "- Position: " << rhs.coordonnee << "\n- Statistics: " << rhs.stat;
        return os;
    }
};
