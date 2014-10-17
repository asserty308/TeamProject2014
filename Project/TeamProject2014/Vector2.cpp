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

void Vector2::normalize()
{
	float lengthReciprocal = 1.f / sqrtf(x * x + y * y);
	x *= lengthReciprocal;
	y *= lengthReciprocal;
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
