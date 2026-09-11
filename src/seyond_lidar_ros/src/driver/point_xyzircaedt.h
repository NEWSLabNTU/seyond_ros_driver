/**
 *  Point type matching Autoware's PointXYZIRCAEDT, the layout Nebula publishes
 *  and the one every deskewing stage in Autoware needs.
 *
 *  PointXYZIRC (point_xyzirc.h) carries no per-point time, and without one a
 *  cloud cannot be motion-compensated by anything, on the CPU or the GPU. That
 *  is the whole reason this layout exists here: a Seyond LiDAR publishing
 *  PointXYZIRC is not merely un-accelerated by
 *  autoware_cuda_pointcloud_preprocessor, it is uncorrectable by it.
 *
 *  Field-by-field, and where each value comes from:
 *
 *    x, y, z      the transformed Cartesian point, as in PointXYZIRC
 *    intensity    reflectance or intensity, clamped to 0-255
 *    return_type  1 for the first/strongest return, 2 for the second/last
 *    channel      scan_id, or ring_id when enable_falcon_ring is set
 *    azimuth      atan2(y, x), radians, computed here: the SDK point carries
 *                 no angles
 *    elevation    atan2(z, hypot(x, y)), radians, computed here
 *    distance     the SDK's own radius, not recomputed from x/y/z
 *    time_stamp   NANOSECONDS AFTER THE MESSAGE HEADER STAMP, unsigned. This
 *                 is an offset, not an absolute time; see driver_lidar.cc.
 *
 *  The field order and types are not free. They match
 *  nebula_common/point_types.hpp exactly, because Autoware's CUDA preprocessor
 *  reads the layout by offset.
 */

#pragma once
#include <pcl/point_types.h>

namespace seyond {

struct EIGEN_ALIGN16 PointXYZIRCAEDT {
  PCL_ADD_POINT4D;                 // x, y, z as floats, with PCL's alignment
  std::uint8_t intensity;
  std::uint8_t return_type;
  std::uint16_t channel;
  float azimuth;
  float elevation;
  float distance;
  std::uint32_t time_stamp;        // nanoseconds after the header stamp
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

}  // namespace seyond

POINT_CLOUD_REGISTER_POINT_STRUCT(
    seyond::PointXYZIRCAEDT,
    (float, x, x)
    (float, y, y)
    (float, z, z)
    (std::uint8_t, intensity, intensity)
    (std::uint8_t, return_type, return_type)
    (std::uint16_t, channel, channel)
    (float, azimuth, azimuth)
    (float, elevation, elevation)
    (float, distance, distance)
    (std::uint32_t, time_stamp, time_stamp))
