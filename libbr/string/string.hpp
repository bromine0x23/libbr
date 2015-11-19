/**
 * @file
 * @brief 字符串类
 * @author Bromine0x23
 * @since 2015/11/6
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy_n.hpp>
#include <libbr/algorithm/find_end.hpp>
#include <libbr/algorithm/find_first_of.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/algorithm/rotate.hpp>
#include <libbr/algorithm/search.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/compressed_pair.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/pair.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/iterator_range.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/optional/optional.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/allocator_traits.hpp>
#include <libbr/type_traits/char_traits.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>
#include <libbr/type_traits/is_iterator.hpp>
#include <libbr/type_traits/is_pod.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

/**
 * @brief 字符串类
 * @tparam TChar 字符类型
 * @tparam TCharTraits 字符类型 TChar 的特性类
 * @tparam TAllocator 分配器类
 */
template<typename TChar, typename TCharTraits = CharTraits<TChar>, typename TAllocator = Allocator<TChar> >
class String;

/**
 * @brief 字符串视图
 * @tparam TChar 字符类型
 * @tparam TCharTraits 字符类型 TChar 的特性类
 *
 * 提供一个无关存储管理的字符串界面，以在其上进行非修改性操作，或用作其他字符串修改性操作的参数
 */
template<typename TChar, typename TCharTraits = CharTraits<TChar> >
class StringView;

template<typename TChar, typename TCharTraits = CharTraits<TChar> >
BR_CONSTEXPR_AFTER_CXX11 auto make_string_view(CString<TChar> string) -> StringView<TChar, TCharTraits> {
	BR_ASSERT(string != nullptr);
	return StringView<TChar, TCharTraits>(string);
};

template<typename TChar, typename TCharTraits = CharTraits<TChar> >
BR_CONSTEXPR_AFTER_CXX11 auto make_string_view(CString<TChar> string, Size count) -> StringView<TChar, TCharTraits> {
	BR_ASSERT(string != nullptr || count == 0);
	return StringView<TChar, TCharTraits>(string, count);
};

template<typename TChar, typename TCharTraits>
class StringView {
public:
	static_assert(IsPOD<TChar>::value, "TChar must be a POD.");

	using CharTraits = TCharTraits;

	using Char = typename CharTraits::Char;

	static_assert(IsSame<Char, TChar>::value, "CharTraits::Char must be same type as TChar.");

	using Reference = Char const &;

	using ConstReference = Char const &;

	using Pointer = Char const *;

	using ConstPointer = Char const *;

	using Iterator = Pointer;

	using ConstIterator = ConstPointer;

	using ReverseIterator = BR::ReverseIterator<Iterator>;

	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

	using Size = BR::Size;

	using Difference = PointerDifference;

	constexpr StringView() noexcept : m_data(nullptr), m_size(0) {
	}

	constexpr StringView(StringView const &) noexcept = default;

	template<typename TAllocator>
	constexpr StringView(String<Char, CharTraits, TAllocator> const & string) noexcept : m_data(string.data()), m_size(
		string.size()) {
	}

	constexpr StringView(Char const * string, Size size) : m_data(string), m_size(size) {
	}

	StringView(Char const * string) : m_data(string), m_size(CharTraits::length(string)) {
	}

	auto operator=(StringView const &) noexcept -> StringView & = default;

	constexpr auto begin() const noexcept -> ConstIterator {
		return cbegin();
	}

	constexpr auto end() const noexcept -> ConstIterator {
		return cend();
	}

	constexpr auto cbegin() const noexcept -> ConstIterator {
		return m_data;
	}

	constexpr auto cend() const noexcept -> ConstIterator {
		return m_data + m_size;
	}

	constexpr auto rbegin() const noexcept -> ConstReverseIterator {
		return crbegin();
	}

	constexpr auto rend() const noexcept -> ConstReverseIterator {
		return crend();
	}

