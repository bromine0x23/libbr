/**
 * @file
 * @brief UniquePointer
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/assert/assert.hpp>
#include <libbr/functional/less.hpp>
#include <libbr/memory/default_deleter.hpp>
#include <libbr/memory/detail/unique_pointer_storage.hpp>
#include <libbr/memory/detail/unique_pointer_traits.hpp>
#include <libbr/operators/equality_comparable.hpp>
#include <libbr/operators/less_than_comparable.hpp>
#include <libbr/operators/template_equality_comparable.hpp>
#include <libbr/operators/template_less_than_comparable.hpp>
#include <libbr/type_traits/add_lvalue_reference.hpp>
#include <libbr/type_traits/boolean.hpp>
#include <libbr/type_traits/conditional.hpp>
#include <libbr/type_traits/enable_if.hpp>
#include <libbr/type_traits/is_array.hpp>
#include <libbr/type_traits/is_assignable.hpp>
#include <libbr/type_traits/is_convertible.hpp>
#include <libbr/type_traits/is_reference.hpp>
#include <libbr/type_traits/is_same.hpp>
#include <libbr/type_traits/remove_extent.hpp>
#include <libbr/type_traits/remove_pointer.hpp>
#include <libbr/type_traits/remove_reference.hpp>
#include <libbr/utility/forward.hpp>
#include <libbr/utility/move.hpp>
#include <libbr/utility/swap.hpp>

namespace BR {

inline namespace Memory {

/**
 * @brief Smart pointer with unique object ownership semantics.
 * @tparam TElement The type of the object managed by this UniquePointer.
 * @tparam TDeleter The function object or lvalue reference to function or to function object, to be called from the destructor.
 */
template< typename TElement, typename TDeleter = DefaultDeleter<TElement> >
class UniquePointer;

/**
 * @brief Creates a unique pointer that manages a new object.
 *
 * Constructs a non-array type TElement. The arguments args are passed to the constructor of TElement.
 * This overload only participates in overload resolution if TElement is not an array type.
 * @tparam TElement The type of the object managed by UniquePointer.
 * @tparam TArgs Type of \p args.
 * @param args List of arguments with which an instance of T will be constructed.
 * @return UniquePointer of an instance of type TElement.
 */
template< typename TElement, typename... TArgs >
inline auto make_unique_pointer(TArgs &&... args) -> EnableIf< NotArray<TElement>, UniquePointer<TElement> > {
	return UniquePointer<TElement>(new TElement(forward<TArgs>(args)...));
}

/**
 * @brief Creates a unique pointer that manages a new object.
 *
 * Constructs an array of unknown bound TElement.
 * This overload only participates in overload resolution if TElement is an array of unknown bound
 * @tparam TElement The type of the object managed by UniquePointer.
 * @param count The size of the array to construct.
 * @return UniquePointer of an instance of type TElement.
 */
template< typename TElement >
inline auto make_unique_pointer(Size count) -> EnableIf< IsArrayUnknownBounds<TElement>, UniquePointer<TElement> > {
	return UniquePointer<TElement>(new RemoveExtent<TElement>[count]());
}

template< typename TElement, typename... TArgs >
inline auto make_unique_pointer(TArgs &&... args) -> EnableIf< IsArrayKnownBounds<TElement> > = delete;

/**
 * swap for UniquePointer
 * @tparam TElement
 * @tparam TDeleter
 * @param x
 * @param y
 */
template< typename TElement, typename TDeleter >
inline void swap(UniquePointer< TElement, TDeleter > & x, UniquePointer< TElement, TDeleter > & y) noexcept {
	x.swap(y);
}

} // namespace Memory



