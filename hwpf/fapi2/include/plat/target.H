/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: hwpf/fapi2/include/plat/target.H $                            */
/*                                                                        */
/* IBM CONFIDENTIAL                                                       */
/*                                                                        */
/* EKB Project                                                            */
/*                                                                        */
/* COPYRIGHT 2012,2019                                                    */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* The source code for this program is not published or otherwise         */
/* divested of its trade secrets, irrespective of what has been           */
/* deposited with the U.S. Copyright Office.                              */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/**
 * @file target.H
 * @brief platform specializations for fapi2 targets
 */

#ifndef __FAPI2_TARGET__
#define __FAPI2_TARGET__

#include <assert.h>
#include <attribute_ids.H>
#include <fapi2_target.H>
#include <plat_target.H>
#include <plat_trace.H>
#include <stdio.h>
#include <string.h>
#include <targeting/predicates/predicatectm.H>
#include <targeting/predicates/predicateisfunctional.H>
#include <targeting/target.H>
#include <targeting/targetservice.H>

#include <algorithm>
#include <array>
#include <string>
#include <vector>

namespace fapi2
{
struct fapi2_targeting_type {
	fapi2::TargetType fapi2Type;
	TARGETING::TYPE targetingType;
};

constexpr size_t NUM_FAPI_TARGETING_TYPES = 24;

// Inline constexpr array: no need for separate .C file
inline constexpr std::array<fapi2_targeting_type, NUM_FAPI_TARGETING_TYPES>
    fapi2ToTargetingTypes{{
	{fapi2::TARGET_TYPE_NONE, TARGETING::TYPE_NA},
	{fapi2::TARGET_TYPE_SYSTEM, TARGETING::TYPE_SYS},
	{fapi2::TARGET_TYPE_DIMM, TARGETING::TYPE_DIMM},
	{fapi2::TARGET_TYPE_PROC_CHIP, TARGETING::TYPE_PROC},
	{fapi2::TARGET_TYPE_FC, TARGETING::TYPE_FC},
	{fapi2::TARGET_TYPE_CORE, TARGETING::TYPE_CORE},
	{fapi2::TARGET_TYPE_EQ, TARGETING::TYPE_EQ},
	{fapi2::TARGET_TYPE_MI, TARGETING::TYPE_MI},
	{fapi2::TARGET_TYPE_PERV, TARGETING::TYPE_PERV},
	{fapi2::TARGET_TYPE_PEC, TARGETING::TYPE_PEC},
	{fapi2::TARGET_TYPE_PHB, TARGETING::TYPE_PHB},
	{fapi2::TARGET_TYPE_MC, TARGETING::TYPE_MC},
	{fapi2::TARGET_TYPE_OMI, TARGETING::TYPE_OMI},
	{fapi2::TARGET_TYPE_OMIC, TARGETING::TYPE_OMIC},
	{fapi2::TARGET_TYPE_MCC, TARGETING::TYPE_MCC},
	{fapi2::TARGET_TYPE_OCMB_CHIP, TARGETING::TYPE_OCMB_CHIP},
	{fapi2::TARGET_TYPE_MEM_PORT, TARGETING::TYPE_MEM_PORT},
	{fapi2::TARGET_TYPE_NMMU, TARGETING::TYPE_NMMU},
	{fapi2::TARGET_TYPE_PAU, TARGETING::TYPE_PAU},
	{fapi2::TARGET_TYPE_IOHS, TARGETING::TYPE_IOHS},
	{fapi2::TARGET_TYPE_PAUC, TARGETING::TYPE_PAUC},
	{fapi2::TARGET_TYPE_PMIC, TARGETING::TYPE_PMIC},
	{fapi2::TARGET_TYPE_GENERICI2CSLAVE,
	 TARGETING::TYPE_GENERIC_I2C_DEVICE},
	{fapi2::TARGET_TYPE_IOLINK, TARGETING::TYPE_SMPGROUP},
    }};

template <TargetType K, MulticastType M, typename V>
static constexpr void plat_apply_target_limits(void)
{
	static_assert(!(K & TARGET_TYPE_MULTICAST),
		      "Multicast targets are not supported on this platform");
}

template <TargetType T, MulticastType M, typename V>
inline void Target<T, M, V>::mcUpdateHandle()
{
}

///
/// @brief Assignment Operator.
/// @param[in] i_right Reference to Target to assign from.
/// @return Reference to 'this' Target
///
template <TargetType K, MulticastType M, typename V>
Target<K, M, V> &Target<K, M, V>::operator=(const Target &i_right)
{
	iv_handle = i_right.iv_handle;
	return *this;
}

///
/// @brief Equality Comparison Operator
/// @param[in] i_right Reference to Target to compare.
/// @return bool. True if equal.
/// @note Platforms need to define this so that the physical
/// targets are determined to be equivilent rather than just the handles
///
template <TargetType K, MulticastType M, typename V>
bool Target<K, M, V>::operator==(const Target &i_right) const
{
	return i_right.iv_handle == iv_handle;
}

///
/// @brief Inquality Comparison Operator
/// @param[in] i_right Reference to Target to compare.
/// @return bool. True if not equal.
/// @note Platforms need to define this so that the physical
/// targets are determined to be equivilent rather than just the handles
///
template <TargetType K, MulticastType M, typename V>
bool Target<K, M, V>::operator!=(const Target &i_right) const
{
	return i_right.iv_handle != iv_handle;
}

///
/// @brief Less Than Comparison Operator
/// @param[in] i_right Reference to Target to compare.
/// @return bool. True if less than i_right.
/// @note Platforms need to define this so that the physical
/// targets are determined to be less than rather than just the handles
///
template <TargetType K, MulticastType M, typename V>
bool Target<K, M, V>::operator<(const Target &i_right) const
{
	return i_right.iv_handle < iv_handle;
}

///
/// @brief Get this target's immediate parent
/// @tparam T_SELF The type of target on which this is called
/// @tparam K_PARENT The desired type of the parent target
/// @tparam V the type of the target's Value
/// @return Target<T> a target representing the parent:1

///
template <TargetType T_SELF, MulticastType M, typename V>
template <TargetType K_PARENT>
inline Target<K_PARENT, M, V> Target<T_SELF, M, V>::getParent(void) const
{
	// It's forbidden to strip multicast from a target below PROC_CHIP
	// level: Since a multicast might end up expanding to more than one
	// unicast target, users are required to use getChildren if they want to
	// map back to unicast.
	static_assert(!(((K ^ T) & TARGET_TYPE_MULTICAST) &&
			((T & TARGET_TYPE_CHIPLETS) != TARGET_TYPE_NONE)),
		      "Parent target for a multicast target must also be "
		      "multicast or PROC_CHIP");

	// For testing
	return Target<T, M, V>(iv_handle);
}

///
/// @brief Get this target's children
/// @tparam T The type of the parent
/// @param[in] i_state The desired TargetState of the children
/// @return std::vector<Target<T> > a vector of present/functional
/// children
/// @warning The children of EX's (cores) are expected to be returned
/// in order. That is, core 0 is std::vector[0].
///
template <TargetType K, MulticastType M, typename V>
template <TargetType T>
inline std::vector<Target<T, M, V>>
    Target<K, M, V>::getChildren(const TargetState i_state) const
{
	std::vector<Target<T, M, V>> targets;
	return targets;
}
// @param[in] i_filter The desired chiplet filter
// @param[in] i_state The desired TargetState of the children
// @return std::vector<Target<T> > a vector of present/functional children

template <TargetType T_SELF, MulticastType M, typename V>
template <TargetType T>
inline std::vector<Target<T, M, V>>
    Target<T_SELF, M, V>::getChildren(const TargetFilter i_filter,
				      const TargetState i_state) const
{
	std::vector<Target<T, M, V>> children;
	return targets;
}

template <TargetType K, MulticastType M, typename V>
template <TargetType T, MulticastType O>
inline Target<T | TARGET_TYPE_MULTICAST, O, V>
    Target<K, M, V>::getMulticast(const MulticastGroup i_group) const
{
	// C++ does not allow partial specialization of class member functions
	// (please prove me wrong!), so we need to use this static assertion
	// instead. On the upside, the error message is much clearer ;)
	static_assert((K == TARGET_TYPE_PROC_CHIP),
		      "Parent target must be the proc chip");
	static_assert(
	    (T & TARGET_TYPE_MULTICASTABLE) != 0,
	    "Requested target type must be part of TARGET_TYPE_MULTICASTABLE");
	static_assert(bitCount<T>::count == 1,
		      "Requested target type must be a single type, "
		      "TARGET_TYPE_MULTICAST will be added automatically");

	return Target<T | TARGET_TYPE_MULTICAST, O, V>();
}

template <TargetType K, MulticastType M, typename V>
template <MulticastType O>
inline Target<TARGET_TYPE_CORE | TARGET_TYPE_MULTICAST, O, V>
    Target<K, M, V>::getMulticast(const MulticastGroup i_group,
				  const MulticastCoreSelect i_cores) const
{
	// C++ does not allow partial specialization of class member functions
	// (please prove me wrong!), so we need to use this static assertion
	// instead. On the upside, the error message is much clearer ;)
	static_assert((K == TARGET_TYPE_PROC_CHIP),
		      "Parent target must be the proc chip");
	return Target<TARGET_TYPE_CORE | TARGET_TYPE_MULTICAST, O, V>();
}

///
/// @brief Get the target at the other end of a bus
/// @tparam T The type of the target on the other end
/// @param[out] o_target A target representing the thing on the other end
/// @param[in] i_state The desired TargetState of the other end
/// @return FAPI2_RC_SUCCESS if OK, platforms will return a non-success
/// ReturnCode in the event of failure
/// @note o_target is only valid if return is FAPI2_RC_SUCCESS
///

template <TargetType K, MulticastType M, typename V>
template <TargetType T>
inline fapi2::ReturnCodes
    Target<K, M, V>::getOtherEnd(Target<T, M, V> &o_target,
				 const TargetState i_state) const
{
	// To keep the compiler quiet about unused variables
	static_cast<void>(i_state);

	o_target = Target<T, M, V>();

	return FAPI2_RC_SUCCESS;
}

///
/// @brief Is the target functional?
/// @return true if target is functional, false if non-functional
///
template <TargetType K, MulticastType M, typename V>
inline bool Target<K, M, V>::isFunctional(void) const
{
	this->get()->getAttr<ATTR_HWAS_STATE>().functional;
}

///
/// @brief Returns the chiplet number associated with the Target
/// @return The chiplet number for the Target. 0 is returned if the
/// Target does not have a chiplet number (for ex, the PROC_CHIP Target)
/// @note For logical targets such as the EX, the chiplet number of
/// their immediate parent chiplet is returned
///
template <TargetType K, MulticastType M, typename V>
inline uint8_t Target<K, M, V>::getChipletNumber(void) const
{
	uint8_t chiplet_id = 0;
	this->get()->getAttr<TARGETING::ATTR_CHIPLET_ID>(
	    chiplet_id) return chiplet_id;
}

template <TargetType K, MulticastType M, typename V>
inline MulticastCoreSelect Target<K, M, V>::_getCoreSelect(void) const
{
	static_assert(
	    K & TARGET_TYPE_CORE,
	    "getCoreSelect is only applicable to TARGET_TYPE_CORE targets");
	// Platform can return the core select value stored in it's Target
	// handle
	return MCCORE_0;
}

///
/// @brief Return the string interpretation of this target
/// @tparam T The type of the target
/// @param[in] i_target Target<T>
/// @param[inout] io_buffer buffer to write in to
/// @param[in] i_bsize size of the buffer
/// @return void
/// @post The contents of the buffer is replaced with the string
/// representation of the target
///
template <TargetType T, MulticastType M, typename V>
inline void toString(const Target<T, M, V> &i_target, char *io_buffer,
		     size_t i_bsize)
{
	TARGETING::ConstTargetPtr target =
	    static_cast<TARGETING::ConstTargetPtr>(i_target->get());
	ATTR_FAPI_NAME_type fapiName = {0};
	if (!target->tryGetAttr<ATTR_FAPI_NAME>(fapiName)) {
		std::cerr << "ERROR: Cannot read FAPI_NAME attribute\n";
		if (i_bsize > 0) {
			io_buffer[0] = '\0';
		}
		return;
	}

	std::string_view name{reinterpret_cast<const char *>(fapiName)};
	size_t copy_len =
	    std::min(i_bsize - 1, name.size()); // leave room for '\0'

	if (i_bsize > 0) {
		std::memcpy(io_buffer, name.data(), copy_len);
		io_buffer[copy_len] = '\0';
	}

	if (copy_len < name.size()) {
	std::cout << "Buffer too small: need %zu bytes, got %zu for %s",
                 name.size() + 1, i_bsize, name.data());
	}
}

