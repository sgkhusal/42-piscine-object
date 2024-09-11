#include "Vector2.hpp"

Vector2::Vector2(void) : _x(0.0), _y(0.0) {}

Vector2::Vector2(float x, float y) : _x(x), _y(y) {}

Vector2::~Vector2(void) {}

Vector2::Vector2(Vector2 const& rhs) : _x(rhs.getX()), _y(rhs.getY()) {}

Vector2& Vector2::operator=(Vector2 const& rhs) {
    if (this != &rhs) {
        _x = rhs.getX();
        _y = rhs.getY();
    }

    return *this;
}

bool Vector2::operator==(Vector2 const& rhs) const {
    return _x == rhs.getX() && _y == rhs.getY();
}

bool Vector2::operator!=(Vector2 const& rhs) const { return !(*this == rhs); }

float Vector2::getX() const { return this->_x; }

float Vector2::getY() const { return this->_y; }

void Vector2::setX(float x) { this->_x = x; }

void Vector2::setY(float y) { this->_y = y; }
