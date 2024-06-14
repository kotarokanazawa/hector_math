// Copyright (c) 2021 Stefan Fabian. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef HECTOR_MATH_ROS_CONVERSIONS_GEOMETRY_MSGS_H
#define HECTOR_MATH_ROS_CONVERSIONS_GEOMETRY_MSGS_H

#include <hector_math/types.h>

#include <Eigen/Geometry>
#include <geometry_msgs/msg/pose.hpp>
#include <geometry_msgs/msg/transform.hpp>
#include <geometry_msgs/msg/twist.hpp>

namespace hector_math
{
/*!
 * IMPORTANT: These conversion methods are provided as headers but the library does not depend on
 * the message types. Hence, make sure that your project depends on them if you use them.
 */
template<typename Scalar>
inline Pose<Scalar> msgToPose( const geometry_msgs::msg::Pose &msg );
template<typename Scalar>
inline Pose<Scalar> msgToPose( const geometry_msgs::msg::Transform &msg );

template<typename Scalar>
inline Eigen::Quaternion<Scalar> msgToQuaternion( const geometry_msgs::msg::Quaternion &msg );

template<typename Scalar>
inline Isometry3<Scalar> msgToTransform( const geometry_msgs::msg::Pose &msg );
template<typename Scalar>
inline Isometry3<Scalar> msgToTransform( const geometry_msgs::msg::Transform &msg );

template<typename Scalar>
inline Twist<Scalar> msgToTwist( const geometry_msgs::msg::Twist &msg );

template<typename Scalar>
inline Vector3<Scalar> msgToVector( const geometry_msgs::msg::Point &msg );
template<typename Scalar>
inline Vector3<Scalar> msgToVector( const geometry_msgs::msg::Vector3 &msg );

template<typename Derived>
inline geometry_msgs::msg::Point vectorToPointMsg( const Eigen::DenseBase<Derived> &vec );
template<typename Derived>
inline geometry_msgs::msg::Vector3 vectorToVectorMsg( const Eigen::DenseBase<Derived> &vec );

template<typename Scalar>
inline geometry_msgs::msg::Pose poseToPoseMsg( const Pose<Scalar> &pose );
template<typename Scalar>
inline geometry_msgs::msg::Transform poseToTransformMsg( const Pose<Scalar> &pose );

template<typename Scalar>
inline geometry_msgs::msg::Quaternion quaternionToMsg( const Eigen::Quaternion<Scalar> &q );

template<typename Scalar>
inline geometry_msgs::msg::Pose transformToPoseMsg( const Isometry3<Scalar> &pose );
template<typename Scalar>
inline geometry_msgs::msg::Transform transformToTransformMsg( const Isometry3<Scalar> &pose );

template<typename Scalar>
inline geometry_msgs::msg::Twist twistToMsg( const hector_math::Twist<Scalar> &twist );

template<typename Scalar>
Pose<Scalar> msgToPose( const geometry_msgs::msg::Pose &msg )
{
  return { msgToVector<Scalar>( msg.position ), msgToQuaternion<Scalar>( msg.orientation ) };
}

template<typename Scalar>
Pose<Scalar> hector_math::msgToPose( const geometry_msgs::msg::Transform &msg )
{
  return { msgToVector<Scalar>( msg.translation ), msgToQuaternion<Scalar>( msg.rotation ) };
}

template<typename Scalar>
Eigen::Quaternion<Scalar> msgToQuaternion( const geometry_msgs::msg::Quaternion &msg )
{
  return { static_cast<Scalar>( msg.w ), static_cast<Scalar>( msg.x ), static_cast<Scalar>( msg.y ),
           static_cast<Scalar>( msg.z ) };
}

template<typename Scalar>
Isometry3<Scalar> msgToTransform( const geometry_msgs::msg::Pose &msg )
{
  Isometry3<Scalar> transform = Isometry3<Scalar>::Identity();
  transform.linear() = msgToQuaternion<Scalar>( msg.orientation ).toRotationMatrix();
  transform.translation() = msgToVector<Scalar>( msg.position );
  return transform;
}

template<typename Scalar>
Isometry3<Scalar> hector_math::msgToTransform( const geometry_msgs::msg::Transform &msg )
{
  Isometry3<Scalar> transform = Isometry3<Scalar>::Identity();
  transform.linear() = msgToQuaternion<Scalar>( msg.rotation ).toRotationMatrix();
  transform.translation() = msgToVector<Scalar>( msg.translation );
  return transform;
}

template<typename Scalar>
Twist<Scalar> msgToTwist( const geometry_msgs::msg::Twist &msg )
{
  return Twist<Scalar>{ msgToVector<Scalar>( msg.linear ), msgToVector<Scalar>( msg.angular ) };
}

template<typename Scalar>
Vector3<Scalar> msgToVector( const geometry_msgs::msg::Point &msg )
{
  return { static_cast<Scalar>( msg.x ), static_cast<Scalar>( msg.y ), static_cast<Scalar>( msg.z ) };
}

template<typename Scalar>
Vector3<Scalar> hector_math::msgToVector( const geometry_msgs::msg::Vector3 &msg )
{
  return { static_cast<Scalar>( msg.x ), static_cast<Scalar>( msg.y ), static_cast<Scalar>( msg.z ) };
}

template<typename Derived>
geometry_msgs::msg::Point vectorToPointMsg( const Eigen::DenseBase<Derived> &vec )
{
  geometry_msgs::msg::Point msg;
  msg.x = vec.x();
  msg.y = vec.y();
  msg.z = vec.z();
  return msg;
}

template<typename Derived>
geometry_msgs::msg::Vector3 vectorToVectorMsg( const Eigen::DenseBase<Derived> &vec )
{
  geometry_msgs::msg::Vector3 msg;
  msg.x = vec.x();
  msg.y = vec.y();
  msg.z = vec.z();
  return msg;
}

template<typename Scalar>
geometry_msgs::msg::Pose poseToPoseMsg( const Pose<Scalar> &pose )
{
  geometry_msgs::msg::Pose msg;
  msg.position = vectorToPointMsg( pose.translation() );
  msg.orientation = quaternionToMsg( pose.orientation() );
  return msg;
}

template<typename Scalar>
geometry_msgs::msg::Transform poseToTransformMsg( const Pose<Scalar> &pose )
{
  geometry_msgs::msg::Transform msg;
  msg.translation = vectorToVectorMsg( pose.translation() );
  msg.rotation = quaternionToMsg( pose.orientation() );
  return msg;
}

template<typename Scalar>
geometry_msgs::msg::Quaternion quaternionToMsg( const Eigen::Quaternion<Scalar> &q )
{
  geometry_msgs::msg::Quaternion msg;
  msg.w = q.w();
  msg.x = q.x();
  msg.y = q.y();
  msg.z = q.z();
  return msg;
}

template<typename Scalar>
geometry_msgs::msg::Pose transformToPoseMsg( const Isometry3<Scalar> &pose )
{
  geometry_msgs::msg::Pose msg;
  msg.position = vectorToPointMsg( pose.translation() );
  msg.orientation = quaternionToMsg( Eigen::Quaternion<Scalar>( pose.linear() ) );
  return msg;
}

template<typename Scalar>
geometry_msgs::msg::Transform transformToTransformMsg( const Isometry3<Scalar> &pose )
{
  geometry_msgs::msg::Transform msg;
  msg.translation = vectorToVectorMsg( pose.translation() );
  msg.rotation = quaternionToMsg( Eigen::Quaternion<Scalar>( pose.linear() ) );
  return msg;
}

template<typename Scalar>
geometry_msgs::msg::Twist twistToMsg( const Twist<Scalar> &twist )
{
  geometry_msgs::msg::Twist msg;
  msg.linear = vectorToVectorMsg( twist.linear() );
  msg.angular = vectorToVectorMsg( twist.angular() );
  return msg;
}
} // namespace hector_math

#endif // HECTOR_MATH_ROS_CONVERSIONS_GEOMETRY_MSGS_H
