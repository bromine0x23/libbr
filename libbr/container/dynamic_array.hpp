/**
 * @file
 * @brief DynamicArray
 * @author Bromine0x23
 * @since 2016/5/1
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/algorithm/copy.hpp>
#include <libbr/algorithm/min.hpp>
#include <libbr/algorithm/fill_n.hpp>
#include <libbr/container/initializer_list.hpp>
#include <libbr/container/tuple.hpp>
#include <libbr/exception/throw.hpp>
#include <libbr/iterator/advance.hpp>
#include <libbr/iterator/distance.hpp>
#include <libbr/iterator/move_iterator.hpp>
#include <libbr/iterator/reverse_iterator.hpp>
#include <libbr/memory/allocator.hpp>
#include <libbr/memory/allocator_traits.hpp>
#include <libbr/memory/construct_backward.hpp>
#include <libbr/memory/pointer_traits.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/has_nothrow_default_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_constructor.hpp>
#include <libbr/type_traits/has_nothrow_move_assignment.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/utility/boolean_constant.hpp>
#include <libbr/utility/move.hpp>

namespace BR {

/**
 * @brief 动态数组
 * @tparam TElement 数组元素类型
 */
template< typename TElement, typename TAllocator = Allocator<TElement> >
class DynamicArray;

template< typename TElement, typename TAllocator >
inline void swap(DynamicArray< TElement, TAllocator> & x, DynamicArray< TElement, TAllocator > & y) noexcept(noexcept(x.swap(y)))  {
	x.swap(y);
}



namespace Detail {
namespace Container {
namespace DynamicArray {

template< typename TElement, typename TAllocator >
class Base {

protected:
	using Element = TElement;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits<TAllocator>;

	using Reference = Element &;

	using ConstReference = Element const &;

	using Size = typename AllocatorTraits ::Size;

	using Difference = typename AllocatorTraits ::Difference;

	using Pointer = typename AllocatorTraits ::Pointer;

	using ConstPointer = typename AllocatorTraits ::ConstPointer;

	using Iterator = Pointer;

	using ConstIterator = ConstPointer;

protected:
	Base() noexcept(HasNothrowDefaultConstructor<Allocator>{}) : m_imp(nullptr, nullptr, nullptr) {
	}

	Base(Allocator const & allocator) : m_imp(nullptr, nullptr, nullptr, allocator) {
	}

	~Base() {
		if (m_storage_begin() != nullptr) {
			m_clear();
			AllocatorTraits::deallocate(m_allocator(), m_begin(), m_capacity());
		}
	}

	auto m_storage_begin() noexcept -> Pointer & {
		return m_imp.get<0>();
	}

	auto m_storage_begin() const noexcept -> Pointer const & {
		return m_imp.get<0>();
	}

	auto m_begin() noexcept -> Pointer & {
		return m_storage_begin();
	}

	auto m_begin() const noexcept -> Pointer const & {
		return m_storage_begin();
	}

	auto m_end() noexcept -> Pointer & {
		return m_imp.get<1>();
	}

	auto m_end() const noexcept -> Pointer const & {
		return m_imp.get<1>();
	}

	auto m_storage_end() noexcept -> Pointer & {
		return m_imp.get<2>();
	}

	auto m_storage_end() const noexcept -> Pointer const & {
		return m_imp.get<2>();
	}

	auto m_allocator() noexcept -> Allocator & {
		return m_imp.get<Allocator>();
	}

	auto m_allocator() const noexcept -> Allocator const & {
		return m_imp.get<Allocator>();
	}

	void m_clear() noexcept {
		m_destruct_at_end(m_begin());
	}

	auto m_capacity() const noexcept -> Size {
		return static_cast<Size>(m_storage_end() - m_storage_begin());
	}

	void m_copy_assign_allocator(Base const & array) {
		m_copy_assign_allocator(array, typename NodeAllocatorTraits::IsPropagateOnContainerCopyAssignment{});
	}