inline namespace Memory {

template< typename TElement, typename TDeleter >
class UniquePointer :
	public TemplateEqualityComparable< UniquePointer< TElement, TDeleter >, UniquePointer >,
	public TemplateLessThanComparable< UniquePointer< TElement, TDeleter >, UniquePointer >,
	public EqualityComparable< UniquePointer< TElement, TDeleter >, NullPointer >,
	public LessThanComparable< UniquePointer< TElement, TDeleter >, NullPointer >
{

public:
	using Element = TElement;

	using Deleter = TDeleter;

	using Pointer = Detail::Memory::UniquePointer::Pointer< Element, RemoveReference<Deleter> >;

private:
	template< typename TOtherElement, typename TOtherDeleter >
	using IsOtherCompatible = BooleanAnd<
		NotArray<TOtherElement>,
		IsConvertible< typename UniquePointer< TOtherElement, TOtherDeleter >::Pointer, Pointer >,
		Conditional< IsReference<Deleter>, IsSame< TOtherDeleter, Deleter >, IsConvertible< TOtherDeleter, Deleter > >
	>;

public:
	/**
	 * @brief Default constructor, constructs UniquePointer that owns nothing.
	 */
	constexpr UniquePointer() noexcept : m_storage() {
		static_assert(NotPointer<Deleter>{}, "Constructed with null function pointer deleter.");
	}

	/**
	 * @brief Constructs UniquePointer that owns nothing.
	 */
	constexpr UniquePointer(NullPointer) noexcept : m_storage() {
		static_assert(NotPointer<Deleter>{}, "Constructed with null function pointer deleter.");
	}

	/**
	 * @brief Constructs a UniquePointer which owns \p pointer.
	 *
	 * Initializing the stored pointer with \p pointer and value-initializing the stored deleter.
	 * @param pointer A pointer to an object to manage.
	 */
	explicit UniquePointer(
		Pointer pointer
	) noexcept : m_storage(move(pointer)) {
		static_assert(NotPointer<Deleter>{}, "Constructed with null function pointer deleter.");
	}

	/**
	 * @brief Constructs a UniquePointer which owns \p pointer with a deleter \p deleter.
	 *
	 * Initializing the stored pointer with \p pointer and initializing a deleter \p deleter.
	 * @param pointer A pointer to an object to manage.
	 * @param deleter A deleter to use to destroy the object.
	 */
	UniquePointer(
		Pointer pointer,
		Detail::Memory::UniquePointer::DeleterLValue<Deleter> deleter
	) noexcept : m_storage(move(pointer), deleter) {
	}

	/**
	 * @brief Constructs a UniquePointer which owns \p pointer with a deleter \p deleter.
	 *
	 * Initializing the stored pointer with \p pointer and initializing a deleter \p deleter.
	 * @param pointer A pointer to an object to manage.
	 * @param deleter A deleter to use to destroy the object.
	 */
	UniquePointer(
		Pointer pointer,
		Detail::Memory::UniquePointer::DeleterRValue<Deleter> deleter
	) noexcept : m_storage(move(pointer), move(deleter)) {
		static_assert(NotReference<TDeleter>{}, "Rvalue deleter bound to reference.");
	}

	/**
	 * @brief Constructs a UniquePointer by transferring ownership from \p pointer to *this.
	 * @param other Another smart pointer to acquire the ownership from.
	 */
	UniquePointer(UniquePointer && other) noexcept : m_storage(other.release(), forward<Deleter>(other.deleter())) {
	}

	/**
	 * @brief Constructs a UniquePointer by transferring ownership from \p pointer to *this, where \p pointer is constructed with a specified deleter.
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param other Another smart pointer to acquire the ownership from.
	 */
	template< typename TOtherElement, typename TOtherDeleter, typename = EnableIf< IsOtherCompatible< TOtherElement, TOtherDeleter > > >
	UniquePointer(
		UniquePointer< TOtherElement, TOtherDeleter > && other
	) noexcept : m_storage(other.release(), forward<TOtherDeleter>(other.deleter())) {
	}

	~UniquePointer() {
		reset();
	}

	/**
	 * @brief Transfers ownership from \p pointer to *this as if by calling reset(pointer.release()) followed by an assignment of deleter() from forward<Deleter>(pointer.deleter()).
	 * @param other Smart pointer from which ownership will be transferred.
	 * @return *this
	 */
	auto operator=(UniquePointer && other) noexcept -> UniquePointer & {
		reset(other.release());
		deleter() = forward<Deleter>(other.deleter());
		return *this;
	}

	/**
	 * @brief Effectively the same as calling reset().
	 * @return *this
	 */
	auto operator=(NullPointer) noexcept -> UniquePointer & {
		reset();
		return *this;
	}

	/**
	 * @brief Transfers ownership from \p pointer to *this as if by calling reset(pointer.release()) followed by an assignment of deleter() from forward<TOtherDeleter>(pointer.deleter()).
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param pointer Smart pointer from which ownership will be transferred.
	 * @return *this
	 */
	template< typename TOtherElement, typename TOtherDeleter >
	auto operator=(
		UniquePointer< TOtherElement, TOtherDeleter > && pointer
	) noexcept -> EnableIf< BooleanAnd< IsOtherCompatible< TOtherElement, TOtherDeleter >, IsAssignable< Deleter &, TOtherDeleter && > >, UniquePointer & > {
		reset(pointer.release());
		deleter() = forward<TOtherDeleter>(pointer.deleter());
		return *this;
	}

	/**
	 * @brief Dereferences pointer to the managed object。
	 * @return Returns the object owned by *this, equivalent to *get().
	 */
	auto operator*() const -> AddLValueReference<Element> {
		return *m_storage.pointer();
	}

	/**
	 * @brief Dereferences pointer to the managed object。
	 * @return Returns a pointer to the object owned by *this, i.e. get().
	 */
	auto operator->() const noexcept -> Pointer {
		return m_storage.pointer();
	}

	/**
	 * @brief Returns a pointer to the managed object or nullptr if no object is owned.
	 * @return Pointer to the managed object or nullptr if no object is owned.
	 */
	auto get() const noexcept -> Pointer {
		return m_storage.pointer();
	}

	/**
	 * @brief Returns the deleter that is used for destruction of the managed object.
	 * @return The stored deleter object.
	 */
	auto deleter() noexcept -> Deleter & {
		return m_storage.deleter();
	}

	/**
	 * @brief Returns the deleter that is used for destruction of the managed object.
	 * @return The stored deleter object.
	 */
	auto deleter() const noexcept -> Deleter const & {
		return m_storage.deleter();
	}

	/**
	 * @brief Checks if there is an associated managed object.
	 * @retval true *this owns an object.
	 * @retval false Otherwise.
	 */
	explicit operator bool() const noexcept {
		return m_storage.pointer() == Pointer() ? false : true;
	}

	/**
	 * @brief Releases the ownership of the managed object if any. get() returns nullptr after the call.
	 * @return Pointer to the managed object or nullptr if there was no managed object, i.e. the value which would be returned by get() before the call.
	 */
	auto release() noexcept -> Pointer {
		auto hold = get();
		m_storage.pointer() = Pointer();
		return hold;
	}

	/**
	 * @brief Replaces the managed object.
	 * @param pointer pointer to a new object to manage.
	 */
	void reset(Pointer pointer = Pointer()) noexcept {
		auto hold = m_storage.pointer();
		m_storage.pointer() = pointer;
		if (hold != nullptr) {
			deleter()(hold);
		}
	}

	/**
	 * @brief Swaps the managed objects.
	 * @param other Another UniquePointer object to swap the managed object and the deleter with.
	 */
	void swap(UniquePointer & other) noexcept {
		m_storage.swap(other.m_storage);
	}

	/**
	 * @brief Compares to another UniquePointer.
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param y The other UniquePointer to compare.
	 * @return get() == y.get()
	*/
	template< typename TOtherElement, typename TOtherDeleter >
	auto operator==(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> Boolean {
		return get() == y.get();
	}

	/**
	 * @brief Compares to another UniquePointer.
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param y The other UniquePointer to compare.
	 * @return Less<>()(x.get(), y.get())
	*/
	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> Boolean {
		return Less<>()(get(), y.get());
	}

	/**
	 * @brief Compares with nullptr.
	 * @return !operator bool()
	*/
	auto operator==(NullPointer) const -> Boolean {
		return !operator bool();
	}

	/**
	 * @brief Compares with nullptr.
	 * @return Less<UniquePointer>()(get(), nullptr)
	*/
	auto operator<(NullPointer) const -> Boolean {
		return Less<Pointer>()(get(), nullptr);
	}

	/**
	 * @brief Compares with nullptr.
	 * @return Less<UniquePointer>()(nullptr, get())
	*/
	auto operator>(NullPointer) const -> Boolean {
		return Less<Pointer>()(nullptr, get());
	}

private:
	Detail::Memory::UniquePointer::Storage< Pointer, Deleter > m_storage;

}; // class UniquePointer< TPointer, TDeleter >

template< typename TElement, typename TDeleter >
class UniquePointer< TElement[], TDeleter > :
	public TemplateEqualityComparable< UniquePointer< TElement[], TDeleter >, UniquePointer >,
	public TemplateLessThanComparable< UniquePointer< TElement[], TDeleter >, UniquePointer >,
	public EqualityComparable< UniquePointer< TElement[], TDeleter >, NullPointer >,
	public LessThanComparable< UniquePointer< TElement[], TDeleter >, NullPointer >
{

public:
	using Element = TElement;

	using Deleter = TDeleter;

	using Pointer = Detail::Memory::UniquePointer::Pointer< Element, RemoveReference<Deleter> >;

private:
	template< typename TOtherElement, typename TOtherDeleter >
	using IsOtherCompatible = BooleanAnd<
		IsArray<TOtherElement>,
		IsSame< Pointer, Element * >,
		IsSame< typename UniquePointer< TOtherElement, TOtherDeleter >::Pointer, typename UniquePointer< TOtherElement, TOtherDeleter >::Element * >,
		IsConvertible< typename UniquePointer< TOtherElement, TOtherDeleter >::Element(*)[], Element(*)[]>,
		Conditional< IsReference<Deleter>, IsSame< TOtherDeleter, Deleter >, IsConvertible< TOtherDeleter, Deleter > >
	>;

	template< typename TOtherPointer >
	using IsPointerCompatible = BooleanOr<
		BooleanOr<
			IsSame< TOtherPointer, Pointer >,
			IsSame< TOtherPointer, NullPointer >
		>,
		BooleanAnd<
			IsSame< Pointer, Element * >,
			IsPointer<TOtherPointer>,
			IsConvertible< RemovePointer<TOtherPointer>(*)[], Element(*)[] >
		>
	>;

	template< typename TOtherPointer >
	using IsResetCompatible = BooleanOr<
		IsSame< TOtherPointer, Pointer >,
		BooleanAnd<
			IsSame< Pointer, Element * >,
			IsPointer<TOtherPointer>,
			IsConvertible< TOtherPointer, Pointer >
		>
	>;

public:
	/**
	 * @brief Default constructor, constructs UniquePointer that owns nothing.
	 */
	constexpr UniquePointer() noexcept : m_storage() {
		static_assert(NotPointer<TDeleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	/**
	 * @brief Constructs UniquePointer that owns nothing.
	 */
	constexpr UniquePointer(NullPointer) noexcept : m_storage() {
		static_assert(NotPointer<TDeleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	/**
	 * @brief Constructs a UniquePointer which owns \p pointer.
	 *
	 * Initializing the stored pointer with \p pointer and value-initializing the stored deleter.
	 * @param pointer A pointer to an object to manage.
	 */
	explicit UniquePointer(Pointer pointer) noexcept : m_storage(move(pointer)) {
		static_assert(NotPointer<TDeleter>(), "UniquePointer constructed with null function pointer deleter");
	}

	/**
	 * @brief Constructs a UniquePointer which owns \p pointer with a deleter \p deleter.
	 *
	 * Initializing the stored pointer with \p pointer and initializing a deleter \p deleter.
	 * @tparam TOtherPointer The type of \p pointer.
	 * @param pointer A pointer to an object to manage.
	 * @param deleter A deleter to use to destroy the object.
	 */
	template< typename TOtherPointer, typename = EnableIf< IsPointerCompatible< TOtherPointer > > >
	UniquePointer(
		TOtherPointer pointer,
		Detail::Memory::UniquePointer::DeleterLValue<Deleter> deleter
	) noexcept : m_storage(pointer, deleter) {
	}

	/**
	 * @brief Constructs a UniquePointer which owns \p pointer with a deleter \p deleter.
	 *
	 * Initializing the stored pointer with \p pointer and initializing a deleter \p deleter.
	 * @tparam TOtherPointer The type of \p pointer.
	 * @param pointer A pointer to an object to manage.
	 * @param deleter A deleter to use to destroy the object.
	 */
	template< typename TOtherPointer, typename = EnableIf< IsPointerCompatible<TOtherPointer> > >
	UniquePointer(
		TOtherPointer pointer,
		Detail::Memory::UniquePointer::DeleterRValue<Deleter> deleter
	) noexcept : m_storage(pointer, move(deleter)) {
		static_assert(NotReference<TDeleter>(), "rvalue deleter bound to reference");
	}

	/**
	 * @brief Constructs a UniquePointer by transferring ownership from \p pointer to *this.
	 * @param other Another smart pointer to acquire the ownership from.
	 */
	UniquePointer(UniquePointer && other) noexcept : m_storage(other.release(), forward<Deleter>(other.deleter())) {
	}

	/**
	 * @brief Constructs a UniquePointer by transferring ownership from \p pointer to *this, where \p pointer is constructed with a specified deleter.
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param other Another smart pointer to acquire the ownership from.
	 */
	template< typename TOtherElement, typename TOtherDeleter, typename = EnableIf< IsOtherCompatible< TOtherElement, TOtherDeleter > > >
	UniquePointer(
		UniquePointer< TOtherElement, TOtherDeleter > && other
	) noexcept : m_storage(other.release(), forward<TOtherDeleter>(other.deleter())) {
	}

	~UniquePointer() {
		reset();
	}

	/**
	 * @brief Transfers ownership from \p pointer to *this as if by calling reset(pointer.release()) followed by an assignment of deleter() from forward<Deleter>(pointer.deleter()).
	 * @param other Smart pointer from which ownership will be transferred.
	 * @return *this
	 */
	auto operator=(UniquePointer && other) noexcept -> UniquePointer & {
		reset(other.release());
		deleter() = forward<Deleter>(other.deleter());
		return *this;
	}

	/**
	 * @brief Effectively the same as calling reset().
	 * @return *this
	 */
	auto operator=(NullPointer) noexcept -> UniquePointer & {
		reset();
		return *this;
	}

	/**
	 * @brief Transfers ownership from \p pointer to *this as if by calling reset(pointer.release()) followed by an assignment of deleter() from forward<TOtherDeleter>(pointer.deleter()).
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param pointer Smart pointer from which ownership will be transferred.
	 * @return *this
	 */
	template< typename TOtherElement, typename TOtherDeleter >
	auto operator=(
		UniquePointer< TOtherElement, TOtherDeleter > && other
	) noexcept -> EnableIf< BooleanAnd< IsOtherCompatible< TOtherElement, TOtherDeleter >, IsAssignable< Deleter &, TOtherDeleter && > >, UniquePointer & > {
		reset(other.release());
		deleter() = forward<Deleter>(other.deleter());
		return *this;
	}

	/**
	 * @brief Provides indexed access to the managed array.
	 * @param index The index of the element to be returned.
	 * @return The element at index i, i.e. get()[i].
	 */
	auto operator[](Size index) const -> AddLValueReference<Element> {
		return m_storage.pointer()[index];
	}

	/**
	 * @brief Returns a pointer to the managed object or nullptr if no object is owned.
	 * @return Pointer to the managed object or nullptr if no object is owned.
	 */
	auto get() const noexcept -> Pointer {
		return m_storage.pointer();
	}

	/**
	 * @brief Returns the deleter that is used for destruction of the managed object.
	 * @return The stored deleter object.
	 */
	auto deleter() noexcept -> Deleter & {
		return m_storage.deleter();
	}

	/**
	 * @brief Returns the deleter that is used for destruction of the managed object.
	 * @return The stored deleter object.
	 */
	auto deleter() const noexcept -> Deleter const & {
		return m_storage.deleter();
	}

	/**
	 * @brief Checks if there is an associated managed object.
	 * @retval true *this owns an object.
	 * @retval false Otherwise.
	 */
	explicit operator bool() const noexcept {
		return m_storage.pointer() == Pointer() ? false : true;
	}

	/**
	 * @brief Releases the ownership of the managed object if any. get() returns nullptr after the call.
	 * @return Pointer to the managed object or nullptr if there was no managed object, i.e. the value which would be returned by get() before the call.
	 */
	auto release() noexcept -> Pointer {
		auto hold = get();
		m_storage.pointer() = Pointer();
		return hold;
	}

	/**
	 * @brief Replaces the managed object.
	 * @tparam TOtherPointer The type of \p pointer.
	 * @param pointer Pointer to a new object to manage.
	 * @return Pointer to a new object to manage.
	 */
	template< typename TOtherPointer >
	auto reset(TOtherPointer pointer) noexcept -> EnableIf< IsResetCompatible<TOtherPointer> > {
		auto hold = m_storage.pointer();
		m_storage.pointer() = pointer;
		if (hold != nullptr) {
			deleter()(hold);
		}
	}

	/**
	 * @biref Equivalent to reset(Pointer()).
	 */
	void reset(NullPointer = nullptr) noexcept {
		reset(Pointer());
	}

	/**
	 * @brief Swaps the managed objects.
	 * @param other Another UniquePointer object to swap the managed object and the deleter with.
	 */
	void swap(UniquePointer & other) noexcept {
		m_storage.swap(other.m_storage);
	}

	/**
	 * @brief Compares to another UniquePointer.
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param y The other UniquePointer to compare.
	 * @return get() == y.get()
	*/
	template< typename TOtherElement, typename TOtherDeleter >
	auto operator==(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> Boolean {
		return get() == y.get();
	}

	/**
	 * @brief Compares to another UniquePointer.
	 * @tparam TOtherElement,TOtherDeleter Template parameter of the other UniquePointer.
	 * @param y The other UniquePointer to compare.
	 * @return Less<>()(x.get(), y.get())
	*/
	template< typename TOtherElement, typename TOtherDeleter >
	auto operator<(UniquePointer< TOtherElement, TOtherDeleter > const & y) const -> Boolean {
		return Less<>()(get(), y.get());
	}

	/**
	 * @brief Compares with nullptr.
	 * @return !operator bool()
	*/
	auto operator==(NullPointer) const -> Boolean {
		return !operator bool();
	}

	/**
	 * @brief Compares with nullptr.
	 * @return Less<UniquePointer>()(get(), nullptr)
	*/
	auto operator<(NullPointer) const -> Boolean {
		return Less<Pointer>()(get(), nullptr);
	}

	/**
	 * @brief Compares with nullptr.
	 * @return Less<UniquePointer>()(nullptr, get())
	*/
	auto operator>(NullPointer) const -> Boolean {
		return Less<Pointer>()(nullptr, get());
	}

private:
	Detail::Memory::UniquePointer::Storage< Pointer, Deleter > m_storage;

}; // class UniquePointer< TElement[], TDeleter >

} // namespace Memory

} // namespace BR