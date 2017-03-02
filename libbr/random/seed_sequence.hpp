/**
 * @file
 * @brief
 * @since 1.0
 */
#pragma once

#include<libbr/config.hpp>
#include<libbr/container/initializer_list.hpp>

namespace BR {

inline namespace Random {

/**
 * @brief
 */
class SeedSequence {
public:
	using Result = UInt32;

public:
	SeedSequence();

	template< typename T >
	SeedSequence(InitializerList<T> list);

	template< typename TInputIterator >
	SeedSequence(TInputIterator first, TInputIterator last);
	template< typename TRandomAccessIterator >
	void generate(TRandomAccessIterator first, TRandomAccessIterator last);

	auto size() const noexcept -> Size;

	template< typename TOutputIterator >
	void parameter(TOutputIterator destination) const;

private:
	SeedSequence(SeedSequence const &) = delete;

	auto operator=(SeedSequence const & ) -> SeedSequence & = delete;

private:

}; // class SeedSequence

} // namespace Random

} // namespace BR