	void m_move_assign_allocator(Base & array) noexcept(
		BooleanOr<
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment >,
			HasNothrowMoveAssignment<Allocator>
		>{}
	) {
		m_move_assign_allocator(array, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment{});
	}

	void m_destruct_at_end(Pointer new_end) noexcept {
		m_destruct_at_end(new_end, HasTrivialDestructor<Element>{});
	}

	static void m_swap_allocator(Allocator & x, Allocator & y) noexcept(
		BooleanOr<
			BooleanNot< typename AllocatorTraits::IsPropagateOnContainerSwap >,
			IsNothrowSwappable<Allocator>
	>{}
	) {
		m_swap_allocator(x, y, typename AllocatorTraits::IsPropagateOnContainerSwap{});
	}

private:
	void m_copy_assign_allocator(Base const & array, BooleanTrue) {
		if (m_allocator() != array.m_allocator()) {
			clear();
			AllocatorTraits::deallocate(m_allocator(), m_storage_begin(), m_capacity());
			m_storage_begin() = m_end() = m_storage_end() = nullptr;
		}
		m_allocator() = array.m_allocator();
	}

	void m_copy_assign_allocator(Base const & array, BooleanFalse) noexcept {
	}

	void m_move_assign_allocator(Base & array, BooleanTrue) noexcept(HasNothrowMoveAssignment<NodeAllocator>{}) {
		m_allocator() = move(list.m_allocator());
	}

	void m_move_assign_allocator(Base & array, BooleanFalse) noexcept {
	}

	void m_destruct_at_end(Pointer new_end, BooleanTrue) {
		m_end() = new_end;
	}

	void m_destruct_at_end(Pointer new_end, BooleanFalse) {
		for (; new_end != end(); ) {
			AllocatorTraits::destroy(m_allocator(), PointerTraits<Pointer>::to_raw(--m_end()));
		}
	}

	static void m_swap_allocator(Allocator & x, Allocator & y, BooleanFalse) noexcept {
	}

	static void m_swap_allocator(Allocator & x, Allocator & y, BooleanTrue) noexcept(IsNothrowSwappable<Allocator>{}) {
		using BR::swap;
		swap(x, y);
	}

private:
	Tuple< Pointer, Pointer, Pointer, Allocator > m_imp;

}; // class Base< TElement, TAllocator >

template< typename TElement, typename TAllocator >
class Buffer {

protected:
	using Element = TElement;

	using Allocator = TAllocator;

	using AllocatorTraits = BR::AllocatorTraits< Allocator >;

	using Pointer = typename AllocatorTraits::Pointer;

	using PointerTraits = BR::PointerTraits<Pointer>;

	template< typename TElement, typename TAllocator >
	friend class BR::DynamicArray;

	Buffer(Buffer && buffer) noexcept(
		HasNothrowMoveConstructor<Allocator>{}
	) : m_storage_begin(buffer.m_storage_begin), m_end(buffer.m_end), m_storage_end(buffer.m_storage_end), m_allocator(buffer.m_allocator) {
		buffer.m_storage_begin = buffer.m_end = buffer.m_storage_end = nullptr;
	}

	Buffer(Size capacity, Allocator & allocator) : m_allocator(allocator) {
		m_end = m_storage_begin = capacity != 0 ? AllocatorTraits::allocate(allocator, capacity) : nullptr;
		m_storage_end = m_storage_begin + capacity;
	}

	~Buffer() {
		if (m_storage_begin != nullptr) {
			m_destruct(HasTrivialDestructor<Element>{});
			AllocatorTraits::allocate(m_allocator, m_storage_begin, static_cast<Size>(m_storage_end - m_storage_begin));
		}
	}

private:
	void m_destruct(BooleanTrue) {
		m_end = m_storage_begin;
	}

