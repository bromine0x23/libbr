#if !defined(BR_TYPE_OPERATE_OP_NAME_C)
#error "BR_TYPE_OPERATE_OP_NAME_C not defined!"
#endif

#if !defined(BR_TYPE_OPERATE_OP_NAME_V)
#error "BR_TYPE_OPERATE_OP_NAME_V not defined!"
#endif

#if !defined(BR_TYPE_OPERATE_OP)
#error "BR_TYPE_OPERATE_OP not defined!"
#endif

#if !defined(BR_TYPE_OPERATE_FORBIDDEN_IF)
#error "BR_TYPE_OPERATE_FORBIDDEN_IF not defined!"
#endif

#include <libbr/config.hpp>
#include <libbr/utility/bool_constant.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/remove_pointer.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {
namespace BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C) {

struct NotCareTag {};
struct IsOperatorReturnTest {
	template< typename TRet >
	static BooleanTrue test(TRet);

	template< typename TRet >
	static BooleanFalse test(...);
};

template< typename TLhs, typename TRhs, typename TRet >
struct IsOperatorReturnBasic : decltype(
	IsOperatorReturnTest::test< TRet >(make_reference<TLhs>() BR_TYPE_OPERATE_OP make_reference<TRhs>())
) {};

template< typename TLhs, typename TRhs, typename TRet >
using IsOperatorReturn = BooleanOr<
	IsSame< TRet, NotCareTag >,
	IsOperatorReturnBasic< TLhs, TRhs, TRet >
>;

struct IsOperatorExistTest {
	template< typename TLhs, typename TRhs, typename = decltype(make_reference<TLhs>() BR_TYPE_OPERATE_OP make_reference<TRhs>()) >
	static auto test(int) -> BooleanTrue;

	template< typename TLhs, typename TRhs >
	static auto test(...) -> BooleanFalse;
};

template< typename TLhs, typename TRhs >
using IsOperatorExist = decltype(IsOperatorExistTest::test< TLhs, TRhs >(0));

template< typename TLhs, typename TRhs, typename TRet, bool forbidden_if >
using HasOperatorBasic = BooleanAnd<
	NotVoid< TLhs >,
	NotVoid< TRhs >,
	BooleanConstant< !forbidden_if >,
	IsOperatorExist< TLhs, TRhs >,
	IsOperatorReturn< TLhs, TRhs, TRet >
>;

template < typename TLhs, typename TRhs, typename TRet >
struct HasOperatorResult {
	using TLhsNoRef = RemoveReference<TLhs>;
	using TRhsNoRef = RemoveReference<TRhs>;
	using TLhsNoPtr = RemoveConstVolatile< RemoveReference< RemovePointer<TLhsNoRef> > >;
	using TRhsNoPtr = RemoveConstVolatile< RemoveReference< RemovePointer<TRhsNoRef> > >;
	using TLhsNoCV  = RemoveConstVolatile<TLhs>;
	using TRhsNoCV  = RemoveConstVolatile<TRhs>;
	using Type = HasOperatorBasic<
		TLhsNoRef,
		TRhsNoRef,
		TRet,
		BR_TYPE_OPERATE_FORBIDDEN_IF
	>;
};

template < typename TLhs, typename TRhs, typename TRet >
using HasOperator = typename HasOperatorResult< TLhs, TRhs, TRet >::Type;

} // namespace BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C)
} // namespace TypeTraits
} // namespace Detail

template< typename TLhs, typename TRhs = TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
struct BR_JOIN(HasOperator, BR_TYPE_OPERATE_OP_NAME_C) : BooleanRewrapPositive<
	Detail::TypeTraits::BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C)::HasOperator< TLhs, TRhs, TRet >
> {};

template< typename TLhs, typename TRhs = TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
struct BR_JOIN(NoOperator, BR_TYPE_OPERATE_OP_NAME_C) : BooleanRewrapNegative<
	Detail::TypeTraits::BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C)::HasOperator< TLhs, TRhs, TRet >
> {};

#if defined(BR_CXX14)

template< typename TLhs, typename TRhs = TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
constexpr auto BR_JOIN(has_operator_, BR_TYPE_OPERATE_OP_NAME_V) = bool_constant< BR_JOIN(HasOperator, BR_TYPE_OPERATE_OP_NAME_C)< TLhs, TRhs, TRet > >;

template< typename TLhs, typename TRhs = TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
constexpr auto BR_JOIN(no_operator_, BR_TYPE_OPERATE_OP_NAME_V) = bool_constant< BR_JOIN(NoOperator, BR_TYPE_OPERATE_OP_NAME_C)< TLhs, TRhs, TRet > >;

#endif // defined(BR_CXX14)

} // namespace BR

#undef BR_TYPE_OPERATE_FORBIDDEN_IF
#undef BR_TYPE_OPERATE_OP
#undef BR_TYPE_OPERATE_OP_NAME_V
#undef BR_TYPE_OPERATE_OP_NAME_C