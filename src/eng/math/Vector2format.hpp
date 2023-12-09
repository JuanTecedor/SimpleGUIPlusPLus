#include "Vector2.hpp"

#include <iostream>

template <typename T>
std::string to_string(const Vector2<T> & vector)
{
    return std::string("Vector2(x=") + std::to_string(vector.x)
        + std::string(", y=") + std::to_string(vector.y) + std::string(")");
}

template <typename T>
std::ostream & operator<<(std::ostream & ostr, const Vector2<T> & vector)
{
    ostr << to_string(vector);
    return ostr;
}