	void m_destruct_at_end(BooleanFalse);

private:
	Pointer m_storage_begin = nullptr;
	Pointer m_end = nullptr;
	Pointer m_storage_end = nullptr;
	Allocator & m_allocator;

}; // class Base< TElement, TAllocator >

template< typename TElement, typename TAllocator >
void Buffer< TElement, TAllocator >::m_destruct(BooleanFalse) {
	for (; m_storage_begin != m_end; ) {
		AllocatorTraits::destroy(m_allocator, PointerTraits::to_raw(--m_end));
	}
}

} // namespace DynamicArray
} // namespace Container
} // namespace Detail

template< typename TElement, typename TAllocator >
class DynamicArray : private Detail::Container::DynamicArray::Base< TElement, TAllocator > {

public:
	/**
	 * @brief 元素类型
	 */
	using Element = TElement;

	/**
	 * @brief 分配器类型
	 */
	using Allocator = TAllocator;

private:
	using Base = Detail::Container::DynamicArray::Base< Element, Allocator >;

public:
	/**
	 * @brief Reference
	 */
	using Reference = typename Base::Reference;

	/**
	 * @brief ConstReference
	 */
	using ConstReference = typename Base::ConstReference;

	/**
	 * @brief Pointer
	 */
	using Pointer = typename Base::Pointer;

	/**
	 * @brief ConstPointer
	 */
	using ConstPointer = typename Base::ConstPointer;

	/**
	 * @brief Difference
	 */
	using Difference = typename Base::Difference;

	/**
	 * @brief Size
	 */
	using Size = typename Base::Size;

	/**
	 * @brief Iterator
	 */
	using Iterator = typename Base::Iterator;

	/**
	 * @brief ConstIterator
	 */
	using ConstIterator = typename Base::ConstIterator;

	/**
	 * @brief ReverseIterator
	 */
	using ReverseIterator = BR::ReverseIterator<Iterator>;

	/**
	 * @brief ConstReverseIterator
	 */
	using ConstReverseIterator = BR::ReverseIterator<ConstIterator>;

	static_assert(IsSame< typename Allocator::Value, Element >{}, "`Allocator::Value` must be same type as `Element`");

private:
	using PointerTraits = BR::PointerTraits<Pointer>;

	using Buffer = Detail::Container::DynamicArray::Buffer< Element, Allocator >;


	template< typename TIterator >
	using IsInputIterator = BooleanAnd<
		IsConvertible< typename IteratorTraits<TIterator>::Category, ReadableTag >,
		IsConvertible< typename IteratorTraits<TIterator>::Category, SinglePassTraversalTag >
	>;

public:
	DynamicArray() noexcept (HasNothrowDefaultConstructor<Allocator>{}) {
	}

	explicit DynamicArray(Allocator const & allocator) noexcept : Base(allocator) {
	}

	DynamicArray(DynamicArray const & other);

	DynamicArray(DynamicArray const & other, Allocator const & allocator);

	DynamicArray(DynamicArray && other) noexcept(HasNothrowMoveConstructor<NodeAllocator>{});

	DynamicArray(DynamicArray && other, Allocator const & allocator);

	explicit DynamicArray(Size n, Allocator const & allocator = Allocator{});

	DynamicArray(ConstReference x, Size n, Allocator const & allocator = Allocator{});

	template< typename TIterator >
	DynamicArray(TIterator f, TIterator l, Allocator const & allocator = Allocator{}, EnableIf< IsInputIterator<TIterator> > * = nullptr) : Base(allocator) {
		m_construct(f, l, typename IteratorTraits<TIterator>::Category{});
	}

	DynamicArray(InitializerList<Element> l, Allocator const & allocator = Allocator{}) : DynamicArray(l.begin(), l.end(), allocator) {
	}

	~DynamicArray() = default;

	/**
	 * @name 赋值
	 */
	///@{

	/**
	 * @brief 复制运算
	 * @param[in] array 源链表
	 */
	auto operator=(DynamicArray const & array) -> DynamicArray &;

