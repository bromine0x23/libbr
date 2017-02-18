#include <libbr/math/float_environment.hpp>

using namespace BR;
using namespace BR::Floating;

#if defined(BR_GCC) || defined(BR_CLANG)

auto libbr_get_floating_round_mode() -> RoundMode {
	UInt32 control;
	asm("fnstcw %0" : "=m"(control));
	return RoundMode(control & 0xC00);
}

auto libbr_set_floating_round_mode(RoundMode mode) -> bool {
	if ((to_i(mode) & ~0xC00) != 0) {
		return false;
	}
	UInt32 control;
	asm("fnstcw %0" : "=m"(control));
	control = (control & ~0xC00) | to_i(mode);
	asm("fldcw %0" : : "m"(control));
#if defined(BR_X86_64)
	UInt32 mxcsr;
	asm ("stmxcsr %0" : "=m" (mxcsr));
	mxcsr = (mxcsr & ~ 0x6000) | (to_i(mode) << 3);
	asm ("ldmxcsr %0" : : "m" (mxcsr));
#endif
	return true;
}

void libbr_get_floating_environment(Environment & environment) {
	asm("fnstenv %0" : "=m" (environment));
	asm("fldenv %0" : : "m" (environment));
#if defined(BR_X86_64)
	asm ("stmxcsr %0" : "=m" (environment.instruction_pointer_offset));
#endif
}

auto libbr_set_floating_environment(Environment const & environment) -> bool {
	Environment temp;
	asm("fnstenv %0" : "=m" (temp));
	temp.control_word &= ~(to_i(Exceptions::all) | to_i(RoundMode::nearest));
	temp.control_word |= (environment.control_word & (to_i(Exceptions::all) | to_i(RoundMode::zero)));
	temp.status_word &= ~to_i(Exceptions::all);
	temp.status_word |= environment.status_word & to_i(Exceptions::all);
	temp.instruction_pointer_offset = 0;
	temp.instruction_pointer_selector = 0;
	temp.operand = 0;
	temp.data_offset = 0;
	temp.data_selector = 0;
	asm("fldenv %0" : : "m" (temp));
#if defined(BR_X86_64)
	UInt32 mxcsr;
	asm ("stmxcsr %0" : "=m" (mxcsr));
	mxcsr = environment.instruction_pointer_offset;
	asm ("ldmxcsr %0" : : "m" (mxcsr));
#endif
	return true;
}

void libbr_set_default_floating_environment() {
	Environment temp;
	asm("fnstenv %0" : "=m" (temp));
	temp.control_word |= to_i(Exceptions::all);
	temp.control_word &= to_i(RoundMode::zero);
	temp.status_word &= ~to_i(Exceptions::all);
	temp.instruction_pointer_offset = 0;
	temp.instruction_pointer_selector = 0;
	temp.operand = 0;
	temp.data_offset = 0;
	temp.data_selector = 0;
	asm("fldenv %0" : : "m" (temp));
#if defined(BR_X86_64)
	UInt32 mxcsr;
	asm("stmxcsr %0" : "=m" (mxcsr));
	mxcsr |= to_i(Exceptions::all) << 7;
	mxcsr &= ~0x6000;
	mxcsr |= to_i(RoundMode::nearest) << 3;
	asm("ldmxcsr %0" : : "m" (mxcsr));
#endif
}

auto libbr_get_floating_exceptions() -> Exceptions {
	UInt16 status;
	asm("fstcw %0" : "=m" (status));
	return Exceptions(~status & to_i(Exceptions::all));
}

auto libbr_test_floating_exceptions(Exceptions exceptions) -> bool {
	UInt32 status;
	asm("fnstsw %0" : "=m" (status));
#if defined(BR_X86_64)
	UInt32 mxcsr;
	asm("stmxcsr %0" : "=m" (mxcsr));
	status |= mxcsr;
#endif
	return (status & to_i(exceptions) & to_i(Exceptions::all)) != 0;
}

auto libbr_throw_floating_exceptions(Exceptions exceptions) -> bool {
	if (exceptions & Exceptions::invalid) {
#if defined(BR_X86_64)
		Float32 f = 0.0;
		asm("divss %0, %0 " : : "x" (f));
		BR_FORCE_USE(f);
#else
		double d;
		asm("fldz; fdiv %%st, %%st(0); fwait" : "=t" (d));
		BR_FORCE_USE(d);
#endif
	}
	if (exceptions & Exceptions::divided_by_zero) {
#if defined(BR_X86_64)
		Float32 f = 1.0;
		Float32 g = 0.0;
		asm("divss %1, %0" : : "x" (f), "x" (g));
		BR_FORCE_USE(f);
		BR_FORCE_USE(g);
#else
		double d;
		asm("fldz; fld1; fdivp %%st, %%st(1); fwait" : "=t" (d));
		BR_FORCE_USE(d);
#endif
	}
	if (exceptions & Exceptions::overflow) {
		Environment temp;
		asm("fnstenv %0" : "=m" (temp));
		temp.status_word |= to_i(Exceptions::overflow);
		asm("fldenv %0" : : "m" (temp));
		asm("fwait");
	}
	if (exceptions & Exceptions::underflow) {
		Environment temp;
		asm("fnstenv %0" : "=m" (temp));
		temp.status_word |= to_i(Exceptions::underflow);
		asm("fldenv %0" : : "m" (temp));
		asm("fwait");
	}
	if (exceptions & Exceptions::inexact) {
		Environment temp;
		asm("fnstenv %0" : "=m" (temp));
		temp.status_word |= to_i(Exceptions::inexact);
		asm("fldenv %0" : : "m" (temp));
		asm("fwait");
	}
	return true;
}

auto libbr_clear_floating_exceptions(Exceptions exceptions) -> bool {
	Environment temp;
	asm("fnstenv %0" : "=m" (temp));
	auto excepts = to_i(exceptions) & to_i(Exceptions::all);
	temp.status_word &= excepts ^ to_i(Exceptions::all);
	asm("fldenv %0" : : "m" (temp));
#if defined(BR_X86_64)
	UInt32 mxcsr;
	asm ("stmxcsr %0" : "=m" (mxcsr));
	mxcsr &= ~excepts;
	asm ("ldmxcsr %0" : : "m" (mxcsr));
#endif
	return true;
}

#else

auto libbr_get_float_round_mode() -> RoundMode {
	return FloatRoundMode(std::fegetround()); // TODO
}

auto libbr_set_float_round_mode(RoundMode mode) -> bool {
	return std::fesetround(to_i(mode)) == 0; // TODO
}

void libbr_get_floating_environment(Environment & environment) {
	std::fegetenv(&environment); // TODO
}

auto libbr_set_floating_environment(Environment const & environment) -> bool {
	return std::fesetenv(&environment) == 0; // TODO
}

auto libbr_test_floating_exceptions(Exceptions exceptions) -> bool {
	return std::fetestexcept(to_i(exceptions)) == 0; // TODO
}

auto libbr_throw_floating_exceptions(Exceptions exceptions) -> bool {
	return std::feraiseexcept(to_i(exceptions)) == 0; // TODO
}

auto libbr_clear_floating_exceptions(Exceptions exceptions) -> bool {
	return std::feclearexceptto_i(exceptions)) == 0; // TODO
}
#endif
