#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy_n.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/memory/memory_copy.hpp>
#include <libbr/string/string_compare.hpp>
#include <libbr/string/string_length.hpp>
#include <libbr/string/string_move.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_operate/max_integer.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/is_input_iterator.hpp>
#include <libbr/type_traits/is_pod.hpp>
#include <libbr/type_traits/is_same.hpp>

namespace BR {

/**
 * @brief 字符串类
 * @tparam TCodeUnit 码元类型
 * @tparam TAllocator 分配器类型
 */
template< typename TCodeUnit, typename TAllocator = Allocator<TCodeUnit> >
class RawString;

template< typename TCodeUnit >
class RawStringView;

template< typename TCodeUnit >
BR_CONSTEXPR_AFTER_CXX11 auto make_raw_string_view(CString<TCodeUnit> string) -> RawStringView<TCodeUnit> {
	BR_ASSERT(string != nullptr);
	return RawStringView<TCodeUnit>(string);
}

template< typename TCodeUnit >
BR_CONSTEXPR_AFTER_CXX11 auto make_raw_string_view(CString<TCodeUnit> string, Size count) -> RawStringView<TCodeUnit> {
	BR_ASSERT(string != nullptr || count == 0);
	return RawStringView<TCodeUnit>(string, count);
}



template< typename TCodeUnit >
class RawStringView {
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
	constexpr RawStringView() noexcept : m_data(nullptr), m_size(0) {
	}

	constexpr RawStringView(RawStringView const &) noexcept = default;

	template<typename TAllocator>
	constexpr RawStringView(RawString< CodeUnit, TAllocator > const & string) noexcept : m_data(string.data()), m_size(string.size()) {
	}

	constexpr RawStringView(CodeUnit const * string, Size size) : m_data(string), m_size(size) {
	}

	auto operator=(RawStringView const &) noexcept -> RawStringView & = default;

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

	constexpr auto length() const noexcept -> Size {
		return m_size;
	}

	constexpr auto empty() const noexcept -> bool {
		return m_size == 0;
	}

	constexpr auto data() const noexcept -> ConstPointer {
		return m_data;
	}

	auto clear() noexcept -> RawStringView {
		m_data = nullptr;
		m_size = 0;
		return *this;
	}

private:
	CodeUnit const * m_data;
	Size m_size;
}; // class RawStringView<TCodeUnit>

template< typename TCodeUnit, typename TAllocator >
class RawString {

public:
	/**
	 * @brief 分配器类
	 * @see BR::Allocator
	 */
	using Allocator = TAllocator;

private:
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
	static_assert(IsSame< TCodeUnit, typename AllocatorTraits::Element >{}, "AllocatorTraits<Allocator>::Value must be TCodeUnit.");

	static_assert(IsPOD<TCodeUnit>{}, "TCodeUnit must be a POD.");

	/**
	 * @brief CodeUnit
	 */
	using CodeUnit = TCodeUnit;

	/**
	 * @brief Element
	 */
	using Element = CodeUnit;

	/**
	 * @brief AllocatorTraits<Allocator>::Size
	 * @see BR::AllocatorTraits::Size
	 */
	using Size = typename AllocatorTraits::Size;

	/**
	 * @brief Value 的非常量引用
	 */
	using Reference = Element &;

	/**
	 * @brief Value 的常量引用
	 */
	using ConstReference = Element const &;

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

	using ConstPointerTraits = BR::PointerTraits<ConstPointer>;

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

public:
	constexpr static auto ALIGNMENT = 32;

#if defined(BR_LITTLE_ENDIAN)
	constexpr static auto SMALL_MASK = 0x01;
	constexpr static auto LARGE_MASK = 0x1UL;
#else // defined(BR_LITTLE_ENDIAN)
	constexpr static auto SMALL_MASK = 0x80;
	constexpr static auto LARGE_MASK = ~Size(~0) >> 1;
#endif // defined(BR_LITTLE_ENDIAN)

	struct LargeStorage {
		Size capacity;
		Size size;
		Pointer data;
	};

	constexpr static auto MIN_CAPACITY
		= (sizeof(LargeStorage) - 1) / sizeof(Element) > 2
			? (sizeof(LargeStorage) - 1) / sizeof(Element) : 2;

	struct SmallStorage {
		union {
			UInt8 size;
			Element padding;
		};
		Element data[MIN_CAPACITY];
	};

	struct Storage {
		union {
			LargeStorage large;
			SmallStorage small;
		};
	};

	class InsertProxy {
		friend class RawString;

	public:
		auto operator<<(RawString & string) -> InsertProxy & {
			return append(string.data(), string.size());
		}

		auto append(RawString & string) -> InsertProxy & {
			return *this << string;
		}

		auto operator<<(RawStringView<CodeUnit> & string) -> InsertProxy & {
			return append(string.data(), string.size());
		}

		auto append(RawStringView<CodeUnit> & string) -> InsertProxy & {
			return *this << string;
		}

		auto operator<<(CString<CodeUnit> string) -> InsertProxy & {
			return append(string, string_length(string));
		}

		auto append(CString<CodeUnit> string) -> InsertProxy & {
			return *this << string;
		}

		auto append(CString<CodeUnit> string, Size length) -> InsertProxy & {
			m_string.insert(m_index, string, length);
			return *this;
		}

		auto operator<<(CodeUnit unit) -> InsertProxy & {
			m_string.insert(m_index, unit);
			return *this;
		}

		auto append(CodeUnit unit) -> InsertProxy & {
			return *this << unit;
		}

		auto append(CodeUnit unit, Size n) -> InsertProxy & {
			m_string.insert(m_index, unit, n);
			return *this;
		}

		auto operator<<(InitializerList<CodeUnit> list) -> InsertProxy & {
			return append(list.begin(), list.end());
		}

		auto append(InitializerList<CodeUnit> list) -> InsertProxy & {
			return *this << list;
		}

		template< typename TIterator >
		auto append(TIterator first, TIterator last) -> InsertProxy & {
			m_string.insert(m_string.cbegin() + m_index, first, last);
			return *this;
		}

	private:
		InsertProxy(RawString & string, Size index) : m_string(string), m_index(index) {
		}

		InsertProxy(InsertProxy const &) = default;

		InsertProxy(InsertProxy &&) = default;

		auto operator=(InsertProxy const &) -> InsertProxy & = default;

		auto operator=(InsertProxy &&) -> InsertProxy & = default;

	private:
		RawString & m_string;
		Size const m_index;
	}; // class InsertProxy