	auto operator=(DynamicArray && array) noexcept(BooleanOr< typename AllocatorTraits::IsPropagateOnContainerMoveAssignment, typename AllocatorTraits::IsAlwaysEqual >{}) -> DynamicArray & {
		m_move_assign(other, typename AllocatorTraits::IsPropagateOnContainerMoveAssignment{});
		return *this;
	};

	auto operator=(InitializerList<Element> l) -> DynamicArray & {
		return assign(l.begin(), l.end());
	}

	auto assign(Element const & x, Size n) -> DynamicArray &;

	template< typename TIterator >
	auto assign(TIterator f, TIterator l) -> EnableIf< IsInputIterator<TIterator>, DynamicArray & > {
		m_assign(f, l, typename IteratorTraits<TIterator>::Category{});
		return *this;
	}

	auto assign(InitializerList<Element> l) -> DynamicArray & {
		return assign(l.begin(), l.end());
	}
	///@}

	/**
	 * @name 成员
	 */
	///@{
	auto allocator() const noexcept -> Allocator {
		return Base::m_allocator();
	}

	auto operator[](Size index) -> Reference {
		BR_ASSERT(index < size());
		return this->m_begin()[index];
	}

	auto operator[](Size index) const -> ConstReference {
		BR_ASSERT(index < size());
		return this->m_begin()[index];
	}

	auto at(Size index) -> Reference {
		if (index >= size()) {
			throw_index_exception("DynamicArray::at(Size)");
		}
		return this->m_begin()[index];
	}

	auto at(Size index) const -> ConstReference {
		if (index >= size()) {
			throw_index_exception("DynamicArray::at(Size)");
		}
		return this->m_begin()[index];
	}

	auto front() -> Reference {
		return *this->m_begin();
	}

	auto front() const -> ConstReference {
		return *this->m_begin();
	}

	auto back() -> Reference {
		return *(this->m_end() - 1);
	}

	auto back() const -> ConstReference {
		return *(this->m_end() - 1);
	}

	auto data() noexcept -> Element * {
		return PointerTraits<Pointer>::to_raw(this->m_begin());
	}

	auto data() const noexcept -> Element const * {
		return PointerTraits<Pointer>::to_raw(this->m_begin());
	}
	///@}

	/**
	 * @name 迭代器
	 */
	///@{
	/**
	 * @brief begin
	 */
	auto begin() noexcept -> Iterator {
		return Iterator(this->m_begin());
	}

	/**
	 * @brief begin
	 */
	auto begin() const noexcept -> ConstIterator {
		return ConstIterator(this->m_begin());
	}

	/**
	 * @brief const begin
	 */
	auto cbegin() const noexcept -> ConstIterator {
		return begin();
	}

	/**
	 * @brief end
	 */
	auto end() noexcept -> Iterator {
		return Iterator(this->m_end());
	}

	/**
	 * @brief end
	 */
	auto end() const noexcept -> ConstIterator {
		return ConstIterator(this->m_end());
	}

	/**
	 * @brief const end
	 */
	auto cend() const noexcept -> ConstIterator {
		return end();
	}

	/**
	 * @brief reverse begin
	 */
	auto rbegin() noexcept -> ReverseIterator {
		return ReverseIterator(end());
	}

