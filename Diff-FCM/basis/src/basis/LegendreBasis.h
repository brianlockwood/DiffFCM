#pragma once

#include "LegendrePolynomials.h"

#include <cmath>

double invSqrt(double x)
{
    return 1.0/std::sqrt(x);
}


template <typename ScalarType>
class LegendreBasis1D
{
public:

    // 1D Basis Functions 
    //  -- 0-1  : Linear Basis
    //  -- i > 2: Integrated Legendre Polynomials (1/sqrt(4*j-2) * (P_i - P_i-2) 
    template <int i>
    static constexpr ScalarType eval(ScalarType x)
    {
        if constexpr (i == 0)
        {
            ScalarType oneHalf = ScalarType(0.5);
            ScalarType one = ScalarType(1.0);
            return oneHalf * (one - x);
        }
       
        if constexpr (i == 1)
        {
            ScalarType oneHalf = ScalarType(0.5);
            ScalarType one = ScalarType(1.0);
            return oneHalf * (one + x);
        }

        if constexpr (i >= 2)
        {
            ScalarType scalar = invSqrt(4*i - 2);

            return scalar*(LegendrePolynomial<i, ScalarType>::eval(x) - LegendrePolynomial<i-2, ScalarType>::eval(x));
        }
    }
};


template <typename ScalarType>
class LegendreBasis2D
{
public:

    // 2D Basis Functions (For Hex's)
    //  -- 0 - 3: Linear Nodal modes
    //  -- 4 - 7: Edge Quadratic Modes
    template <int i>
    static constexpr ScalarType eval(ScalarType x, ScalarType y)
    {
        if constexpr (i == 0)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*LegendreBasis1D<ScalarType>::template eval<0>(y);
        }

        if constexpr (i == 1)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*LegendreBasis1D<ScalarType>::template eval<0>(y);
        }

        if constexpr (i == 2)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*LegendreBasis1D<ScalarType>::template eval<1>(y);
        }

        if constexpr (i == 3)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*LegendreBasis1D<ScalarType>::template eval<1>(y);
        }
       
        if constexpr (i == 4)
        {
            return LegendreBasis1D<ScalarType>::template eval<2>(x)*LegendreBasis1D<ScalarType>::template eval<0>(y);
        }

        if constexpr (i == 5)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*LegendreBasis1D<ScalarType>::template eval<2>(y);
        }

        if constexpr (i == 6)
        {
            return LegendreBasis1D<ScalarType>::template eval<2>(x)*LegendreBasis1D<ScalarType>::template eval<1>(y);
        }

        if constexpr (i == 7)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*LegendreBasis1D<ScalarType>::template eval<2>(y);
        }

        if constexpr (i == 8)
        {
            return LegendreBasis1D<ScalarType>::template eval<2>(x)*LegendreBasis1D<ScalarType>::template eval<2>(y);
        }
    }
};


template <typename ScalarType>
class LegendreBasis3D
{
public:

    // 3D Basis Functions (For Hex's)
    //  -- 0 - 7: Linear Nodal modes
    template <int i>
    static constexpr ScalarType eval(ScalarType x, ScalarType y, ScalarType z)
    {
        if constexpr (i == 0)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }

        if constexpr (i == 1)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }

        if constexpr (i == 2)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }

        if constexpr (i == 3)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }
       
        if constexpr (i == 4)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }

        if constexpr (i == 5)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }

        if constexpr (i == 6)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }

        if constexpr (i == 7)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }
    }

    static constexpr ScalarType eval(int i, ScalarType x, ScalarType y, ScalarType z)
    {
        if (i == 0)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }
        else if (i == 1)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }
        else if (i == 2)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }
        else if (i == 3)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<0>(z);
        }
        else if (i == 4)
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }
        else if (i == 5)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<0>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }
        else if (i == 6)
        {
            return LegendreBasis1D<ScalarType>::template eval<1>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }
        else
        {
            return LegendreBasis1D<ScalarType>::template eval<0>(x)*
                        LegendreBasis1D<ScalarType>::template eval<1>(y) *
                        LegendreBasis1D<ScalarType>::template eval<1>(z);
        }
    }
};
