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

#define BR_TYPE_OPERATE_NAMESPACE BR_JOIN(BinaryOperator, BR_TYPE_OPERATE_OP_NAME)

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

template< typename TLhs, typename TRhs, typename TRet >
struct IsOperatorReturnBasic : decltype(
	IsOperatorReturnTest::test< TRet >(make_reference< TLhs >() BR_TYPE_OPERATE_OP make_reference< TRhs >())
) {};

template< typename TLhs, typename TRhs, typename TRet >
using IsOperatorReturn = BooleanOr<
	IsSame< TRet, NotCareTag >,
	IsOperatorReturnBasic< TLhs, TRhs, TRet >
>;

struct IsOperatorExistTest {
	template< typename TLhs, typename TRhs, typename = decltype(make_reference< TLhs >() BR_TYPE_OPERATE_OP make_reference< TRhs >()) >
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
	using TLhsNoRef = RemoveReference< TLhs >;
	using TRhsNoRef = RemoveReference< TRhs >;
	using TLhsNoPtr = RemoveConstVolatile< RemoveReference< RemovePointer< TLhsNoRef > > >;
	using TRhsNoPtr = RemoveConstVolatile< RemoveReference< RemovePointer< TRhsNoRef > > >;
	using TLhsNoCV  = RemoveConstVolatile< TLhs >;
	using TRhsNoCV  = RemoveConstVolatile< TRhs >;
	using Type = HasOperatorBasic<
		TLhsNoRef,
		TRhsNoRef,
		TRet,
		BR_TYPE_OPERATE_FORBIDDEN_IF
	>;
};

template < typename TLhs, typename TRhs, typename TRet >
using HasOperator = typename HasOperatorResult< TLhs, TRhs, TRet >::Type;

} // namespace BR_TYPE_OPERATE_NAMESPACE
} // namespace Detail

template< typename TLhs, typename TRhs = TLhs, typename TRet = Detail::BR_TYPE_OPERATE_NAMESPACE::NotCareTag >
struct BR_JOIN(HasOperator, BR_TYPE_OPERATE_OP_NAME) : Boolean<
	Detail::BR_TYPE_OPERATE_NAMESPACE::HasOperator< TLhs, TRhs, TRet >
> {};

template< typename TLhs, typename TRhs = TLhs, typename TRet = Detail::BR_TYPE_OPERATE_NAMESPACE::NotCareTag >
struct BR_JOIN(NoOperator, BR_TYPE_OPERATE_OP_NAME) : BooleanNot<
	Detail::BR_TYPE_OPERATE_NAMESPACE::HasOperator< TLhs, TRhs, TRet >
> {};

} // namespace TypeOperate
} // namespace BR

#undef BR_TYPE_OPERATE_NAMESPACE
#undef BR_TYPE_OPERATE_FORBIDDEN_IF
#undef BR_TYPE_OPERATE_OP
#undef BR_TYPE_OPERATE_OP_NAME