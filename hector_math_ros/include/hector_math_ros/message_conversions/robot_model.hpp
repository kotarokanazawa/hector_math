// Copyright (c) 2021 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef HECTOR_MATH_ROS_ROBOT_MODEL_H
#define HECTOR_MATH_ROS_ROBOT_MODEL_H

// You will need to depend on moveit and moveit_msgs if you use this header.

#include "hector_math/robot/robot_model.h"
#include <moveit/robot_model_loader/robot_model_loader.hpp>
#include <moveit/robot_state/conversions.hpp>
#include <moveit/robot_state/robot_state.hpp>
#include <moveit_msgs/msg/display_robot_state.hpp>

namespace hector_math
{

template<typename Scalar>
inline moveit::core::RobotState
robotModelToRobotState( const RobotModel<Scalar> &model, const urdf::ModelSharedPtr &urdf,
                        const srdf::ModelSharedPtr &srdf = std::make_shared<srdf::Model>() )
{
  moveit::core::RobotModelPtr robot_model = std::make_shared<moveit::core::RobotModel>( urdf, srdf );
  moveit::core::RobotState state( robot_model );
  const auto &names = model.jointNames();
  const auto &positions = model.jointPositions();
  const auto &variable_names = state.getVariableNames();
  for ( size_t i = 0; i < names.size(); ++i ) {
    if ( std::find( variable_names.begin(), variable_names.end(), names[i] ) == variable_names.end() )
      continue;
    state.setVariablePosition( names[i], positions[i] );
  }
  state.update();
  return state;
}

template<typename Scalar>
inline moveit::core::RobotState robotModelToRobotState( const RobotModel<Scalar> &model,
                                                        const urdf::Model &urdf )
{
  return robotModelToRobotState( model, std::make_shared<urdf::Model>( urdf ),
                                 std::make_shared<srdf::Model>() );
}

template<typename Scalar>
inline moveit::core::RobotState robotModelToRobotState( const RobotModel<Scalar> &model,
                                                        const urdf::Model &urdf,
                                                        const srdf::Model &srdf )
{
  return robotModelToRobotState( model, std::make_shared<urdf::Model>( urdf ),
                                 std::make_shared<srdf::Model>( srdf ) );
}
} // namespace hector_math

#endif // HECTOR_MATH_ROS_ROBOT_MODEL_H
