/**
 * @file
 * @brief 字符串类
 * @author Bromine0x23
 * @since 2015/10/2
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/max.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/container/compressed_pair.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/exception/argument_exception.hpp>
#include <libbr/exception/out_of_range_exception.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/type_operate/bool.hpp>
#include <libbr/type_operate/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assign.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/allocator_traits.hpp>
#include <libbr/type_traits/char_traits.hpp>
#include <libbr/type_traits/is_pod.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/iterator_traits.hpp>
#include <libbr/type_traits/pointer_traits.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/enumerator.hpp>

namespace BR {

/**
 * @brief 字符串类
 * @tparam TChar 字符类型
 * @tparam TCharTraits 字符类型 TChar 的特性类
 * @tparam TAllocator 分配器类
 */
template< typename TChar, typename TCharTraits = BR::CharTraits<TChar>, typename TAllocator = BR::Allocator<TChar> >
class String {

public:

	static_assert(IsPOD<TChar>::value, "TChar must be a POD.");

	/**
	 * @brief 该类本身
	 */
	using Self = String;

	/**
	 * @brief 字符类型 TChar 的特性类
	 * @see BR::CharTraits
	 */
	using CharTraits = TCharTraits;

	/**
	 * @brief CharTraits::Char ，必须和 \em TChar 相同
	 */
	using Char = typename CharTraits::Char;

	static_assert(IsSame< Char, TChar >::value, "CharTraits::Char must be same type as TChar.");

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

	static_assert(IsSame< Value, TChar >::value, "AllocatorTraits<Allocator>::Value must be same type as TChar.");

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

	struct Storage {
		Size capacity;
		Size size;
		Pointer pointer;
	};

	CompressedPair< Storage, Allocator > m_pair;

public:
	constexpr static Size npos = -1;

public:

	/**
	 * @name 默认构造函数
	 *
	 * 构造空串（长度为0）
	 */
	///@{
	/**
	 * @brief 不指定分配器的版本
	 */
	String() : String(Allocator()) {
	}

	/**
	 * @brief 指定分配器的版本
	 * @param[in] allocator 分配器
	 */
	explicit String(Allocator const & allocator) : m_pair(allocator) {
		m_zeroize();
	}
	///@}

	/**
	 * @name 复制构造函数
	 *
	 * 构造给定字符串的副本
	 */
	///@{
	/**
	 * @brief 不指定分配器的版本
	 * @param[in] string 源字符串
	 */
	String(String const & string) : String(string, AllocatorTraits::select_on_container_copy_construction(string.m_allocator())) {
	}

	/**
	 * @brief 指定分配器的版本
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 */
	String(String const & string, Allocator const & allocator) : m_pair(allocator) {
		m_construct(string.m_get_pointer(), string.m_get_size());
	}
	///@}

	/**
	 * @name 移动构造函数
	 *
	 * 把源字符串的内容搬移到新串中
	 */
	///@{
	/**
	 * @brief 不指定分配器的版本
	 * @param[in] string 源字符串
	 */
	String(String && string) noexcept(HasNothrowMoveConstructor<Allocator>::value) : m_pair(move(string.m_pair)) {
		string.m_zeroize();
	}

	/**
	 * @brief 指定分配器的版本
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 */
	String(String && string, Allocator const & allocator) : m_pair(allocator) {
		if (allocator != string.allocator()) {
			m_construct(string.m_get_pointer(), string.m_get_size());
		} else {
			m_move(string);
		}
	}
	///@}

	/**
	 * @name 从C风格的字符串构造
	 */
	///@{
	/**
	 * @brief 完全复制的版本
	 * @param[in] string 源字符串
	 * @param[in] allocator 分配器
	 */
	String(CString<Char> string, Allocator const & allocator = Allocator()) : m_pair(allocator) {
		BR_ASSERT(string != nullptr);
		Size size = CharTraits::length(string);
		m_construct(string, size, size);
	}

