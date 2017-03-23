#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/string/string_compare.hpp>
#include <libbr/string/string_copy.hpp>
#include <libbr/type_traits/is_pod.hpp>
#include <libbr/type_traits/integer_traits.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

/**
 * @brief Describes an object that can refer to a constant contiguous sequence of code units with the first element of the sequence at position zero.
 * @tparam TCodeUnit Type of code units.
 */
template< typename TCodeUnit >
class RawStringView;

/**
 * @brief Creates RawStringView from an unit array.
 * @tparam TCodeUnit Type of code unit.
 * @param string Pointer to the beginning of the unit array.
 * @return The created RawStringView object.
 */
template< typename TCodeUnit >
BR_CONSTEXPR_AFTER_CXX11 auto make_raw_string_view(CString<TCodeUnit> string) -> RawStringView<TCodeUnit> {
	BR_ASSERT(string != nullptr);
	return RawStringView<TCodeUnit>(string);
}

/**
 * @brief Creates RawStringView from an unit array.
 * @tparam TCodeUnit Type of code unit.
 * @param string Pointer to the beginning of the unit array.
 * @param count Number of units.
 * @return The created RawStringView object.
 */
template< typename TCodeUnit >
BR_CONSTEXPR_AFTER_CXX11 auto make_raw_string_view(CString<TCodeUnit> string, Size count) -> RawStringView<TCodeUnit> {
	BR_ASSERT(string != nullptr || count == 0);
	return RawStringView<TCodeUnit>(string, count);
}

