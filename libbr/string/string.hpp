/**
 * @file
 * @brief 字符串类
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/string/raw_string.hpp>
#include <libbr/string/string_view.hpp>
#include <libbr/encoding/encoding.hpp>
#include <libbr/type_traits/make_signed.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

/**
 * @brief 字符串类
 * @tparam TEncoding 编码类型
 * @tparam TAllocator 分配器类型
 */
template< typename TEncoding = DefaultEncoding, typename TAllocator = Allocator<typename TEncoding::CodeUnit> >
class String;


template< typename TEncoding, typename TAllocator >
class String : public RawString< typename TEncoding::CodeUnit, TAllocator > {

public:
	using Encoding = TEncoding;

	using Allocator = TAllocator;

private:
	using Base = BR::RawString< typename Encoding::CodeUnit, Allocator >;

public:
	using RawString = Base;

	using CodeUnit = typename Base::CodeUnit;

	using CodePoint = typename Encoding::CodePoint;

	using Size = typename Base::Size;

	using Index = MakeSigned<Size>;

public:
	String() : Base() {
	}

	String(Allocator allocator) : Base(allocator) {
	}

	String(String const & string) : Base(string.as_raw()) {
	}

	String(String const & string, Allocator const & allocator) : Base(string.as_raw(), allocator) {
	}

	String(String && string) : Base(move(string.as_raw())) {
	}

	String(String && string, Allocator const & allocator) : Base(move(string.as_raw()), allocator) {
	}

	String(RawString const & string) : Base(string) {
	}

	String(RawString const & string, Allocator const & allocator) : Base(string, allocator) {
	}

	String(RawString && string) : Base(move(string)) {
	}

	String(RawString && string, Allocator const & allocator) : Base(move(string), allocator) {
	}

	String(CString<CodeUnit> string, Allocator const & allocator = Allocator()) : Base(string, allocator) {
	}

	String(CString<CodeUnit> string, Size length, Allocator const & allocator = Allocator()) : Base(string, length, allocator) {
	}

	String(StringView<Encoding> string, Allocator const & allocator = Allocator()) : Base(string, allocator) {
	}

	String(RawStringView<CodeUnit> string, Allocator const & allocator = Allocator()) : Base(string, allocator) {
	}

	template< typename TIterator >
	String(TIterator first, TIterator last, Allocator const & allocator = Allocator()) : Base(first, last, allocator) {
	}

	String(InitializerList<CodeUnit> list, Allocator const & allocator = Allocator()) : Base(list, allocator) {
	}

	auto operator=(String const & string) -> String & {
		Base::operator=(string);
		return *this;
	}

	auto operator=(String && string) -> String & {
		Base::operator=(move(string));
		return *this;
	}

	/**
	 * @brief count by code point, O(n)
	 * @return length
	 */
	auto length() const -> Size {
		if (Encoding::MAX_ENCODED_LENGTH == Encoding::MIN_ENCODED_LENGTH) {
			return Size((this->size() + Encoding::MIN_ENCODED_LENGTH - 1) / Encoding::MIN_ENCODED_LENGTH);
		}
		auto p = this->data();
		auto const e = p + this->size();
		Size l = 0;
		for (l = 0; p < e; ++l) {
			p += Encoding::length(p);
		}
		return l;
	}

	auto as_raw() noexcept -> RawString & {
		return static_cast<RawString &>(*this);
	}

	auto as_raw() const noexcept -> RawString const & {
		return static_cast<RawString const &>(*this);
	}

	auto to_raw() const -> RawString {
		return RawString(*this);
	}

	auto index(CodePoint point, Size start = 0) const -> Index {
		return 0;
	}

	auto index(String const & string, Size start = 0) const -> Index {
		return 0;
	}

	auto index(StringView<Encoding> const & string, Size start = 0) const -> Index {
		return 0;
	}

	auto index(CString<CodeUnit> string, Size start) const -> Index {
		return 0;
	}

	auto index(CString<CodeUnit> string, Size length, Size start) const -> Index {
		return 0;
	}

	auto rindex(CodePoint point, Size start = 0) const -> Index {
		return 0;
	}

	auto rindex(String const & string, Size start = 0) const -> Index {
		return 0;
	}

	auto rindex(StringView<Encoding> const & string, Size start = 0) const -> Index {
		return 0;
	}

}; // class String

extern template class String<DefaultEncoding>;

inline namespace Literal {

inline namespace StringLiteral {

inline auto operator "" _s(CString<Char8> string, Size length) -> String<DefaultEncoding> {
	return String<DefaultEncoding>(string, length);
}

inline auto operator "" _s(CString<Char16> string, Size length) -> String<UTF16Encoding> {
	return String<UTF16Encoding>(string, length);
}

} // inline namespace StringLiteral

} // inline namespace Literal

} // namespace BR