	/**
	 * @brief reverse begin
	 */
	auto rbegin() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(end());
	}

	/**
	 * @brief const reverse begin
	 */
	auto crbegin() const noexcept -> ConstReverseIterator {
		return rbegin();
	}

	/**
	 * @brief reverse end
	 */
	auto rend() noexcept -> ReverseIterator {
		return ReverseIterator(begin());
	}

	/**
	 * @brief reverse end
	 */
	auto rend() const noexcept -> ConstReverseIterator {
		return ConstReverseIterator(begin());
	}

	/**
	 * @brief const reverse end
	 */
	auto crend() const noexcept -> ConstReverseIterator {
		return rend();
	}
	///@}

	/**
	 * @name 容量
	 */
	///@{
	/**
	 * @brief begin
	 */
	/**
	 * @brief is empty
	 */
	auto is_empty() const noexcept -> bool {
		return this->m_begin() == this->m_end();
	}

	/**
	 * @brief size
	 */
	auto size() const noexcept -> Size {
		return static_cast<Size>(this->m_end() - this->m_begin());
	}

	auto capacity() const noexcept -> Size {
		return this->m_capacity();
	}

	/**
	 * @brief max size
	 */
	auto max_size() const noexcept -> Size {
		return min<Size>(AllocatorTraits::max_size(this->m_allocator()), IntegerTraits<Size>::max() / 2);
	}

	/**
	 * @brief 设置容量为至少 \em size
	 * @param[in] count 预留容量
	 */
	auto reserve(Size count) -> DynamicArray &;

	/**
	 * @brief 缩减容量，释放未使用的空间
	 */
	auto clamp() noexcept -> DynamicArray &;
	///@}

	/**
	 * @name 添加性操作
	 */
	///@{
	/**
	 * @brief 从参数构造对象并添加到尾部
	 */
	template< typename ... TArgs >
	auto emplace_back(TArgs && ... args) -> DynamicArray &;

	auto insert_back(Element const & x) -> DynamicArray & {
		return emplace_back(x);
	}

	auto insert_back(Element && x) -> DynamicArray & {
		return emplace_back(move(x));
	}

	template< typename ... TArgs >
	auto emplace(ConstIterator p, TArgs && ... args) -> Iterator;

	auto insert(ConstIterator p, Element const & x) -> Iterator {
		return emplace(p, x);
	}

	auto insert(ConstIterator p, Element && x) -> Iterator {
		return emplace(p, move(x));
	}

	auto insert(ConstIterator p, Element const & x, Size s) -> Iterator;

	template< typename TInputIterator >
	auto insert(ConstIterator p, TInputIterator f, TInputIterator l) -> EnableIf< IsInputIterator<TInputIterator>, TInputIterator >;

	auto insert(ConstIterator p, InitializerList<Element> l) -> Iterator {
		return insert(p, l.begin(), l.end());
	}
	///@}

	/**
	 * @name 删除操作
	 */
	///@{
	auto clear() noexcept -> DynamicArray & {
		auto old_size = size();
		m_clear();
		m_annotate_shrink(old_size);
	}

	auto erase(ConstIterator p) -> Iterator;

	auto erase(ConstIterator f, ConstIterator l) -> Iterator;

	auto erase_back() -> DynamicArray &;
	///@}

	/**
	 * @name 杂项
	 */
	///@{
	void swap(DynamicArray & other) noexcept(BooleanOr< BooleanNot< typename NodeAllocatorTraits::IsPropagateOnContainerSwap >, IsNothrowSwappable<NodeAllocator> >{});
	///@}

