#ifndef BR_TYPE_OPERATE_OP_NAME
#error "BR_TYPE_OPERATE_OP_NAME not defined!"
#endif

#ifndef BR_TYPE_OPERATE_OP
#error "BR_TYPE_OPERATE_OP not defined!"
#endif

#ifndef BR_TYPE_OPERATE_FORBIDDEN_IF
#error "BR_TYPE_OPERATE_FORBIDDEN_IF not defined!"
#endif

#include <libbr/config.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/is_same.hpp>
#include <libbr/type_operate/is_void.hpp>
#include <libbr/type_operate/remove_const_volatile.hpp>
#include <libbr/type_operate/remove_pointer.hpp>
#include <libbr/type_operate/remove_reference.hpp>
#include <libbr/utility/make_value.hpp>

#define BR_TYPE_OPERATE_NAMESPACE BR_JOIN(SuffixOperator, BR_TYPE_OPERATE_OP_NAME)

namespace BR {
namespace TypeOperate {

namespace Detail {
namespace BR_TYPE_OPERATE_NAMESPACE {

struct NotCareTag {};
struct IsOperatorReturnTest {
	template< typename TRet >
	static BooleanTrue test(TRet);

	template< typename TRet >
	static BooleanFalse test(...);
};

template< typename TLhs, typename TRet >
struct IsOperatorReturnBasic : decltype(
	IsOperatorReturnTest::test< TRet >(make_reference< TLhs >() BR_TYPE_OPERATE_OP >())
) {};

template< typename TLhs, typename TRet >
using IsOperatorReturn = BooleanOr<
	IsSame< TRet, NotCareTag >,
	IsOperatorReturnBasic< TLhs, TRet >
>;

struct IsOperatorExistTest {
	template< typename TLhs, typename = decltype(make_reference< TLhs >() BR_TYPE_OPERATE_OP ) >
	static BooleanTrue test(int);

	template< typename TLhs >
	static BooleanFalse test(...);
};

template< typename TLhs >
using IsOperatorExist = decltype(IsOperatorExistTest::test< TLhs >(0));

template< typename TLhs, typename TRet, bool forbidden_if >
using HasOperatorBasic = BooleanAnd<
	NotVoid< TLhs >,
	BooleanConstant< !forbidden_if >,
	IsOperatorExist< TLhs >,
	IsOperatorReturn< TLhs, TRet >
>;

template < typename TLhs, typename TRet >
struct HasOperatorResult {
	using TLhsNoRef = RemoveReference< TLhs >;
	using TLhsNoPtr = RemoveConstVolatile< RemoveReference< RemovePointer< TLhsNoRef > > >;
	using TLhsNoCV  = RemoveConstVolatile< TLhs >;
	using Type = HasOperatorBasic<
		TLhsNoRef,
		TRet,
		BR_TYPE_OPERATE_FORBIDDEN_IF
	>;
};

template < typename TLhs, typename TRet >
using HasOperator = typename HasOperatorResult< TLhs, TRet >::Type;

} // namespace BR_TYPE_OPERATE_NAMESPACE
} // namespace Detail

template< typename TLhs, typename TRet = Detail::BR_TYPE_OPERATE_NAMESPACE::NotCareTag >
struct BR_JOIN(HasOperator, BR_TYPE_OPERATE_OP_NAME) : Boolean<
	Detail::BR_TYPE_OPERATE_NAMESPACE::HasOperator< TLhs, TRet >
> {};

template< typename TLhs, typename TRet = Detail::BR_TYPE_OPERATE_NAMESPACE::NotCareTag >
struct BR_JOIN(NoOperator, BR_TYPE_OPERATE_OP_NAME) : BooleanNot<
	Detail::BR_TYPE_OPERATE_NAMESPACE::HasOperator< TLhs, TRet >
> {};

} // namespace TypeOperate
} // namespace BR

#undef BR_TYPE_OPERATE_NAMESPACE
#undef BR_TYPE_OPERATE_FORBIDDEN_IF
#undef BR_TYPE_OPERATE_OP
#undef BR_TYPE_OPERATE_OP_NAME