template< typename TCodeUnit >
class RawStringView :
	public EqualityComparable< RawStringView<TCodeUnit> >,
	public LessThanComparable< RawStringView<TCodeUnit> >
{
public:
	static_assert(IsPOD<TCodeUnit>{}, "TCodeUnit must be a POD.");

	using CodeUnit = TCodeUnit;

	using Element = CodeUnit;

	using Reference = Element const &;

	using ConstReference = Element const &;

	using Pointer = Element const *;

	using ConstPointer = Element const *;

	using Iterator = Pointer;

	using ConstIterator = ConstPointer;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

	using Size = ::BR::Size;

	using Difference = PointerDifference;

public:
	/**
	 * @brief Default constructor.
	 *
	 * Constructs an empty RawStringView.
	 * After construction, data() is equal to nullptr, and size() is equal to 0.
	 */
	constexpr RawStringView() noexcept : m_data(nullptr), m_size(0) {
	}

	/**
	 * @brief Copy constructor.
	 *
	 * Constructs a view of the same content as other.
	 * After construction, data() is equal to other.data(), and size() is equal to other.size().
	 * @param other Another view to initialize the view with.
	 */
	constexpr RawStringView(RawStringView const & other) noexcept = default;

	/**
	 * @brief Constructs a view of the first \p count units of the character array starting with the element pointed by \p units.
	 * @param units Pointer to a unit array or a C string to initialize the view with.
	 * @param count Number of units to include in the view.
	 */
	constexpr RawStringView(CodeUnit const * units, Size count) : m_data(units), m_size(count) {
	}

	/**
	 * @brief Constructs a view of the null-terminated unit sequence pointed to by units, not including the terminating null unit.
	 * @param units Pointer to a unit array or a C string to initialize the view with.
	 */
	RawStringView(CodeUnit const * units) : m_data(units), m_size(string_length(units)) {
	}

	/**
	 * @brief Replaces the view with that of view.
	 * @return *this
	 */
	auto operator=(RawStringView const &) noexcept -> RawStringView & = default;

	/**
	 * @brief Returns an iterator to the beginning.
	 * @return ConstIterator to the first unit.
	 */
	//@{
	constexpr auto begin() const noexcept -> ConstIterator {
		return cbegin();
	}

	constexpr auto cbegin() const noexcept -> ConstIterator {
		return m_data;
	}
	//@}

	/**
	 * @brief Returns an iterator to the end.
	 * @return ConstIterator to the unit following the last unit.
	 */
	//@{
	constexpr auto end() const noexcept -> ConstIterator {
		return cend();
	}

	constexpr auto cend() const noexcept -> ConstIterator {
		return m_data + m_size;
	}
	//@}

	/**
	 * @brief Returns a reverse iterator to the beginning.
	 * @return ConstReverseIterator to the first unit.
	 */
	//@{
	constexpr auto rbegin() const noexcept -> ConstReverseIterator {
		return crbegin();
	}

	constexpr auto crbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(cend());
	}
	//@}

	/**
	 * @brief Returns a reverse iterator to the end.
	 * @return ConstReverseIterator to the unit following the last unit.
	 */
	//@{
	constexpr auto rend() const noexcept -> ConstReverseIterator {
		return crend();
	}

	constexpr auto crend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(cbegin());
	}
	//@}

	/**
	 * @brief Returns the number of units.
	 * @return The number of units in the view.
	 */
	//@{
	constexpr auto size() const noexcept -> Size {
		return m_size;
	}

	constexpr auto length() const noexcept -> Size {
		return m_size;
	}
	//@}

	/**
	 * @brief Returns the maximum number of units.
	 * @return Maximum number of units.
	 */
	constexpr auto max_size() const noexcept -> Size {
		return IntegerTraits<Size>::max();
	}

	/**
	 * @brief Checks whether the view is empty.
	 * @retval true The view is empty.
	 * @retval false Otherwise.
	 */
	constexpr auto empty() const noexcept -> Boolean {
		return m_size == 0;
	}

	/**
	 * @brief Access specified unit.
	 *
	 * No bounds checking is performed.
	 * @param position Position of the unit to return.
	 * @return Const reference to the requested unit.
	 */
	constexpr auto operator[](Size position) const noexcept -> ConstReference {
		return m_data[position];
	}

	/**
	 * @brief Access specified unit.
	 *
	 * Returns a reference to the character at specified location \p position.
	 * Bounds checking is performed, exception of type IndexException will be thrown on invalid access.
	 * @param position Position of the unit to return.
	 * @return Const reference to the requested unit.
	 */
	constexpr auto at(Size position) const -> ConstReference {
		return position >= size() ? (throw_index_exception(BR_CURRENT_FUNCTION), m_data[0]) : m_data[position];
	}

	/**
	 * @brief Accesses the first unit.
	 *
	 * Returns reference to the first unit in the view.
	 * @return Const reference to the first unit, equivalent to operator[](0).
	 */
	constexpr auto front() const -> ConstReference {
		return BR_ASSERT_MESSAGE(!empty(), "String is empty."), m_data[0];
	}

	/**
	 * @brief Accesses the last unit.
	 *
	 * Returns reference to the last unit in the view.
	 * @return Const reference to the last unit, equivalent to operator[](size() - 1).
	 */
	constexpr auto back() const -> ConstReference {
		return BR_ASSERT_MESSAGE(!empty(), "String is empty."), m_data[m_size - 1];
	}

	/**
	 * @brief Returns a pointer to the underlying unit array.
	 *
	 * The pointer is such that the range [data(); data() + size()) is valid and the values in it correspond to the values of the view.
	 * @return A pointer to the underlying character array.
	 */
	constexpr auto data() const noexcept -> ConstPointer {
		return m_data;
	}

	/**
	 * @brief Set to empty sequence.
	 * @return *this;
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto clear() noexcept -> RawStringView & {
		m_data = nullptr;
		m_size = 0;
		return *this;
	}

	/**
	 * @brief Moves the start of the view forward by \p count units.
	 * @param count Number of units to remove from the start of the view.
	 * @return *this
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto remove_prefix(Size count) noexcept -> RawStringView & {
		BR_ASSERT_MESSAGE(count <= size(), "Can't remove more than size().");
		m_data += count;
		m_size -= count;
		return *this;
	}

	/**
	 * @brief Moves the end of the view back by \p count units.
	 * @param count Number of units to remove from the end of the view.
	 * @return *this
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto remove_suffix(Size count) noexcept -> RawStringView & {
		BR_ASSERT_MESSAGE(count <= size(), "Can't remove more than size()");
		m_size -= count;
		return *this;
	}

	/**
	 * @brief Swaps the contents.
	 * @param other Another view to swap with.
	 * @return *this
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto swap(RawStringView & other) noexcept -> RawStringView & {
		swap(m_data, other.m_data);
		swap(m_size, other.m_size);
		return *this;
	}

	/**
	 * @brief Copies the sub-sequence [position, position + copied) to the unit sequence pointed to by \p destination,
	 *        where copied is the smaller of \p count and size() - \p position.
	 * @param destination Pointer to the destination unit sequence.
	 * @param count Requested sub-sequence length.
	 * @param position Position of the first copied unit.
	 * @return Number of units copied.
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto copy_to(CodeUnit * destination, Size count, Size position = 0) const -> Size {
		if (position > size()) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		auto copied = min(count, size() - position);
		string_copy(destination, data() + position, copied);
		return copied;
	}

	/**
	 * @brief Returns a view of the sub-sequence [position, position - min(count, size() - position)).
	 * @param position Position of the first copied unit.
	 * @param count Requested sub-sequence length.
	 * @return View of the substring [position, position - min(count, size() - position)).
	 */
	//@{
	constexpr auto slice(Size position = 0, Size count = IntegerTraits<Size>::max()) const -> RawStringView {
		return position > size()
			? (throw_index_exception(BR_CURRENT_FUNCTION), RawStringView())
			: RawStringView(data() + position, min(count, size() - position));
	}

	constexpr auto operator()(Size position, Size count) const -> RawStringView {
		return slice(position, count);
	}
	//@}

	/**
	 * @brief Compares two views.
	 * @param view Another view to compare.
	 * @return A Relation value indicate compare result.
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto compare(RawStringView view) const noexcept -> Relation {
		Size min_size = min(size(), view.size());
		auto relation = string_compare(data(), view.data(), min_size);
		if (relation == Relation::EQ) {
			relation = size() == view.size() ? Relation::EQ : (size() < view.size() ? Relation::LT : Relation::GT);
		}
		return relation;
	}

	/**
	 * @brief Compares with unit sequence.
	 * @param units Pointer to the unit sequence to compare to.
	 * @return A Relation value indicate compare result.
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto compare(CodeUnit const * units) const -> Relation {
		return compare(RawStringView(units));
	}

	/**
	 * @brief Compares with unit sequence.
	 * @param units Pointer to the unit sequence to compare to.
	 * @param count Number of units to compare.
	 * @return A Relation value indicate compare result.
	 */
	BR_CONSTEXPR_AFTER_CXX11 auto compare(CodeUnit const * units, Size count) const -> Relation {
		return compare(RawStringView(units, count));
	}

	/**
	 * @brief
	 * @param y Another view to compare.
	 * @retval true Two views are equal.
	 * @retval false Otherwise.
	 */
	auto operator==(RawStringView y) noexcept -> Boolean {
		return size() == y.size() ? compare(y) == Relation::EQ : false;
	}

	/**
	 * @brief
	 * @param y Another view to compare.
	 * @retval true This view is lexicographically less than \p y.
	 * @retval false Otherwise.
	 */
	auto operator<(RawStringView y) noexcept -> Boolean {
		return compare(y) == Relation::LT;
	}

private:
	CodeUnit const * m_data;
	Size m_size;
}; // class RawStringView<TCodeUnit>

inline namespace Literal {

/**
 * @brief Creates RawStringView literal from an unit array literal.
 * @param string Pointer to the beginning of the raw character array literal.
 * @param length Length of the raw character array literal.
 * @return The RawStringView literal.
 */
//@{
inline auto operator "" _rsv(CString<Char8> string, Size length) -> RawStringView<Char8> {
	return RawStringView<Char8>(string, length);
}

inline auto operator "" _rsv(CString<Char16> string, Size length) -> RawStringView<Char16> {
	return RawStringView<Char16>(string, length);
}

inline auto operator "" _rsv(CString<Char32> string, Size length) -> RawStringView<Char32> {
	return RawStringView<Char32>(string, length);
}
//@}

} // inline namespace Literal


} // namespace BR