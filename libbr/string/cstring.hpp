/**
 * @file
 * @brief cstring
 * @author Bromine0x23
 * @since 2015/11/5
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/math/relation.hpp>

namespace BR {

/**
 * @brief like C STL strcmp
 * @param[in] X
 * @param[in] Y
 */
//@{
auto string_compare(CString<NChar> X, CString<NChar> Y) -> Relation;

auto string_compare(CString<WChar> X, CString<WChar> Y) -> Relation;
//@}

/**
 * @brief like C STL strcmp
 * @param[in] X
 * @param[in] Y
 * @param[in] n
 */
//@{
auto string_compare(CString<NChar> X, CString<NChar> Y, Size n) -> Relation;

auto string_compare(CString<WChar> X, CString<WChar> Y, Size n) -> Relation;
//@}

/**
 * @brief like C STL strcat
 * @param[out] D
 * @param[in] S
 */
//@{
auto string_concat(NChar * D, CString<NChar> S) -> NChar *;

auto string_concat(WChar * D, CString<WChar> S) -> WChar *;
//@}

/**
 * @brief like C STL strncat
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
//@{
auto string_concat(NChar * D, CString<NChar> S, Size n) -> NChar *;

auto string_concat(WChar * D, CString<WChar> S, Size n) -> WChar *;
//@}

/**
 * @brief like C STL strcpy
 * @param[out] D
 * @param[in] S
 */
//@{
auto string_copy(NChar * D, CString<NChar> S) -> NChar *;

auto string_copy(WChar * D, CString<WChar> S) -> WChar *;
//@}

/**
 * @brief like C STL strncpy
 * @param[out] D
 * @param[in] S
 * @param[in] n
 */
//@{
auto string_copy(NChar * D, CString<NChar> S, Size n) -> NChar *;

auto string_copy(WChar * D, CString<WChar> S, Size n) -> WChar *;
//@}

/**
 * @brief like C STL strlen
 * @param[in] S
 */
//@{
auto string_find(NChar const * S, NChar c) -> NChar const *;

auto string_find(WChar const * S, WChar c) -> WChar const *;
//@}

/**
 * @brief like C STL strlen
 * @param[in] S
 */
//@{
auto string_find(NChar * S, NChar c) -> NChar *;

auto string_find(WChar * S, WChar c) -> WChar *;
//@}

/**
 * @brief like C STL strlen
 * @param[out] X
 */
//@{
auto string_length(CString<NChar> X) -> Size;

auto string_length(CString<WChar> X) -> Size;
//@}

/**
 * @brief like C STL strlen
 * @param[in] S
 * @param[in] K
 */
//@{
auto string_search(NChar const * S, CString<NChar> K) -> NChar const *;

auto string_search(WChar const * S, CString<WChar> K) -> WChar const *;
//@}

/**
 * @brief like C STL strlen
 * @param[in] S
 * @param[in] K
 */
//@{
auto string_search(NChar * S, CString<NChar> K) -> NChar *;

auto string_search(WChar * S, CString<WChar> K) -> WChar *;
//@}

} // namespace BR

