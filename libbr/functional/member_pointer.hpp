/**
 * @file
 * @brief member_pointer
 * @author Bromine0x23
 * @since 2015/10/31
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/type_operate/call_result.hpp>
#include <libbr/utility/forward.hpp>


namespace BR {

namespace Detail {
namespace Functional {

template< typename TMemberPointer >
class MemberPointer {
public:
	constexpr MemberPointer(TMemberPointer pointer) noexcept : m_pointer(pointer) {
	}

	template< typename ... TArgs >
	auto operator() (TArgs && ... args) const -> CallResult< TMemberPointer, TArgs ... > {
		return invoke(m_pointer, forward<TArgs>(args)...);
	}

private:
	TMemberPointer m_pointer;
};

} // namespace Functional
} // namespace Detail

template< typename TMember, typename TClass >
inline auto member_pointer(TMember TClass::* member_pointer) noexcept -> Detail::Functional::MemberPointer< TMember TClass::* > {
	return Detail::Functional::MemberPointer< TMember TClass::* >(member_pointer);
}

} // namespace BR