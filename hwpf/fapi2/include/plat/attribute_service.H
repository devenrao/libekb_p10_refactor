#pragma once

#include <targeting/target.H>
#include <targeting/xmltohb/attributeenums.H>
#include <targeting/xmltohb/attributetraits.H>

/**
 *  @brief Macro that directly maps a FAPI_ATTR_GET to a Targeting attr get
 *
 *  Firstly there is a compile time check that the user's VAL variable matches
 *  the Targeting attribute type, this is optimized out, then there is a
 *  single function call
 */
#define FAPI2_PLAT_ATTR_SVC_TRYGETMACRO_DIRECT(ID, PTARGET, VAL) \
    ((PTARGET)->tryGetAttr<TARGETING::ATTRIBUTE_ID::ID>(VAL))
    
#define FAPI2_PLAT_ATTR_SVC_TRYSETMACRO_DIRECT(ID, PTARGET, VAL) \
    ((PTARGET)->trySetAttr<TARGETING::ATTRIBUTE_ID::ID>(VAL))    