	/**
	 * @brief 限制复制长度的版本
	 * @param[in] string 源字符串
	 * @param[in] n 最大复制长度
	 * @param[in] allocator 分配器
	 */
	String(CString<Char> string, Size n, Allocator const & allocator = Allocator()) : m_pair(allocator) {
		BR_ASSERT(string != nullptr || n == 0);
		m_construct(string, n, n);
	}
	///@}

	/**
	 * @name 从范围构造
	 */
	///@{
	/**
	 * @param[in] first, last 范围\f$[first, last)\f$
	 * @param[in] allocator 分配器
	 */
	/*
	template< typename TInputIterator >
	String(TInputIterator first, TInputIterator last, Allocator const & allocator = Allocator()) : m_pair(allocator) {
		m_construct(first, last);
	}
	*/

	template< typename TInputIterator >
	String(Enumerator<TInputIterator> enumerator, Allocator const & allocator = Allocator()) : m_pair(allocator) {
		m_construct(enumerator);
	}

	///@}

	/**
	 * @name 从初始化列表构造
	 */
	///@{
	/**
	 * @brief 指定分配器的版本
	 * @param[in] list 初始化列表
	 * @param[in] allocator 分配器
	 */
	String(InitializerList<Char> list, Allocator const & allocator = Allocator()) : String(make_enumerator(list.begin(), list.end()), allocator) {
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
	 * @name 赋值
	 */
	///@{
	/**
	 * @brief 复制赋值运算符
	 * @param[in] string 源字符串
	 */
	auto operator=(String const & string) -> String & {
		return this->assign(string);
	}

	/**
	 * @brief 移动赋值运算符
	 * @param[in] string 源字符串
	 */
	auto operator=(String && string) -> String & {
		this->swap(string);
		return this;
	}

	/**
	 * @brief 从C风格字符串复制
	 * @param[in] string 源字符串
	 * @see CString
	 */
	auto operator=(CString<Char> string) -> String & {
		return assign(string);
	}

	/**
	 * @brief 从初始化列表复制
	 * @param[in] list 初始化列表
	 * @see InitializerList
	 */
	auto operator=(InitializerList<Char> list) -> String & {
		return assign(list);
	}

	auto assign(String const & string) -> String & {
		if (this != &string) {
			m_copy_assign_allocator(string);
			assign(string.data(), string.size());
		}
		return *this;
	}

	auto assign(String const & string, Size position, Size count = npos) -> String &;

	auto assign(String && string) -> String & {
		this->swap(string);
		return this;
	}

	auto assign(CString<Char> string) -> String & {
		BR_ASSERT(string != nullptr);
		return assign(string, CharTraits::length(string));
	}

	auto assign(CString<Char> string, Size count) -> String &;

	template< typename TInputIterator >
	auto assign(TInputIterator first, TInputIterator last) -> EnableIf< BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> >, String & >;

	template< typename TInputIterator >
	auto assign(TInputIterator first, TInputIterator last) -> EnableIf< IsForwardIterator<TInputIterator>, String & >;

	auto assign(InitializerList<Char> list) -> String & {
		return assign(list.begin(), list.size());
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
	 * @brief 返回表示迭代开始的迭代器(常量限定)
	 */
	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	/**
	 * @brief 返回表示迭代结束的迭代器(常量限定)
	 */
	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	/**
	 * @brief 返回表示反向迭代开始的迭代器(常量限定)
	 */
	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
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
	 * @brief 元素访问(无边界检查)
	 * @param[in] index 索引
	 */
	auto operator[](Size index) -> Reference {
		BR_ASSERT(index < size());
		return m_get_pointer()[index];
	}

	/**
	 * @brief 元素访问(无边界检查)
	 * @param[in] index 索引
	 */
	auto operator[](Size index) const noexcept -> ConstReference {
		BR_ASSERT(index < size());
		return m_get_pointer()[index];
	}

	/**
	 * @brief 元素访问(有边界检查)
	 * @param[in] index 索引
	 */
	auto at(Size index) -> Reference {
		if (index >= size()) {
			throw OutOfRangeException("String::at(Size index)");
		}
		return m_get_pointer()[index];
	}

	/**
	 * @brief 元素访问(有边界检查)
	 * @param[in] index 索引
	 */
	auto at(Size index) const -> ConstReference {
		if (index >= size()) {
			throw OutOfRangeException("String::at(Size index)");
		}
		return m_get_pointer()[index];
	}

	/**
	 * @brief 返回
	 */
	auto data() const noexcept -> Char const * {
		return &*m_get_pointer();
	}

	auto c_string() const noexcept -> CString<Char> {
		return data();
	}

	auto front() -> Reference {
		return operator[](0);
	}

	auto front() const noexcept -> ConstReference {
		return operator[](0);
	}

	auto back() -> Reference {
		return operator[](size() - 1);
	}

	auto back() const noexcept -> ConstReference {
		return operator[](size() - 1);
	}

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
	 * @brief 字符串(字符)长度
	 */
	auto length() const noexcept -> Size {
		return size();
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

	auto clear() noexcept -> String & {
		CharTraits::assign(*m_get_pointer(), Char());
		m_set_size(0);
		return *this;
	}

	/*
	void resize(Size n, Char c);

	void resize(Size n) {
		resize(n, Char());
	}
	*/

	/**
	 * @name 追加操作
	 */
	///@{
	/**
	 * @brief 追加(运算符版本)
	 * @param[in] string 追加内容
	 * @see append(String const & string)
	 */
	auto operator<<(String const & string) -> String & {
		return append(string);
	}

	auto operator<<(CString<Char> string) -> String & {
		return append(string);
	}

	auto operator<<(Char c) -> String & {
		return append(c);
	}

	auto operator<<(InitializerList<Char> list) -> String & {
		return append(list);
	}

	/**
	 * @brief 追加
	 * @param[in] string 追加内容
	 */
	auto append(String const & string) -> String & {
		return append(string.data(), string.size());
	}

	auto append(String const & string, Size position, Size count = npos) -> String &;

	auto append(CString<Char> string) -> String & {
		BR_ASSERT(string != nullptr);
		return append(string, CharTraits::length(string));
	}

	auto append(CString<Char> string, Size count) -> String &;

	auto append(Char ch) -> String &;

	template< typename TInputIterator >
	auto append(TInputIterator first, TInputIterator last) -> EnableIf< BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> >, String & >;

	template< typename TInputIterator >
	auto append(TInputIterator first, TInputIterator last) -> EnableIf< IsForwardIterator<TInputIterator>, String & >;

	auto append(InitializerList<Char> list) -> String & {
		return append(list.begin(), list.end());
	}
	///@}



protected:
	void m_out_of_range_exception() {
		throw OutOfRangeException("String");
	}

private:
	constexpr static auto ALIGNMENT = 8;

	constexpr static auto m_align_size(Size size) noexcept -> Size {
		return ((size + 1) + (ALIGNMENT - 1) & ~(ALIGNMENT - 1));
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
		m_storage().capacity;
	}

	void m_set_capacity(Size capacity) {
		m_storage().capacity = capacity;
	}

	auto m_get_size() const -> Size {
		m_storage().size;
	}

	void m_set_size(Size size) {
		m_storage().size = size;
	}

	auto m_get_pointer() -> Pointer {
		m_storage().pointer;
	}

	auto m_get_pointer() const -> ConstPointer {
		m_storage().pointer;
	}

	void m_set_pointer(Pointer pointer) {
		m_storage().pointer = pointer;
	}

	void m_zeroize();

	void m_init(Size size);

	void m_construct(CString<Char> string, Size size, Size reserve);

	void m_construct(Char ch, Size size);

	template< typename TInputIterator >
	auto m_construct(Enumerator<TInputIterator> enumerator) -> EnableIf< BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> > >;

	template< typename TInputIterator >
	auto m_construct(Enumerator<TInputIterator> enumerator) -> EnableIf< IsForwardIterator<TInputIterator> >;

	template< typename TInputIterator >
	auto m_construct(TInputIterator first, TInputIterator last) -> EnableIf< BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> > >;

	template< typename TInputIterator >
	auto m_construct(TInputIterator first, TInputIterator last) -> EnableIf< IsForwardIterator<TInputIterator> >;

	void m_destruct() {
		AllocatorTraits::deallocate(m_allocator(), m_get_pointer(), m_get_capacity());
	}

	void m_copy_assign_allocator(String const & string) {
		m_copy_assign_allocator(string, AllocatorTraits::IsPropagateOnContainerCopyAssignment());
	}

	void m_copy_assign_allocator(String const & string, BooleanTrue _dummy) {
	}

	void m_copy_assign_allocator(String const & string, BooleanFalse _dummy) {
		if (m_allocator() != string.m_allocator()) {
			clear();
			clamp();
		}
		m_allocator() = string.m_allocator();
	}

	void m_grow_and_replace(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count, CString<Char> string);

	void m_grow(Size old_capacity, Size delta_capacity, Size old_size, Size copy_count, Size delete_count, Size add_count);

}; // class String< TChar, TTraits, TAllocator >

template< typename TChar, typename TCharTraits, typename TAllocator >
void String< TChar, TCharTraits, TAllocator >::m_zeroize() {
	m_set_capacity(0);
	m_set_size(0);
	m_set_pointer(nullptr);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
void String< TChar, TCharTraits, TAllocator >::m_init(Size size) {
	if (size > max_size()) {
		throw ArgumentException("String");
	}
	auto capacity = m_align_size(size + 1);
	m_set_pointer(AllocatorTraits::allocate(m_allocator(), capacity));
	m_set_capacity(capacity);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
void String< TChar, TCharTraits, TAllocator >::m_construct(CString<Char> string, Size size, Size reserve) {
	m_init(reserve);
	auto pointer = m_get_pointer();
	CharTraits::copy(&*pointer, string, size);
	CharTraits::assign(pointer[size], Char());
	m_set_size(size);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
void String< TChar, TCharTraits, TAllocator >::m_construct(Char ch, Size size) {
	m_init(size);
	auto pointer = m_get_pointer();
	CharTraits::assign(&*pointer, size, ch);
	CharTraits::assign(pointer[size], Char());
	m_set_size(size);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::m_construct(Enumerator<TInputIterator> enumerator) -> EnableIf<
	BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> >
> {
	m_zeroize();
	try {
		enumerator.each([this](Char ch){
			append(ch);
		});
	} catch (...) {
		m_destruct();
		throw;
	}
};

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::m_construct(Enumerator<TInputIterator> enumerator) -> EnableIf< IsForwardIterator<TInputIterator> > {
	auto size = static_cast<Size>(enumerator.size());
	m_init(size);
	auto pointer = m_get_pointer();
	enumerator.each([this, &pointer](Char ch){
		CharTraits::assign(*pointer++, ch);
	});
	CharTraits::assign(*pointer, Char());
	m_set_size(size);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::m_construct(TInputIterator first, TInputIterator last) -> EnableIf<
	BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> >
> {
	m_zeroize();
	try {
		for (; first != last; ++first) {
			append(*first);
		}
	} catch (...) {
		m_destruct();
		throw;
	}
}

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::m_construct(TInputIterator first, TInputIterator last) -> EnableIf< IsForwardIterator<TInputIterator> > {
	auto size = static_cast<Size>(distance(first, last));
	m_init(size);
	auto pointer = m_get_pointer();
	for (; first != last; ++first, ++pointer) {
		CharTraits::assign(*pointer, *first);
	}
	CharTraits::assign(*pointer, Char());
	m_set_size(size);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
void String< TChar, TCharTraits, TAllocator >::m_grow_and_replace(
	Size old_capacity,
	Size delta_capacity,
	Size old_size,
	Size copy_count,
	Size delete_count,
	Size add_count,
	CString<Char> string
) {
	auto const MAX_SIZE = max_size();
	if (delta_capacity > max_size - old_capacity - 1) {
		throw ArgumentException("String");
	}
	auto old_pointer = m_get_pointer();
	auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
		? m_align_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
		: MAX_SIZE;
	auto new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
	if (copy_count != 0) {
		CharTraits::copy(&*new_pointer, &*old_pointer, copy_count);
	}
	if (add_count != 0) {
		CharTraits::copy(&*new_pointer + copy_count, string, add_count);
	}
	auto const second_copy_count = old_size - delete_count - copy_count;
	if (second_copy_count != 0) {
		CharTraits::copy(&*new_pointer + copy_count + add_count, &*old_pointer + copy_count + delete_count, second_copy_count);
	}
	m_set_pointer(new_pointer);
	m_set_capacity(new_capacity);
	Size new_size = old_size + add_count - delete_count;
	m_set_size(new_size);
	CharTraits::assign(new_pointer[new_size], Char());
}


template< typename TChar, typename TCharTraits, typename TAllocator >
void String< TChar, TCharTraits, TAllocator >::m_grow(
	Size old_capacity,
	Size delta_capacity,
	Size old_size,
	Size copy_count,
	Size delete_count,
	Size add_count
) {
	auto const MAX_SIZE = max_size();
	if (delta_capacity > max_size - old_capacity) {
		throw ArgumentException("String");
	}
	auto old_pointer = m_get_pointer();
	auto const new_capacity = (old_capacity < MAX_SIZE / 2 - ALIGNMENT)
		? m_align_size(max(old_capacity + delta_capacity, 2 * old_capacity) + 1)
		: MAX_SIZE;
	auto new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
	if (copy_count != 0) {
		CharTraits::copy(&*new_pointer, &*old_pointer, copy_count);
	}
	auto const second_copy_count  = old_size - delete_count - copy_count;
	if (second_copy_count != 0) {
		CharTraits::copy(&*new_pointer + copy_count + add_count, &*old_pointer + copy_count + delete_count, second_copy_count);
	}
	m_set_pointer(new_pointer);
	m_set_capacity(new_capacity);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
auto String< TChar, TCharTraits, TAllocator >::assign(CString<Char> string, Size count) -> String & {
	BR_ASSERT(string != nullptr || count == 0);
	auto capacity = m_get_capacity();
	if (m_get_capacity() >= count) {
		Pointer pointer = m_get_pointer();
		CharTraits::move(&*pointer, string, count);
		CharTraits::assign(pointer[count], Char());
		m_set_size(count);
	} else {
		auto size = m_get_size();
		m_grow_and_replace(capacity, count - capacity, size, 0, size, count, string);
	}
}

template< typename TChar, typename TCharTraits, typename TAllocator >
auto String< TChar, TCharTraits, TAllocator >::assign(String const & string, Size position, Size count) -> String & {
	auto const size = string.size();
	if (position > size) {
		throw OutOfRangeException("String");
	}
	return assign(string.data() + position, min(count, size - position));
}

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::assign(TInputIterator first, TInputIterator last)->EnableIf< BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> >, String & > {
	clear();
	for (; first != last; ++first) {
		append(*first);
	}
	return *this;
}

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::assign(TInputIterator first, TInputIterator last)->EnableIf< IsForwardIterator<TInputIterator>, String & > {
	auto const count = static_cast<Size>(distance(first, last));
	auto const capacity = m_get_capacity();
	if (capacity < count) {
		auto const size = m_get_size();
		m_grow(capacity, count - capacity, size, 0, size);
	}
	auto pointer = m_get_pointer();
	for (; first != last; ++first, ++pointer) {
		CharTraits::assign(*pointer, *first);
	}
	CharTraits::assign(*pointer++, Char());
	m_set_size(count);
	return *this;
}

template< typename TChar, typename TCharTraits, typename TAllocator >
auto String< TChar, TCharTraits, TAllocator >::reserve(Size count) -> String & {
	if (count > max_size()) {
		throw ArgumentException("String");
	}
	auto const old_capacity = m_get_capacity();
	auto const size = m_get_size();
	auto const new_capacity = m_align_size(max(count, size) + 1);
	if (new_capacity != old_capacity) {
		auto const old_pointer = m_get_pointer();
		Pointer new_pointer;
		if (new_capacity > old_capacity) {
			new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
		} else {
			try {
				new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
			} catch (...) {
				return;
			}
		}
		CharTraits::copy(&*new_pointer, &*old_pointer, size + 1);
		m_set_pointer(new_pointer);
		m_set_capacity(new_capacity);
	}
	return *this;
}

template< typename TChar, typename TCharTraits, typename TAllocator >
auto String< TChar, TCharTraits, TAllocator >::clamp() -> String & {
	auto const old_capacity = m_get_capacity();
	auto const size = m_get_size();
	auto const new_capacity = m_align_size(size + 1);
	if (new_capacity < old_capacity) {
		auto const old_pointer = m_get_pointer();
		Pointer new_pointer;
		try {
			new_pointer = AllocatorTraits::allocate(m_allocator(), new_capacity);
		} catch (...) {
			return;
		}
		CharTraits::copy(&*new_pointer, &*old_pointer, size + 1);
		m_set_pointer(new_pointer);
		m_set_capacity(new_capacity);
	}
	return *this;
}

template< typename TChar, typename TCharTraits, typename TAllocator >
auto String< TChar, TCharTraits, TAllocator >::append(String const & string, Size position, Size count) -> String & {
	auto const size = string.size();
	if (position > size) {
		throw OutOfRangeException("String");
	}
	return append(string.data() + position, min(count, size - position));
}

template< typename TChar, typename TCharTraits, typename TAllocator >
auto String< TChar, TCharTraits, TAllocator >::append(CString<Char> string, Size count) -> String & {
	BR_ASSERT(string != nullptr || count == 0);
	auto const capacity = m_get_capacity();
	auto const old_size = m_get_size();
	if (capacity - old_size >= count) {
		if (count != 0) {
			auto const pointer = m_get_pointer();
			auto const new_size = old_size + count;
			CharTraits::copy(&*pointer + old_size, string, count);
			CharTraits::assign(pointer[new_size], Char());
			m_set_size(new_size);
		}
	} else {
		m_grow_and_replace(capacity, old_size + count - capacity, old_size, old_size, 0, count, string);
	}
	return *this;
}

template< typename TChar, typename TCharTraits, typename TAllocator >
auto String< TChar, TCharTraits, TAllocator >::append(Char ch) -> String & {
	auto const capacity = m_get_capacity();
	auto const old_size = m_get_size();
	auto const new_size = old_size + 1;
	if (new_size == capacity) {
		m_grow(old_size, 1, size, size, 0);
	}
	auto pointer = &*m_get_pointer() + old_size;
	CharTraits::assign(*pointer, ch);
	CharTraits::assign(*++pointer, Char());
	m_set_size(new_size);
}

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::append(TInputIterator first, TInputIterator last) -> EnableIf< BooleanAnd< IsInputIterator<TInputIterator>, NotForwardIterator<TInputIterator> >, String & > {
	for (; first != last; ++first) {
		append(*first);
	}
	return *this;
}

template< typename TChar, typename TCharTraits, typename TAllocator >
template< typename TInputIterator >
auto String< TChar, TCharTraits, TAllocator >::append(TInputIterator first, TInputIterator last) -> EnableIf< IsForwardIterator<TInputIterator>, String & > {
	auto const size = m_get_size();
	auto const capacity = m_get_capacity();
	auto const count = static_cast<Size>(distance(first, last));
	if (count != 0) {
		if (capacity - size < count) {
			m_grow(capacity, size + count - capacity, size, size, 0);
		}
		auto pointer = &*m_get_pointer() + size;
		for (; first != last; ++pointer, ++first) {
			CharTraits::assign(*pointer, *first);
		}
		CharTraits::assign(*pointer, Char());
		m_set_size(size + count);
	}
	return *this;
}

} // namespace BR