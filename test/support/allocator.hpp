#include <cstdlib>
#include <libbr/config.hpp>
#include <libbr/iterator/basic_iterator.hpp>
#include <libbr/iterator/category.hpp>
#include <libbr/memory/address_of.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_const.hpp>

template< typename TElement >
class BareAllocator {
public:
	using Element = TElement;

	BareAllocator() noexcept {
	}

	template< typename TOtherElement >
	BareAllocator(BareAllocator<TOtherElement>) noexcept {
	}

	auto allocate(BR::Size n) -> Element * {
		return static_cast< Element * >(::operator new(n * sizeof(Element)));
	}

	void deallocate(Element * p, BR::Size) {
		return ::operator delete(static_cast<void *>(p));
	}

	auto operator==(BareAllocator) -> bool {
		return true;
	}

	auto operator!=(BareAllocator y) -> bool  {
		return !operator==(y);
	}
};

template< typename TElement >
class SimpleAllocator;

template< typename TElement >
class SimplePointer;

template<>
class SimplePointer<void> {
public:
	template< typename TOtherElement >
	friend class SimplePointer;

	SimplePointer() noexcept = default;
	SimplePointer(BR::NullPointer) noexcept : m_pointer(nullptr) {
	}

	template< typename TElement, typename = BR::EnableIf< BR::NotConst<TElement> > >
	SimplePointer(SimplePointer<TElement> p) noexcept : m_pointer(p.m_pointer) {
	}

	explicit operator bool() const {
		return m_pointer != nullptr;
	}

	auto operator==(SimplePointer y) -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(SimplePointer y) -> bool {
		return !operator==(y);
	}
private:
	void * m_pointer;
};

template<>
class SimplePointer<void const> {
public:
	template< typename TOtherElement >
	friend class SimplePointer;

	SimplePointer() noexcept = default;
	SimplePointer(BR::NullPointer) noexcept : m_pointer(nullptr) {
	}

	template< typename TElement >
	SimplePointer(SimplePointer<TElement> p) noexcept : m_pointer(p.m_pointer) {
	}

	explicit operator bool() const {
		return m_pointer != nullptr;
	}

	auto operator==(SimplePointer y) -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(SimplePointer y) -> bool {
		return !operator==(y);
	}
private:
	void const * m_pointer;
};

template< typename TElement >
class SimplePointer : public BR::BasicIterator {
public:
	using Element   = TElement;
	using Reference = Element &;
	using Pointer   = Element *;
	using Difference = BR::PointerDifference;
	struct Category : public BR::IteratorTag, public BR::ReadableTag, public BR::WritableTag, public BR::RandomAccessTraversalTag {
	};

	template< typename TOtherElement >
	friend class SimplePointer;

	template< typename TOtherElement >
	friend class SimpleAllocator;

public:
	SimplePointer() noexcept = default;

	SimplePointer(BR::NullPointer) noexcept : m_pointer(nullptr) {
	}

	explicit SimplePointer(SimplePointer<void> p) noexcept : m_pointer(static_cast< Element * >(p.m_pointer)) {
	}

	explicit operator bool() const {
		return m_pointer != nullptr;
	}

	auto operator*() const -> Reference {
		return *m_pointer;
	}

	auto operator->() const -> Pointer {
		return m_pointer;
	}

	auto operator++() -> SimplePointer & {
		++m_pointer;
		return *this;
	}
	auto operator++(int) -> SimplePointer {
		SimplePointer tmp(*this);
		++m_pointer;
		return tmp;
	}

	auto operator--() -> SimplePointer & {
		--m_pointer;
		return *this;
	}

	auto operator--(int) -> SimplePointer {
		SimplePointer tmp(*this);
		--m_pointer;
		return tmp;
	}

	auto operator+=(Difference n) -> SimplePointer & {
		m_pointer += n;
		return *this;
	}

	auto operator-=(Difference n) -> SimplePointer & {
		m_pointer -= n;
		return *this;
	}

	auto operator+(Difference n) const -> SimplePointer {
		SimplePointer tmp(*this);
		tmp += n;
		return tmp;
	}

	auto operator-(Difference n) const -> SimplePointer {
		SimplePointer tmp(*this);
		tmp -= n;
		return tmp;
	}

	auto operator-(SimplePointer y) const -> Difference {
		return m_pointer - y.m_pointer;
	}

	auto operator[](Difference n) const -> Reference {
		return m_pointer[n];
	}

	auto operator==(SimplePointer y) -> bool {
		return m_pointer == y.m_pointer;
	}

	auto operator!=(SimplePointer y) -> bool {
		return !operator==(y);
	}

	auto operator<(SimplePointer y) -> bool {
		return m_pointer < y.m_pointer;
	}

	auto operator>(SimplePointer y) -> bool {
		return y < *this;
	}

	auto operator<=(SimplePointer y) -> bool {
		return !(y < *this);
	}

	auto operator>=(SimplePointer y) -> bool {
		return !operator<(y);
	}

	static auto make_pointer(Element & e) -> SimplePointer {
		return SimplePointer(BR::address_of(e));
	}

private:
	explicit SimplePointer(Element * p) noexcept : m_pointer(p) {
	}

private:
	Element * m_pointer;
};

template< typename TElement >
class SimpleAllocator {
public:
	using Element = TElement;

	using Pointer = SimplePointer<Element>;

	SimpleAllocator() = default;

	template< typename TOtherElement >
	SimpleAllocator(SimpleAllocator<TOtherElement>) {
	}

	auto allocate(BR::PointerDifference n) -> Pointer {
		return Pointer(static_cast< Element * >(::operator new(n * sizeof(Element))));
	}

	void deallocate(Pointer p, BR::PointerDifference) {
		return ::operator delete(p.m_pointer);
	}

	auto operator==(SimpleAllocator) -> bool {
		return true;
	}

	auto operator!=(SimpleAllocator y) -> bool  {
		return !operator==(y);
	}
};