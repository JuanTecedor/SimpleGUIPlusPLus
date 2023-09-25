#ifndef ANGLE_HPP
#define ANGLE_HPP

#include <compare>

class Angle
{
public:
    constexpr Angle() = default;
private:
    constexpr explicit Angle(const float & degrees) :
        m_degrees{degrees}
    {
    }
public:
    [[nodiscard]] constexpr static Angle from_degrees(const float & angle)
    {
        return Angle{angle};
    }

    [[nodiscard]] static Angle from_radians(const float & angle);
    
    [[nodiscard]] float as_degrees() const;
    [[nodiscard]] float as_radians() const;

    auto operator<=>(const Angle & rhs) const = default;
    Angle operator+=(const Angle & rhs) noexcept;
private:
    float m_degrees = {};
    constexpr static inline auto HALF_CIRCLE_DEG = 180;
};

#endif
