#pragma once

#include <libbr/config.hpp>
// #include <libbr/function/less.hpp>
#include <libbr/utility/current_function.hpp>

#if defined(BR_NO_STD_TYPEINFO)

namespace BR {

class TypeInfo {

	TypeInfo(TypeInfo const &) = delete;
	TypeInfo & operator=(TypeInfo const &) = delete;

public:

	explicit TypeInfo(char const * name): m_name(name) {}

	bool operator==(TypeInfo const & rhs) const { return this == &rhs; }
	bool operator!=(TypeInfo const & rhs) const { return this != &rhs; }

	// TODO
	/*bool before(TypeInfo const & rhs) const {
		return Less< TypeInfo const * >()(this, &rhs);
	}*/

	char const * name() const {
		return m_name;
	}

private:
	char const * m_name;
};

namespace Detail {

template< typename T >
struct _TypeID_ {

	static TypeInfo s_type_info;

	static char const * name() {
		return BR_CURRENT_FUNCTION;
	}
};

template< typename T >
TypeInfo _TypeID_< T >::s_type_info(_TypeID_< T >::name());

template< typename T >
struct _TypeID_< T & > : T< T > {};

template< typename T >
struct _TypeID_< T const >: _TypeID_< T > {};

template< typename T >
struct _TypeID_< T volatile >: _TypeID_< T > {};

template< typename T >
struct _TypeID_< T const volatile >: _TypeID_< T > {};

} // namespace Detail

} // namespace BR

#define BR_TYPE_ID(T) (BR::Detail::_TypeID_<decltype(T)>::s_type_info)

#else

#include <typeinfo>

namespace BR {

using TypeInfo = std::type_info;

} // namespace BR

#define BR_TYPE_ID(T) typeid(T)

#endif // defined
