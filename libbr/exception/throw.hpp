/**
 * @file
 * @brief throw functions
 * @author Bromine0x23
 * @since 2015/11/6
 */
#pragma once

#include <libbr/config.hpp>

namespace BR {

/**
 * 抛出 RuntimeException
 * @throw RuntimeException
 * @param message 消息
 */
[[noreturn]] void throw_runtime_exception(CString<NChar> message);

/**
 * 抛出 LogicException
 * @throw LogicException
 * @param message 消息
 */
[[noreturn]] void throw_logic_exception(CString<NChar> message);

/**
 * 抛出 ArgumentException
 * @throw ArgumentException
 * @param message 消息
 */
[[noreturn]] void throw_argument_exception(CString<NChar> message);

/**
 * 抛出 DomainException
 * @throw DomainException
 * @param message 消息
 */
[[noreturn]] void throw_domain_exception(CString<NChar> message);

/**
 * 抛出 IndexException
 * @throw IndexException
 * @param message 消息
 */
[[noreturn]] void throw_index_exception(CString<NChar> message);

/**
 * 抛出 LengthException
 * @throw LengthException
 * @param message 消息
 */
[[noreturn]] void throw_length_exception(CString<NChar> message);

}