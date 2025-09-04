/**
 *  Point type compatible with Autoware's PointXYZIRC format
 *  
 *  Maps Seyond data to Autoware format:
 *  - is_2nd_return -> return_type (R in XYZIRC: 0=unknown, 1=strongest/first, 2=last/second)
 *  - scan_id -> channel (C in XYZIRC: channel/ring/laser ID - vertical scanning line ID)
 */

#pragma once
#include <pcl/point_types.h>

namespace seyond {

struct EIGEN_ALIGN16 PointXYZIRC {
  PCL_ADD_POINT4D;                // x, y, z position
  float intensity;                 // Intensity value
  std::uint8_t return_type;       // Return type (R): 0=unknown, 1=strongest (first), 2=last (second)
  std::uint16_t channel;           // Channel (C): Scanning line ID (vertical line number)
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

}  // namespace seyond

// Register the point type with PCL
POINT_CLOUD_REGISTER_POINT_STRUCT(
    seyond::PointXYZIRC,
    (float, x, x)
    (float, y, y)
    (float, z, z)
    (float, intensity, intensity)
    (std::uint8_t, return_type, return_type)
    (std::uint16_t, channel, channel))