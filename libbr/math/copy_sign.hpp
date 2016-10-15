/**
 * @file
 * @brief copy_sign
 * @author Bromine0x23
 * @since 2016/10/11
 */
#pragma once

#include <libbr/config.hpp>

extern "C" {

/**
 * like isinf
 * @param f
 * @return
 */
//@{
auto libbr_copy_sign_s(BR::SFloat x, BR::SFloat y) -> BR::SFloat;

auto libbr_copy_sign_d(BR::DFloat x, BR::DFloat y) -> BR::DFloat;

auto libbr_copy_sign_q(BR::QFloat x, BR::QFloat y) -> BR::QFloat;
//@}

}

namespace BR {

inline auto copy_sign(SFloat x, SFloat y) -> SFloat {
	return libbr_copy_sign_s(x, y);
}

inline auto copy_sign(DFloat x, DFloat y) -> DFloat {
	return libbr_copy_sign_d(x, y);
}

inline auto copy_sign(QFloat x, QFloat y) -> QFloat {
	return libbr_copy_sign_q(x, y);
}

} // namespace BR