#pragma once

#include <libbr/config.hpp>
#include <libbr/type_operate/add_const.hpp>
#include <libbr/type_operate/add_const_volatile.hpp>
#include <libbr/type_operate/add_volatile.hpp>
#include <libbr/type_operate/type.hpp>
#include <libbr/utility/integral_constant.hpp>

namespace BR {

/**
 * @brief 元组
 * @tparam TTypes 各个内容类型
 */
template< typename ... TTypes >
class Tuple;

/**
 * @brief 获取(类)元组类型的长度
 * @tparam T (类)元组类型
 */
template< typename T >
struct TupleSize;

#if defined(BR_CXX14)

/**
 * @brief TupleSize 的模板变量版本
 * @tparam T 待检查类型
 * @see BR::TupleSize
 */
template< typename T >
constexpr auto tuple_size = integral_constant< TupleSize<T> >;

#endif // defined(BR_CXX14)

template< typename T >
struct TupleSize< T const > : public TupleSize<T> {};

template< typename T >
struct TupleSize< T volatile > : public TupleSize<T> {};

template< typename T >
struct TupleSize< T const volatile > : public TupleSize<T> {};

/**
 * @brief 获取(类)元组类型在给定索引的元素类型
 * @tparam I 索引值
 * @tparam T (类)元组类型
 */
template< Size I, typename T >
struct TypeTupleElement;

/**
 * @brief TypeTupleElement 的简写版本
 * @tparam I
 * @tparam T
 * @see TypeTupleElement
 */
template< Size I, typename T >
using TupleElement = TypeUnwrap< TypeTupleElement< I, T > >;

template< Size I, typename T >
struct TypeTupleElement< I, T const > : public TypeAddConst< TupleElement< I, T > > {};

template< Size I, typename T >
struct TypeTupleElement< I, T volatile > : public TypeAddVolatile< TupleElement< I, T > > {};

template< Size I, typename T >
struct TypeTupleElement< I, T const volatile > : public TypeAddConstVolatile< TupleElement< I, T > > {};

} // namespace BR