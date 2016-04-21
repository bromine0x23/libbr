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
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/remove_pointer.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/is_void.hpp>
#include <libbr/utility/make_value.hpp>

namespace BR {

namespace Detail {
namespace TypeTraits {
namespace BR_JOIN(SuffixOperator, BR_TYPE_OPERATE_OP_NAME_C) {

struct NotCareTag {};
struct IsOperatorReturnTest {
	template< typename TRet >
	static BooleanTrue test(TRet);

	template< typename TRet >
	static BooleanFalse test(...);
};

template< typename TLhs, typename TRet >
struct IsOperatorReturnBasic : decltype(
	IsOperatorReturnTest::test< TRet >(make_reference<TLhs>() BR_TYPE_OPERATE_OP)
) {};

template< typename TLhs, typename TRet >
using IsOperatorReturn = BooleanOr<
	IsSame< TRet, NotCareTag >,
	IsOperatorReturnBasic< TLhs, TRet >
>;

struct IsOperatorExistTest {
	template< typename TLhs, typename = decltype(make_reference<TLhs>() BR_TYPE_OPERATE_OP ) >
	static BooleanTrue test(int);

	template< typename TLhs >
	static BooleanFalse test(...);
};

template< typename TLhs >
using IsOperatorExist = decltype(IsOperatorExistTest::test< TLhs >(0));

template< typename TLhs, typename TRet, bool forbidden_if >
using HasOperatorBasic = BooleanAnd<
	NotVoid<TLhs>,
	BooleanConstant< !forbidden_if >,
	IsOperatorExist<TLhs>,
	IsOperatorReturn< TLhs, TRet >
>;

template < typename TLhs, typename TRet >
struct HasOperatorResult {
	using TLhsNoRef = RemoveReference<TLhs>;
	using TLhsNoPtr = RemoveConstVolatile< RemoveReference< RemovePointer<TLhsNoRef> > >;
	using TLhsNoCV  = RemoveConstVolatile<TLhs>;
	using Type = HasOperatorBasic<
		TLhsNoRef,
		TRet,
		BR_TYPE_OPERATE_FORBIDDEN_IF
	>;
};

template < typename TLhs, typename TRet >
using HasOperator = typename HasOperatorResult< TLhs, TRet >::Type;

} // namespace BR_JOIN(SuffixOperator, BR_TYPE_OPERATE_OP_NAME_C)
} // namespace TypeTraits
} // namespace Detail

template< typename TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(SuffixOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
struct BR_JOIN(HasOperator, BR_TYPE_OPERATE_OP_NAME_C) : BooleanRewrapPositive<
	Detail::TypeTraits::BR_JOIN(SuffixOperator, BR_TYPE_OPERATE_OP_NAME_C)::HasOperator< TLhs, TRet >
> {};

template< typename TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(SuffixOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
struct BR_JOIN(NoOperator, BR_TYPE_OPERATE_OP_NAME_C) : BooleanRewrapNegative<
	Detail::TypeTraits::BR_JOIN(SuffixOperator, BR_TYPE_OPERATE_OP_NAME_C)::HasOperator< TLhs, TRet >
> {};

#if defined(BR_CXX14)

template< typename TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(PrefixOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
constexpr auto BR_JOIN(has_operator_, BR_TYPE_OPERATE_OP_NAME_V) = bool_constant< BR_JOIN(HasOperator, BR_TYPE_OPERATE_OP_NAME_C)< TLhs, TRet > >;

template< typename TLhs, typename TRet = Detail::TypeTraits::BR_JOIN(PrefixOperator, BR_TYPE_OPERATE_OP_NAME_C)::NotCareTag >
constexpr auto BR_JOIN(no_operator_, BR_TYPE_OPERATE_OP_NAME_V) = bool_constant< BR_JOIN(NoOperator, BR_TYPE_OPERATE_OP_NAME_C)< TLhs, TRet > >;

#endif // defined(BR_CXX14)

} // namespace BR

#undef BR_TYPE_OPERATE_FORBIDDEN_IF
#undef BR_TYPE_OPERATE_OP
#undef BR_TYPE_OPERATE_OP_NAME_V
#undef BR_TYPE_OPERATE_OP_NAME_C