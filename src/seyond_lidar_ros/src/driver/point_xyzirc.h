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
  PCL_ADD_POINT4D;                // This adds x, y, z as floats with proper alignment
  std::uint8_t intensity;          // Intensity value (UINT8) - matches Autoware spec  
  std::uint8_t return_type;        // Return type (UINT8): 0=unknown, 1=strongest (first), 2=last (second)
  std::uint16_t ring;              // Ring/Channel (UINT16): Scanning line ID (vertical line number)
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

}  // namespace seyond

// Register the point type with PCL
// Field names match Autoware's expected format: x, y, z, I, R, C
// Data types match Autoware spec: FLOAT32, FLOAT32, FLOAT32, UINT8, UINT8, UINT16
POINT_CLOUD_REGISTER_POINT_STRUCT(
    seyond::PointXYZIRC,
    (float, x, x)
    (float, y, y)
    (float, z, z)
    (std::uint8_t, intensity, I)       // Map intensity to field name "I" (UINT8)
    (std::uint8_t, return_type, R)     // Map return_type to field name "R" (UINT8)
    (std::uint16_t, ring, C))           // Map ring to field name "C" (UINT16)