#pragma once

#include <gtest/gtest.h>
#include <libbr/config.hpp>

#define CONSTANT_CHECK(expected_value, actual_value) EXPECT_EQ(expected_value, actual_value)

#define TRAITS_APPLY(name, ...) ((name< __VA_ARGS__ >{})())

#define TRAITS_APPLY_IS( name, ...) ((Is  ## name< __VA_ARGS__ >{})())
#define TRAITS_APPLY_NOT(name, ...) ((Not ## name< __VA_ARGS__ >{})())

#define TRAITS_APPLY_HAS(name, ...) ((Has ## name< __VA_ARGS__ >{})())
#define TRAITS_APPLY_NO( name, ...) ((No  ## name< __VA_ARGS__ >{})())

#define IS_TRAITS_CHECK(expected_value, traits, ...)\
	CONSTANT_CHECK(expected_value,  TRAITS_APPLY_IS( traits, ##__VA_ARGS__));\
	CONSTANT_CHECK(expected_value, !TRAITS_APPLY_NOT(traits, ##__VA_ARGS__));

#define HAS_TRAITS_CHECK(expected_value, traits, ...)\
	CONSTANT_CHECK(expected_value,  TRAITS_APPLY_HAS(traits, ##__VA_ARGS__));\
	CONSTANT_CHECK(expected_value, !TRAITS_APPLY_NO( traits, ##__VA_ARGS__));

#define IS_TRAITS_CHECK_CV(expected_value, traits, T)\
	IS_TRAITS_CHECK(expected_value, traits, T);\
	IS_TRAITS_CHECK(expected_value, traits, T const);\
	IS_TRAITS_CHECK(expected_value, traits, T volatile);\
	IS_TRAITS_CHECK(expected_value, traits, T const volatile);

#define HAS_TRAITS_CHECK_CV(expected_value, traits, T)\
	HAS_TRAITS_CHECK(expected_value, traits, T);\
	HAS_TRAITS_CHECK(expected_value, traits, T const);\
	HAS_TRAITS_CHECK(expected_value, traits, T volatile);\
	HAS_TRAITS_CHECK(expected_value, traits, T const volatile);

#define INTEGRAL_CHECK(expected_value, traits, ...) CONSTANT_CHECK(expected_value,  TRAITS_APPLY(traits, ##__VA_ARGS__));

class Class { int i; };

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