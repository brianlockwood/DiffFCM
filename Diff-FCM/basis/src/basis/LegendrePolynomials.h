#pragma once

#include "types/simd.h"

template <int N, typename ScalarType>
class LegendrePolynomial
{
public:
    static ScalarType eval(ScalarType x)
    {
        ScalarType N_inv = inv(ScalarType(N));
        return (ScalarType(2*(N-1) + 1)*x*LegendrePolynomial<N-1, ScalarType>::eval(x) - ScalarType(N-1)*LegendrePolynomial<N-2, ScalarType>::eval(x))*N_inv;
    }
};

template <typename ScalarType>
class LegendrePolynomial<0, ScalarType>
{
public:
    static ScalarType eval([[maybe_unused]] ScalarType x)
    {
        return ScalarType(1);
    }
};

template <typename ScalarType>
class LegendrePolynomial<1, ScalarType>
{
public:
    static ScalarType eval([[maybe_unused]] ScalarType x)
    {
        return x;
    }
};