	class ReplaceProxy {
		friend class RawString;

	public:
		auto operator=(RawString & string) -> ReplaceProxy & {
			return assign(string.data(), string.size());
		}

		auto assign(RawString & string) -> ReplaceProxy & {
			return *this = string;
		}

		auto operator=(RawStringView<CodeUnit> & string) -> ReplaceProxy & {
			return assign(string.data(), string.size());
		}

		auto assign(RawStringView<CodeUnit> & string) -> ReplaceProxy & {
			return *this = string;
		}

		auto operator=(CString<CodeUnit> string) -> ReplaceProxy & {
			return assign(string, string_length(string));
		}

		auto assign(CString<CodeUnit> string) -> ReplaceProxy & {
			return *this = string;
		}

		auto assign(CString<CodeUnit> string, Size length) -> ReplaceProxy & {
			m_string.replace(m_index, m_count, string, length);
			return *this;
		}

		auto assign(CodeUnit unit, Size n) -> ReplaceProxy & {
			m_string.replace(m_index, m_count, unit, n);
			return *this;
		}

		auto operator=(InitializerList<CodeUnit> list) -> ReplaceProxy & {
			return assign(list.begin(), list.end());
		}

		auto assign(InitializerList<CodeUnit> list) -> ReplaceProxy & {
			return *this = list;
		}

		template< typename TIterator >
		auto assign(TIterator first, TIterator last) -> ReplaceProxy & {
			m_string.replace(m_string.cbegin() + m_index, m_string.cbegin() + m_index + m_count, first, last);
			return *this;
		}

	private:
		ReplaceProxy(RawString & string, Size index, Size count) : m_string(string), m_index(index), m_count(count) {
		}

		ReplaceProxy(ReplaceProxy const &) = default;

		ReplaceProxy(ReplaceProxy &&) = default;

		auto operator=(ReplaceProxy const &) -> ReplaceProxy & = default;

		auto operator=(ReplaceProxy &&) -> ReplaceProxy & = default;

	private:
		RawString & m_string;
		Size const m_index;
		Size const m_count;
	}; // class ReplaceProxy

public:
	/**
	 * @name 构造函数
	 */
	///@{
	/**
	 * @brief 默认构造
	 */
	RawString() noexcept(HasNothrowDefaultConstructor<Allocator>{}) {
		m_zeroize();
	}

	/**
	 * @brief 指定分配器，并默认构造
	 * @param[in] allocator 分配器
	 */
	explicit RawString(Allocator const & allocator) noexcept : m_impl(allocator) {
		m_zeroize();
	}

	/**
	 * @brief 复制构造函数
	 * @param[in] string 源字符串
	 */
	RawString(RawString const & string) : m_impl(AllocatorTraits::select_on_container_copy_construction(string.allocator())) {
		m_construct(string.m_get_raw_pointer(), string.m_get_size());
	}

	/**
	 * @brief 指定分配器，并复制内容
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 * @see String(String const & string)
	 */
	RawString(RawString const & string, Allocator const & allocator) : m_impl(allocator) {
		m_construct(string.m_get_raw_pointer(), string.m_get_size());
	}

	/**
	 * @brief 移动构造
	 * @param[in] string 源字符串
	 *
	 * 把源字符串的内容搬移到新串中
	 */
	RawString(RawString && string) noexcept : m_impl(move(string.m_impl)) {
		string.m_zeroize();
	}

	/**
	 * @brief 指定分配器，并移动内容
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 * @see String(String && string)
	 *
	 */
	RawString(RawString && string, Allocator const & allocator) : m_impl(allocator) {
		if (allocator != string.m_allocator()) {
			m_construct(string.m_get_raw_pointer(), string.m_get_size());
		} else {
			m_storage() = string.m_storage();
			string.m_zeroize();
		}
	}

	RawString(CString<CodeUnit> string, Allocator const & allocator = Allocator()) : RawString(string, string_length(string), allocator) {
	}

	/**
	 * @brief 从给定长度的码元序列构造
	 * @param[in] string 码元序列
	 * @param[in] length 长度
	 * @param[in] allocator 分配器
	 */
	RawString(CString<CodeUnit> string, Size length, Allocator const & allocator = Allocator()) : m_impl(allocator) {
		BR_ASSERT(string != nullptr);
		m_construct(string, length);
	}

	/**
	 * @brief 从字符串视图构造
	 * @param string 字符串视图
	 * @param allocator 分配器
	 */
	RawString(RawStringView<CodeUnit> const & string, Allocator const & allocator = Allocator()) : m_impl(allocator) {
		m_construct(string.data(), string.size());
	}

	// RawString(CodeUnit unit, Size count, Allocator const & allocator = Allocator());

	/**
	 * @brief 从迭代器区间构造
	 * @tparam TIterator
	 * @param first 区间头
	 * @param last 区间尾
	 * @param allocator 分配器
	 */
	template< typename TIterator >
	RawString(TIterator first, TIterator last, Allocator const & allocator = Allocator(), EnableIf< IsInputIterator<TIterator> > * = nullptr) : m_impl(allocator) {
		m_construct(first, last, typename IteratorTraits<TIterator>::Category{});
	}

	/**
	 * @brief 从初始化列表构造
	 * @param list 初始化列表
	 * @param allocator 分配器
	 */
	RawString(InitializerList<CodeUnit> list, Allocator const & allocator = Allocator()) : RawString(list.begin(), list.end(), allocator) {
	}
	///@}

	/**
	 * @brief 析构函数
	 */
	~RawString() {
		m_destruct();
	}

	/**
	 * @name 迭代器
	 */
	///@{
	//@{
	/**
	 * @return 指向首个码元的迭代器
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(m_get_pointer());
	}

	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(m_get_pointer());
	}

	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}
	//@}

	//@{
	/**
	 * @return 指向末尾码元之后一个位置的迭代器
	 */
	auto end() noexcept -> Iterator {
		return Iterator(m_get_pointer() + size());
	}

	auto end() const noexcept -> ConstIterator {
		return ConstIterator(m_get_pointer() + size());
	}

	auto cend() const noexcept -> ConstIterator {
		return end();
	}
	//@}

	//@{
	/**
	 * @return 指向末尾码元的反向迭代器
	 */
	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
	}
	//@}

	//@{
	/**
	 * @return 指向首位码元之前一个位置的反向迭代器
	 */
	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	auto crend() const noexcept -> ConstReverseIterator {
		return rend();
	}
	//@}
	///@}

