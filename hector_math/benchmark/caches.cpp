// Copyright (c) 2021 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
#include "hector_math/containers/quaternion_cache.h"

#include <benchmark/benchmark.h>
#include <random>

using namespace hector_math;

template<typename Scalar, QuaternionBinningMode mode>
static void quaternionCacheInsert( benchmark::State &state )
{
  QuaternionCache<Scalar, int, mode> cache;
  std::vector<Eigen::Quaternion<Scalar>, Eigen::aligned_allocator<Eigen::Quaternion<Scalar>>> quaternions;
  quaternions.resize( state.max_iterations );
  for ( benchmark::IterationCount i = 0; i < state.max_iterations; ++i )
    quaternions[i] = Eigen::Quaternion<Scalar>::UnitRandom();
  int i = 0;
  for ( auto _ : state ) { cache.insert( quaternions[i], i ); }
}

template<typename Scalar, QuaternionBinningMode mode>
static void quaternionCacheFind( benchmark::State &state )
{
  QuaternionCache<Scalar, int, mode> cache;
  std::vector<Eigen::Quaternion<Scalar>, Eigen::aligned_allocator<Eigen::Quaternion<Scalar>>> quaternions;
  quaternions.resize( state.max_iterations );
  for ( benchmark::IterationCount i = 0; i < state.max_iterations; ++i ) {
    quaternions[i] = Eigen::Quaternion<Scalar>::UnitRandom();
    cache.insert( quaternions[i], i );
  }
  int i = 0;
  for ( auto _ : state ) {
    if ( cache.find( quaternions[i] )->second != i )
      throw std::runtime_error( "Unexpected" );
  }
}

BENCHMARK_TEMPLATE( quaternionCacheInsert, float, QuaternionBinningMode::LargestDim )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheInsert, float, QuaternionBinningMode::Spherical )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheInsert, float, QuaternionBinningMode::SphericalFibonacci )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheFind, float, QuaternionBinningMode::LargestDim )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheFind, float, QuaternionBinningMode::Spherical )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheFind, float, QuaternionBinningMode::SphericalFibonacci )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );

BENCHMARK_TEMPLATE( quaternionCacheInsert, double, QuaternionBinningMode::LargestDim )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheInsert, double, QuaternionBinningMode::Spherical )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheInsert, double, QuaternionBinningMode::SphericalFibonacci )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheFind, double, QuaternionBinningMode::LargestDim )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheFind, double, QuaternionBinningMode::Spherical )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );
BENCHMARK_TEMPLATE( quaternionCacheFind, double, QuaternionBinningMode::SphericalFibonacci )
    ->Unit( benchmark::kNanosecond )
    ->Iterations( 2000000 );

BENCHMARK_MAIN();
