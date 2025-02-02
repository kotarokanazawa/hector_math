// Copyright (c) 2022 Aljoscha Schmidt. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <gtest/gtest.h>

#undef NDEBUG
#include <hector_math/containers/bounded_vector.h>

using namespace hector_math;

template<typename Scalar>
class BoundedVectorTest : public testing::Test
{
};

typedef testing::Types<float, double, int> Implementations;

TYPED_TEST_CASE( BoundedVectorTest, Implementations );

TYPED_TEST( BoundedVectorTest, tests )
{
  using Scalar = TypeParam;
  const size_t maxSize = 25;
  BoundedVector<Scalar, maxSize> vector;
  EXPECT_TRUE( vector.size() == 0 );
  // add items 0,1,...,maxSize-1
  for ( size_t i = 0; i < maxSize; i++ ) {
    vector.push_back( Scalar( i ) );
    EXPECT_TRUE( vector.size() == i + 1 );
  }
  EXPECT_THROW( vector.push_back( 0 ), std::length_error );
  // delete last item
  vector.pop_back();
  EXPECT_TRUE( vector.size() == maxSize - 1 );
  // delete first item -> all other items must be moved -> 1,2,..maxSize-2
  vector.erase( vector.begin() );
  EXPECT_TRUE( vector.size() == maxSize - 2 );
  for ( size_t i = 0; i < maxSize - 2; i++ ) {
    EXPECT_TRUE( vector[i] == static_cast<Scalar>( i + 1 ) );
  }
  // delete first 3 items -> all other items must be moved -> 4,5,..maxSize-5
  vector.erase( vector.begin(), vector.begin() + 3 ); // removes all elements in [first,last)
  EXPECT_TRUE( vector.size() == maxSize - 2 - 3 );
  for ( size_t i = 0; i < maxSize - 6; i++ ) {
    EXPECT_TRUE( vector[i] == static_cast<Scalar>( i + 4 ) );
  }
  vector.clear();
  EXPECT_TRUE( vector.size() == 0 );
  // construct items 0,1,...,maxSize-1
  for ( size_t i = 0; i < maxSize; i++ ) {
    vector.emplace_back( Scalar( i ) );
    EXPECT_TRUE( vector.size() == i + 1 );
  }
  EXPECT_THROW( vector.emplace_back( 0 ), std::length_error );
  EXPECT_TRUE( vector.front() == 0 );
  EXPECT_TRUE( vector.back() == maxSize - 1 );
  // Should not die as long as we stay within maxSize.
  vector.reserve( maxSize - 1 );
  vector.reserve( maxSize );
  EXPECT_DEATH( vector.reserve( maxSize + 1 ),
                "Bounded vector can not reserve more than max size!" );
}

int main( int argc, char **argv )
{
  testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