	constexpr auto crbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(cend());
	}

	constexpr auto crend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(cbegin());
	}

	constexpr auto size() const noexcept -> Size {
		return m_size;
	}

	constexpr auto is_empty() const noexcept -> bool {
		return m_size == 0;
	}

	constexpr auto operator[](Size index) const -> ConstReference {
		return m_data[index];
	}

	BR_CONSTEXPR_AFTER_CXX11 auto at(Size index) const -> ConstReference {
		if (index >= size()) {
			throw_index_exception("StringView::at");
		}
		return m_data[index];
	}

	constexpr auto front() const -> ConstReference {
		return m_data[0];
	}

	constexpr auto back() const -> ConstReference {
		return m_data[m_size - 1];
	}

	constexpr auto data() const -> ConstPointer {
		return m_data;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto clear() noexcept -> StringView {
		m_data = nullptr;
		m_size = 0;
		return *this;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto remove_prefix(Size n) noexcept -> StringView {
		BR_ASSERT(n <= size());
		m_data += n;
		m_size -= n;
		return *this;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto remove_suffix(Size n) noexcept -> StringView {
		BR_ASSERT(n <= size());
		m_size -= n;
		return *this;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto swap(StringView & other) noexcept -> StringView {
		BR::swap(m_data, other.m_data);
		BR::swap(m_size, other.m_size);
		return *this;
	}

	template<typename TAllocator>
	explicit operator String<Char, CharTraits, TAllocator>() const {
		return String<Char, CharTraits, TAllocator>(begin(), end());
	}

	template<typename TAllocator = Allocator<Char> >
	auto to_string(TAllocator const & allocator = TAllocator()) const -> String<Char, CharTraits, TAllocator> {
		return String<Char, CharTraits, TAllocator>(begin(), end(), allocator);
	}

	auto copy(Char * S, Size length, Size position = 0) const -> Size {
		if (position > size()) {
			throw_index_exception("StringView::copy");
		}
		Size left = min(length, size() - position);
		copy_n(begin() + position, left, S);
		return left;
	}

	BR_CONSTEXPR_AFTER_CXX11 auto slice(Size position) const -> StringView {
		if (position > size()) {
			throw_index_exception("StringView::slice");
		}
		return StringView(data() + position, size() - position);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto slice(Size position, Size count) const -> StringView {
		if (position > size()) {
			throw_index_exception("StringView::slice");
		}
		return StringView(data() + position, min(count, size() - position));
	}

	BR_CONSTEXPR_AFTER_CXX11 auto compare(StringView const & view) const noexcept -> Relation {
		Size left = min(size(), view.size());
		Relation relation = CharTraits::compare(data(), view.data(), left);
		if (relation == Relation::EQ) {
			relation = size() != view.size() ? (size() < view.size() ? Relation::LT : Relation::GT) : Relation::EQ;
		}
		return relation;
	}

	auto index(StringView view, Size offset = 0) const noexcept -> Optional<Size>;

	auto index(Char c, Size offset = 0) const noexcept -> Optional<Size>;

	auto rindex(StringView view, Size offset = 0) const noexcept -> Optional<Size>;

	auto rindex(Char c, Size offset = 0) const noexcept -> Optional<Size>;

	auto first(StringView view, Size offset = 0) const noexcept -> Optional<Size>;

	auto first_not(StringView view, Size offset = 0) const noexcept -> Optional<Size>;

	auto first_not(Char c, Size offset = 0) const noexcept -> Optional<Size>;

	auto last(StringView view, Size offset = 0) const noexcept -> Optional<Size>;

	auto last_not(StringView view, Size offset = 0) const noexcept -> Optional<Size>;

	auto last_not(Char c, Size offset = 0) const noexcept -> Optional<Size>;

private:
	Char const * m_data;
	Size m_size;
}; // StringView< TChar, TCharTraits >

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::index(StringView view, Size offset) const noexcept -> Optional<Size> {
	if (offset > m_size || m_size - offset < view.size()) {
		return null_optional;
	}
	if (view.size() == 0) {
		return null_optional;
	}
	auto result = search(m_data + offset, m_data + m_size, view.begin(), view.end(), CharTraits::equal);
	if (result == m_data + m_size) {
		return null_optional;
	}
	return static_cast<Size>(result - m_data);
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::index(Char c, Size offset) const noexcept -> Optional<Size> {
	if (offset >= m_size) {
		return null_optional;
	}
	auto result = CharTraits::find(m_data + offset, c, m_size - offset);
	if (result == nullptr) {
		return null_optional;
	}
	return static_cast<Size>(result - m_data);
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::rindex(StringView view, Size offset) const noexcept -> Optional<Size> {
	offset = min(offset, m_size);
	if (view.size() < m_size - offset) {
		offset += view.size();
	} else {
		offset = view.size();
	}
	auto result = find_end(m_data, m_data + offset, view.begin(), view.end(), CharTraits::equal);
	if (view.size() > 0 && result == m_data + offset) {
		return null_optional;
	}
	return static_cast<Size>(result - m_data);
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::rindex(Char c, Size offset) const noexcept -> Optional<Size> {
	if (m_size < 1) {
		return null_optional;
	}
	if (offset < m_size) {
		++offset;
	} else {
		offset = m_size;
	}
	for (auto p = m_data + offset; p != m_data;) {
		if (CharTraits::equal(*--p, c)) {
			return static_cast<Size>(p - m_data);
		}
	}
	return null_optional;
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::first(StringView view, Size offset) const noexcept -> Optional<Size> {
	if (offset >= m_size || view.size() == 0) {
		return null_optional;
	}
	auto result = find_first_of(m_data + offset, m_data + m_size, view.begin(), view.end(), CharTraits::equal);
	if (result == m_data + m_size) {
		return null_optional;
	}
	return static_cast<Size>(result - m_data);
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::first_not(StringView view, Size offset) const noexcept -> Optional<Size> {
	if (offset < m_size) {
		auto e = m_data + m_size;
		for (auto p = m_data + offset; p != e; ++p) {
			if (CharTraits::find(view.data(), view.size(), *p) == nullptr) {
				return static_cast<Size>(p - m_data);
			}
		}
	}
	return null_optional;
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::first_not(Char c, Size offset) const noexcept -> Optional<Size> {
	if (offset < m_size) {
		auto e = m_data + m_size;
		for (auto p = m_data + offset; p != e; ++p) {
			if (CharTraits::equal(*p, c)) {
				return static_cast<Size>(p - m_data);
			}
		}
	}
	return null_optional;
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::last(StringView view, Size offset) const noexcept -> Optional<Size> {
	if (view.size() != 0) {
		if (offset < m_size) {
			++offset;
		} else {
			offset = m_size;
		}
		for (auto p = m_data + offset; p != m_data;) {
			if (CharTraits::find(view.data(), view.size(), *--p) != nullptr) {
				return static_cast<Size>(p - m_data);
			}
		}
	}
	return null_optional;
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::last_not(StringView view, Size offset) const noexcept -> Optional<Size> {
	if (offset < m_size) {
		++offset;
	} else {
		offset = m_size;
	}
	for (auto p = m_data + offset; p != m_data;) {
		if (CharTraits::find(view.data(), view.size(), *--p) == nullptr) {
			return static_cast<Size>(p - m_data);
		}
	}
	return null_optional;
};

template<typename TChar, typename TCharTraits>
auto StringView<TChar, TCharTraits>::last_not(Char c, Size offset) const noexcept -> Optional<Size> {
	if (offset < m_size) {
		++offset;
	} else {
		offset = m_size;
	}
	for (auto p = m_data + offset; p != m_data;) {
		if (!CharTraits::equal(*p, c)) {
			return static_cast<Size>(p - m_data);
		}
	}
	return null_optional;
};

template<typename TChar, typename TCharTraits, typename TAllocator>
class String {

public:
	static_assert(IsPOD<TChar>::value, "TChar must be a POD.");

	/**
	 * @brief 字符类型 TChar 的特性类
	 * @see BR::CharTraits
	 */
	using CharTraits = TCharTraits;

	/**
	 * @brief CharTraits::Char ，必须和 \em TChar 相同
	 */
	using Char = typename CharTraits::Char;

	static_assert(IsSame<Char, TChar>::value, "CharTraits::Char must be same type as TChar.");

	/**
	 * @brief 分配器类
	 * @see BR::Allocator
	 */
	using Allocator = TAllocator;

private:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	/**
	 * @brief AllocatorTraits<Allocator>::Value ，分配器分配的单元类型，必须和 \em TChar 相同
	 * @see BR::AllocatorTraits::Value
	 */
	using Value = typename AllocatorTraits::Value;

	static_assert(IsSame<Value, TChar>::value, "AllocatorTraits<Allocator>::Value must be same type as TChar.");

	/**
	 * @brief AllocatorTraits<Allocator>::Size
	 * @see BR::AllocatorTraits::Size
	 */
	using Size = typename AllocatorTraits::Size;

	/**
	 * @brief Value 的非常量引用
	 */
	using Reference = Value &;

	/**
	 * @brief Value 的常量引用
	 */
	using ConstReference = Value const &;

	/**
	 * @brief AllocatorTraits<Allocator>::Pointer ，与指向 Value 的非常量指针等同的类型
	 * @see AllocatorTraits::Pointer
	 */
	using Pointer = typename AllocatorTraits::Pointer;

	/**
	 * @brief AllocatorTraits<Allocator>::ConstPointer ，与指向 Value 的常量指针等同的类型
	 * @see AllocatorTraits::ConstPointer
	 */
	using ConstPointer = typename AllocatorTraits::ConstPointer;

private:
	using PointerTraits = BR::PointerTraits<Pointer>;

public:
	/**
	 * @brief AllocatorTraits<Allocator>::Difference, 指针之差的结果类型
	 * @see AllocatorTraits::Difference
	 */
	using Difference = typename AllocatorTraits::Difference;

	/**
	 * @brief 迭代器
	 */
	using Iterator = Pointer;

	/**
	 * @brief 常量迭代器
	 */
	using ConstIterator = ConstPointer;

	/**
	 * @brief 反向迭代器
	 */
	using ReverseIterator = BR::ReverseIterator<Iterator>;

	/**
	 * @brief 反向常量迭代器
	 */
	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

private:
	template< typename TIterator >
	using IsInputIterator = BooleanAnd<
		IsConvertible< typename IteratorTraits<TIterator>::Category, ReadableTag >,
		IsConvertible< typename IteratorTraits<TIterator>::Category, SinglePassTraversalTag >
	>;

private:
	struct Storage {
		Size capacity;
		Size size;
		Pointer pointer;
	};

public:

	/**
	 * @name 构造函数
	 */
	///@{
	/**
	 * @brief 默认构造
	 *
	 * 设置为空串（长度为0）
	 */
	String() {
		m_zeroize();
	}

	/**
	 * @brief 指定分配器，并默认构造
	 * @param[in] allocator 分配器
	 */
	explicit String(Allocator const & allocator) : m_pair(allocator) {
		m_zeroize();
	}

	/**
	 * @brief 复制构造函数
	 * @param[in] string 源字符串
	 */
	String(String const & string) :
		m_pair(AllocatorTraits::select_on_container_copy_construction(string.m_allocator())) {
		m_construct(string.m_get_pointer(), string.m_get_size());
	}

	/**
	 * @brief 指定分配器，并复制内容
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 * @see String(String const & string)
	 */
	String(String const & string, Allocator const & allocator) : m_pair(allocator) {
		m_construct(string.m_get_pointer(), string.m_get_size());
	}

	/**
	 * @brief 移动构造
	 * @param[in] string 源字符串
	 *
	 * 把源字符串的内容搬移到新串中
	 */
	String(String && string) noexcept(HasNothrowMoveConstructor<Allocator>::value) : m_pair(move(string.m_pair)) {
		string.m_zeroize();
	}

	/**
	 * @brief 指定分配器，并移动内容
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 * @see String(String && string)
	 *
	 */
	String(String && string, Allocator const & allocator) : m_pair(allocator) {
		if (allocator != string.m_allocator()) {
			m_construct(string.m_get_pointer(), string.m_get_size());
		} else {
			m_storage() = string.m_storage();
			string.m_zeroize();
		}
	}

	/**
	 * @brief 从C风格的字符串复制
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 */
	String(Char const * string, Allocator const & allocator = Allocator()) : m_pair(allocator) {
		BR_ASSERT(string != nullptr);
		m_construct(string, CharTraits::length(string));
	}

	String(Char const * string, Size length, Allocator const & allocator = Allocator()) : m_pair(allocator) {
		BR_ASSERT(string != nullptr);
		m_construct(string, length);
	}

	/**
	 * @brief 从字符串视图构造
	 * @param[in] view 字符串视图
	 * @param[in] allocator 分配器
	 */
	String(StringView<Char, CharTraits> const & view, Allocator const & allocator = Allocator()) : m_pair(allocator) {
		m_construct(view.data(), view.size());
	}

	/**
	 * @brief 从迭代器区间构造
	 * @param[in] first, last 区间\f$[first, last)\f$
	 * @param[in] allocator 分配器
	 */
	template< typename TIterator >
	String(TIterator first, TIterator last, Allocator const & allocator = Allocator(), EnableIf< IsInputIterator<TIterator> > * = nullptr) : m_pair(allocator) {
		m_construct(first, last, IteratorTraits<TIterator>::category());
	}

	/**
	 * @brief 从初始化列表构造
	 * @param[in] list 初始化列表
	 * @param[in] allocator 分配器
	 */
	String(InitializerList<Char> list, Allocator const & allocator = Allocator()) :
		String(list.begin(), list.end(), allocator) {
	}
	///@}

	/**
	 * @name 析构函数
	 */
	///@{
	~String() {
		m_destruct();
	}
	///@}

	/**
	 * @name 迭代器
	 */
	///@{
	/**
	 * @brief 返回表示迭代开始的迭代器
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(m_get_pointer());
	}

	/**
	 * @brief 返回表示迭代开始的迭代器
	 */
	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(m_get_pointer());
	}

	/**
	 * @brief 返回表示迭代开始的迭代器(常量限定)
	 */
	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	/**
	 * @brief 返回表示迭代结束的迭代器
	 */
	auto end() noexcept -> Iterator {
		return Iterator(m_get_pointer() + size());
	}

	/**
	 * @brief 返回表示迭代结束的迭代器
	 */
	auto end() const noexcept -> ConstIterator {
		return ConstIterator(m_get_pointer() + size());
	}

	/**
	 * @brief 返回表示迭代结束的迭代器(常量限定)
	 */
	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	/**
	 * @brief 返回表示反向迭代开始的迭代器
	 */
	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	/**
	 * @brief 返回表示反向迭代开始的迭代器
	 */
	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	/**
	 * @brief 返回表示反向迭代开始的迭代器(常量限定)
	 */
	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
	}

	/**
	 * @brief 返回表示反向迭代结束的迭代器
	 */
	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	/**
	 * @brief 返回表示反向迭代结束的迭代器
	 */
	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	/**
	 * @brief 返回表示反向迭代结束的迭代器(常量限定)
	 */
	auto crend() const noexcept -> ConstReverseIterator {
		return rend();
	}
	///@}

	/**
	 * @name 元素访问
	 */
	///@{
	/**
	 * @brief 获取元素引用，无越界检查
	 * @param[in] index 索引
	 * @see Location
	 *
	 * 返回重载了 operator<< 的对象，用于插入，或隐式转型为 Char
	 */
	auto operator[](Size index) -> Reference {
		BR_ASSERT(index < size());
		return m_char(index);
	}

	/**
	 * @brief 获取元素常引用，无越界检查
	 * @param[in] index 索引
	 */
	auto operator[](Size index) const noexcept -> ConstReference {
		BR_ASSERT(index < size());
		return m_char(index);
	}

	/**
	 * @brief 获取元素引用，有越界检查
	 * @param[in] index 索引
	 * @see Location
	 *
	 * 返回重载了 operator<< 的对象，用于插入，或隐式转型为 Char
	 */
	auto at(Size index) -> Reference {
		if (index >= size()) {
			throw_index_exception("String::at(Size)");
		}
		return m_char(index);
	}

	/**
	 * @brief 获取元素常引用，无越界检查
	 * @param[in] index 索引
	 */
	auto at(Size index) const -> ConstReference {
		if (index >= size()) {
			throw_index_exception("String::at(Size) const");
		}
		return m_char(index);
	}

	/**
	 * @brief 返回数据
	 */
	auto data() const noexcept -> Char const * {
		return BR::PointerTraits<ConstPointer>::to_raw(m_get_pointer());
	}

	/**
	 * @brief 返回头字符
	 */
	auto front() -> Reference {
		return m_char(0);
	}

	/**
	 * @brief 返回头字符
	 */
	auto front() const noexcept -> ConstReference {
		return m_char(0);
	}

	/**
	 * @brief 返回尾字符
	 */
	auto back() -> Reference {
		return m_char(size() - 1);
	}

	/**
	 * @brief 返回尾字符
	 */
	auto back() const noexcept -> ConstReference {
		return m_char(size() - 1);
	}

	/**
	 * @brief 返回分配器
	 */
	auto get_allocator() const noexcept -> Allocator {
		return m_allocator();
	}
	///@}

	/**
	 * @name 容量
	 */
	///@{
	/**
	 * @brief 是否为空串
	 */
	bool is_empty() const noexcept {
		return size() == 0;
	}

	/**
	 * @brief 字符串(字符)长度
	 */
	auto size() const noexcept -> Size {
		return m_get_size();
	}

	/**
	 * @brief 字符串最大(字符)长度
	 */
	auto max_size() const noexcept -> Size {
		return AllocatorTraits::max_size(m_allocator());
	}

	/**
	 * @brief 当前分配的内存空间容量
	 */
	auto capacity() const noexcept -> Size {
		return m_get_capacity() - 1;
	}

	/**
	 * @brief 设置容量为至少 \em size
	 * @param[in] count 预留容量
	 */
	auto reserve(Size count) -> String &;

	/**
	 * @brief 缩减容量，释放未使用的空间
	 */
	auto clamp() -> String &;
	///@}

	/**
	 * @name 切片
	 */
	///@{
	constexpr auto to_view() const noexcept -> StringView<Char, CharTraits> {
		return StringView<Char, CharTraits>(data(), size());
	}

	constexpr operator StringView<Char, CharTraits>() noexcept {
		return StringView<Char, CharTraits>(data(), size());
	};

	BR_CONSTEXPR_AFTER_CXX11 auto operator()(Size index) const -> StringView<Char, CharTraits> {
		return to_view().slice(index);
	}

	BR_CONSTEXPR_AFTER_CXX11 auto operator()(Size index, Size count) const -> StringView<Char, CharTraits> {
		return to_view().slice(index, count);
	}
	///@}

	/**
	 * @name 比较操作
	 */
	///@{
	auto compare(StringView<Char, CharTraits> const & view) const noexcept -> Relation;

	auto operator==(StringView<Char, CharTraits> const & y) const noexcept -> bool {
		return compare(y) == Relation::EQ;
	}

	auto operator!=(StringView<Char, CharTraits> const & y) const noexcept -> bool {
		return !operator==(y);
	}

	auto operator<(StringView<Char, CharTraits> const & y) const noexcept -> bool {
		return compare(y) == Relation::LT;
	}

	auto operator>(StringView<Char, CharTraits> const & y) const noexcept -> bool {
		return compare(y) == Relation::GT;
	}

	auto operator<=(StringView<Char, CharTraits> const & y) const noexcept -> bool {
		return !operator>(y);
	}

	auto operator>=(StringView<Char, CharTraits> const & y) const noexcept -> bool {
		return !operator<(y);
	}
	///@}

	/**
	 * @name 赋值操作
	 */
	///@{
	/**
	 * @brief 复制赋值运算符
	 * @param[in] string 源字符串
	 */
	auto operator=(String const & string) -> String & {
		if (this != &string) {
			m_copy_assign_allocator(string, typename AllocatorTraits::IsPropagateOnContainerCopyAssignment());
			*this = string.to_view();
		}
		return *this;
	}

	/**
	 * @brief 移动赋值运算符
	 * @param[in] string 源字符串
	 */
	auto operator=(String && string) -> String & {
		m_move_assign(string, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment());
		return *this;
	}

	/**
	 * @brief 从字符串视图赋值
	 * @param[in] view 字符串视图
	 */
	auto operator=(StringView<Char, CharTraits> const & view) -> String &;

	/**
	 * @brief 从初始化列表复制
	 * @param[in] list 初始化列表
	 * @see InitializerList
	 */
	auto operator=(InitializerList<Char> list) -> String & {
		return operator=(make_iterator_range(list.begin(), list.end()));
	}

	/**
	 * @brief 从迭代器区间复制
	 * @param[in] first, last 区间\f$[first, last)\f$
	 */
	template<typename TIterator >
	auto operator=(IteratorRange<TIterator> range) -> EnableIf< IsInputIterator<TIterator>, String & >  {
		m_assign(range.begin(), range.end(), IteratorTraits<TIterator>::category());
		return *this;
	}

	/**
	 * @brief 设置为空串
	 */
	auto clear() -> String & {
		CharTraits::assign(*m_get_pointer(), Char());
		m_set_size(0);
		return *this;
	}
	///@}

	/**
	 * @name 追加操作
	 */
	///@{
	/**
	 * @brief 追加(字符串视图版本)
	 * @param[in] view 追加内容
	 */
	auto operator<<(StringView<Char, CharTraits> const & view) -> String &;

	/**
	 * @brief 追加字符
	 * @param[in] c 追加内容
	 */
	auto operator<<(Char c) -> String &;

	/**
	 * @brief 追加迭代器区间中的内容
	 * @param[in] first, last 区间\f$[first, last)\f$
	 */
	template< typename TIterator >
	auto operator<<(IteratorRange<TIterator> range) -> EnableIf< IsInputIterator<TIterator>, String & > {
		m_append(range.begin(), range.end(), IteratorTraits<TIterator>::category());
		return *this;
	}

	/**
	 * @brief 追加(初始化列表版本)
	 * @param[in] list 追加内容
	 */
	auto operator<<(InitializerList<Char> list) -> String & {
		return operator<<(make_iterator_range(list.begin(), list.end()));
	}

	/**
	 * @brief 追加重复字符
	 * @param[in] chars 字符及其重复次数
	 */
	auto operator<<(Pair<Char, Size> const & chars) -> String &;
	///@}

	/**
	 * @name 连接操作
	 */
	///@{
	auto operator+(StringView<Char, CharTraits> const & string) -> String;

	auto operator+(Char string) -> String;

	auto operator+(Pair<Char, Size> const & chars) -> String;
	///@}

	/**
	 * @name 插入操作
	 */
	///@{
	auto insert(Size index, StringView<Char, CharTraits> const & view) -> String &;

	auto insert(Size index, Char c) -> String &;

	auto insert(Size index, Pair<Char, Size> const & chars) -> String &;

	auto insert(ConstIterator position, Char c) -> Iterator {
		auto const index = position - begin();
		insert(index, c);
		return begin() + index;
	}

	auto insert(ConstIterator position, Pair<Char, Size> chars) -> Iterator {
		auto const index = position - begin();
		insert(index, chars);
		return begin() + index;
	}

	template<typename TIterator >
	auto insert(ConstIterator position, IteratorRange<TIterator> range) -> EnableIf< IsInputIterator<TIterator>, Iterator > {
		return insert(position, range.begin(), range.end());
	}

	auto insert(ConstIterator position, InitializerList<Char> list) -> Iterator {
		return insert(position, list.begin(), list.end());
	}

	template<typename TIterator>
	auto insert(ConstIterator position, TIterator first, TIterator last) -> EnableIf< IsInputIterator<TIterator>, Iterator > {
		return m_insert(position, first, last, IteratorTraits<TIterator>::category());
	}
	///@}

	/**
	 * @name 替换操作
	 */
	///@{
	auto replace(Size index, Size count, StringView<Char, CharTraits> const & view) -> String &;

	auto replace(Size index, Size length, Pair<Char, Size> const & chars) -> String &;

	auto replace(ConstIterator first, ConstIterator last, InitializerList<Char> list) -> String & {
		return replace(first, last, list.begin(), list.end());
	}

	template<typename TIterator >
	auto replace(ConstIterator first0, ConstIterator last0, TIterator first1, TIterator last1) -> EnableIf< IsInputIterator<TIterator>, String & >;
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	auto remove(Size index, Size count) -> String &;

	auto remove(ConstIterator position) -> Iterator {
		auto index = position - begin();
		remove(static_cast<Size>(index), 1);
		return begin() + index;
	}

	auto remove(ConstIterator first, ConstIterator last) -> Iterator {
		auto index = first - begin();
		remove(static_cast<Size>(index), static_cast<Size>(last - first));
		return begin() + index;
	}
	///@}

private:
	constexpr static auto ALIGNMENT = 16;

	constexpr static auto m_allocate_size(Size size) noexcept -> Size {
		return (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
	}

	auto m_storage() noexcept -> Storage & {
		return m_pair.first();
	}

	auto m_storage() const noexcept -> Storage const & {
		return m_pair.first();
	}

	auto m_allocator() noexcept -> Allocator & {
		return m_pair.second();
	}

	auto m_allocator() const noexcept -> Allocator const & {
		return m_pair.second();
	}

	auto m_get_capacity() const -> Size {
		return m_storage().capacity;
	}

	void m_set_capacity(Size capacity) {
		m_storage().capacity = capacity;
	}

	auto m_get_size() const -> Size {
		return m_storage().size;
	}

	void m_set_size(Size size) {
		m_storage().size = size;
	}

	auto m_get_pointer() -> Pointer {
		return m_storage().pointer;
	}

	auto m_get_pointer() const -> ConstPointer {
		return m_storage().pointer;
	}

	void m_set_pointer(Pointer pointer) {
		m_storage().pointer = pointer;
	}

	auto m_char(Size index) noexcept -> Char & {
		return m_get_pointer()[index];
	}

	auto m_char(Size index) const noexcept -> Char const & {
		return m_get_pointer()[index];
	}

	void m_zeroize();

	void m_prepare(Size size);

	void m_construct(Char const * string, Size size) {
		m_construct(string, size, size);
	}

	void m_construct(Char const * string, Size size, Size reserve);

	void m_construct(Char ch, Size size);

	template<typename TSinglePassIterator>
	void m_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag);

	template<typename TForwardIterator>
	void m_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag);

	void m_destruct() {
		AllocatorTraits::deallocate(m_allocator(), m_get_pointer(), m_get_capacity());
	}

	void m_copy_assign_allocator(String const & string, BooleanTrue) noexcept {
	}

	void m_copy_assign_allocator(String const & string, BooleanFalse) {
		if (m_allocator() != string.m_allocator()) {
			clear();
			clamp();
		}
		m_allocator() = string.m_allocator();
	}

	void m_move_assign(String & string, BooleanTrue) noexcept(HasNothrowMoveAssign<Allocator>::value) {
		clear();
		clamp();
		m_storage() = string.m_storage();
		m_allocator() = move(string.m_allocator());
		string.m_zeroize();
	}

	void m_move_assign(String & string, BooleanFalse) {
		if (m_allocator() != string.m_allocator()) {
			*this = string;
		} else {
			clear();
			clamp();
			m_storage() = string.m_storage();
			string.m_zeroize();
		}
	}

	void m_grow_and_replace(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count, Char const * string);

	void m_grow(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count = 0);

	template< typename TSinglePassIterator >
	void m_assign(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		clear();
		for (; first != last; ++first) {
			*this << *first;
		}
	}

	template< typename TForwardIterator >
	void m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag);

	template< typename TSinglePassIterator >
	void m_append(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		for (; first != last; ++first) {
			*this << *first;
		}
	}

	template< typename TForwardIterator >
	void m_append(TForwardIterator first, TForwardIterator last, ForwardTraversalTag);

	template< typename TSinglePassIterator >
	auto m_insert(ConstIterator position, TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) -> Iterator;

	template< typename TForwardIterator >
	auto m_insert(ConstIterator position, TForwardIterator first, TForwardIterator last, ForwardTraversalTag) -> Iterator;

private:
	CompressedPair<Storage, Allocator> m_pair;

}; // class String< TChar, TCharTraits, TAllocator >

template<typename TChar, typename TCharTraits, typename TAllocator>
void String<TChar, TCharTraits, TAllocator>::m_zeroize() {
	m_set_capacity(0);
	m_set_size(0);
	m_set_pointer(nullptr);
}

template<typename TChar, typename TCharTraits, typename TAllocator>
void String<TChar, TCharTraits, TAllocator>::m_prepare(Size size) {
	if (size > max_size()) {
		throw_length_exception("String::m_prepare");
	}
	auto capacity = m_allocate_size(size + 1);
	m_set_pointer(AllocatorTraits::allocate(m_allocator(), capacity));
	m_set_capacity(capacity);
}

template<typename TChar, typename TCharTraits, typename TAllocator>
void String<TChar, TCharTraits, TAllocator>::m_construct(Char const * S, Size size, Size reserve) {
	m_prepare(reserve + 1);
	auto pointer = m_get_pointer();
	CharTraits::copy(PointerTraits::to_raw(pointer), S, size);
	CharTraits::assign(pointer[size], Char());
	m_set_size(size);
}

template<typename TChar, typename TCharTraits, typename TAllocator>
void String<TChar, TCharTraits, TAllocator>::m_construct(Char c, Size size) {
	m_prepare(size + 1);
	auto pointer = m_get_pointer();
	CharTraits::fill(PointerTraits::to_raw(pointer), c, size);
	CharTraits::assign(pointer[size], Char());
	m_set_size(size);
}

template<typename TChar, typename TCharTraits, typename TAllocator>
template<typename TSinglePassIterator>
void String<TChar, TCharTraits, TAllocator>::m_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
	m_zeroize();
	try {
		for (; first != last; ++first) {
			*this << *first;
		}
	} catch (...) {
		m_destruct();
		throw;
	}
}

template<typename TChar, typename TCharTraits, typename TAllocator>
template<typename TForwardIterator>
void String<TChar, TCharTraits, TAllocator>::m_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	auto size = static_cast<Size>(distance(first, last));
	m_prepare(size + 1);
	auto pointer = m_get_pointer();
	for (; first != last; ++first, ++pointer) {
		CharTraits::assign(*pointer, *first);
	}
	CharTraits::assign(*pointer, Char());
	m_set_size(size);
}

template<typename TChar, typename TCharTraits, typename TAllocator>
void String<TChar, TCharTraits, TAllocator>::m_grow_and_replace(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count, Char const * string) {
	auto const MAX_SIZE = max_size();
	if (delta_capacity > MAX_SIZE - old_capacity - 1) {
		throw_length_exception("String::m_grow_and_replace");
	}
	auto old_pointer = m_get_pointer();
	auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
							  ? m_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
							  : MAX_SIZE;
	auto new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
	if (copy_count != 0) {
		CharTraits::copy(PointerTraits::to_raw(new_pointer), PointerTraits::to_raw(old_pointer), copy_count);
	}
	if (add_count != 0) {
		CharTraits::copy(PointerTraits::to_raw(new_pointer) + copy_count, string, add_count);
	}
	auto const second_copy_count = old_size - delete_count - copy_count;
	if (second_copy_count != 0) {
		CharTraits::copy(
			PointerTraits::to_raw(new_pointer) + copy_count + add_count,
			PointerTraits::to_raw(old_pointer) + copy_count + delete_count,
			second_copy_count
		);
	}
	m_set_pointer(new_pointer);
	m_set_capacity(new_capacity);
	Size new_size = old_size + add_count - delete_count;
	m_set_size(new_size);
	CharTraits::assign(new_pointer[new_size], Char());
}


template<typename TChar, typename TCharTraits, typename TAllocator>
void String<TChar, TCharTraits, TAllocator>::m_grow(
	Size old_capacity,
	Size delta_capacity,
	Size old_size,
	Size copy_count,
	Size delete_count,
	Size add_count
) {
	auto const MAX_SIZE = max_size();
	if (delta_capacity > MAX_SIZE - old_capacity) {
		throw_length_exception("String::m_grow");
	}
	auto old_pointer = m_get_pointer();
	auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
							  ? m_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
							  : MAX_SIZE;
	auto new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
	if (copy_count != 0) {
		CharTraits::copy(PointerTraits::to_raw(new_pointer), PointerTraits::to_raw(old_pointer), copy_count);
	}
	auto const second_copy_count = old_size - delete_count - copy_count;
	if (second_copy_count != 0) {
		CharTraits::copy(
			PointerTraits::to_raw(new_pointer) + copy_count + add_count,
			PointerTraits::to_raw(old_pointer) + copy_count + delete_count,
			second_copy_count
		);
	}
	m_set_pointer(new_pointer);
	m_set_capacity(new_capacity);
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::compare(StringView<Char, CharTraits> const & view) const noexcept -> Relation {
	Size lhs_size = m_get_size();
	Size rhs_size = view.size();
	auto result = CharTraits::compare(data(), view.data(), min(lhs_size, rhs_size));
	if (result != Relation::EQ) {
		return result;
	}
	if (lhs_size < rhs_size) {
		return Relation::LT;
	}
	if (lhs_size > rhs_size) {
		return Relation::GT;
	}
	return Relation::EQ;
};

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::reserve(Size count) -> String & {
	if (count > max_size()) {
		throw_length_exception("String::reserve");
	}
	auto old_capacity = m_get_capacity();
	auto size = m_get_size();
	auto new_capacity = m_allocate_size(max(count, size) + 1);
	if (new_capacity != old_capacity) {
		auto old_pointer = m_get_pointer();
		Pointer new_pointer;
		if (new_capacity > old_capacity) {
			new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
		} else {
			try {
				new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
			} catch (...) {
				return *this;
			}
		}
		CharTraits::copy(PointerTraits::to_raw(new_pointer), PointerTraits::to_raw(old_pointer), size + 1);
		m_set_pointer(new_pointer);
		m_set_capacity(new_capacity);
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::clamp() -> String & {
	auto old_capacity = m_get_capacity();
	auto size = m_get_size();
	auto new_capacity = m_allocate_size(size + 1);
	if (new_capacity < old_capacity) {
		auto const old_pointer = m_get_pointer();
		Pointer new_pointer;
		try {
			new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
		} catch (...) {
			return *this;
		}
		CharTraits::copy(PointerTraits::to_raw(new_pointer), PointerTraits::to_raw(old_pointer), size + 1);
		m_set_pointer(new_pointer);
		m_set_capacity(new_capacity);
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::operator=(StringView<Char, CharTraits> const & view) -> String & {
	auto capacity = m_get_capacity();
	if (m_get_capacity() >= view.size()) {
		auto pointer = m_get_pointer();
		CharTraits::move(PointerTraits::to_raw(pointer), view.data(), view.size());
		CharTraits::assign(pointer[view.size()], Char());
		m_set_size(view.size());
	} else {
		auto size = m_get_size();
		m_grow_and_replace(capacity, view.size() - capacity, size, 0, size, view.size(), view.data());
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
template<typename TForwardIterator>
void String<TChar, TCharTraits, TAllocator>::m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	auto count = static_cast<Size>(distance(first, last));
	auto capacity = m_get_capacity();
	if (capacity < count) {
		auto const size = m_get_size();
		m_grow(capacity, count - capacity, size, 0, size);
	}
	auto pointer = m_get_pointer();
	for (; first != last; ++first, ++pointer) {
		CharTraits::assign(*pointer, *first);
	}
	CharTraits::assign(*pointer, Char());
	m_set_size(count);
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::operator<<(StringView<Char, CharTraits> const & view) -> String & {
	auto capacity = m_get_capacity();
	auto old_size = m_get_size();
	if (capacity - old_size >= view.size()) {
		if (view.size() != 0) {
			auto pointer = m_get_pointer();
			auto new_size = old_size + view.size();
			CharTraits::copy(PointerTraits::to_raw(pointer) + old_size, view.data(), view.size());
			CharTraits::assign(pointer[new_size], Char());
			m_set_size(new_size);
		}
	} else {
		m_grow_and_replace(
			capacity,
			old_size + view.size() - capacity,
			old_size,
			old_size,
			0,
			view.size(),
			view.data());
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::operator<<(Char ch) -> String & {
	auto capacity = m_get_capacity();
	auto old_size = m_get_size();
	auto new_size = old_size + 1;
	if (new_size == capacity) {
		m_grow(capacity, 1, old_size, old_size, 0);
	}
	auto pointer = PointerTraits::to_raw(m_get_pointer()) + old_size;
	CharTraits::assign(*pointer, ch);
	CharTraits::assign(*++pointer, Char());
	m_set_size(new_size);
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::operator<<(Pair<Char, Size> const & chars) -> String & {
	auto count = chars.second;
	if (count > 0) {
		auto capacity = m_get_capacity();
		auto old_size = m_get_size();
		auto new_size = old_size + count;
		if (capacity < new_size) {
			m_grow(capacity, new_size - capacity, old_size, old_size, 0);
		}
		auto pointer = m_get_pointer();
		CharTraits::fill(PointerTraits::to_raw(pointer) + old_size, chars.first, count);
		CharTraits::assign(pointer[new_size], Char());
		m_set_size(new_size);
	}
	return *this;
};

template<typename TChar, typename TCharTraits, typename TAllocator>
template<typename TForwardIterator>
void String<TChar, TCharTraits, TAllocator>::m_append(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	auto size = m_get_size();
	auto capacity = m_get_capacity();
	auto count = static_cast<Size>(distance(first, last));
	if (count != 0) {
		if (capacity - size < count) {
			m_grow(capacity, size + count - capacity, size, size, 0);
		}
		auto pointer = PointerTraits::to_raw(m_get_pointer()) + size;
		for (; first != last; ++pointer, ++first) {
			CharTraits::assign(*pointer, *first);
		}
		CharTraits::assign(*pointer, Char());
		m_set_size(size + count);
	}
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::operator+(StringView<Char, CharTraits> const & y) -> String {
	String result(get_allocator());
	auto size_x = m_get_size();
	result.m_construct(m_get_pointer(), size_x, size_x + y.size());
	result << y;
	return result;
};

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::operator+(Char y) -> String {
	String result(get_allocator());
	auto size_x = m_get_size();
	result.m_construct(m_get_pointer(), size_x, size_x + 1);
	result << y;
	return result;
};

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::operator+(Pair<Char, Size> const & y) -> String {
	String result(get_allocator());
	auto size_x = m_get_size();
	result.m_construct(m_get_pointer(), size_x, size_x + y.second);
	result << y;
	return result;
};

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::insert(Size index, StringView<Char, CharTraits> const & view) -> String & {
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception("BR::m_insert");
	}
	auto capacity = m_get_capacity();
	auto source = view.data();
	auto count = view.size();
	if (capacity - old_size >= count) {
		if (count > 0) {
			auto new_size = old_size + count;
			auto pointer = PointerTraits::to_raw(m_get_pointer());
			auto move_count = old_size - index;
			if (move_count > 0) {
				if (pointer + index <= source && source < pointer + old_size) {
					source += count;
				}
				CharTraits::move(pointer + index + count, pointer + index, move_count);
			}
			CharTraits::move(pointer + index, source, count);
			CharTraits::assign(pointer[new_size], Char());
			m_set_size(new_size);
		}
	} else {
		m_grow_and_replace(capacity, old_size + count - capacity, old_size, index, 0, count, source);
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::insert(Size index, Char ch) -> String & {
	auto old_size = m_get_size();
	auto new_size = old_size + 1;
	auto capacity = m_get_capacity();
	Char * pointer;
	if (capacity == old_size) {
		m_grow(capacity, 1, old_size, index, 0, 1);
		pointer = PointerTraits::to_raw(m_get_pointer());
	} else {
		pointer = PointerTraits::to_raw(m_get_pointer());
		Size move_count = old_size - index;
		if (move_count > 0) {
			CharTraits::move(pointer + index + 1, pointer + index, move_count);
		}
	}
	CharTraits::assign(pointer[index], ch);
	CharTraits::assign(pointer[new_size], Char());
	m_set_size(new_size);
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::insert(Size index, Pair<Char, Size> const & chars) -> String & {
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception("BR::insert");
	}
	auto count = chars.second;
	if (count > 0) {
		auto capacity = m_get_capacity();
		auto new_size = old_size + count;
		Char * pointer = nullptr;
		if (capacity >= new_size) {
			pointer = PointerTraits::to_raw(m_get_pointer());
			Size move_count = old_size - index;
			if (move_count > 0) {
				CharTraits::move(pointer + index + count, pointer + index, move_count);
			}
		} else {
			m_grow(capacity, new_size - capacity, old_size, index, 0, count);
			pointer = PointerTraits::to_raw(m_get_pointer());
		}
		CharTraits::fill(pointer + index, chars.first, count);
		CharTraits::assign(pointer[new_size], Char());
		m_set_size(new_size);
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
template<typename TSinglePassIterator>
auto String<TChar, TCharTraits, TAllocator>::m_insert(ConstIterator position, TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) -> Iterator {
	auto index = position - begin();
	auto old_size = m_get_size();
	for (; first != last; ++first) {
		*this << *first;
	}
	auto pointer = m_get_pointer();
	rotate(pointer + index, pointer + old_size, pointer + size());
	return begin() + index;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
template<typename TForwardIterator>
auto String<TChar, TCharTraits, TAllocator>::m_insert(ConstIterator position, TForwardIterator first, TForwardIterator last, ForwardTraversalTag) -> Iterator {
	auto index = position - begin();
	auto old_size = m_get_size();
	auto capacity = m_get_capacity();
	Size count = static_cast<Size>(distance(first, last));
	if (count > 0) {
		auto new_size = old_size + count;
		Char * pointer = nullptr;
		if (capacity >= new_size) {
			pointer = PointerTraits::to_raw(m_get_pointer());
			Size move_count = old_size - index;
			if (move_count > 0) {
				CharTraits::move(pointer + index + count, pointer + index, move_count);
			}
		} else {
			m_grow(capacity, new_size - capacity, old_size, index, 0, count);
			pointer = PointerTraits::to_raw(m_get_pointer());
		}
		CharTraits::assign(pointer[new_size], Char());
		m_set_size(new_size);
		for (pointer += index; first != last; ++pointer, (void) ++first) {
			CharTraits::assign(*pointer, *first);
		}
	}
	return begin() + index;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::replace(Size index, Size count, StringView<Char, CharTraits> const & view) -> String & {
	auto old_size = m_get_size();
	auto capacity = m_get_capacity();
	auto source_data = view.data();
	auto source_count = view.size();
	if (capacity - old_size + count >= source_count) {
		Char * pointer = PointerTraits::to_raw(m_get_pointer());
		if (count != source_count) {
			auto move_count = old_size - index - count;
			if (move_count > 0) {
				if (count > source_count) {
					CharTraits::move(pointer + index, source_data, source_count);
					CharTraits::move(pointer + index + source_count, pointer + index + count, move_count);
					goto FINISH;
				} else {
					if (pointer + index < source_data && source_data < pointer + source_count) {
						if (pointer + index + count <= source_data) {
							source_data += source_count - count;
						} else {
							CharTraits::move(pointer + index, source_data, count);
							index += count;
							source_data += source_count;
							source_count -= count;
							count = 0;
						}
					}
				}
			}
		}
		CharTraits::move(pointer + index, source_data, source_count);
		FINISH:
		auto new_size = old_size + source_count - count;
		CharTraits::assign(pointer[new_size], Char());
		m_set_size(new_size);
	} else {
		m_grow_and_replace(
			capacity,
			old_size - source_count + count - capacity,
			old_size,
			index,
			count,
			source_count,
			source_data
		);
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::replace(Size index, Size length, Pair<Char, Size> const & chars) -> String & {
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception("String::replace");
	}
	length = min(length, old_size - index);
	auto capacity = m_get_capacity();
	auto count = chars.second;
	Char * pointer = nullptr;
	auto new_size = old_size - length + count;
	if (capacity - old_size + length >= count) {
		pointer = PointerTraits::to_raw(m_get_pointer());
		if (length != count) {
			auto move_count = old_size - index - length;
			if (move_count > 0) {
				CharTraits::move(pointer + index + count, pointer + index + length, move_count);
			}
		}
	} else {
		m_grow(capacity, new_size - capacity, old_size, index, length, count);
		pointer = PointerTraits::to_raw(m_get_pointer());
	}
	CharTraits::fill(pointer + index, chars.first, count);
	CharTraits::assign(pointer[new_size], Char());
	m_set_size(new_size);
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
template<typename TIterator>
auto String<TChar, TCharTraits, TAllocator>::replace(ConstIterator first0, ConstIterator last0, TIterator first1, TIterator last1) -> EnableIf< IsInputIterator<TIterator>, String & > {
	for (; ; ++first0, (void) ++first1) {
		if (first0 == last0) {
			if (first1 != last1) {
				insert(first0, first1, last1);
			}
			break;
		}
		if (first1 == last1) {
			remove(first0, last0);

			break;
		}
		CharTraits::assign(const_cast<Char & >(*first0), *first1);
	}
	return *this;
}

template<typename TChar, typename TCharTraits, typename TAllocator>
auto String<TChar, TCharTraits, TAllocator>::remove(Size index, Size count) -> String & {
	auto old_size = m_get_size();
	if (count > 0) {
		auto new_size = old_size - count;
		Char * pointer = PointerTraits::to_raw(m_get_pointer());
		auto move_count = new_size - index;
		if (move_count > 0) {
			CharTraits::move(pointer + index, pointer + index + count, move_count);
		}
		CharTraits::assign(pointer[new_size], Char());
		m_set_size(new_size);
	}
	return *this;
};

extern template
class String<NChar>;

extern template
class String<WChar>;

extern template
class String<Char16>;

extern template
class String<Char32>;

inline namespace Literal {

inline auto operator "" _S(NChar const  * string, Size length) -> String<NChar> {
	return String<NChar>(string, length);
}

inline auto operator "" _S(WChar const  * string, Size length) -> String<WChar> {
	return String<WChar>(string, length);
}

inline auto operator "" _S(Char16 const  * string, Size length) -> String<Char16> {
	return String<Char16>(string, length);
}

inline auto operator "" _S(Char32 const  * string, Size length) -> String<Char32> {
	return String<Char32>(string, length);
}

} // inline namespace Literal

} // namespace BR