///
/// @brief Return the string interpretation of this target
/// @tparam T The type of the target
/// @tparam B The type of the buffer
/// @param[in] i_target A pointer to the Target<T>
/// @param[in] io_buffer buffer to write in to
/// @param[in] i_bsize  size of the buffer
/// @return void
/// @post The contents of the buffer is replaced with the string
/// representation of the target
///
template <TargetType T, MulticastType M, typename V>
inline void toString(const Target<T, M, V> *i_target, char *io_buffer,
		     size_t i_bsize)
{
	toString(*i_target, io_buffer, i_bsize);
}

/* Copied from collect_reg_ffdc.H. We can't just include
 * collect_reg_ffdc.H because that first includes target.H (this file)
 * so we have no way of accessing it's definition of this. So instead
 * we have to redefine it here. */
const fapi2::TargetType PLAT_TARGET_TYPE_PROC_CHIPLETS =
    fapi2::TARGET_TYPE_EX | fapi2::TARGET_TYPE_MCS | fapi2::TARGET_TYPE_XBUS |
    fapi2::TARGET_TYPE_CORE | fapi2::TARGET_TYPE_EQ | fapi2::TARGET_TYPE_MCA |
    fapi2::TARGET_TYPE_MCBIST | fapi2::TARGET_TYPE_MI |
    fapi2::TARGET_TYPE_CAPP | fapi2::TARGET_TYPE_DMI | fapi2::TARGET_TYPE_OBUS |
    fapi2::TARGET_TYPE_OBUS_BRICK | fapi2::TARGET_TYPE_SBE |
    fapi2::TARGET_TYPE_PPE | fapi2::TARGET_TYPE_PERV | fapi2::TARGET_TYPE_PEC |
    fapi2::TARGET_TYPE_PHB | fapi2::TARGET_TYPE_MC | fapi2::TARGET_TYPE_OMI |
    fapi2::TARGET_TYPE_MEM_PORT;

