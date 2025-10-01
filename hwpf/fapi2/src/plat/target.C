#include <fapi2_target.H>
#include <plat_target.H>

namespace fapi2
{

// Create specific target
// TARGET_TYPE_SYSTEM
template <>
Target<TARGET_TYPE_SYSTEM, MULTICAST_OR, plat_target_handle_t>::Target()
{
    //TODO:pdbg to targeting cleanup
}

} // namespace fapi2
