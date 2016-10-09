#include "test.hpp"

#include<libbr/type_traits/is_abstract.hpp>

using namespace BR;

namespace {

struct C00 {};
struct C01 { virtual void f(void) = 0; };
struct C02 { private: virtual void f(void) = 0; };
struct C03 : public C00 {};
struct C04 : public C01 {};
struct C05 : public C02 {};
struct C06 : public C01 { virtual void f(void) {} };
struct C07 : public C02 { private: virtual void f(void) {} };
struct C08 : public C01, public C02 {};
struct C09 : public C08 { virtual void f(void) {} };
struct C10 : public C01 { virtual void f(void) {}; virtual void h(void) = 0; };
struct C11 : public C10 { virtual void h(void) {} };
struct C12 : public virtual C01 {};
struct C13 : public virtual C02 {};
struct C14 : public C12, public C13 {};
struct C15 : public C14 { virtual void f(void) {} };
struct C16 : public C01 { virtual void f(void) = 0; };
struct C17 : public C02 { private: virtual void f(void) = 0; };
struct C18 { virtual void f(void) {} };
struct C19 { virtual ~C19(void) {} virtual void f(void) {} };
struct C20 : public C19 { virtual void f(void) = 0; };
struct C21 : public C19 { virtual void f(void) {} };
struct C22 { virtual void g(void) = 0; virtual void h(void) = 0; };
struct C23 : public C22 { virtual void g(void) {}  virtual void h(void) {} };
struct C24 { virtual ~C24(void) = 0; };
struct C25 { virtual ~C25(void) = 0; }; C25::~C25(void) {}
struct C26 : public C25 { virtual ~C26(void) = 0; }; C26::~C26(void) {}
struct C27 : public C26 { virtual ~C27(void) {} };
struct C28 { virtual void f(void) = 0; }; void C28::f(void) {}
struct C29 : public C28 {};
struct C30 : public C29 { virtual void f() {} };
struct C31 : public C29 { virtual void f(); }; void C31::f(void) {}
struct C32 : public virtual C00 {};

template<typename T> struct TC00 {};
template<typename T> struct TC01 { virtual void f(void) = 0; };
template<typename T> struct TC02 { private: virtual void f(void) = 0; };
template<typename T> struct TC03 : public TC00<T> {};
template<typename T> struct TC04 : public TC01<T> {};
template<typename T> struct TC05 : public TC02<T> {};
template<typename T> struct TC06 : public TC01<T> { virtual void f(void) {} };
template<typename T> struct TC07 : public TC02<T> { private: virtual void f(void) {} };
template<typename T> struct TC08 : public TC01<T>, public TC02<T> {};
template<typename T> struct TC09 : public TC08<T> { virtual void f(void) {} };
template<typename T> struct TC10 : public TC01<T> { virtual void f(void) {}; virtual void h(void) = 0; };
template<typename T> struct TC11 : public TC10<T> { virtual void h(void) {} };
template<typename T> struct TC12 : public virtual TC01<T> {};
template<typename T> struct TC13 : public virtual TC02<T> {};
template<typename T> struct TC14 : public TC12<T>, public TC13<T> {};
template<typename T> struct TC15 : public TC14<T> { virtual void f(void) {} };
template<typename T> struct TC16 : public TC01<T> { virtual void f(void) = 0; };
template<typename T> struct TC17 : public TC02<T> { private: virtual void f(void) = 0; };
template<typename T> struct TC18 { virtual void f(void) {} };
template<typename T> struct TC19 { virtual ~TC19(void) {} virtual void f(void) {} };
template<typename T> struct TC20 : public TC19<T> { virtual void f(void) = 0; };
template<typename T> struct TC21 : public TC19<T> { virtual void f(void) {} };
template<typename T> struct TC22 { virtual void g(void) = 0; virtual void h(void) = 0; };
template<typename T> struct TC23 : public TC22<T> { virtual void g(void) {}  virtual void h(void) {} };
template<typename T> struct TC24 { virtual ~TC24(void) = 0; };
template<typename T> struct TC25 { virtual ~TC25(void) = 0; }; template<typename T> TC25<T>::~TC25(void) {}
template<typename T> struct TC26 : public TC25<T> { virtual ~TC26(void) = 0; }; template<typename T> TC26<T>::~TC26(void) {}
template<typename T> struct TC27 : public TC26<T> { virtual ~TC27(void) {} }; 
template<typename T> struct TC28 { virtual void f(void) = 0; }; template<typename T> void TC28<T>::f(void) {}
template<typename T> struct TC29 : public TC28<T> {};
template<typename T> struct TC30 : public TC29<T> { virtual void f() {} };
template<typename T> struct TC31 : public TC29<T> { virtual void f(); }; template<typename T> void TC31<T>::f(void) {}
template<typename T> struct TC32 : public virtual TC00<T> {};

} // namespace [anonymous]

TEST(TypeTraits, IsAbstract) {
	IS_TRAITS_CHECK(false, Abstract, abstract, void);
	IS_TRAITS_CHECK(false, Abstract, abstract, int);
	IS_TRAITS_CHECK(false, Abstract, abstract, int *);
	IS_TRAITS_CHECK(false, Abstract, abstract, int &);
	IS_TRAITS_CHECK(false, Abstract, abstract, int &&);
	IS_TRAITS_CHECK(false, Abstract, abstract, int(int));

	IS_TRAITS_CHECK_CV(false, Abstract, abstract, Class);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, Abstract);

	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C00);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C01);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C02);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C03);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C04);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C05);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C06);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C07);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C08);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C09);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C10);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C11);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C12);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C13);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C14);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C15);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C16);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C17);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C18);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C19);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C20);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C21);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C22);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C23);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C24);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C25);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C26);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C27);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C28);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, C29);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C30);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C31);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, C32);

	IS_TRAITS_CHECK(false, Abstract, abstract, C00 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C01 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C02 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C03 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C04 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C05 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C06 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C07 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C08 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C09 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C10 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C11 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C12 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C13 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C14 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C15 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C16 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C17 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C18 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C19 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C20 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C21 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C22 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C23 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C24 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C25 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C26 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C27 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C28 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C29 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C30 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C31 &);
	IS_TRAITS_CHECK(false, Abstract, abstract, C32 &);

	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC00<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC01<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC02<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC03<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC04<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC05<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC06<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC07<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC08<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC09<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC10<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC11<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC12<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC13<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC14<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC15<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC16<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC17<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC18<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC19<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC20<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC21<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC22<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC23<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC24<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC25<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC26<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC27<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC28<int>);
	IS_TRAITS_CHECK_CV(true , Abstract, abstract, TC29<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC30<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC31<int>);
	IS_TRAITS_CHECK_CV(false, Abstract, abstract, TC32<int>);

	IS_TRAITS_CHECK(false, Abstract, abstract, TC00<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC01<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC02<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC03<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC04<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC05<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC06<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC07<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC08<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC09<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC10<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC11<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC12<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC13<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC14<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC15<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC16<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC17<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC18<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC19<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC20<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC21<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC22<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC23<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC24<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC25<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC26<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC27<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC28<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC29<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC30<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC31<int> &);
	IS_TRAITS_CHECK(false, Abstract, abstract, TC32<int> &);
}