	/**
	 * @name 成员访问
	 */
	///@{
	//@{
	/**
	 * @param index
	 */
	auto at(Size index) -> CodeUnit & {
		if (index >= size()) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		return m_get_pointer()[index];
	}

	auto at(Size index) const -> CodeUnit const & {
		if (index >= size()) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		return m_get_pointer()[index];
	}
	//@}

	//@{
	/**
	 * @param index
	 */
	auto operator[](Size index) -> CodeUnit & {
		BR_ASSERT(index <= size());
		return m_get_pointer()[index];
	}

	auto operator[](Size index) const -> CodeUnit const & {
		BR_ASSERT(index <= size());
		return m_get_pointer()[index];
	}
	//@}

	/**
	 * @param index
	 * @return
	 */
	auto operator()(Size index) -> InsertProxy {
		BR_ASSERT(index <= size());
		return InsertProxy(*this, index);
	}

	/**
	 * @param index
	 * @param count
	 * @return
	 */
	auto operator()(Size index, Size count) -> ReplaceProxy {
		BR_ASSERT(index <= size());
		return ReplaceProxy(*this, index, count);
	}

	/**
	 * @brief 获取分配器
	 */
	auto allocator() const noexcept -> Allocator {
		return m_allocator();
	}

	//@{
	/**
	 * @return 指向首位码元之前一个位置的反向迭代器
	 */
	auto data() -> CodeUnit * {
		return m_get_raw_pointer();
	}

	auto data() const -> CodeUnit const * {
		return m_get_raw_pointer();
	}
	//@}

	//@{
	/**
	 * @return 指向首位码元之前一个位置的反向迭代器
	 */
	auto front() -> Reference {
		return m_get_pointer()[0];
	}

	auto front() const -> ConstReference {
		return m_get_pointer()[0];
	}
	//@}

	//@{
	/**
	 * @return 指向首位码元之前一个位置的反向迭代器
	 */
	auto back() -> Reference {
		return m_get_pointer()[size() - 1];
	}

	auto back() const -> ConstReference {
		return m_get_pointer()[size() - 1];
	}
	//@}

	operator RawStringView<CodeUnit>() const {
		return RawStringView<CodeUnit>(m_get_pointer(), m_get_size());
	}
	///@}

	/**
	 * @name 容量
	 */
	///@{
	/**
	 * @brief 是否为空串
	 */
	bool empty() const noexcept {
		return size() == 0;
	}

	/**
	 * @brief 长度
	 */
	auto size() const noexcept -> Size {
		return m_get_size();
	}

