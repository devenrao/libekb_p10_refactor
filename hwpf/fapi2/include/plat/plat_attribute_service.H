#pragma once

#include <attribute_ids.H>
#include <fapi2_attribute_service.H>
#include <return_code.H>
#include <target.H>
#include <targeting/target.H>
#include <targeting/xmltohb/attributeenums.H>
#include <targeting/xmltohb/attributetraits.H>
#include <targeting/xmltohb/fapi2platattrmacros.H>

namespace fapi2::platAttrSvc
{
// Check if AttributeTraits<A> has TypeStdArr
template <typename T, typename = void>
struct has_TypeStdArr : std::false_type {
};

template <typename T>
struct has_TypeStdArr<T, std::void_t<typename T::TypeStdArr>> : std::true_type {
};

template <TARGETING::ATTRIBUTE_ID A, typename TargetT>
ReturnCode getTargetingAttr(const TargetT& fapiTarget, void* o_pAttr)
{
	if (auto target = fapiTarget.get(); target) {
		using TraitType = typename TARGETING::AttributeTraits<A>::Type;
		return target->template tryGetAttr<A>(
			   *reinterpret_cast<TraitType*>(o_pAttr))
			   ? FAPI2_RC_SUCCESS
			   : FAPI2_RC_PLAT_ERR_SEE_DATA;
	}
	return FAPI2_RC_PLAT_ERR_SEE_DATA;
}

template <TARGETING::ATTRIBUTE_ID A, typename TargetT, typename ValT>
fapi2::ReturnCode setTargetingAttr(TargetT& fapiTarget, ValT* i_pAttr)
{
    if (auto target = fapiTarget.get(); target) {
        using TraitType = typename TARGETING::AttributeTraits<A>::Type;
        const auto* attrPtr = reinterpret_cast<const TraitType*>(i_pAttr);
        return target->template trySetAttr<A>(*attrPtr)
               ? FAPI2_RC_SUCCESS
               : FAPI2_RC_PLAT_ERR_SEE_DATA;
    }
    return FAPI2_RC_PLAT_ERR_SEE_DATA;
}
} // namespace fapi2::platAttrSvc

// ------------------------------------------------------------
// Macros for attribute access
// ------------------------------------------------------------

// Low-level GET macro (calls template function)
#define FAPI2_PLAT_ATTR_SVC_GETMACRO_DIRECT(ID, PTARGET, VAL)                  \
	platAttrSvc::getTargetingAttr<                                         \
	    fapiToTargeting::Fapi2ToTargetingAttr<ID>::value>(PTARGET, &(VAL))

#define FAPI2_PLAT_ATTR_SVC_SETMACRO_DIRECT(ID, PTARGET, VAL)                  \
	platAttrSvc::setTargetingAttr<                                         \
	    fapiToTargeting::Fapi2ToTargetingAttr<ID>::value>(PTARGET, &(VAL))

#define PLAT_GET_CHIP_EC_FEATURE_OVERRIDE(ID, TARGET, VAL) FAPI2_RC_SUCCESS
