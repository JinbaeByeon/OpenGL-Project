#include "util.h"



float Length(const float x, const  float y)
{
	return sqrtf(x*x + y*y);
}

float Length(const float x, const float y, const float z)
{
	return sqrtf(x*x + y*y + z*z);
}