	/**
	 * @brief 最大长度
	 */
	auto max_size() const noexcept -> Size {
		auto const m = AllocatorTraits::max_size(allocator());
#if defined(BR_LITTLE_ENDIAN)
		return m - ALIGNMENT;
#else
		return (m <= ~LARGE_MASK ? m : m / 2) - ALIGNMENT;
#endif // defined(BR_LITTLE_ENDIAN)
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
	auto reserve(Size count = 0) -> RawString &;

	/**
	 * @brief 缩减容量，释放未使用的空间
	 */
	auto shrink() -> RawString & {
		return reserve();
	}
	///@}

	/**
	 * @name 比较操作
	 */
	///@{
	//@{
	/**
	 * @param y
	 * @return *this <=> y
	 */
	auto compare(RawString const & y) const noexcept -> Relation {
		return m_compare(y.data(), y.size());
	}

	auto compare(RawStringView<CodeUnit> y) const noexcept -> Relation {
		return m_compare(y.data(), y.size());
	}

	auto compare(CString<CodeUnit> y) const noexcept -> Relation {
		return m_compare(y, string_length(y));
	}
	//@}

	//@{
	/**
	 * @param y
	 * @return *this == y
	 */
	auto operator==(RawString const & y) const noexcept -> bool {
		return compare(y) == Relation::EQ;
	}

	auto operator==(RawStringView<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::EQ;
	}

	auto operator==(CString<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::EQ;
	}
	//@}

	//@{
	/**
	 * @param y
	 * @return *this != y
	 */
	auto operator!=(RawString const & y) const noexcept -> bool {
		return !operator==(y);
	}

	auto operator!=(RawStringView<CodeUnit> y) const noexcept -> bool {
		return !operator==(y);
	}

	auto operator!=(CString<CodeUnit> y) const noexcept -> bool {
		return !operator==(y);
	}
	//@}

	//@{
	/**
	 * @param y
	 * @return *this < y
	 */
	auto operator<(RawString const & y) const noexcept -> bool {
		return compare(y) == Relation::LT;
	}

	auto operator<(RawStringView<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::LT;
	}

	auto operator<(CString<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::LT;
	}
	//@}

	//@{
	/**
	 * @param y
	 * @return *this > y
	 */
	auto operator>(RawString const & y) const noexcept -> bool {
		return compare(y) == Relation::GT;
	}

	auto operator>(RawStringView<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::GT;
	}

	auto operator>(CString<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::GT;
	}
	//@}

	//@{
	/**
	 * @param y
	 * @return *this <= y
	 */
	auto operator<=(RawString const & y) const noexcept -> bool {
		return !operator>(y);
	}

	auto operator<=(RawStringView<CodeUnit> y) const noexcept -> bool {
		return !operator>(y);
	}

	auto operator<=(CString<CodeUnit> y) const noexcept -> bool {
		return !operator>(y);
	}
	//@}

	//@{
	/**
	 * @param y
	 * @return *this >= y
	 */
	auto operator>=(RawString const & y) const noexcept -> bool {
		return !operator<(y);
	}

	auto operator>=(RawStringView<CodeUnit> y) const noexcept -> bool {
		return !operator<(y);
	}

	auto operator>=(CString<CodeUnit> y) const noexcept -> bool {
		return !operator<(y);
	}
	//@}
	///@}

	/**
	 * @name 赋值
	 */
	///@{
	/**
	 * @brief 设为空串
	 */
	auto clear() noexcept -> RawString & {
		*m_get_pointer() = CodeUnit(0);
		m_set_size(0);
		return *this;
	}

	//@{
	/**
	 * @brief 复制赋值
	 * @param string
	 */
	auto operator=(RawString const & string) -> RawString & {
		if (this != &string) {
			m_copy_assign_allocator(string, typename AllocatorTraits::IsPropagateOnContainerCopyAssignment{});
			assign(string.data(), string.size());
		}
		return *this;
	}

	auto assign(RawString const & string) -> RawString & {
		return *this = string;
	}
	//@}

	//@{
	/**
	 * @brief 移动赋值
	 * @param string
	 */
	auto operator=(RawString && string) noexcept(BooleanAnd< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment, typename AllocatorTraits::IsAlwaysEqual >{}) -> RawString & {
		m_move_assign(string, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment{});
		return *this;
	}

	auto assign(RawString && string) -> RawString & {
		return *this = move(string);
	}
	//@}

	//@{
	/**
	 * @brief 以字符串视图赋值
	 * @param string 字符串视图
	 */
	auto operator=(RawStringView<CodeUnit> string) -> RawString & {
		assign(string.data(), string.size());
		return *this;
	}

	auto assign(RawStringView<CodeUnit> string) -> RawString & {
		return *this = string;
	}
	//@}

	//@{
	/**
	 * @brief 以初始化列表赋值
	 * @param list 初始化列表
	 */
	auto operator=(InitializerList<CodeUnit> list) -> RawString & {
		return assign(list.begin(), list.end());
	}

	auto assign(InitializerList<CodeUnit> list) -> RawString & {
		return *this = list;
	}
	//@}

	//@{
	/**
	 * @brief 以码元序列赋值
	 * @param string 序列
	 */
	auto operator=(CString<CodeUnit> string) -> RawString & {
		return assign(string, string_length(string));
	}

	auto assign(CString<CodeUnit> string) -> RawString & {
		return assign(string, string_length(string));
	}
	//@}

	/**
	 * @brief 以码元序列赋值
	 * @param string 序列
	 * @param length 序列长度
	 */
	auto assign(CString<CodeUnit> string, Size length) -> RawString &;

	//@{
	/**
	 * @param unit
	 */
	auto operator=(CodeUnit unit) -> RawString &;

	auto assign(CodeUnit unit) -> RawString &;
	//@}

	/**
	 * @param unit
	 * @param n
	 */
	auto assign(CodeUnit unit, Size n) -> RawString &;

	/**
	 * @tparam TIterator
	 * @param first
	 * @param last
	 */
	template< typename TIterator >
	auto assign(TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> RawString & {
		m_assign(first, last, typename IteratorTraits<TIterator>::Category{});
		return *this;
	}
	///@}

	/**
	 * @name 追加
	 */
	///@{
	//@{
	/**
	 * @param string
	 */
	auto operator<<(RawString const & string) -> RawString & {
		return append(string.m_get_raw_pointer(), string.m_get_size());
	}

	auto append(RawString const & string) -> RawString & {
		return *this << string;
	}
	//@}

	//@{
	/**
	 * @param string
	 */
	auto operator<<(RawStringView<CodeUnit> string) -> RawString & {
		return append(string.data(), string.size());
	}

	auto append(RawStringView<CodeUnit> string) -> RawString & {
		return *this << string;
	}
	//@}

	//@{
	/**
	 * @param string
	 */
	auto operator<<(CString<CodeUnit> string) -> RawString & {
		return assign(string, string_length(string));
	}

	auto append(CString<CodeUnit> string) -> RawString & {
		return assign(string, string_length(string));
	}

	//@}

	/**
	 * @param string
	 * @param length
	 */
	auto append(CString<CodeUnit> string, Size length) -> RawString &;

	//@{
	/**
	 *
	 * @param unit
	 */
	auto operator<<(CodeUnit unit) -> RawString & {
		return append(unit);
	}

	auto append(CodeUnit unit) -> RawString &;
	//@}

	/**
	 *
	 * @param unit
	 * @param n
	 */
	auto append(CodeUnit unit, Size n) -> RawString &;

	//@{
	/**
	 * @param list
	 */
	auto operator<<(InitializerList<CodeUnit> list) -> RawString & {
		return append(list.begin(), list.end());
	}

	auto append(InitializerList<CodeUnit> list) -> RawString & {
		return append(list.begin(), list.end());
	}
	//@}

	/**
	 * @tparam TIterator
	 * @param first
	 * @param last
	 */
	template< typename TIterator >
	auto append(TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> RawString & {
		m_append(first, last, typename IteratorTraits<TIterator>::Category{});
		return *this;
	}
	///@}

	/**
	 * @name 插入
	 */
	///@{
	/**
	 * @brief 在指定位置插入字符串
	 * @param index
	 * @param string
	 */
	auto insert(Size index, RawString const & string) -> RawString & {
		return insert(index, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param string
	 */
	auto insert(Size index, RawStringView<CodeUnit> const & string) -> RawString & {
		return insert(index, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param string
	 */
	auto insert(Size index, CString<CodeUnit> string) -> RawString & {
		return insert(index, string, string_length(string));
	}

	/**
	 * @param index
	 * @param string
	 * @param length
	 */
	auto insert(Size index, CString<CodeUnit> string, Size length) -> RawString &;

	/**
	 * @param index
	 * @param unit
	 * @return
	 */
	auto insert(Size index, CodeUnit unit) -> RawString &;

	/**
	 * @param index
	 * @param unit
	 * @param n
	 */
	auto insert(Size index, CodeUnit unit, Size n) -> RawString &;

	/**
	 * @param position
	 * @param unit
	 */
	auto insert(ConstIterator position, CodeUnit unit) -> Iterator {
		auto const index = position - begin();
		insert(index, unit);
		return begin() + index;
	}

	/**
	 * @param position
	 * @param unit
	 * @param n
	 */
	auto insert(ConstIterator position, CodeUnit unit, Size n) -> Iterator {
		auto const index = position - begin();
		insert(index, unit, n);
		return begin() + index;
	}

	/**
	 * @param position
	 * @param list
	 */
	auto insert(ConstIterator position, InitializerList<CodeUnit> list) -> Iterator {
		return insert(position, list.begin(), list.end());
	}

	/**
	 * @tparam TIterator
	 * @param position
	 * @param first
	 * @param last
	 */
	template<typename TIterator>
	auto insert(ConstIterator position, TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> Iterator {
		return m_insert(position, first, last, typename IteratorTraits<TIterator>::Category{});
	}
	///@}

	/**
	 * @name 替换
	 */
	///@{
	/**
	 * @param index
	 * @param count
	 * @param string
	 */
	auto replace(Size index, Size count, RawString const & string) -> RawString & {
		return replace(index, count, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param count
	 * @param string
	 */
	auto replace(Size index, Size count, RawStringView<CodeUnit> const & string) -> RawString & {
		return replace(index, count, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param count
	 * @param string
	 */
	auto replace(Size index, Size count, CString<CodeUnit> string) -> RawString & {
		return replace(index, count, string, string_length(string));
	}

	/**
	 * @param index
	 * @param count
	 * @param string
	 * @param length
	 */
	auto replace(Size index, Size count, CString<CodeUnit> string, Size length) -> RawString &;

	/**
	 * @param index
	 * @param count
	 * @param unit
	 */
	auto replace(Size index, Size count, CodeUnit unit) -> RawString &;

	/**
	 * @param index
	 * @param count
	 * @param unit
	 * @param n
	 */
	auto replace(Size index, Size count, CodeUnit unit, Size n) -> RawString &;

	/**
	 * @param first
	 * @param last
	 * @param string
	 */
	auto replace(ConstIterator first, ConstIterator last, RawString const & string) -> RawString & {
		return replace(first, last, string.data(), string.size());
	}

	/**
	 * @param first
	 * @param last
	 * @param string
	 */
	auto replace(ConstIterator first, ConstIterator last, RawStringView<CodeUnit> const & string) -> RawString & {
		return replace(first, last, string.data(), string.size());
	}

	/**
	 * @param first
	 * @param last
	 * @param string
	 */
	auto replace(ConstIterator first, ConstIterator last, CString<CodeUnit> string) -> RawString & {
		return replace(first, last, string, string_length(string));
	}

	/**
	 * @param first
	 * @param last
	 * @param string
	 * @param length
	 */
	auto replace(ConstIterator first, ConstIterator last, CString<CodeUnit> string, Size length) -> RawString & {
		return replace(static_cast<Size>(first - begin()), static_cast<Size>(last - first), string, length);
	}

	/**
	 * @param first
	 * @param last
	 * @param list
	 */
	auto replace(ConstIterator first, ConstIterator last, InitializerList<CodeUnit> list) -> RawString & {
		return replace(first, last, list.begin(), list.end());
	}

	/**
	 * @tparam TIterator
	 * @param first0
	 * @param last0
	 * @param first1
	 * @param last1
	 */
	template<typename TIterator >
	auto replace(ConstIterator first0, ConstIterator last0, TIterator first1, TIterator last1, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> RawString &;
	///@}

	/**
	 * @name 删除
	 */
	///@{
	/**
	 * @param index
	 * @param count
	 */
	auto remove(Size index, Size count) -> RawString &;

	/**
	 * @param position
	 */
	auto remove(ConstIterator position) -> Iterator {
		auto index = position - begin();
		remove(static_cast<Size>(index), 1);
		return begin() + index;
	}

	/**
	 * @param first
	 * @param last
	 */
	auto remove(ConstIterator first, ConstIterator last) -> Iterator {
		auto index = first - begin();
		remove(static_cast<Size>(index), static_cast<Size>(last - first));
		return begin() + index;
	}
	///@}

private:
	constexpr static auto m_allocate_size(Size size) noexcept -> Size {
		return size < MIN_CAPACITY ? MIN_CAPACITY : (size + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1);
	}

	auto m_allocator() noexcept -> Allocator & {
		return m_impl.template get<Allocator>();
	}

	auto m_allocator() const noexcept -> Allocator const & {
		return m_impl.template get<Allocator>();
	}

	auto m_storage() noexcept -> Storage & {
		return m_impl.template get<Storage>();
	}

	auto m_storage() const noexcept -> Storage const & {
		return m_impl.template get<Storage>();
	}

	auto m_large() noexcept -> LargeStorage & {
		return m_storage().large;
	}

	auto m_large() const noexcept -> LargeStorage const & {
		return m_storage().large;
	}

	auto m_small() noexcept -> SmallStorage & {
		return m_storage().small;
	}

	auto m_small() const noexcept -> SmallStorage const & {
		return m_storage().small;
	}

	auto m_is_large() const noexcept -> bool {
		return bool(m_small().size & SMALL_MASK);
	}

	auto m_get_capacity() const noexcept -> Size {
		return m_is_large() ? m_get_large_capacity() : m_get_small_capacity();
	}

	auto m_get_large_capacity() const noexcept -> Size {
		return m_large().capacity & Size(~LARGE_MASK);
	}

	void m_set_large_capacity(Size capacity) noexcept {
		m_large().capacity = LARGE_MASK | capacity;
	}

	auto m_get_small_capacity() const noexcept -> Size {
		return MIN_CAPACITY;
	}

	auto m_get_size() const noexcept -> Size {
		return m_is_large() ? m_get_large_size() : m_get_small_size();
	}

	void m_set_size(Size size) noexcept {
		m_is_large() ? m_set_large_size(size) : m_set_small_size(size);
	}

	auto m_get_large_size() const noexcept -> Size {
		return m_large().size;
	}

	void m_set_large_size(Size size) noexcept {
		m_large().size = size;
	}

	auto m_get_small_size() const -> Size {
#if defined(BR_LITTLE_ENDIAN)
		return m_small().size >> 1;
#else
		return m_small().size;
#endif // defined(BR_LITTLE_ENDIAN)
	}

	void m_set_small_size(Size size) noexcept {
#if defined(BR_LITTLE_ENDIAN)
		m_small().size = Byte(size << 1);
#else
		m_small().size = Byte(size);
#endif // defined(BR_LITTLE_ENDIAN)
	}

	auto m_get_pointer() noexcept -> Pointer {
		return m_is_large() ? m_get_large_pointer() : m_get_small_pointer();
	}

	auto m_get_pointer() const noexcept -> ConstPointer {
		return m_is_large() ? m_get_large_pointer() : m_get_small_pointer();
	}

	auto m_get_large_pointer() noexcept -> Pointer {
		return m_large().data;
	}

	auto m_get_large_pointer() const noexcept -> ConstPointer {
		return m_large().data;
	}

	void m_set_large_pointer(Pointer pointer) noexcept {
		m_large().data = pointer;
	}

	auto m_get_small_pointer() noexcept -> Pointer {
		return PointerTraits::make_pointer(m_small().data[0]);
	}

	auto m_get_small_pointer() const noexcept -> ConstPointer {
		return ConstPointerTraits::make_pointer(m_small().data[0]);
	}

	auto m_get_raw_pointer() noexcept -> Element * {
		return PointerTraits::to_raw(m_get_pointer());
	}

	auto m_get_raw_pointer() const noexcept -> Element const * {
		return ConstPointerTraits::to_raw(m_get_pointer());
	}

	void m_zeroize() noexcept {
		m_small().size = 0;
		for (auto & byte : m_small().data) {
			byte = 0;
		}
	}

	void m_prepare(Size size);

	void m_construct(CodeUnit const * units, Size length) {
		m_construct(units, length, length);
	}

	void m_construct(CodeUnit const * units, Size length, Size reserve);

	template< typename TSinglePassIterator >
	void m_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag);

	template< typename TForwardIterator >
	void m_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag);

	void m_destruct() {
		if (m_is_large()) {
			AllocatorTraits::deallocate(m_allocator(), m_get_large_pointer(), m_get_large_capacity());
		}
	}

	auto m_compare(CodeUnit const * rhs_data, Size rhs_size) const noexcept -> Relation;

	void m_copy_assign_allocator(RawString const & string, BooleanTrue) noexcept {
	}

	void m_copy_assign_allocator(RawString const & string, BooleanFalse) {
		if (m_allocator() != string.m_allocator()) {
			clear();
			shrink();
		}
		m_allocator() = string.m_allocator();
	}

	void m_move_assign(RawString & string, BooleanTrue) noexcept(HasNothrowMoveAssignment<Allocator>{}) {
		clear();
		shrink();
		m_storage() = string.m_storage();
		m_allocator() = move(string.m_allocator());
		string.m_zeroize();
	}

	void m_move_assign(RawString & string, BooleanFalse) {
		if (m_allocator() != string.m_allocator()) {
			*this = string;
		} else {
			clear();
			shrink();
			m_storage() = string.m_storage();
			string.m_zeroize();
		}
	}

	void m_grow_and_replace(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count, CodeUnit const * units);

	void m_grow(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count = 0);

	template< typename TSinglePassIterator >
	void m_assign(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
		clear();
		m_append(first, last, SinglePassTraversalTag{});
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
	Tuple<Allocator, Storage> m_impl;

}; // class RawString< TCodeUnit, TAllocator >

template< typename TCodeUnit, typename TAllocator >
void RawString< TCodeUnit, TAllocator>::m_prepare(Size size) {
	if (size > max_size()) {
		throw_length_exception(BR_CURRENT_FUNCTION);
	}
	if (size < MIN_CAPACITY) {
		m_set_small_size(size);
	} else {
		auto capacity = m_allocate_size(size + 1);
		auto pointer = AllocatorTraits::allocate(m_allocator(), capacity);
		m_set_large_pointer(pointer);
		m_set_large_capacity(capacity);
		m_set_large_size(size);
	}
}

template< typename TCodeUnit, typename TAllocator >
void RawString< TCodeUnit, TAllocator >::m_construct(CodeUnit const * units, Size length, Size reserve) {
	m_prepare(reserve);
	auto pointer = m_get_pointer();
	copy_n(units, length, PointerTraits::to_raw(pointer));
	pointer[length] = CodeUnit(0);
	m_set_size(length);
}

template< typename TCodeUnit, typename TAllocator >
template< typename TSinglePassIterator >
void RawString< TCodeUnit, TAllocator >::m_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
	m_zeroize();
#if !defined(BR_NO_EXCEPTIONS)
	try {
#endif
		for (; first != last; ++first) {
			append(*first);
		}
#if !defined(BR_NO_EXCEPTIONS)
	} catch (...) {
		if (m_is_large()) {
			AllocatorTraits::deallocate(m_allocator(), m_get_large_pointer(), m_get_large_capacity());
		}
		throw;
	}
#endif
}

template< typename TCodeUnit, typename TAllocator >
template< typename TForwardIterator >
void RawString< TCodeUnit, TAllocator >::m_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	auto size = static_cast<Size>(distance(first, last));
	if (size > max_size()) {
		throw_length_exception(BR_CURRENT_FUNCTION);
	}

	Pointer pointer;
	if (size < MIN_CAPACITY) {
		m_set_small_size(size);
		pointer = m_get_small_pointer();
	} else {
		auto capacity = m_allocate_size(size);
		pointer = AllocatorTraits::allocate(m_allocator(), capacity);
		m_set_large_pointer(pointer);
		m_set_large_capacity(capacity);
		m_set_large_size(size);
	}
	for (; first != last; ++first, (void) ++pointer) {
		*pointer = *first;
	}
	*pointer = CodeUnit(0);
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::reserve(Size count) -> RawString & {
	if (count > max_size()) {
		throw_length_exception(BR_CURRENT_FUNCTION);
	}
	auto size = m_get_size();
	auto old_capacity = m_get_capacity(), new_capacity = m_allocate_size(max(count, size) + 1);
	if (new_capacity != old_capacity) {
		Pointer old_pointer = m_get_pointer(), new_pointer;
		bool now_large;
		if (new_capacity == MIN_CAPACITY) {
			now_large = false;
			new_pointer = m_get_small_pointer();
		} else {
			if (new_capacity > old_capacity) {
				new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
			} else {
				try {
					new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
				} catch (...) {
					return *this;
				}
			}
			now_large = true;
		}
		memory_copy(PointerTraits::to_raw(m_get_small_pointer()), PointerTraits::to_raw(old_pointer), size + 1);
		if (m_is_large()) {
			AllocatorTraits::deallocate(m_allocator(), old_pointer, old_capacity);
		}
		if (now_large) {
			m_set_large_capacity(new_capacity);
			m_set_large_size(size);
			m_set_large_pointer(new_pointer);
		} else {
			m_set_small_size(size);
		}
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::m_compare(CodeUnit const * rhs_data, Size rhs_size) const noexcept -> Relation {
	Size lhs_size = size();
	auto result = string_compare(data(), rhs_data, min(lhs_size, rhs_size));
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
}

template< typename TCodeUnit, typename TAllocator >
void RawString< TCodeUnit, TAllocator>::m_grow_and_replace(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count, CodeUnit const * units) {
	auto const MAX_SIZE = max_size();
	if (old_capacity + delta_capacity > MAX_SIZE - 1) {
		throw_length_exception(BR_CURRENT_FUNCTION);
	}
	auto old_pointer = m_get_pointer();
	auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
		? m_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
		: MAX_SIZE;
	auto new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
	if (copy_count != 0) {
		copy_n(PointerTraits::to_raw(old_pointer), copy_count, PointerTraits::to_raw(new_pointer));
	}
	if (add_count != 0) {
		copy_n(units, add_count, PointerTraits::to_raw(new_pointer) + copy_count);
	}
	auto const second_copy_count = old_size - delete_count - copy_count;
	if (second_copy_count != 0) {
		copy_n(PointerTraits::to_raw(old_pointer) + copy_count + delete_count, second_copy_count, PointerTraits::to_raw(new_pointer) + copy_count + add_count);
	}
	if (old_capacity != MIN_CAPACITY) {
		AllocatorTraits::deallocate(m_allocator(), old_pointer, old_capacity);
	}
	m_set_large_pointer(new_pointer);
	m_set_large_capacity(new_capacity);
	Size new_size = copy_count + add_count + second_copy_count;
	new_pointer[new_size] = CodeUnit(0);
	m_set_large_size(new_size);
}

template< typename TCodeUnit, typename TAllocator >
void RawString<TCodeUnit, TAllocator>::m_grow(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count) {
	auto const MAX_SIZE = max_size();
	if (delta_capacity > MAX_SIZE - old_capacity) {
		throw_length_exception(BR_CURRENT_FUNCTION);
	}
	auto old_pointer = m_get_pointer();
	auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
		? m_allocate_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
		: MAX_SIZE;
	auto new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
	if (copy_count != 0) {
		copy_n(PointerTraits::to_raw(old_pointer), copy_count, PointerTraits::to_raw(new_pointer));
	}
	auto const second_copy_count = old_size - delete_count - copy_count;
	if (second_copy_count != 0) {
		copy_n(PointerTraits::to_raw(old_pointer) + copy_count + delete_count, second_copy_count, PointerTraits::to_raw(new_pointer) + copy_count + add_count);
	}
	m_set_large_pointer(new_pointer);
	m_set_large_capacity(new_capacity);
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::assign(CString<CodeUnit> string, Size length) -> RawString & {
	BR_ASSERT(length == 0 || string != nullptr);
	auto capacity = m_get_capacity();
	if (m_get_capacity() > length) {
		auto pointer = m_get_raw_pointer();
		string_move(pointer, string, length);
		pointer[length] = CodeUnit(0);
		m_set_size(length);
	} else {
		auto size = m_get_size();
		m_grow_and_replace(capacity, length - capacity, size, 0, size, length, string);
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
template< typename TForwardIterator >
void RawString< TCodeUnit, TAllocator >::m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	auto count = static_cast<Size>(distance(first, last));
	auto capacity = m_get_capacity();
	if (capacity < count) {
		auto const size = m_get_size();
		m_grow(capacity, count - capacity, size, 0, size);
	}
	auto pointer = m_get_pointer();
	for (; first != last; ++first, ++pointer) {
		*pointer = *first;
	}
	*pointer = CodeUnit(0);
	m_set_size(count);
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::append(CString<CodeUnit> string, Size length) -> RawString & {
	BR_ASSERT(length == 0 || string != nullptr);
	auto capacity = m_get_capacity();
	auto size = m_get_size();
	if (capacity - size >= length) {
		if (length != 0) {
			auto pointer = m_get_raw_pointer();
			copy_n(string, length, pointer + size);
			size += length;
			pointer[size] = CodeUnit(0);
			m_set_size(size);
		}
	} else {
		m_grow_and_replace(capacity, size + length - capacity, size, size, 0, length, string);
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::append(CodeUnit unit) -> RawString & {
	auto capacity = m_get_capacity();
	auto old_size = m_get_size();
	auto new_size = old_size + 1;
	if (new_size == capacity) {
		m_grow(capacity, 1, old_size, old_size, 0);
	}
	auto pointer = PointerTraits::to_raw(m_get_pointer()) + old_size;
	*pointer = unit;
	*++pointer = CodeUnit(0);
	m_set_size(new_size);
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::append(CodeUnit unit, Size n) -> RawString & {
	if (n > 0) {
		auto capacity = m_get_capacity();
		auto old_size = m_get_size();
		auto new_size = old_size + n;
		if (capacity < new_size) {
			m_grow(capacity, new_size - capacity, old_size, old_size, 0);
		}
		auto pointer = m_get_raw_pointer();
		fill_n(pointer + old_size, n, unit);
		pointer[new_size] = CodeUnit(0);
		m_set_size(new_size);
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
template< typename TForwardIterator >
void RawString< TCodeUnit, TAllocator >::m_append(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	auto size = m_get_size();
	auto capacity = m_get_capacity();
	auto count = static_cast<Size>(distance(first, last));
	if (count != 0) {
		if (capacity - size < count) {
			m_grow(capacity, size + count - capacity, size, size, 0);
		}
		auto pointer = PointerTraits::to_raw(m_get_pointer()) + size;
		for (; first != last; ++pointer, ++first) {
			*pointer = *first;
		}
		*pointer = CodeUnit(0);
		m_set_size(size + count);
	}
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::insert(Size index, CString<CodeUnit> string, Size length) -> RawString & {
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception(BR_CURRENT_FUNCTION);
	}
	auto capacity = m_get_capacity();
	if (capacity - old_size >= length) {
		if (length > 0) {
			auto new_size = old_size + length;
			auto pointer = PointerTraits::to_raw(m_get_pointer());
			auto move_count = old_size - index;
			if (move_count > 0) {
				if (pointer + index <= string && string < pointer + old_size) {
					string += length;
				}
				string_move(pointer + index + length, pointer + index, move_count);
			}
			string_move(pointer + index, string, length);
			pointer[new_size] = CodeUnit(0);
			m_set_size(new_size);
		}
	} else {
		m_grow_and_replace(capacity, old_size + length - capacity, old_size, index, 0, length, string);
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::insert(Size index, CodeUnit unit) -> RawString & {
	auto old_size = m_get_size();
	auto new_size = old_size + 1;
	auto capacity = m_get_capacity();
	CodeUnit * pointer;
	if (capacity == old_size) {
		m_grow(capacity, 1, old_size, index, 0, 1);
		pointer = PointerTraits::to_raw(m_get_pointer());
	} else {
		pointer = PointerTraits::to_raw(m_get_pointer());
		Size move_count = old_size - index;
		if (move_count > 0) {
			string_move(pointer + index + 1, pointer + index, move_count);
		}
	}
	pointer[index] = unit;
	pointer[new_size] = CodeUnit(0);
	m_set_size(new_size);
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::insert(Size index, CodeUnit unit, Size n) -> RawString & {
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception(BR_CURRENT_FUNCTION);
	}
	if (n > 0) {
		auto capacity = m_get_capacity();
		auto new_size = old_size + n;
		CodeUnit * pointer = nullptr;
		if (capacity >= new_size) {
			pointer = PointerTraits::to_raw(m_get_pointer());
			Size move_count = old_size - index;
			if (move_count > 0) {
				string_move(pointer + index + n, pointer + index, move_count);
			}
		} else {
			m_grow(capacity, new_size - capacity, old_size, index, 0, n);
			pointer = PointerTraits::to_raw(m_get_pointer());
		}
		fill_n(pointer + index, n, unit);
		pointer[new_size] = CodeUnit(0);
		m_set_size(new_size);
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
template< typename TSinglePassIterator >
auto RawString< TCodeUnit, TAllocator >::m_insert(ConstIterator position, TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) -> Iterator {
	auto index = position - begin();
	auto old_size = m_get_size();
	for (; first != last; ++first) {
		*this << *first;
	}
	auto pointer = m_get_pointer();
	rotate(pointer + index, pointer + old_size, pointer + size());
	return begin() + index;
}

template< typename TCodeUnit, typename TAllocator >
template< typename TForwardIterator >
auto RawString< TCodeUnit, TAllocator >::m_insert(ConstIterator position, TForwardIterator first, TForwardIterator last, ForwardTraversalTag) -> Iterator {
	auto index = position - begin();
	auto old_size = m_get_size();
	auto capacity = m_get_capacity();
	Size count = static_cast<Size>(distance(first, last));
	if (count > 0) {
		auto new_size = old_size + count;
		CodeUnit * pointer = nullptr;
		if (capacity >= new_size) {
			pointer = PointerTraits::to_raw(m_get_pointer());
			Size move_count = old_size - index;
			if (move_count > 0) {
				string_move(pointer + index + count, pointer + index, move_count);
			}
		} else {
			m_grow(capacity, new_size - capacity, old_size, index, 0, count);
			pointer = PointerTraits::to_raw(m_get_pointer());
		}
		pointer[new_size] = CodeUnit(0);
		m_set_size(new_size);
		for (pointer += index; first != last; ++pointer, (void) ++first) {
			*pointer = *first;
		}
	}
	return begin() + index;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::replace(Size index, Size count, CString<CodeUnit> string, Size length) -> RawString & {
	BR_ASSERT(length == 0 || string != nullptr);
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception(BR_CURRENT_FUNCTION);
	}
	count = min(count, old_size - index);
	auto capacity = m_get_capacity();
	if (capacity - old_size + count >= length) {
		auto pointer = m_get_raw_pointer();
		if (count != length) {
			auto move_count = old_size - index - count;
			if (move_count > 0) {
				if (count > length) {
					string_move(pointer + index, string, length);
					string_move(pointer + index + length, pointer + index + count, move_count);
					goto FINISH;
				}
				if (pointer + index < string && string < pointer + length) {
					if (pointer + index + count <= string) {
						string += length - count;
					} else {
						string_move(pointer + index, string, count);
						index += count;
						string += length;
						length -= count;
						count = 0;
					}
				}
				string_move(pointer + index + length, pointer + index + count, move_count);
			}
		}
		string_move(pointer + index, string, length);
FINISH:
		auto new_size = old_size + length - count;
		pointer[new_size] = CodeUnit(0);
		m_set_size(new_size);
	} else {
		m_grow_and_replace(capacity, old_size - count + length - capacity, old_size, index, count, length, string);
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::replace(Size index, Size count, CodeUnit unit) -> RawString & {
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception(BR_CURRENT_FUNCTION);
	}
	count = min(count, old_size - index);
	auto capacity = m_get_capacity();
	CodeUnit * pointer = nullptr;
	auto new_size = old_size - count + 1;
	if (capacity - old_size + count >= 1) {
		pointer = PointerTraits::to_raw(m_get_pointer());
		if (count != 1) {
			auto move_count = old_size - index - count;
			if (move_count > 0) {
				string_move(pointer + index + 1, pointer + index + count, move_count);
			}
		}
	} else {
		m_grow(capacity, new_size - capacity, old_size, index, count, 1);
		pointer = PointerTraits::to_raw(m_get_pointer());
	}
	pointer[index] = unit;
	pointer[new_size] = CodeUnit(0);
	m_set_size(new_size);
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::replace(Size index, Size count, CodeUnit unit, Size n) -> RawString & {
	auto old_size = m_get_size();
	if (index > old_size) {
		throw_index_exception(BR_CURRENT_FUNCTION);
	}
	count = min(count, old_size - index);
	auto capacity = m_get_capacity();
	CodeUnit * pointer = nullptr;
	auto new_size = old_size - count + n;
	if (capacity - old_size + count >= n) {
		pointer = PointerTraits::to_raw(m_get_pointer());
		if (count != n) {
			auto move_count = old_size - index - count;
			if (move_count > 0) {
				string_move(pointer + index + n, pointer + index + count, move_count);
			}
		}
	} else {
		m_grow(capacity, new_size - capacity, old_size, index, count, n);
		pointer = PointerTraits::to_raw(m_get_pointer());
	}
	fill_n(pointer + index, n, unit);
	pointer[new_size] = CodeUnit(0);
	m_set_size(new_size);
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
template< typename TIterator >
auto RawString< TCodeUnit, TAllocator >::replace(ConstIterator first0, ConstIterator last0, TIterator first1, TIterator last1, EnableIf< IsInputIterator<TIterator> > *) -> RawString & {
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
		const_cast<CodeUnit &>(*first0) = *first1;
	}
	return *this;
}

template< typename TCodeUnit, typename TAllocator >
auto RawString< TCodeUnit, TAllocator >::remove(Size index, Size count) -> RawString & {
	auto old_size = m_get_size();
	if (count > 0) {
		auto new_size = old_size - count;
		CodeUnit * pointer = PointerTraits::to_raw(m_get_pointer());
		auto move_count = new_size - index;
		if (move_count > 0) {
			string_move(pointer + index, pointer + index + count, move_count);
		}
		pointer[new_size] = CodeUnit(0);
		m_set_size(new_size);
	}
	return *this;
}

extern template class RawString<Char8>;

extern template class RawString<Char16>;

extern template class RawString<Char32>;

inline namespace Literal {

inline namespace RawStringLiteral {

inline auto operator "" _rs(CString<Char8> string, Size length) -> RawString<Char8> {
	return RawString<Char8>(string, length);
}

inline auto operator "" _rs(CString<Char16> string, Size length) -> RawString<Char16> {
	return RawString<Char16>(string, length);
}

inline auto operator "" _rs(CString<Char32> string, Size length) -> RawString<Char32> {
	return RawString<Char32>(string, length);
}

} // inline namespace RawStringLiteral

} // inline namespace Literal

} // namespace BR