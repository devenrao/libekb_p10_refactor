#pragma once

#include <attribute_ids.H>
#include <return_code.H>
#include <target.H>
#include <targeting/xmltohb/fapi2platattrmacros.H>

namespace fapi2
{
#define FAPI2_PLAT_ATTR_SVC_GETMACRO_DIRECT(ID, PTARGET, VAL) ReturnCode{}
#define FAPI2_PLAT_ATTR_SVC_SETMACRO_DIRECT(ID, PTARGET, VAL) ReturnCode{}
#define PLAT_GET_CHIP_EC_FEATURE_OVERRIDE(ID, TARGET, VAL) FAPI2_RC_SUCCESS
}
