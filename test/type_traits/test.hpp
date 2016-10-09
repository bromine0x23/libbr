#pragma once

#include "../test.hpp"
#include <libbr/config.hpp>

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

#define INTEGRAL_CHECK(expected_value, Traits, traits, ...)\
	CONSTANT_CHECK(expected_value,  TRAITS_APPLY(Traits, ##__VA_ARGS__));

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