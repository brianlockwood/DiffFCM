#include "basis/GaussLegendreQuadratureRule.h"

#include <cmath>

#include <benchmark/benchmark.h>

#include "types/Matrix.h"

#include "basis/Bspline.h"

static void BM_GaussSum(benchmark::State& state) {
    using Basis = BSpline<3, double>;
    
    Basis bspline;  
    for (auto _ : state)
    {
        Matrix<double, Basis::size()> me(0.0);

        auto F = [&bspline, &me](auto w, auto x) -> void
        { 
            Vector<double, Basis::size()> phi;
            for (int i = 0; i < Basis::size(); ++i)
                phi(i) = bspline(i, x);

            for (int i = 0; i < Basis::size(); ++i)
                for (int j = 0; j < Basis::size(); ++j)
                    me(i,j) += w*phi(i)*phi(j);
        };

        GaussLegendreQuadrature::gaussSum<5>(F);

        benchmark::DoNotOptimize(me);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_GaussSum);

static void BM_Integrate(benchmark::State& state) {
    using Basis = BSpline<3, double>;
    
    Basis bspline;

    auto F = [&bspline](auto x) -> Matrix<double, Basis::size()> 
    { 
        Vector<double, Basis::size()> phi;
        for (int i = 0; i < Basis::size(); ++i)
            phi(i) = bspline(i, x);

        Matrix<double, Basis::size()> me(0.0);
        for (int i = 0; i < Basis::size(); ++i)
            for (int j = 0; j < Basis::size(); ++j)
                me(i,j) = phi(i)*phi(j);

        return me;
    };

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(GaussLegendreQuadrature::integrate1D<5>(F));
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Integrate);

static void BM_IntegrateScalar(benchmark::State& state) {
    using Basis = BSpline<3, double>;
    
    Basis bspline;

    for (auto _ : state)
    {
        Matrix<double, Basis::size()> me(0.0);
        for (int i = 0; i < Basis::size(); ++i)
        {
            for (int j = 0; j < Basis::size(); ++j)
            {
                auto F = [&bspline, &i, &j](auto x) -> double
                {   
                    return bspline(i, x)*bspline(j, x);
                };

                me(i,j) = GaussLegendreQuadrature::integrate1D<5>(F);
            }
        }

        benchmark::DoNotOptimize(me);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_IntegrateScalar);


BENCHMARK_MAIN();