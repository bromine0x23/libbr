/**
 * @file
 * @brief member_pointer
 * @author Bromine0x23
 * @since 2015/10/31
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/functional/invoke.hpp>
#include <libbr/functional/variadic_functor.hpp>
#include <libbr/type_operate/call_result.hpp>
#include <libbr/utility/forward.hpp>

namespace BR {

#if defined(BR_DOXYGEN)
inline namespace Functional {

/**
 * @brief Functor for member function
 * @tparam TMember
 * @tparam TClass
 * @param member_pointer
 * @return
 */
template< typename TMember, typename TClass >
auto member_pointer(TMember TClass::* member_pointer) noexcept;

} // namespace Functional
#endif // defined(BR_DOXYGEN)

namespace Detail {
namespace Functional {

template< typename TMemberPointer >
class MemberPointer : public VariadicFunctor {
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


inline namespace Functional {

template< typename TMember, typename TClass >
inline auto member_pointer(TMember TClass::* member_pointer) noexcept -> Detail::Functional::MemberPointer< TMember TClass::* > {
	return Detail::Functional::MemberPointer< TMember TClass::* >(member_pointer);
}
} // namespace Functional

} // namespace BR