#pragma once

#include "../test.hpp"
#include <libbr/config.hpp>

#if defined(BR_SKIP_TYPE_TRAITS_TEST)

#define IS_TRAITS_CHECK(...)
#define HAS_TRAITS_CHECK(...)
#define IS_TRAITS_CHECK_CV(...)
#define HAS_TRAITS_CHECK_CV(...)
#define INTEGRAL_TRAITS_CHECK(...)
#define TYPE_TRAITS_CHECK(...)
#define TYPE_TRAITS_CHECKS(...)

#else

#define CONSTANT_CHECK(expected_value, actual_value) EXPECT_EQ(expected_value, actual_value)

#define TRAITS_APPLY(name, ...) ((name< __VA_ARGS__ >{})())

#if defined(BR_CXX14)
#  define IS_TRAITS_CHECK_CXX14(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  (is_  ## traits< __VA_ARGS__ >));\
	CONSTANT_CHECK(expected_value, !(not_ ## traits< __VA_ARGS__ >));
#  define HAS_TRAITS_CHECK_CXX14(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  (has_ ## traits< __VA_ARGS__ >));\
	CONSTANT_CHECK(expected_value, !(no_  ## traits< __VA_ARGS__ >));
#else
#  define IS_TRAITS_CHECK_CXX14(...)
#  define HAS_TRAITS_CHECK_CXX14(...)
#endif

#define IS_TRAITS_CHECK(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  (Is  ## Traits< __VA_ARGS__ >{}));\
	CONSTANT_CHECK(expected_value, !(Not ## Traits< __VA_ARGS__ >{}));\
	IS_TRAITS_CHECK_CXX14(expected_value, Traits, traits, __VA_ARGS__)

#define HAS_TRAITS_CHECK(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  (Has ## Traits< __VA_ARGS__ >{}));\
	CONSTANT_CHECK(expected_value, !(No  ## Traits< __VA_ARGS__ >{}));\
	HAS_TRAITS_CHECK_CXX14(expected_value, Traits, traits, __VA_ARGS__)

#define IS_TRAITS_CHECK_CV(expected_value, Traits, traits, T)\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T);\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T const);\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T volatile);\
	IS_TRAITS_CHECK(expected_value, Traits, traits, T const volatile);

#define HAS_TRAITS_CHECK_CV(expected_value, Traits, traits, T)\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T);\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T const);\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T volatile);\
	HAS_TRAITS_CHECK(expected_value, Traits, traits, T const volatile);

#define INTEGRAL_TRAITS_CHECK(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  TRAITS_APPLY(Traits, ##__VA_ARGS__));

template< typename T0, typename T1 >
struct IsSameType {
	constexpr static auto value = false;
};

template< typename T >
struct IsSameType< T, T > {
	constexpr static auto value = true;
};

#define TYPE_CHECK(expected_type, actual_type) ASSERT_TRUE((::IsSameType< expected_type, actual_type >::value))

#define TYPE_TRAITS_APPLY_FULL( name, ...) Type ## name< __VA_ARGS__ >::Type
#define TYPE_TRAITS_APPLY_SHORT(name, ...)         name< __VA_ARGS__ >

#define TYPE_TRAITS_CHECK(expected_type, traits, ...)\
	TYPE_CHECK(expected_type, TYPE_TRAITS_APPLY_FULL( traits, ##__VA_ARGS__));\
	TYPE_CHECK(expected_type, TYPE_TRAITS_APPLY_SHORT(traits, ##__VA_ARGS__));

#define TYPE_TRAITS_CHECKS(traits, from_suffix, to_suffix)\
	TYPE_TRAITS_CHECK(         bool      to_suffix, traits,          bool      from_suffix);\
	TYPE_TRAITS_CHECK(         char      to_suffix, traits,          char      from_suffix);\
	TYPE_TRAITS_CHECK(  signed char      to_suffix, traits,   signed char      from_suffix);\
	TYPE_TRAITS_CHECK(unsigned char      to_suffix, traits, unsigned char      from_suffix);\
	TYPE_TRAITS_CHECK(         wchar_t   to_suffix, traits,          wchar_t   from_suffix);\
	TYPE_TRAITS_CHECK(         char16_t  to_suffix, traits,          char16_t  from_suffix);\
	TYPE_TRAITS_CHECK(         char32_t  to_suffix, traits,          char32_t  from_suffix);\
	TYPE_TRAITS_CHECK(         short     to_suffix, traits,          short     from_suffix);\
	TYPE_TRAITS_CHECK(unsigned short     to_suffix, traits, unsigned short     from_suffix);\
	TYPE_TRAITS_CHECK(         int       to_suffix, traits,          int       from_suffix);\
	TYPE_TRAITS_CHECK(unsigned int       to_suffix, traits, unsigned int       from_suffix);\
	TYPE_TRAITS_CHECK(         long      to_suffix, traits,          long      from_suffix);\
	TYPE_TRAITS_CHECK(unsigned long      to_suffix, traits, unsigned long      from_suffix);\
	TYPE_TRAITS_CHECK(         long long to_suffix, traits,          long long from_suffix);\
	TYPE_TRAITS_CHECK(unsigned long long to_suffix, traits, unsigned long long from_suffix);\
	TYPE_TRAITS_CHECK(     float         to_suffix, traits,      float         from_suffix);\
	TYPE_TRAITS_CHECK(     double        to_suffix, traits,      double        from_suffix);\
	TYPE_TRAITS_CHECK(long double        to_suffix, traits, long double        from_suffix);\
	TYPE_TRAITS_CHECK(UDT                to_suffix, traits, UDT                from_suffix);

#endif

class Class { public: int i; };

template< typename T >
class TemplateClass { public: T t; };

class Empty {};

union Union { int i; Empty e; };

enum Enum { value };

enum class EnumClass { value };

struct Abstract {
	virtual void f(int) = 0;
};

class Polymorphic {
	virtual void f(int);
};

class PolymorphicDerived : public Polymorphic {};

class Incomplete;

class Base {};

class Derived : public Base {};

class FinalInherit final : public Base {};

struct ExplicitConstruct {
	explicit ExplicitConstruct(int &);
	ExplicitConstruct(double &);
	ExplicitConstruct(int &, double &);
};

struct AnyConstructor {
	template< typename ... TArgs >
	AnyConstructor(TArgs && ... args);
};

struct DeleteDefaultConstructor {
	DeleteDefaultConstructor() = delete;
};

struct DeleteCopyConstructor {
	DeleteCopyConstructor(DeleteCopyConstructor const &) = delete;
};

struct DeleteDestructor {
	~DeleteDestructor() = delete;
};

struct AbstractDeleteDestructor {
	~AbstractDeleteDestructor() = delete;
	virtual void f(int) = 0;
};