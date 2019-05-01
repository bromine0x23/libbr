#pragma once

#include <libbr/config.hpp>

class Class {
public:
	int i;

	void f1();
	int f2();
	int f3(int);
	int f4(int, float);
	int f5() &&;
};

struct Struct {
	int i;

	void f1();
	int f2();
	int f3(int);
	int f4(int, float);
	int f5() &&;
};

template< typename T >
class TemplateClass {
public:
	T t;
};

class Empty {};

union Union {
	int i;
	double d;
	Empty e;
};

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

struct VirtualInherit : public virtual Base {};
