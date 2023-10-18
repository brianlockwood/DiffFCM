#pragma once

#include <utility>
#include <array>

#include <cmath>

#ifdef SSE2
#include <xmmintrin.h>
#endif

#ifdef AVX
#include <immintrin.h>
#endif

template <int Size, typename Real>
struct SimdTypeTraits;


#ifdef SSE2
template <>
struct SimdTypeTraits<2, double>
{
    using Type = __m128d;

    static Type create(double a)
    {
        return _mm_set_pd(a,a);
    }

    static Type create(double a, double b)
    {
        return _mm_set_pd(b,a);
    }

    static Type mul(const Type &a, const Type &b)
    {
        return _mm_mul_pd(a, b);
    }

    static Type inv(const Type &a)
    {
        Type one = _mm_set_pd(1.0, 1.0);
        return _mm_div_pd(one, a);
    }

    static Type sub(const Type &a, const Type &b)
    {
        return _mm_sub_pd(a, b);
    }

    static Type add(const Type &a, const Type &b)
    {
        return _mm_add_pd(a, b);
    }

    static void store(std::array<double,2> &result, const Type &a)
    {
        _mm_store_pd(result.data(), a);
    }

    static double reduceAdd(const Type &a)
    {
        std::array<double,2> result;
        _mm_store_pd(result.data(), a);
        return result[0] + result[1];
    }

    static Type cos(const Type &a)
    {
        std::array<double,2> result;
        _mm_store_pd(result.data(), a);
        return _mm_set_pd(std::cos(result[0]), std::cos(result[1]));
    }
};
#elif AVX
template <>
struct SimdTypeTraits<4, double>
{
    using Type = __m256d;

    static Type create(double a)
    {
        return _mm256_set_pd(a,a,a,a);
    }

    static Type create(double a, double b, double c, double d)
    {
        return _mm256_set_pd(d,c,b,a);
    }

    static Type mul(const Type &a, const Type &b)
    {
        return _mm256_mul_pd(a, b);
    }

    static Type inv(const Type &a)
    {
        Type one = _mm256_set_pd(1.0, 1.0, 1.0, 1.0);
        return _mm256_div_pd(one, a);
    }

    static Type sub(const Type &a, const Type &b)
    {
        return _mm256_sub_pd(a, b);
    }

    static Type add(const Type &a, const Type &b)
    {
        return _mm256_add_pd(a, b);
    }

    static void store(std::array<double,4> &result, const Type &a)
    {
        _mm256_store_pd(result.data(), a);
    }

    static double reduceAdd(const Type &a)
    {
        std::array<double,4> result;
        _mm256_store_pd(result.data(), a);
        return result[0] + result[1] + result[2] + result[3];
    }

    static Type cos(const Type &a)
    {
        std::array<double,4> result;
        _mm256_store_pd(result.data(), a);
        return _mm256_set_pd( std::cos(result[0]), std::cos(result[1]), 
                 std::cos(result[2]), std::cos(result[3]) );
    }
};
#endif

template <int Size, typename Real>
class v
{
public:
    using SimdTraits = SimdTypeTraits<Size, Real>;
    using Simd_t = typename SimdTraits::Type;

    template <typename... Args>
    v(Args... args)
        : data(SimdTraits::create(std::forward<Args>(args)...))
    {}

    v(const Simd_t &data)
        : data(data)
    {}

    v(Simd_t &&data)
        : data(data)
    {}

    v& operator=(const Simd_t &other) 
    {
        data = other;
        return *this;
    }

    v& operator=(Simd_t &&other) 
    {
        data = other;
        return *this;
    }

    // Rule of 5
    v(const v &other)
        : data(other.data)
    {}

    v(v &&other)
        : data(other.data)
    {}

    ~v() = default;

    v& operator=(const v &other) 
    {
        data = other.data;
        return *this;
    }

    v& operator=(v &&other) 
    {
        data = other.data;
        return *this;
    }

    std::array<Real, Size> asArray()
    {
        std::array<Real, Size> result;
        SimdTypeTraits<Size, Real>::store(result, data);

        return result;
    }

    Real reduceAdd()
    {
        return SimdTypeTraits<Size, Real>::reduceAdd(data);
    }

    Simd_t data;
};

template <int Size, typename Real>
inline v<Size, Real> operator*(const v<Size, Real> &a, const v<Size, Real> &b)
{
    return SimdTypeTraits<Size, Real>::mul(a.data,b.data);
}

template <int Size, typename Real>
inline v<Size, Real> operator-(const v<Size, Real> &a, const v<Size, Real> &b)
{
    return SimdTypeTraits<Size, Real>::sub(a.data,b.data);
}

template <int Size, typename Real>
inline v<Size, Real> operator+(const v<Size, Real> &a, const v<Size, Real> &b)
{
    return SimdTypeTraits<Size, Real>::add(a.data,b.data);
}

template <int Size, typename Real>
inline v<Size, Real> inv(const v<Size, Real> &a)
{
    return SimdTypeTraits<Size, Real>::inv(a.data);
}

inline double inv(double a)
{
    return 1.0/a;
}

#ifdef SSE2
    using v2d = v<2,double>; 
#endif

#ifdef AVX
    using v4d = v<4,double>; 
#endif

namespace Math
{
template <int Size, typename Real>
inline v<Size, Real> cos(const v<Size, Real> &a)
{
    return SimdTypeTraits<Size, Real>::cos(a.data);
}
inline double cos(double a)
{
    return std::cos(a);
}
}
