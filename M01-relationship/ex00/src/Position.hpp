#pragma once

#include "test_utils.hpp"

class Position {
 public:
    Position(void) : x(0), y(0), z(0) { test::comment("Position constructor called"); }
    Position(int x, int y, int z) : x(x), y(y), z(z) {
        test::comment("Position constructor called");
    }
    Position(Position const& pos) : x(pos.getX()), y(pos.getY()), z(pos.getZ()) {
        test::comment("Position copy constructor called");
    }
    ~Position(void) { test::comment("Position destructor called"); }

    int const& getX(void) const { return x; }
    int const& getY(void) const { return y; }
    int const& getZ(void) const { return z; }

 private:
    int x;
    int y;
    int z;

    friend class Worker;

    friend std::ostream& operator<<(std::ostream& os, Position const& rhs) {
        os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
        return os;
    }
};
