/**
 * @file
 * @brief Conjunction - 逻辑与（AND）
 * @author Bromine0x23
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/conditional.hpp>

namespace BR {

inline namespace Utility {

/**
 * @brief 逻辑与（AND），支持短路求值
 * @tparam TBooleans
 * @see ConjunctionByValue
 * @see conjunction
 */
template< typename... TBooleans >
struct Conjunction;

/**
 * @brief 逻辑与（AND），支持短路求值
 * @tparam values
 * @see Conjunction
 * @see conjunction_by_value
 */
template< Boolean... values >
struct ConjunctionByValue;

/**
 * @brief Conjunction 的模板变量版本
 * @tparam TBooleans
 * @see Conjunction
 */
template< typename... TBooleans >
constexpr auto conjunction = boolean_constant< Conjunction<TBooleans...> >;

/**
 * @brief ConjunctionByValue 的模板变量版本
 * @tparam values
 * @see ConjunctionByValue
 */
template< Boolean... values >
constexpr auto conjunction_by_value = boolean_constant< ConjunctionByValue<values...> >;

} // namespace Utility



namespace _ {
namespace Utility {

template< typename... TBs >
struct ConjunctionBasic;

template<>
struct ConjunctionBasic<> : public BooleanTrue {};

template< typename TB0, typename... TBn >
struct ConjunctionBasic< TB0, TBn... > : public Conditional< TB0, ConjunctionBasic< TBn... >, BooleanFalse > {};

template< Boolean... values >
struct ConjunctionByValueBasic;

template<>
struct ConjunctionByValueBasic<> : public BooleanTrue {};

template< Boolean... values >
struct ConjunctionByValueBasic< true, values... > : public BooleanConstant< ConjunctionByValueBasic<values...>{} > {};

template< Boolean... values >
struct ConjunctionByValueBasic< false, values... > : public BooleanFalse {};


template< typename... TBs >
struct Conjunction : public ConjunctionBasic<TBs...> {};

template< typename TB >
struct Conjunction<TB> : public BooleanRewrap<TB> {};

template< Boolean... values >
struct ConjunctionByValue : public ConjunctionByValueBasic<values...> {};

template< Boolean value >
struct ConjunctionByValue<value> : public BooleanConstant<value> {};

} // namespace Utility
} // namespace _

inline namespace Utility {

template< typename... TBooleans >
struct Conjunction : public BooleanRewrapPositive< _::Utility::Conjunction<TBooleans...> > {};

template< Boolean... values >
struct ConjunctionByValue : public BooleanRewrapPositive< _::Utility::ConjunctionByValue<values...> > {};

} // namespace Utility

} // namespace BR
