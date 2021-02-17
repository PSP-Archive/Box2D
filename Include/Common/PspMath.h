#ifndef _pspmath_h_
#define _pspmath_h_

#include <psptypes.h>

#define PI   3.14159265358979f
#define PI_2 1.57079632679489f

extern "C" 
{
	float vfpu_sqrtf(float x);
	float vfpu_asinf(float x);
	float vfpu_atanf(float x);
	float vfpu_atan2f(float x, float y);
	void vfpu_sincos(float r, float *s, float *c);
}

#endif