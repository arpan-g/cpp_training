#include "FastAngle.h"
#include <math.h>

const float PIx2=6.283185307f;

FastAngle FastAngle::Deg2FastAngle(const int &a_NrDeg)
{
	FastAngle l_Result((a_NrDeg << 16) / 360);
	return l_Result;
}
FastAngle FastAngle::Deg2FastAngle(const float &a_NrDeg)
{
	FastAngle l_Result(static_cast<uint16_t>((a_NrDeg * 65536.0f) / 360.0f));
	return l_Result;
}

//all other methods are still to be defined