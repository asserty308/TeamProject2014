#pragma once

class Vector2
{
	private:
		float x, y;

	public:
		Vector2(float x, float y);
		Vector2();
		
		float getX() const;
		void setX(float x);
		float getY() const;
		void setY(float y);

		void normalize();

		Vector2 operator+(const Vector2& right) const;
		Vector2& operator+=(const Vector2& right);
		Vector2 operator-(const Vector2& right) const;
		Vector2 operator*(const Vector2& right) const;
		Vector2& operator*=(const Vector2& right);
		Vector2 operator*(const float& right) const;
};