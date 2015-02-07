#pragma once

#include "Vector2.hpp"

template <typename T>
T clamp(T min, T max, T value){
	if (value < min){
		return min;
	} else if (value > max){
		return max;
	} else{
		return value;
	}
}

template <typename T>
T lerp(T a, T b, float alpha){
	return a * (1 - alpha) + b * alpha;
}

