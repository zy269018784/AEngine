#pragma once
#include <limits> 
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace GMath
{
    // ========================================================================
    // Type Traits and Floating Point Helpers
    // ========================================================================

    #define MachineEpsilon std::numeric_limits<Float>::epsilon() * 0.5f

    /**
     * @brief Check if an integral value is infinite (always false)
     * @tparam T Integral type
     * @param v Value to check
     * @return false for all integral types
     */
    template <typename T>
    inline typename std::enable_if_t<std::is_integral_v<T>, bool> IsInf(T v) {
        return false;
    }

    template <typename T>
    inline typename std::enable_if_t<std::is_floating_point_v<T>, bool> IsInf(T v) {

        return std::isinf(v);
    }


    /**
     * @brief Check if a floating point value is finite
     * @tparam T Floating point type
     * @param v Value to check
     * @return true if value is finite (not inf or nan)
     */
    template <typename T>
    inline typename std::enable_if_t<std::is_floating_point_v<T>, bool>
    IsFinite(T v) {
        return std::isfinite(v);
    }

    /**
     * @brief Check if an integral value is finite (always true)
     * @tparam T Integral type
     * @param v Value to check
     * @return true for all integral types
     */
    template <typename T>
    inline typename std::enable_if_t<std::is_integral_v<T>, bool> IsFinite(T v) {
        return true;
    }

    /**
     * @brief Compute gamma correction factor for floating point error analysis
     * @param n Number of operations
     * @return Gamma factor: (n * MachineEpsilon) / (1 - n * MachineEpsilon)
     */
    inline constexpr Float gamma(int n) {
        return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
    }

    // ========================================================================
    // Fused Multiply-Add (FMA)
    // ========================================================================

    /**
     * @brief FMA for integral types (simple multiply-add)
     * @tparam T Integral type
     * @param a Multiplier
     * @param b Multiplier
     * @param c Addend
     * @return a * b + c
     */
    template <typename T>
    inline typename std::enable_if_t<std::is_integral_v<T>, T> FMA(T a, T b, T c) {
        return a * b + c;
    }

    /**
     * @brief FMA for floating point (uses hardware FMA if available)
     * @param a Multiplier
     * @param b Multiplier
     * @param c Addend
     * @return a * b + c with single rounding
     */
    inline Float FMA(Float a, Float b, Float c) {
        return std::fma(a, b, c);
    }

    // ========================================================================
    // Type Punning with Bit Cast
    // ========================================================================

    /**
     * @brief Reinterpret the bits of one type as another (size must match)
     * @tparam To Destination type
     * @tparam From Source type
     * @param src Source value
     * @return Destination value with same bit representation
     */
    template <class To, class From>
    typename std::enable_if_t<sizeof(To) == sizeof(From) &&
                              std::is_trivially_copyable_v<From> &&
                              std::is_trivially_copyable_v<To>,
                              To>
    Bit_Cast(const From& src) noexcept {
        static_assert(std::is_trivially_constructible_v<To>,
                      "This implementation requires the destination type to be trivially constructible");
        To dst;
        std::memcpy(&dst, &src, sizeof(To));
        return dst;
    }

    /**
     * @brief Convert float to its bit representation as uint32_t
     * @param f Input float
     * @return Bit representation of the float
     */
    inline std::uint32_t FloatToBits(float f) {
        return Bit_Cast<std::uint32_t, float>(f);
    }

    /**
     * @brief Convert uint32_t bit representation back to float
     * @param ui Input uint32_t
     * @return Float with the given bit representation
     */
    inline float BitsToFloat(std::uint32_t ui) {
        return Bit_Cast<float, std::uint32_t>(ui);
    }

    // ========================================================================
    // Next Float (ULP-based Adjacent Values)
    // ========================================================================

    /**
     * @brief Get the next representable float greater than v
     * @param v Input float
     * @return Smallest float > v (or v if already +inf)
     */
    inline float NextFloatUp(float v) {
        // Handle infinity and negative zero
        if (IsInf(v) && v > 0.f)
            return v;
        if (v == -0.f)
            v = 0.f;

        // Advance v to next higher float
        std::uint32_t ui = FloatToBits(v);
        if (v >= 0)
            ++ui;
        else
            --ui;
        return BitsToFloat(ui);
    }

    /**
     * @brief Get the next representable float less than v
     * @param v Input float
     * @return Largest float < v (or v if already -inf)
     */
    inline float NextFloatDown(float v) {
        // Handle infinity and positive zero
        if (IsInf(v) && v < 0.)
            return v;
        if (v == 0.f)
            v = -0.f;

        std::uint32_t ui = FloatToBits(v);
        if (v > 0)
            --ui;
        else
            ++ui;
        return BitsToFloat(ui);
    }

    // ========================================================================
    // Rounding Operations (Directed Rounding)
    // ========================================================================

    /**
     * @brief Add with rounding up
     * @param a First operand
     * @param b Second operand
     * @return NextFloatUp(a + b)
     */
    inline Float AddRoundUp(Float a, Float b) {
        return NextFloatUp(a + b);
    }

    /**
     * @brief Add with rounding down
     * @param a First operand
     * @param b Second operand
     * @return NextFloatDown(a + b)
     */
    inline Float AddRoundDown(Float a, Float b) {
        return NextFloatDown(a + b);
    }

    /**
     * @brief Subtract with rounding up (a - b)
     * @param a First operand
     * @param b Second operand
     * @return NextFloatUp(a - b)
     */
    inline Float SubRoundUp(Float a, Float b) {
        return AddRoundUp(a, -b);
    }

    /**
     * @brief Subtract with rounding down (a - b)
     * @param a First operand
     * @param b Second operand
     * @return NextFloatDown(a - b)
     */
    inline Float SubRoundDown(Float a, Float b) {
        return AddRoundDown(a, -b);
    }

    /**
     * @brief Multiply with rounding up
     * @param a First operand
     * @param b Second operand
     * @return NextFloatUp(a * b)
     */
    inline Float MulRoundUp(Float a, Float b) {
        return NextFloatUp(a * b);
    }

    /**
     * @brief Multiply with rounding down
     * @param a First operand
     * @param b Second operand
     * @return NextFloatDown(a * b)
     */
    inline Float MulRoundDown(Float a, Float b) {
        return NextFloatDown(a * b);
    }

    /**
     * @brief Divide with rounding up (a / b)
     * @param a Numerator
     * @param b Denominator
     * @return NextFloatUp(a / b)
     */
    inline Float DivRoundUp(Float a, Float b) {
        return NextFloatUp(a / b);
    }

    /**
     * @brief Divide with rounding down (a / b)
     * @param a Numerator
     * @param b Denominator
     * @return NextFloatDown(a / b)
     */
    inline Float DivRoundDown(Float a, Float b) {
        return NextFloatDown(a / b);
    }

    /**
     * @brief Square root with rounding up
     * @param a Input value
     * @return NextFloatUp(sqrt(a))
     */
    inline Float SqrtRoundUp(Float a) {
        return NextFloatUp(std::sqrt(a));
    }

    /**
     * @brief Square root with rounding down
     * @param a Input value
     * @return max(0, NextFloatDown(sqrt(a)))
     */
    inline Float SqrtRoundDown(Float a) {
        return std::max<Float>(0, NextFloatDown(std::sqrt(a)));
    }

    /**
     * @brief Fused multiply-add with rounding up
     * @param a Multiplier
     * @param b Multiplier
     * @param c Addend
     * @return NextFloatUp(FMA(a, b, c))
     */
    inline Float FMARoundUp(Float a, Float b, Float c) {
        return NextFloatUp(FMA(a, b, c));
    }

    /**
     * @brief Fused multiply-add with rounding down
     * @param a Multiplier
     * @param b Multiplier
     * @param c Addend
     * @return NextFloatDown(FMA(a, b, c))
     */
    inline Float FMARoundDown(Float a, Float b, Float c) {
        return NextFloatDown(FMA(a, b, c));
    }

    // ========================================================================
    // Basic Math Utilities
    // ========================================================================

    /**
     * @brief Compute square of a value
     * @tparam T Numeric type
     * @param v Input value
     * @return v * v
     */
    template <typename T>
    inline constexpr T Sqr(T v) {
        return v * v;
    }

} // namespace GMath