#pragma once

#include "types/simd.h"

#include <array>
#include <cmath>

// Gauss-Legendre Quadrature integrates polynomial of degree
//    p = 2*N - 1 exact where N is the number of sample points

//  Table:
//   N | P
//   -----
//   1 | 1
//   2 | 3
//   3 | 5
//   4 | 7
//   5 | 9

template <int Order>
struct GaussLegendreQuadratureRule;

template <>
struct GaussLegendreQuadratureRule<1>
{
    static constexpr int N = 1;
    static constexpr std::array<double, N> points = {0.0};
    static constexpr std::array<double, N> weights = {2.0};
};

static constexpr double SQRT3 = 1.73205080757;

template <>
struct GaussLegendreQuadratureRule<3>
{
    static constexpr int N = 2;
    static constexpr std::array<double, N> points = {-1.0/SQRT3, 1.0/SQRT3};
    static constexpr std::array<double, N> weights = {1.0, 1.0};
};

static constexpr double SQRT5 = 2.2360679775;

template <>
struct GaussLegendreQuadratureRule<5>
{
    static constexpr int N = 3;
    static constexpr std::array<double, N> points = {-SQRT3/SQRT5, 0.0, SQRT3/SQRT5};
    static constexpr std::array<double, N> weights = {5.0/9.0, 8.0/9.0, 5.0/9.0};
};


// TODO: Should use higher precision data
template <>
struct GaussLegendreQuadratureRule<7>
{
    static constexpr int N = 4;
    static constexpr std::array<double, N> points = {-0.861136,-0.339981,0.339981,0.861136};
    static constexpr std::array<double, N> weights = {0.347855,0.652145,0.652145,0.347855};
};


// TODO: Should use higher precision data
template <>
struct GaussLegendreQuadratureRule<9>
{
    static constexpr int N = 5;
    static constexpr std::array<double, N> points = {-0.90618,-0.538469, 0.0, 0.538469, 0.90618};
    static constexpr std::array<double, N> weights = {0.236927, 0.478629, 0.568889, 0.478629, 0.236927};
};


// TODO:
// Template Rule on Dimension, have array for each dimension (x, y, z)
// Can do SIMD over quadrature points by grabbing each array N elements at a time
// and passing to call back function (Other way around would mean array of a Vector2 or Vector3, 
// which means these would have to fit in SIMD register)

namespace GaussLegendreQuadrature
{

template <int Order, typename F>
auto integrate1D(const F &integrand)
{
    constexpr auto w = GaussLegendreQuadratureRule<Order>::weights;
    constexpr auto points = GaussLegendreQuadratureRule<Order>::points;

    auto sum = w[0]*integrand(points[0]);
    for (int i = 1; i < GaussLegendreQuadratureRule<Order>::N; ++i)
    {
        sum += w[i]*integrand(points[i]);
    }

    return sum;
}

template <int Order, typename F>
void gaussSum(const F &func)
{
    constexpr auto w = GaussLegendreQuadratureRule<Order>::weights;
    constexpr auto points = GaussLegendreQuadratureRule<Order>::points;

    for (int i = 0; i < GaussLegendreQuadratureRule<Order>::N; ++i)
    {
        func(w[i], points[i]);
    }
}

template <int Order, typename F>
void gaussSum2D(const F &func)
{
    constexpr auto w = GaussLegendreQuadratureRule<Order>::weights;
    constexpr auto points = GaussLegendreQuadratureRule<Order>::points;

    for (int i = 0; i < GaussLegendreQuadratureRule<Order>::N; ++i)
    {
        for (int j = 0; j < GaussLegendreQuadratureRule<Order>::N; ++j)
        {
            func(w[i]*w[j], points[i], points[j]);
        }
    }
}

// #ifdef SSE2
// template <int Order, typename F>
// auto integrate1D_SIMD(const F &integrand)
// {
//     constexpr auto w = GaussLegendreQuadratureRule<Order>::weights;
//     constexpr auto points = GaussLegendreQuadratureRule<Order>::points;

//     v2d sum = 0.0;
//     for (int i = 0; GaussLegendreQuadratureRule<Order>::N; i = i + 2)
//     {
//         v2d points_v(points[i], points[i+1]);
//         v2d w_v(w[i], w[i+1]);
//         sum = sum + w_v*integrand(points_v);
//     }

//     return sum.reduceAdd();
// }
// #elif AVX
// template <int Order, typename F>
// auto integrate1D_SIMD(const F &integrand)
// {
//     constexpr auto w = GaussLegendreQuadratureRule<Order>::weights;
//     constexpr auto points = GaussLegendreQuadratureRule<Order>::points;

//     v4d sum = 0.0;
//     for (int i = 0; GaussLegendreQuadratureRule<Order>::N; i = i + 4)
//     {
//         v4d points_v(points[i], points[i+1], points[i+2], points[i+3]);
//         v4d w_v(w[i], w[i+1], w[i+2], w[i+3]);
//         sum = sum + w_v*integrand(points_v);
//     }

//     return sum.reduceAdd();
// }
// #endif

// template <int Order, typename F>
// auto integrate2D(const F &integrand)
// {
//     constexpr auto w = GaussLegendreQuadratureRule<Order>::weights;
//     constexpr auto points = GaussLegendreQuadratureRule<Order>::points;

//     auto sum = 0.0;
//     for (int i = 0; i < GaussLegendreQuadratureRule<Order>::N; ++i)
//     {
//         for (int j = 0; j < GaussLegendreQuadratureRule<Order>::N; ++j)
//         {
//             sum += w[i]*w[j]*integrand(points[i], points[j]);
//         }

//     return sum;
// }

// template <int Order, typename F, typename T>
// auto integrate3D(const F &integrand, const T &initial)
// {
//     constexpr auto w = GaussLegendreQuadratureRule<Order>::weights;
//     constexpr auto points = GaussLegendreQuadratureRule<Order>::points;

//     auto sum = initial;
//     for (int i = 0; i < GaussLegendreQuadratureRule<Order>::N; ++i)
//     {
//         for (int j = 0; j < GaussLegendreQuadratureRule<Order>::N; ++j)
//         {
//             for (int k = 0; k < GaussLegendreQuadratureRule<Order>::N; ++k)
//             {
//                 sum += w[i]*w[j]*w[k]*integrand(points[i], points[j], points[k]);
//             }
//         }
//     }

//     return sum;
// }

}