#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/math/relation.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/operators/template_equality_comparable.hpp>
#include <libbr/operators/template_less_than_comparable.hpp>
#include <libbr/string/detail/raw_string_basic.hpp>
#include <libbr/string/raw_string_view.hpp>
#include <libbr/string/string_length.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/has_nothrow_copy_assignment.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/is_input_iterator.hpp>

namespace BR {

/**
 * @brief Stores and manipulates sequences of code units.
 * @tparam TCodeUnit Type of code units.
 * @tparam TAllocator Type of allocator used to allocate internal storage.
 */
template< typename TCodeUnit, typename TAllocator = Allocator<TCodeUnit> >
class RawString;


template< typename TCodeUnit, typename TAllocator >
class RawString :
	private Detail::String::RawString::Basic<TCodeUnit, TAllocator>,
	public EqualityComparable< RawString< TCodeUnit, TAllocator > >,
	public LessThanComparable< RawString< TCodeUnit, TAllocator > >,
	public EqualityComparable< RawString< TCodeUnit, TAllocator >, RawStringView< TCodeUnit > >,
	public LessThanComparable< RawString< TCodeUnit, TAllocator >, RawStringView< TCodeUnit > >,
	public EqualityComparable< RawString< TCodeUnit, TAllocator >, CString< TCodeUnit > >,
	public LessThanComparable< RawString< TCodeUnit, TAllocator >, CString< TCodeUnit > >
{
private:
	using Self = RawString;

public:
	/**
	 * @brief 分配器类
	 * @see BR::Allocator
	 */
	using Allocator = TAllocator;

	/**
	 * @brief CodeUnit
	 */
	using CodeUnit = TCodeUnit;

private:
	using Base = Detail::String::RawString::Basic< CodeUnit, Allocator >;

public:
	/**
	 * @brief Element
	 */
	using Element = typename Base::Element;

	/**
	 * @brief AllocatorTraits<Allocator>::Size
	 * @see BR::AllocatorTraits::Size
	 */
	using Size = typename Base::Size;

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
	using Pointer = typename Base::Pointer;

	/**
	 * @brief AllocatorTraits<Allocator>::ConstPointer ，与指向 Value 的常量指针等同的类型
	 * @see AllocatorTraits::ConstPointer
	 */
	using ConstPointer = typename Base::ConstPointer;

	/**
	 * @brief AllocatorTraits<Allocator>::Difference, 指针之差的结果类型
	 * @see AllocatorTraits::Difference
	 */
	using Difference = typename Base::Difference;

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
	using AllocatorTraits = BR::AllocatorTraits<Allocator>;

public:
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
	RawString() noexcept(HasNothrowDefaultConstructor<Allocator>{}) : Base() {
		this->m_zeroize();
	}

	/**
	 * @brief 指定分配器，并默认构造
	 * @param[in] allocator 分配器
	 */
	explicit RawString(Allocator const & allocator) noexcept : Base(allocator) {
		this->m_zeroize();
	}

	/**
	 * @brief 复制构造函数
	 * @param[in] other 源字符串
	 */
	RawString(Self const & other) : Base(AllocatorTraits::select_on_container_copy_construction(other.allocator())) {
		this->m_construct(other.m_raw_data(), other.m_size());
	}

	/**
	 * @brief 指定分配器，并复制内容
	 * @param[in] other 源字符串
	 * @param[in] allocator 分配器
	 * @see String(String const & string)
	 */
	RawString(Self const & other, Allocator const & allocator) : Base(allocator) {
		this->m_construct(other.m_raw_data(), other.m_size());
	}

	/**
	 * @brief 移动构造
	 * @param[in] other 源字符串
	 *
	 * 把源字符串的内容搬移到新串中
	 */
	RawString(Self && other) noexcept : Base(move(other)) {
	}

	/**
	 * @brief 指定分配器，并移动内容
	 * @param[in] other 源字符串
	 * @param[in] allocator 分配器
	 * @see String(String && string)
	 *
	 */
	RawString(Self && other, Allocator const & allocator) : Base(move(other), allocator) {
	}

	RawString(CString<CodeUnit> string, Allocator const & allocator = Allocator()) : RawString(string, string_length(string), allocator) {
	}

	/**
	 * @brief 从给定长度的码元序列构造
	 * @param[in] string 码元序列
	 * @param[in] length 长度
	 * @param[in] allocator 分配器
	 */
	RawString(CString<CodeUnit> string, Size length, Allocator const & allocator = Allocator()) : Base(allocator) {
		BR_ASSERT(string != nullptr);
		this->m_construct(string, length);
	}

	/**
	 * @brief 从字符串视图构造
	 * @param string 字符串视图
	 * @param allocator 分配器
	 */
	RawString(RawStringView<CodeUnit> const & string, Allocator const & allocator = Allocator()) : Base(allocator) {
		this->m_construct(string.data(), string.size());
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
	RawString(TIterator first, TIterator last, Allocator const & allocator = Allocator(), EnableIf< IsInputIterator<TIterator> > * = nullptr) : Base(allocator) {
		this->m_construct(first, last);
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
	 * @name 迭代器
	 */
	///@{
	//@{
	/**
	 * @return 指向首个码元的迭代器
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(this->m_data());
	}

	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(this->m_data());
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
		return Iterator(this->m_data() + this->m_size());
	}

	auto end() const noexcept -> ConstIterator {
		return ConstIterator(this->m_data() + this->m_size());
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
		return this->m_data()[index];
	}

	auto at(Size index) const -> CodeUnit const & {
		if (index >= size()) {
			throw_index_exception(BR_CURRENT_FUNCTION);
		}
		return this->m_data()[index];
	}
	//@}

	//@{
	/**
	 * @param index
	 */
	auto operator[](Size index) -> CodeUnit & {
		BR_ASSERT(index <= size());
		return this->m_data()[index];
	}

	auto operator[](Size index) const -> CodeUnit const & {
		BR_ASSERT(index <= size());
		return this->m_data()[index];
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
		return this->m_allocator();
	}

	//@{
	/**
	 * @return 指向首位码元之前一个位置的反向迭代器
	 */
	auto data() -> CodeUnit * {
		return this->m_raw_data();
	}

	auto data() const -> CodeUnit const * {
		return this->m_raw_data();
	}
	//@}

	//@{
	/**
	 * @return 指向首位码元之前一个位置的反向迭代器
	 */
	auto front() -> Reference {
		return this->m_data()[0];
	}

	auto front() const -> ConstReference {
		return this->m_data()[0];
	}
	//@}

	//@{
	/**
	 * @return 指向首位码元之前一个位置的反向迭代器
	 */
	auto back() -> Reference {
		return this->m_data()[this->size() - 1];
	}

	auto back() const -> ConstReference {
		return this->m_data()[this->size() - 1];
	}
	//@}

	operator RawStringView<CodeUnit>() const {
		return RawStringView<CodeUnit>(this->m_data(), this->m_size());
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
		return this->m_size();
	}

	/**
	 * @brief 最大长度
	 */
	auto max_size() const noexcept -> Size {
		return this->m_max_size();
	}

	/**
	 * @brief 当前分配的内存空间容量
	 */
	auto capacity() const noexcept -> Size {
		return this->m_capacity() - 1;
	}

	/**
	 * @brief 设置容量为至少 \em size
	 * @param[in] count 预留容量
	 */
	auto reserve(Size count = 0) -> Self & {
		this->m_reserve(count);
		return *this;
	}

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
		return this->m_compare(y.data(), y.size());
	}

	auto compare(RawStringView<CodeUnit> y) const noexcept -> Relation {
		return this->m_compare(y.data(), y.size());
	}

	auto compare(CString<CodeUnit> y) const noexcept -> Relation {
		return this->m_compare(y, string_length(y));
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
	auto operator>(RawStringView<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::GT;
	}

	auto operator>(CString<CodeUnit> y) const noexcept -> bool {
		return compare(y) == Relation::GT;
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
	auto clear() noexcept -> Self & {
		this->m_clear();
		return *this;
	}

	//@{
	/**
	 * @brief 复制赋值
	 * @param other
	 */
	auto operator=(Self const & other) -> Self & {
		this->m_assign(other);
		return *this;
	}

	auto assign(Self const & other) -> Self & {
		return *this = other;
	}
	//@}

	//@{
	/**
	 * @brief 移动赋值
	 * @param other
	 */
	auto operator=(Self && other) noexcept(
		BooleanAnd< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment, typename AllocatorTraits::IsAlwaysEqual >{}
	) -> Self & {
		this->m_assign(move(other));
		return *this;
	}

	auto assign(Self && string) -> Self & {
		return *this = move(string);
	}
	//@}

	//@{
	/**
	 * @brief 以字符串视图赋值
	 * @param string 字符串视图
	 */
	auto operator=(RawStringView<CodeUnit> string) -> Self & {
		return assign(string.data(), string.size());
	}

	auto assign(RawStringView<CodeUnit> string) -> Self & {
		return assign(string.data(), string.size());
	}
	//@}

	//@{
	/**
	 * @brief 以初始化列表赋值
	 * @param list 初始化列表
	 */
	auto operator=(InitializerList<CodeUnit> list) -> Self & {
		return assign(list.begin(), list.end());
	}

	auto assign(InitializerList<CodeUnit> list) -> Self & {
		return assign(list.begin(), list.end());
	}
	//@}

	//@{
	/**
	 * @brief 以码元序列赋值
	 * @param string 序列
	 */
	auto operator=(CString<CodeUnit> string) -> Self & {
		return assign(string, string_length(string));
	}

	auto assign(CString<CodeUnit> string) -> Self & {
		return assign(string, string_length(string));
	}
	//@}

	/**
	 * @brief 以码元序列赋值
	 * @param string 序列
	 * @param length 序列长度
	 */
	auto assign(CString<CodeUnit> string, Size length) -> Self & {
		this->m_assign(string, length);
		return *this;
	}

	//@{
	/**
	 * @param unit
	 */
	auto operator=(CodeUnit unit) -> Self &;

	auto assign(CodeUnit unit) -> Self &;
	//@}

	/**
	 * @param unit
	 * @param n
	 */
	auto assign(CodeUnit unit, Size n) -> Self &;

	/**
	 * @tparam TIterator
	 * @param first
	 * @param last
	 */
	template< typename TIterator >
	auto assign(TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> Self & {
		this->m_assign(first, last);
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
	auto operator<<(RawString const & string) -> Self & {
		return append(string.data(), string.size());
	}

	auto append(RawString const & string) -> Self & {
		return append(string.data(), string.size());
	}
	//@}

	//@{
	/**
	 * @param string
	 */
	auto operator<<(RawStringView<CodeUnit> string) -> Self & {
		return append(string.data(), string.size());
	}

	auto append(RawStringView<CodeUnit> string) -> Self & {
		return append(string.data(), string.size());
	}
	//@}

	//@{
	/**
	 * @param string
	 */
	auto operator<<(CString<CodeUnit> string) -> Self & {
		return append(string, string_length(string));
	}

	auto append(CString<CodeUnit> string) -> Self & {
		return append(string, string_length(string));
	}

	//@}

	/**
	 * @param string
	 * @param length
	 */
	auto append(CString<CodeUnit> string, Size length) -> Self & {
		this->m_append(string, length);
		return *this;
	}

	//@{
	/**
	 *
	 * @param unit
	 */
	auto operator<<(CodeUnit unit) -> Self & {
		return append(unit);
	}

	auto append(CodeUnit unit) -> Self & {
		this->m_append(unit);
		return *this;
	}
	//@}

	/**
	 *
	 * @param unit
	 * @param n
	 */
	auto append(CodeUnit unit, Size n) -> Self & {
		this->m_append(unit, n);
		return *this;
	}

	//@{
	/**
	 * @param list
	 */
	auto operator<<(InitializerList<CodeUnit> list) -> Self & {
		return append(list.begin(), list.end());
	}

	auto append(InitializerList<CodeUnit> list) -> Self & {
		return append(list.begin(), list.end());
	}
	//@}

	/**
	 * @tparam TIterator
	 * @param first
	 * @param last
	 */
	template< typename TIterator >
	auto append(TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> Self & {
		this->m_append(first, last);
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
	auto insert(Size index, RawString const & string) -> Self & {
		return insert(index, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param string
	 */
	auto insert(Size index, RawStringView<CodeUnit> const & string) -> Self & {
		return insert(index, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param string
	 */
	auto insert(Size index, CString<CodeUnit> string) -> Self & {
		return insert(index, string, string_length(string));
	}

	/**
	 * @param index
	 * @param string
	 * @param length
	 */
	auto insert(Size index, CString<CodeUnit> string, Size length) -> Self & {
		this->m_insert(index, string, length);
		return *this;
	}

	/**
	 * @param index
	 * @param unit
	 * @return
	 */
	auto insert(Size index, CodeUnit unit) -> Self & {
		this->m_insert(index, unit);
		return *this;
	}

	/**
	 * @param index
	 * @param unit
	 * @param n
	 */
	auto insert(Size index, CodeUnit unit, Size count) -> Self & {
		this->m_insert(index, unit, count);
		return *this;
	}

	/**
	 * @param position
	 * @param unit
	 */
	auto insert(ConstIterator position, CodeUnit unit) -> Iterator {
		auto const index = position - cbegin();
		insert(index, unit);
		return begin() + index;
	}

	/**
	 * @param position
	 * @param unit
	 * @param n
	 */
	auto insert(ConstIterator position, CodeUnit unit, Size count) -> Iterator {
		auto const index = position - cbegin();
		insert(index, unit, count);
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
	 * @param first,last
	 */
	template<typename TIterator>
	auto insert(ConstIterator position, TIterator first, TIterator last, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> Iterator {
		return begin() + this->m_insert(position - cbegin(), first, last);
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
	auto replace(Size index, Size count, Self const & string) -> Self & {
		return replace(index, count, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param count
	 * @param string
	 */
	auto replace(Size index, Size count, RawStringView<CodeUnit> const & string) -> Self & {
		return replace(index, count, string.data(), string.size());
	}

	/**
	 * @param index
	 * @param count
	 * @param string
	 */
	auto replace(Size index, Size count, CString<CodeUnit> string) -> Self & {
		return replace(index, count, string, string_length(string));
	}

	/**
	 * @param index
	 * @param count
	 * @param string
	 * @param length
	 */
	auto replace(Size index, Size count, CString<CodeUnit> string, Size length) -> Self & {
		this->m_replace(index, count, string, length);
		return *this;
	}

	/**
	 * @param index
	 * @param count
	 * @param unit
	 */
	auto replace(Size index, Size count, CodeUnit unit) -> Self & {
		this->m_replace(index, count, unit);
		return *this;
	}

	/**
	 * @param index
	 * @param count
	 * @param unit
	 * @param count
	 */
	auto replace(Size index, Size count, CodeUnit unit, Size n) -> Self & {
		this->m_replace(index, count, unit, n);
		return *this;
	}

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
		return replace(static_cast<Size>(first - cbegin()), static_cast<Size>(last - first), string, length);
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
	auto replace(ConstIterator first0, ConstIterator last0, TIterator first1, TIterator last1, EnableIf< IsInputIterator<TIterator> > * = nullptr) -> Self & {
		this->m_replace(first0 - cbegin(), last0 - cbegin(), first1, last1);
		return *this;

	}
	///@}

	/**
	 * @name 删除
	 */
	///@{
	/**
	 * @param index
	 * @param count
	 */
	auto remove(Size index, Size count) -> Self & {
		this->m_remove(index, count);
		return *this;
	}

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

}; // class RawString< TCodeUnit, TAllocator >

extern template class RawString<Char8>;

extern template class RawString<Char16>;

extern template class RawString<Char32>;

inline namespace Literal {

inline auto operator "" _rs(CString<Char8> string, Size length) -> RawString<Char8> {
	return RawString<Char8>(string, length);
}

inline auto operator "" _rs(CString<Char16> string, Size length) -> RawString<Char16> {
	return RawString<Char16>(string, length);
}

inline auto operator "" _rs(CString<Char32> string, Size length) -> RawString<Char32> {
	return RawString<Char32>(string, length);
}

} // inline namespace Literal

} // namespace BR