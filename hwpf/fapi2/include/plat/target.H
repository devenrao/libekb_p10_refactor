/**
 * @file target.H
 * @brief platform specializations for fapi2 targets
 */
#pragma once

#include <assert.h>
#include <attribute_ids.H>
#include <fapi2_target.H>
#include <plat_target.H>
#include <plat_trace.H>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <string>
#include <vector>

namespace fapi2
{

template <TargetType K, MulticastType M, typename V>
static constexpr void plat_apply_target_limits(void)
{
	static_assert(!(K & TARGET_TYPE_MULTICAST),
		      "Multicast targets are not supported on this platform");
}

template <TargetType T, MulticastType M, typename V>
inline void Target<T, M, V>::mcUpdateHandle(){};

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
/// @tparam T The type of the parent
/// @return Target<T> a target representing the parent
///
template <TargetType K, MulticastType M, typename V>
template <TargetType T>
inline Target<T, M, V> Target<K, M, V>::getParent(void) const
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
    //TODO:switch to targeting
	std::vector<Target<T>> targets;
	return targets;
}

// @brief Get this target's children, filtered
// @tparam T The type of the parent
// @tparam T_SELF The type of target on which this is called
// @tparam V the type of the target's Value
// @param[in] i_filter The desired chiplet filter
// @param[in] i_state The desired TargetState of the children
// @return std::vector<Target<T> > a vector of present/functional children

template <TargetType T_SELF, MulticastType M, typename V>
template <TargetType T>
inline std::vector<Target<T, M, V>>
    Target<T_SELF, M, V>::getChildren(const TargetFilter i_filter,
				      const TargetState i_state) const
{
    //TODO: switch to targeting
	std::vector<Target<T, M, V>> children;
	return children;
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
	return FAPI2_RC_SUCCESS;
}

///
/// @brief Is the target functional?
/// @return true if target is functional, false if non-functional
///

template <TargetType K, MulticastType M, typename V>
inline bool Target<K, M, V>::isFunctional(void) const
{
    //TODO: switch to targeting
	return false;
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
    //TODO:switch to targeting
    return 0;
}


///
/// @brief Return the string interpretation of this target
/// @tparam T The type of the target
/// @param[in] i_target Target<T>
/// @param[in] i_buffer buffer to write in to
/// @param[in] i_bsize size of the buffer
/// @return void
/// @post The contents of the buffer is replaced with the string
/// representation of the target
///
template <TargetType T, MulticastType M, typename V>
inline void toString(const Target<T, M, V> &i_target, char *i_buffer,
		     size_t i_bsize)
{
    //TODO: switch to targeting
}

///
/// @brief Return the string interpretation of this target
/// @tparam T The type of the target
/// @tparam B The type of the buffer
/// @param[in] i_target A pointer to the Target<T>
/// @param[in] i_buffer buffer to write in to
/// @param[in] i_bsize  size of the buffer
/// @return void
/// @post The contents of the buffer is replaced with the string
/// representation of the target
///
template <TargetType T, MulticastType M, typename V>
inline void toString(const Target<T, M, V> *i_target, char *i_buffer,
		     size_t i_bsize)
{
	toString(*i_target, i_buffer, i_bsize);
}

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
    //TODO: switch to targeting
	return Target<T, M, V>();
}

// @brief Get a target from its Type and instance info
// @tparam T The type of the target to return
// @tparam V type of the targets value
// @param[in] i_type   - Type of target to find
// @param[in] instance - instance of the target to find
//
// @return Target<T>* pointer to a target of type T

// NOTE: Function caller owns the object returned.

template <TargetType T, MulticastType M = MULTICAST_OR,
	  typename V = fapi2::plat_target_handle_t>
inline Target<T, M, V> *getTarget(TargetType i_type, uint8_t instance)
{
    return nullptr;
}

} // namespace fapi2
