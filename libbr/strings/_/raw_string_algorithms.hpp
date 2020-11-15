#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/find_end.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/string/string_compare.hpp>
#include <libbr/string/string_find.hpp>

namespace BR {
namespace _ {
namespace String {
namespace RawString {

template< typename TCodeUnit, typename Size, typename Index >
constexpr inline auto index(
	TCodeUnit const * const data, Size size,
	TCodeUnit unit,
	Index offset
) noexcept -> Index {
	Size position = offset < 0 ? size - offset : offset;
	if (position >= size) {
		return -1;
	}
	auto result = string_find(data + position, unit, size - position);
	if (result == nullptr) {
		return -1;
	}
	return static_cast<Index>(result - data);
}

template< typename TCodeUnit >
constexpr inline auto index_basic(
	TCodeUnit const * first0, TCodeUnit const * last0,
	TCodeUnit const * first1, TCodeUnit const * last1
) noexcept -> TCodeUnit const * {
	auto const length1 = last1 - first1;
	if (length1 == 0) {
		return first0;
	}
	auto length0 = last1 - first1;
	if (length0 < length1) {
		return last0;
	}
	for (auto const front1 = *first1;; ++first0) {
		length0 = last0 - first0;
		if (length0 < length1) {
			return last0;
		}

		first0 = string_find(first0, front1, length0 - length1 + 1);
		if (first0 == nullptr) {
			return last0;
		}

		if (string_compare(first0, first1, length1) == Relation::EQ) {
			return first0;
		}
	}
}

template< typename TCodeUnit, typename Size, typename Index >
constexpr inline auto index(
	TCodeUnit const * const data, Size size,
	TCodeUnit const * const units, Size length,
	Index offset
) noexcept -> Index {
	Size position = offset < 0 ? size - offset : offset;
	auto result = index_basic(data + position, data + size, units, units + length);
	if (result == data + size) {
		return -1;
	}
	return static_cast<Index>(result - data);
}

template< typename TCodeUnit, typename Size, typename Index >
constexpr inline auto rindex(
	TCodeUnit const * const data, Size size,
	TCodeUnit unit,
	Index offset
) noexcept -> Index {
	Size position = offset < 0 ? size - offset : offset;
	if (size < 1) {
		return -1;
	}
	if (position < size) {
		++position;
	} else {
		position = size;
	}
	for (auto pointer = data + position; pointer != data;) {
		--pointer;
		if (*pointer == unit) {
			return static_cast<Index>(pointer - data);
		}
	}
	return -1;
}

template< typename TCodeUnit, typename Size, typename Index >
constexpr inline auto rindex(
	TCodeUnit const * const data, Size size,
	TCodeUnit const * const units, Size length,
	Index offset
) noexcept -> Index {
	Size position = offset < 0 ? size - offset : offset;
	if (length < size - position) {
		position += length;
	} else {
		position = size;
	}
	auto result = find_end(data, data + position, units, units + length);
	if (length > 0 && result == data + position) {
		return -1;
	}
	return static_cast<Index>(result - data);
}

} // namespace RawString
} // namespace String
} // namespace _
} // namespace BR