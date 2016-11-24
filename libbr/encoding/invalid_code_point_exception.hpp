/**
 * @file
 * @brief 无效码位异常
 * @author Bromine0x23
 * @since 1.0
 */
#pragma once

#include <libbr/config.hpp>
#include <libbr/exception/argument_exception.hpp>

namespace BR {

template< typename TCodePoint >
class InvalidCodePointException : public ArgumentException {

public:
	using BaseException = ArgumentException;

	using CodePoint = TCodePoint;

	InvalidCodePointException(CString<NChar> encoding, CodePoint code) : BaseException("BR::InvalidCodePointException"), m_encoding(encoding), m_code(code) {
	};

	~InvalidCodePointException() noexcept override {
	}

	auto encoding() const -> CString<NChar> {
		return m_encoding;
	}

	auto code_point() const -> CodePoint {
		return m_code;
	}

private:
	CString<NChar> m_encoding;
	CodePoint m_code;

}; // class InvalidCodePointException

} // namespace BR