///
/// @brief Get an enumerated target of a specific type
/// @tparam T The type of the target
/// @param[in] ordinal representing the ordinal number of
/// the desired target
/// @return Target<T> the target requested
///
template <TargetType T, MulticastType M, typename V>
inline Target<T, M, V> getTarget(uint64_t ordinal)
{
	// To keep compiler happy.
	return Target<T, M, V>(target);
}

///
/// @brief Return the entity of given target
/// @tparam T The type of the target
/// @param[in] i_target Target<T>
/// @param[in] i_buffer buffer to write entity path
/// @return void
/// @post The contents of the buffer is replaced with the entity path
/// of the target
///
template <TargetType T, MulticastType M, typename V>
inline void getTgtEntityPath(const Target<T, M, V> &i_target,
			     std::vector<uint8_t> &o_buffer)
{
	AttributeTraits<ATTR_PHYS_PATH>::Type entityPath;
	if (!i_target->tryGetAttr<ATTR_PHYS_PATH>(entityPath)) {
		std::cerr << "Could not read ATTR_PHYS_PATH attribute \n";
		return;
	}

	// Use ranges: just copy the raw bytes directly
	std::span<const uint8_t> bytes(entityPath.data(),
				       entityPath.getSize() *
					   sizeof(EntityPath::PathElement));

	o_buffer.assign(bytes.begin(), bytes.end());
}

// constexpr lookup functions
inline constexpr TARGETING::TYPE
    convertFapi2TypeToTargeting(fapi2::TargetType t)
{
	for (auto entry : conversion::fapi2ToTargetingTypes) {
		if (entry.fapi2Type == t)
			return entry.targetingType;
	}
	return TARGETING::TYPE_NA;
}

inline constexpr fapi2::TargetType
    convertTargetingTypeToFapi2(TARGETING::TYPE t)
{
	for (auto entry : conversion::fapi2ToTargetingTypes) {
		if (entry.targetingType == t)
			return entry.fapi2Type;
	}
	return fapi2::TARGET_TYPE_NONE;
}
} // namespace fapi2
