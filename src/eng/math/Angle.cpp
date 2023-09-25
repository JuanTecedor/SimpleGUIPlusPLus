#include "Angle.hpp"

#include <numbers>

Angle Angle::from_radians(const float & angle)
{
    return Angle{angle * (HALF_CIRCLE_DEG / std::numbers::pi_v<float>)};
}

float Angle::as_degrees() const
{
    return m_degrees;
}

float Angle::as_radians() const
{
    return m_degrees * (std::numbers::pi_v<float> / HALF_CIRCLE_DEG);
}

Angle Angle::operator+=(const Angle & rhs) noexcept
{
    m_degrees += rhs.m_degrees;
    return *this;
}