private:
	constexpr static auto m_new_capacity(Size new_size) noexcept -> Size {
		Size max_size = this->max_size();
		if (max_size < new_size) {
			throw_length_exception(BR_CURRENT_FUNCTION);
		}
		Size capacity = this->capacity();
		return (capacity < max_size / 2) ? max<Size>(2 * capacity, new_size) : max_size;
	}

	void m_allocate(Size n) {
		if (n > max_size()) {
			throw_length_exception();
		}
		this->m_storage_begin() = this->m_end() = AllocatorTraits::allocate(this->m_allocator(), n);
		this->m_storage_end() = this->m_storage_begin() + n;
	}

	void m_deallocate() noexcept {
		if (this->m_storage_begin() != nullptr) {
			clear();
			AllocatorTraits::deallocate(this->m_allocator(), this->m_storage_begin(), capacity());
			this->m_storage_begin() = this->m_end() = this->m_storage_end() = nullptr;
		}
	}

	template<typename TSinglePassIterator>
	void m_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag);

	template<typename TForwardIterator>
	void m_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag);

	void m_construct_at_end(Size n);

	void m_construct_at_end(Size n, ConstReference x);

	template<typename TForwardIterator>
	void m_construct_at_end(TForwardIterator first, TForwardIterator last);

	template<typename TSinglePassIterator>
	void m_assign(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag);

	template<typename TForwardIterator>
	void m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag);

	void m_move_assign(DynamicArray & other, BooleanTrue) noexcept(HasNothrowMoveAssign<Allocator>{}) {
		m_deallocate();
		m_move_assign_allocator(other);
		this->m_storage_begin() = other.m_storage_begin();
		this->m_end() = other.m_end();
		this->m_storage_end() = other.m_storage_end();
		other.m_storage_begin() = other.m_end() = other.m_storage_end() = nullptr;
	}

	void m_move_assign(DynamicArray & other, BooleanFalse) noexcept(typename AllocatorTraits::IsAlwaysEqual{}) {
		if (m_allocator() == other.m_allocator()) {
			m_move_assign(other, BooleanTrue{});
		} else {
			assign(make_move_iterator(other.begin()), make_move_iterator(other.end()));
		}
	}

	void m_reallocate(Size new_capacity);

	Pointer m_reallocate(Size new_capacity, Size reverse);

	void m_move_elements(Pointer from_begin, Pointer from_end, Pointer to_begin) {
		Pointer old_end = this->m_end();
		auto n = old_end - to_begin;
		for (auto p = from_begin + n; p < from_end; ++p, ++this->m_end()) {
			construct(m_allocator(), PointerTraits::to_raw(this->m_end()), move(*p));
		}
		move_backward(from_begin, from_end + n, old_end);
	}

}; // class DynamicArray< TElement, TAllocator >

template< typename TElement, typename TAllocator >
template<typename TSinglePassIterator>
void DynamicArray< TElement, TAllocator >::m_construct(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
	for (; first != last; ++first) {
		insert_back(*first);
	}
}

template< typename TElement, typename TAllocator >
template<typename TForwardIterator>
void DynamicArray< TElement, TAllocator >::m_construct(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	Size n = static_cast<Size>(distance(first, last));
	if (n > 0) {
		m_allocate(__n);
		m_construct_at_end(first, last, n);
	}
}

template< typename TElement, typename TAllocator >
void DynamicArray< TElement, TAllocator >::m_construct_at_end(Size n) {
	Allocator & allocator = this->m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(this->m_end()));
		++this->m_end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
void DynamicArray< TElement, TAllocator >::m_construct_at_end(Size n, ConstReference x) {
	Allocator & allocator = this->m_allocator();
	do {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(this->m_end()), x);
		++this->m_end();
		--n;
	} while (n > 0);
}

template< typename TElement, typename TAllocator >
template<typename TForwardIterator>
void DynamicArray< TElement, TAllocator >::m_construct_at_end(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	Allocator & allocator = this->m_allocator();
	for (; first != last; ++last, (void) ++this->m_end()) {
		AllocatorTraits::construct(allocator, PointerTraits::to_raw(this->m_end()), *last);
	}
}

template< typename TElement, typename TAllocator >
template<typename TSinglePassIterator>
void DynamicArray< TElement, TAllocator >::m_assign(TSinglePassIterator first, TSinglePassIterator last, SinglePassTraversalTag) {
	clear();
	for (; first != last; ++first) {
		insert_back(*first);
	}
};

