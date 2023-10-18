#include "basis/LegendrePolynomials.h"

#include <benchmark/benchmark.h>

// static void BM_DOUBLE(benchmark::State& state) {
//   for (auto _ : state)
//   {
//     benchmark::DoNotOptimize(LegendrePolynomial<10, double>::eval(state.range(0)));
//     benchmark::DoNotOptimize(LegendrePolynomial<10, double>::eval(state.range(1)));
//     benchmark::DoNotOptimize(LegendrePolynomial<10, double>::eval(0.5*state.range(0)));
//     benchmark::DoNotOptimize(LegendrePolynomial<10, double>::eval(0.5*state.range(1)));
//   }
// }
// Register the function as a benchmark
//BENCHMARK(BM_DOUBLE)->Args({-1,1});

#ifdef SSE2
// Define another benchmark
// static void BM_SIMD(benchmark::State& state) {
//   for (auto _ : state)
//   {
//     v2d x{state.range(0), state.range(1)};
//     benchmark::DoNotOptimize(LegendrePolynomial<10, v2d>::eval(x));

//     v2d x1{0.5*state.range(0), 0.5*state.range(1)};
//     benchmark::DoNotOptimize(LegendrePolynomial<10, v2d>::eval(x1));
//   }
// }
//BENCHMARK(BM_SIMD)->Args({-1,1});
#endif

#ifdef AVX
// Define another benchmark
// static void BM_SIMD_AVX(benchmark::State& state) {
//   for (auto _ : state)
//   {
//     v4d x{state.range(0), state.range(1), 0.5*state.range(0), 0.5*state.range(1)};
//     benchmark::DoNotOptimize(LegendrePolynomial<10, v4d>::eval(x));
//   }
// }
//BENCHMARK(BM_SIMD_AVX)->Args({-1,1});
#endif

//BENCHMARK_MAIN();