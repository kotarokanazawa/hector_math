// Copyright (c) 2021 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "../benchmark/iterators_input.h"
#include "hector_math/iterators/polygon_iterator.h"
#include <fstream>
#include <iostream>

using namespace hector_math;

using Scalar = double;

template<typename Derived>
void dumpEigenDenseBase( const Eigen::DenseBase<Derived> &dense, const std::string &path )
{
  std::ofstream output( path, std::ios_base::out );
  if ( !output.is_open() ) {
    std::cerr << "Couldn't open file to dump heightmap!" << std::endl;
    return;
  }
  for ( Eigen::Index x = 0; x < dense.rows(); ++x ) {
    for ( Eigen::Index y = 0; y < dense.cols(); ++y ) {
      output << dense( x, y );
      if ( y != dense.cols() - 1 )
        output << ",";
    }
    if ( x != dense.rows() - 1 )
      output << std::endl;
  }
  output.flush();
  output.close();
}

int main( int, char ** )
{
  Polygon<Scalar> polygon = createPolygon<Scalar>() / Scalar( 0.05 );
  GridMap<Scalar> map( 20, 20 );
  map.setConstant( 0 );

  iteratePolygon<Scalar>( polygon, map.rows(), map.cols(),
                          [&map]( Eigen::Index x, Eigen::Index y ) { map( x, y ) = 1; } );

  dumpEigenDenseBase( map, "polygon.txt" );
  polygon = createSkewedQuadranglePolygon<Scalar>() / Scalar( 0.05 );
  map.setConstant( 0 );

  iteratePolygon<Scalar>( polygon, map.rows(), map.cols(),
                          [&map]( Eigen::Index x, Eigen::Index y ) { map( x, y ) = 1; } );

  dumpEigenDenseBase( map, "quadrangle_polygon.txt" );

  return 0;
}