template< typename TElement, typename TAllocator >
template<typename TForwardIterator>
void DynamicArray< TElement, TAllocator >::m_assign(TForwardIterator first, TForwardIterator last, ForwardTraversalTag) {
	Size new_size = static_cast<Size>(distance(first, last));
	if (capacity() < new_size) {
		m_deallocate();
		m_allocate(m_new_capacity(new_size));
		m_construct_at_end(first, last, new_size);
	} else {
		TForwardIterator mid = last;
		bool growing = false;
		if (size() < new_size) {
			growing = true;
			mid = first;
			advance(mid, size());
		}
		Pointer new_end = copy(first, mid, this->begin());
		if (growing) {
			m_construct_at_end(mid, last, new_size - size());
		} else {
			this->m_destruct_at_end(new_end);
		}
	}
}

template< typename TElement, typename TAllocator >
void DynamicArray< TElement, TAllocator >::m_reallocate(Size new_capacity) {
	Buffer buffer(new_capacity, m_allocator());
	buffer.m_end = construct_forward(this->m_allocator(), make_move_iterator_if_noexcept(this->m_begin()), make_move_iterator_if_noexcept(this->m_end()), buffer.m_end);
	swap(this->m_storage_begin(), buffer.m_storage_begin);
	swap(this->m_end(), buffer.m_end);
	swap(this->m_storage_end(), buffer.m_storage_end);
}

