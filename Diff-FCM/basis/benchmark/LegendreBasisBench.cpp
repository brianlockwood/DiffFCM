#include "basis/LegendreBasis.h"

#include <benchmark/benchmark.h>

// static void BM_BASIS_DOUBLE(benchmark::State& state) {
//   for (auto _ : state)
//   {
//     benchmark::DoNotOptimize(LegendreBasis1D<double>::eval<0>(state.range(0)));
//     benchmark::DoNotOptimize(LegendreBasis1D<double>::eval<0>(state.range(1)));
//     benchmark::DoNotOptimize(LegendreBasis1D<double>::eval<0>(0.5*state.range(0)));
//   }
// }
// // Register the function as a benchmark
// BENCHMARK(BM_BASIS_DOUBLE)->Args({-1,1});

#ifdef SSE2
// Define another benchmark
// static void BM_BASIS_SIMD(benchmark::State& state) {
//   for (auto _ : state)
//   {
//     v2d x{state.range(0), state.range(1)};
//     benchmark::DoNotOptimize(LegendrePolynomial<10, v2d>::eval(x));

//     v2d x1{0.5*state.range(0), 0.5*state.range(1)};
//     benchmark::DoNotOptimize(LegendrePolynomial<10, v2d>::eval(x1));
//   }
// }
//BENCHMARK(BM_BASIS_SIMD)->Args({-1,1});
#endif

#ifdef AVX
// Define another benchmark
// static void BM_BASIS_SIMD_AVX(benchmark::State& state) {
//   for (auto _ : state)
//   {
//     v4d x{state.range(0), state.range(1), 0.5*state.range(0), 0.5*state.range(1)};
//     benchmark::DoNotOptimize(LegendreBasis1D<v4d>::eval<0>(x));
//   }
// }
//BENCHMARK(BM_BASIS_SIMD_AVX)->Args({-1,1});
#endif

//BENCHMARK_MAIN();