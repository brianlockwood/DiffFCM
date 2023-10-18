#include "basis/Bspline.h"

#include <benchmark/benchmark.h>

static void BSpline_1stOrder_double(benchmark::State& state) {
  BSpline<1, double> bspline;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(bspline(0, state.range(1)));
  }
}
BENCHMARK(BSpline_1stOrder_double)->Args({-1,1});

static void BSpline_2ndOrder_double(benchmark::State& state) {
  BSpline<2, double> bspline;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(bspline(0, state.range(1)));
  }
}
BENCHMARK(BSpline_2ndOrder_double)->Args({-1,1});

static void BSpline_3rdOrder_double(benchmark::State& state) {
  BSpline<3, double> bspline;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(bspline(0, state.range(1)));
  }
}
BENCHMARK(BSpline_3rdOrder_double)->Args({-1,1});

static void BSpline_9thOrder_double(benchmark::State& state) {
  BSpline<9, double> bspline;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(bspline(0, state.range(1)));
  }
}
BENCHMARK(BSpline_9thOrder_double)->Args({-1,1});

//BENCHMARK_MAIN();