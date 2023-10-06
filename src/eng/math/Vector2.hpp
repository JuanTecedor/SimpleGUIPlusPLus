#ifndef VECTOR_2_HPP
#define VECTOR_2_HPP

#include <type_traits>
#include <cmath>
#include <cassert>

#include "Angle.hpp"

template<typename T>
class Vector2
{
public:
    constexpr Vector2() = default;

    constexpr Vector2(const T & p_x, const T & p_y) noexcept :
        x{p_x}, y{p_y}
    {
    }

    template <typename U>
    constexpr explicit Vector2(const Vector2<U> & other) :
        x{static_cast<T>(other.x)}, y{static_cast<T>(other.y)}
    {
    }

    Vector2(const T & len, const Angle & alpha) :
        x{len * static_cast<T>(std::cos(alpha.as_radians()))},
        y{len * static_cast<T>(std::sin(alpha.as_radians()))}
    {
        static_assert(std::is_floating_point_v<T>);
    }

    [[nodiscard]] constexpr T length() const
    {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] constexpr T length_squared() const
    {
        return dot(*this);
    }

    [[nodiscard]] constexpr Vector2 perpendicular() const
    {
        return Vector2<T>{-y, x};
    }

    [[nodiscard]] constexpr T dot(const Vector2<T> & rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }

    [[nodiscard]] Vector2 normalized() const
    {
        check_length_dbg();
        return Vector2<T>(*this) / length();
    }

    void normalize()
    {
        check_length_dbg();
        (*this) /= length();
    }
private:
    void check_length_dbg() const
    {
        assert(x != T{} || y != T{});
    }
public:

    [[nodiscard]] Angle angle_to(const Vector2 & rhs) const
    {
        static_assert(std::is_floating_point_v<T>);
        assert(*this != Vector2<T>{});
        assert(rhs != Vector2<T>{});
        return Angle::from_radians(static_cast<float>(std::atan2(cross(rhs), dot(rhs))));
    }

    [[nodiscard]] Angle angle() const
    {
        static_assert(std::is_floating_point_v<T>);
        assert(*this != Vector2<T>{});
        return Angle::from_radians(static_cast<float>(std::atan2(y, x)));
    }

    [[nodiscard]] Vector2 projected_onto(const Vector2<T> & axis) const
    {
        static_assert(std::is_floating_point_v<T>);
        assert(axis != Vector2<T>{});
        return dot(axis) / axis.lengthSq() * axis;
    }

    [[nodiscard]] Vector2 rotated_by(const Angle & phi) const
    {
        static_assert(std::is_floating_point_v<T>);
        T cos = std::cos(static_cast<T>(phi.as_radians()));
        T sin = std::sin(static_cast<T>(phi.as_radians()));
        return Vector2<T>(cos * x - sin * y, sin * x + cos * y);
    }

    [[nodiscard]] Vector2 comp_wise_mul(const Vector2 & other) const
    {
        return Vector2<T>(x * other.x, y * other.y);
    }

    [[nodiscard]] Vector2 comp_wise_div(const Vector2 & other) const
    {
        assert(other.x != 0);
        assert(other.y != 0);
        return Vector2<T>(x / other.x, y / other.y);
    }

    auto operator<=>(const Vector2 &) const = default;

    [[nodiscard]] constexpr Vector2 operator+(const Vector2 & rhs) const noexcept {
        return {x + rhs.x, y + rhs.y};
    }

    [[nodiscard]] constexpr Vector2 operator-(const Vector2 & rhs) const noexcept {
        return {x - rhs.x, y - rhs.y};
    }

    [[nodiscard]] constexpr Vector2 operator-() const noexcept {
        return {-x, -y};
    }

    template <typename U> requires (std::integral<U> or std::floating_point<U>)
    [[nodiscard]] constexpr Vector2 operator*(const U & scalar) const noexcept {
        return {x * scalar, y * scalar};
    }

    [[nodiscard]] constexpr T operator*(const Vector2 & rhs) const noexcept {
        return dot(rhs);
    }

    template <typename U> requires (std::integral<U> or std::floating_point<U>)
    [[nodiscard]] constexpr Vector2 operator/(const U & scalar) const noexcept {
        return {x / scalar, y / scalar};
    }

    constexpr Vector2 operator+=(const Vector2 & rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr Vector2 operator-=(const Vector2 & rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    template <typename U> requires (std::integral<U> or std::floating_point<U>)
    constexpr Vector2 operator*=(const U & scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <typename U>
    constexpr Vector2 operator/=(const U & scalar) noexcept {
        x /= scalar;
        y /= scalar;
        return *this;
    }


    T x{};
    T y{};

    const inline static Vector2 UNIT_X = {static_cast<T>(1) , static_cast<T>(0)};
    const inline static Vector2 UNIT_Y = {static_cast<T>(0), static_cast<T>(1)};
};

template <typename T>
constexpr Vector2<T> operator*(const T & scalar, const Vector2<T> & rhs) noexcept
{
    return rhs * scalar;
}

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2u = Vector2<unsigned int>;

#endif
