/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
#pragma once

#include <fapi2_hw_access.H>
#include <plat_hw_access.H>

namespace fapi2
{
//------------------------------------------------------------------------------
// HW Communication Functions to be implemented at the platform layer.
//------------------------------------------------------------------------------

///
/// @brief Platform-level implementation of getScom()
/// @tparam K template parameter, passed in target.
/// @param[in]  i_target   HW target to operate on.
/// @param[in]  i_address  SCOM register address to read from.
/// @param[out] o_data     Buffer that holds data read from HW target.
/// @return fapi::ReturnCode. FAPI2_RC_SUCCESS if success, else error code.
///
template <TargetType K, MulticastType M, typename V>
inline ReturnCode getScom(const Target<K, M, V>& i_target,
			  const uint64_t i_address, buffer<uint64_t>& o_data)
{
    //TODO: switch to targeting
	return FAPI2_RC_SUCCESS;
}


/// @brief Platform-level implementation of putScom()
/// @tparam K template parameter, passed in target.
/// @param[in] i_target     HW target to operate on.
/// @param[in] i_address    SCOM register address to write to.
/// @param[in] i_data       Buffer that holds data to write into address.
/// @return fapi::ReturnCode. FAPI2_RC_SUCCESS if success, else error code.
template <TargetType K, MulticastType M, typename V>
inline ReturnCode putScom(const Target<K, M, V>& i_target,
			  const uint64_t i_address,
			  const buffer<uint64_t> i_data)
{
    //TODO: switch to targeting
	return FAPI2_RC_SUCCESS;
}

/// @brief Platform-level implementation of putScomUnderMask()
/// @tparam K template parameter, passed in target.
/// @param[in] i_target     HW target to operate on.
/// @param[in] i_address    SCOM register address to write to.
/// @param[in] i_data       Buffer that holds data to write into address.
/// @param[in] i_mask       Buffer that holds the mask value.
/// @return fapi::ReturnCode. FAPI2_RC_SUCCESS if success, else error code.
template <TargetType K, MulticastType M, typename V>
inline ReturnCode putScomUnderMask(const Target<K, M, V>& i_target,
				   const uint64_t i_address,
				   const buffer<uint64_t> i_data,
				   const buffer<uint64_t> i_mask)
{
    //TODO: switch to targeting
	return FAPI2_RC_SUCCESS;
}

template <TargetType K, MulticastType M, typename V>
inline ReturnCode
    getCfamRegister(const Target<K, M, V>& i_target,
		    const uint32_t i_address, buffer<uint32_t>& o_data)
{
	return FAPI2_RC_SUCCESS;
}



template <TargetType K, MulticastType M, typename V>
inline ReturnCode
    putCfamRegister(const Target<K, M, V>& i_target,
		    const uint32_t i_address, const buffer<uint32_t> i_data)
{
	return FAPI2_RC_SUCCESS;
}
}; // namespace fapi2
