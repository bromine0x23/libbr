#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/current_function.hpp>

#if defined(BR_NO_STD_TYPEINFO)

#include <libbr/functional/less.hpp>

namespace BR {

class TypeInfo {

public:

	explicit TypeInfo(CString<NChar> name): m_name(name) {
	}

	auto operator==(TypeInfo const & rhs) const -> bool {
		return this == &rhs;
	}

	auto operator!=(TypeInfo const & rhs) const -> bool {
		return this != &rhs;
	}


	auto before(TypeInfo const & rhs) const -> bool {
		return Less< TypeInfo const * >()(this, &rhs);
	}

	auto name() const -> CString<NChar> {
		return m_name;
	}

private:
	TypeInfo(TypeInfo const & info) = delete;

	auto operator=(TypeInfo const & info) -> TypeInfo & = delete;

private:
	CString<NChar> m_name;
};

namespace Detail {
namespace Utility {

template< typename T >
struct TypeID;

template< typename T >
struct TypeID< T & > : TypeID< T > {
};

template< typename T >
struct TypeID< T const >: TypeID< T > {
};

template< typename T >
struct TypeID< T volatile >: TypeID< T > {
};

template< typename T >
struct TypeID< T const volatile >: TypeID< T > {
};

template< typename T >
struct TypeID {

	static TypeInfo type_info;

	static auto name() -> CString<NChar> {
		return BR_CURRENT_FUNCTION;
	}
};

template< typename T >
TypeInfo TypeID<T>::type_info(TypeID<T>::name());

} // namespace Utility
} // namespace Detail

} // namespace BR

#define BR_TYPE_ID(T) (BR::Detail::TypeID<decltype(T)>::type_info)

#else

#include <typeinfo>

namespace BR {

using TypeInfo = std::type_info;

} // namespace BR

#define BR_TYPE_ID(T) typeid(T)

#endif // defined
