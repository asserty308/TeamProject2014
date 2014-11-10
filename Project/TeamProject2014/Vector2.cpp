#include <cmath>

#include "Vector2.hpp"

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2()
{
	Vector2(0.f, 0.f);
}

float Vector2::getX() const
{
	return x;
}

void Vector2::setX(float x)
{
	this->x = x;
}

float Vector2::getY() const
{
	return y;
}

void Vector2::setY(float y)
{
	this->y = y;
}

float Vector2::getLength()
{
	return sqrtf(x * x + y * y);
}

void Vector2::normalize()
{
	float lengthReciprocal = 1.f / getLength();
	x *= lengthReciprocal;
	y *= lengthReciprocal;
}

float Vector2::dotProduct(Vector2 a, Vector2 b){
	return a.x * b.x + a.y * b.y;
}

Vector2 Vector2::projectVector(Vector2 a, Vector2 b){
	float adotb = dotProduct(a, b);
	float bdotb = dotProduct(b, b);
	float dotDivision = adotb / bdotb;

	return b * dotDivision;
}

Vector2 Vector2::operator+(const Vector2& right) const
{
	return Vector2(x + right.x, y + right.y);
}

Vector2& Vector2::operator+=(const Vector2& right)
{
	x += right.x;
	y += right.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& right) const
{
	return Vector2(x - right.x, y - right.y);
}

Vector2 Vector2::operator*(const Vector2& right) const
{
	return Vector2(x * right.x, y * right.y);
}

Vector2& Vector2::operator*=(const Vector2& right)
{
	x *= right.x;
	y *= right.y;
	return *this;
}

Vector2 Vector2::operator*(const float& right) const
{
	return Vector2(x * right, y * right);
}


