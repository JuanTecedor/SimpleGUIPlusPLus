#ifndef ANGLE_HPP
#define ANGLE_HPP

#include <compare>
#include <numbers>

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
    
    [[nodiscard]] float as_degrees() const noexcept
    {
        return m_degrees;
    }

    [[nodiscard]] float as_radians() const;

    auto operator<=>(const Angle &) const = default;  // NOLINT Bug https://reviews.llvm.org/D95714?id=320393
    Angle operator+=(const Angle & rhs) noexcept;
private:
    float m_degrees = {};
    void adjust_bounds() noexcept;
public:
    constexpr static inline auto HALF_CIRCLE_DEG = 180.F;
    constexpr static inline auto FULL_CIRCLE_DEG = 360.F;
    constexpr static inline auto THREE_QUARTER_CIRCLE_DEG = 270.F;
    constexpr static inline auto ONE_POINT_FIVE_PI = 1.5F * std::numbers::pi_v<float>;
};

#endif
