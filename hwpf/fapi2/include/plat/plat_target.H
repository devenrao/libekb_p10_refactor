/**
 * @file plat_target.H
 * @brief platform definitions for fapi2 targets
 */

#pragma once

#include <targeting/target.H>
//
// Define what a platform handle looks like. For Hostboot,
// for example, this might be a void*. For the SBE, this
// will be a uint64_t ...
//
namespace fapi2
{
typedef TARGETING::ConstTargetPtr plat_target_handle_t;
}
