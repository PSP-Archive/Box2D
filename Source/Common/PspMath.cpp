#include "PspMath.h"

float vfpu_asinf(float x)
{
    float result;
    __asm__ volatile (
        "mtv     %1, S000\n"
        "vcst.s  S001, VFPU_PI_2\n"
        "vasin.s S000, S000\n"
        "vmul.s  S000, S000, S001\n"
        "mfv     %0, S000\n"
        : "=r"(result) : "r"(x));
    return result;
}

void vfpu_sincos(float r, float *s, float *c) {
	__asm__ volatile (
		"mtv      %2, S002\n"
		"vcst.s   S003, VFPU_2_PI\n"
		"vmul.s   S002, S002, S003\n"
		"vrot.p   C000, S002, [s, c]\n"
		"mfv      %0, S000\n"
		"mfv      %1, S001\n"
	: "=r"(*s), "=r"(*c): "r"(r));
}

float vfpu_sqrtf(float x) {
	float result;
	__asm__ volatile (
		"mtv     %1, S000\n"
		"vsqrt.s S000, S000\n"
		"mfv     %0, S000\n"
	: "=r"(result) : "r"(x));
	return result;
}

float vfpu_atanf(float x) {
	float result;
	// result = asinf(x/sqrt(x*x+1))
	__asm__ volatile (
		"mtv      %1, S000\n"
		"vmul.s   S001, S000, S000\n"
		"vadd.s   S001, S001, S001[1]\n"
		"vrsq.s   S001, S001\n"
		"vmul.s   S000, S000, S001\n"
		"vasin.s  S000, S000\n"
		"vcst.s   S001, VFPU_PI_2\n"
		"vmul.s   S000, S000, S001\n"
		"mfv      %0, S000\n"
	: "=r"(result) : "r"(x));
	return result;
}


inline static float  vfpu_fabsf(float x) {
	float r;
	__asm__ volatile( "abs.s %0, %1" : "=f"(r) :"f"(x):"memory");
	return r;
}


float vfpu_atan2f(float y, float x) {
	float r;

	if ( vfpu_fabsf(x) >=  vfpu_fabsf(y)) {
		r = vfpu_atanf(y/x);
		if   (x < 0.0f) r += (y>=0.0f ? PI : -PI);
	} else {
		r = -vfpu_atanf(x/y);
		r += (y < 0.0f ? -PI_2 : PI_2);
	}
	return r;
}