template< typename TElement, typename TAllocator >
void DynamicArray< TElement, TAllocator >::m_reallocate(Size new_capacity, Pointer reverse_position) {
	Buffer buffer(new_capacity, m_allocator());
	buffer.m_end = construct_forward(this->m_allocator(), make_move_iterator_if_noexcept(this->m_begin()), make_move_iterator_if_noexcept(reverse_position), buffer.m_end);
	Pointer pointer = buffer.m_end;
	++buffer.m_end;
	buffer.m_end = construct_forward(this->m_allocator(), make_move_iterator_if_noexcept(reverse_position), make_move_iterator_if_noexcept(this->m_end()), buffer.m_end);
	swap(this->m_storage_begin(), buffer.m_storage_begin);
	swap(this->m_end(), buffer.m_end);
	swap(this->m_storage_end(), buffer.m_storage_end);
	return pointer;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
void DynamicArray< TElement, TAllocator >::m_reallocate_and_emplace(Size new_capacity, Pointer position, TArgs && ... args) {
	Buffer buffer(new_capacity, m_allocator());
	buffer.m_end = construct_forward(this->m_allocator(), make_move_iterator_if_noexcept(this->m_begin()), make_move_iterator_if_noexcept(split_pointer), buffer.m_end);
	construct(this->m_allocator(), buffer.m_end, forward<TArgs>(args)...);
	++buffer.m_end;
	buffer.m_end = construct_forward(this->m_allocator(), make_move_iterator_if_noexcept(position), make_move_iterator_if_noexcept(this->m_end()), buffer.m_end);
	swap(this->m_storage_begin(), buffer.m_storage_begin);
	swap(this->m_end(), buffer.m_end);
	swap(this->m_storage_end(), buffer.m_storage_end);
}

template< typename TElement, typename TAllocator >
DynamicArray< TElement, TAllocator >::DynamicArray(DynamicArray const & other) : Base(AllocatorTraits::select_on_container_copy_construction(other.m_allocator())) {
	Size n = other.size();
	if (n > 0) {
		m_allocator(n);
		m_construct_at_end(other.begin(), other.end(), n);
	}
}

template< typename TElement, typename TAllocator >
DynamicArray< TElement, TAllocator >::DynamicArray(DynamicArray const & other, Allocator const & allocator) : Base(allocator) {
	Size n = other.size();
	if (n > 0) {
		m_allocator(n);
		m_construct_at_end(other.begin(), other.end(), n);
	}
}

template< typename TElement, typename TAllocator >
DynamicArray< TElement, TAllocator >::DynamicArray(DynamicArray && other) noexcept(HasNothrowMoveConstructor<NodeAllocator>{}) : Base(move(other.m_allocator())) {
	this->m_storage_begin() = other.m_storage_begin();
	this->m_end() = other.m_end();
	this->m_storage_end() = other.m_storage_end();
	other.m_storage_begin() = other.m_end() = other.m_storage_end() = nullptr;
}

template< typename TElement, typename TAllocator >
DynamicArray< TElement, TAllocator >::DynamicArray(DynamicArray && other, Allocator const & allocator) : Base(allocator) {
	if (m_allocator() == other.m_allocator()) {
		this->m_storage_begin() = other.m_storage_begin();
		this->m_end() = other.m_end();
		this->m_storage_end() = other.m_storage_end();
		other.m_storage_begin() = other.m_end() = other.m_storage_end() = nullptr;
	} else {
		assign(make_move_iterator(other.begin()), make_move_iterator(other.end()));
	}
}

template< typename TElement, typename TAllocator >
DynamicArray< TElement, TAllocator >::DynamicArray(Size n, Allocator const & allocator = Allocator{}) : Base(allocator) {
	if (n > 0) {
		m_allocate(n);
		m_construct_at_end(n);
	}
}

template< typename TElement, typename TAllocator >
DynamicArray< TElement, TAllocator >::DynamicArray(ConstReference x, Size n, Allocator const & allocator = Allocator{}) : Base(allocator) {
	if (n > 0) {
		m_allocate(n);
		m_construct_at_end(n, x);
	}
}

template< typename TElement, typename TAllocator >
auto DynamicArray< TElement, TAllocator >::operator=(DynamicArray const & other) -> DynamicArray & {
	if (this != &other) {
		m_copy_assignment_allocator()(other);
		assign(other.m_begin(), other.m_end());
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto DynamicArray< TElement, TAllocator >::assign(Element const & x, Size n) -> DynamicArray & {
	if (capacity() < n) {
		m_deallocate();
		m_allocate(m_new_capacity(n));
		m_construct_at_end(n, x);
	} else {
		Size s = size();
		fill_n(this->m_begin(), min(n, s), x);
		if (s < n) {
			m_construct_at_end(n - s, x);
		} else {
			this->m_destruct_at_end(this->m_begin() + n);
		}
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto DynamicArray< TElement, TAllocator >::reserve(Size new_capacity) -> DynamicArray & {
	if (capacity() < new_capacity) {
		m_reallocate(new_capacity);
	}
	return *this;
}

template< typename TElement, typename TAllocator >
auto DynamicArray< TElement, TAllocator >::clamp() noexcept -> DynamicArray & {
	if (size() < capacity()) {
#if !defined(BR_NO_EXCEPTIONS)
		try {
#endif
			m_reallocate(size());
#if !defined(BR_NO_EXCEPTIONS)
		} catch (...) {
		}
#endif
	}
}
template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto DynamicArray< TElement, TAllocator >::emplace_back(TArgs && ... args) -> DynamicArray & {
	if (!(this->m_end() < this->m_storage_end())) {
		m_reallocate(m_new_capacity(size() + 1));
	}
	AllocatorTraits::construct(this->m_allocator(), PointerTraits::to_raw(this->m_end()), forward<TArgs>(args)...);
	++this->m_end();
	return *this;
}

template< typename TElement, typename TAllocator >
template< typename ... TArgs >
auto DynamicArray< TElement, TAllocator >::emplace(ConstIterator position, TArgs && ... args) -> Iterator {
	Pointer p = this->m_begin() + (position - begin());
	if (this->m_end() < this->m_storage_end()) {
		if (p == this->m_end()) {
			++this->m_end();
		} else {
			m_move_elements(p, this->m_end(), p + 1);
		}
	} else {
		p = m_reallocate(m_new_capacity(size() + 1), p);
	}
	AllocatorTraits::construct(this->m_allocator(), PointerTraits::to_raw(p), forward<TArgs>(args)...);
	return Iterator(p);
}

template< typename TElement, typename TAllocator >
auto insert(ConstIterator p, Element const & x, Size s) -> Iterator {

};

} // namespace BR