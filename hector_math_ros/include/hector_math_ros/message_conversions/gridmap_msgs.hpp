// Copyright (c) 2021 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef HECTOR_MATH_ROS_GRIDMAP_MSGS_H
#define HECTOR_MATH_ROS_GRIDMAP_MSGS_H

#include "hector_math/types.h"

#include <grid_map_msgs/msg/grid_map.hpp>
#include <rclcpp/logging.hpp>

namespace hector_math
{
template<typename Scalar, typename MultiArrayMessageType>
Eigen::Ref<const GridMap<Scalar>> mapMultiArrayMessageToGridMap( const MultiArrayMessageType &msg )
{
  bool row_major = false;
  if ( msg.layout.dim[0].label == "column_index" )
    row_major = false;
  else if ( msg.layout.dim[0].label == "row_index" )
    row_major = true;
  else
    RCLCPP_WARN( rclcpp::get_logger( "hector_math" ),
                 "Layout label is not set correctly. Assuming column major." );

  Eigen::Index cols = row_major ? msg.layout.dim.at( 1 ).size : msg.layout.dim.at( 0 ).size;
  Eigen::Index rows = row_major ? msg.layout.dim.at( 0 ).size : msg.layout.dim.at( 1 ).size;
  if ( ( (bool)GridMap<Scalar>::IsRowMajor ) != row_major ) {
    return Eigen::Map<const Eigen::Array<Scalar, Eigen::Dynamic, Eigen::Dynamic,
                                         GridMap<Scalar>::IsRowMajor ? Eigen::ColMajor : Eigen::RowMajor>>(
        msg.data.data(), rows, cols );
  }

  return Eigen::Map<const GridMap<Scalar>>( msg.data.data(), rows, cols );
}

template<typename Scalar>
inline GridMap<Scalar> msgToGridMap( const std_msgs::msg::Float32MultiArray &msg,
                                     int row_start_index = 0, int column_start_index = 0 )
{
  using namespace hector_math::eigen;
  if ( msg.layout.dim.size() < 2 ) {
    RCLCPP_ERROR( rclcpp::get_logger( "hector_math" ),
                  "Could not convert array message to GridMap. Array does not have 2 dimensions." );
    return {};
  }
  if ( msg.layout.dim.size() != 2 ) {
    RCLCPP_WARN( rclcpp::get_logger( "hector_math" ),
                 "FloatArray to GridMap conversion. Array has more than 2 dimensions." );
  }
  Eigen::Array<float, -1, -1> result;
  result = mapMultiArrayMessageToGridMap<float>( msg );

  return flip( shift( result, row_start_index, column_start_index ) ).cast<Scalar>();
}
} // namespace hector_math

#endif // HECTOR_MATH_ROS_GRIDMAP_MSGS_H
