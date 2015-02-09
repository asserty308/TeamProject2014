#pragma once

#include "Vector2.hpp"

template <typename T>
T clamp(T min, T max, T value){
	if (value < min){
		return min;
	} else if (value > max){
		return max;
	} 
	return value;
}

template <typename T>
T lerp(T a, T b, float alpha){
	return a * (1 - alpha) + b * alpha;
}

template <typename T>
T angleFromVector(Vector2 vector)
{
	// degrees [-180, 180]
	T degrees = (atan2f(vector.getX(), vector.getY()) * 180.f) / M_PI;

	// flip
	degrees = -degrees;

	// degrees [0, 360] (+180 so that angle 0 points DOWN not to the RIGHT as it would with std atan2)
	degrees += 180.f + 180.f;

	if (degrees >= 360.f)
		degrees -= 360.f;

	return degrees;
}
