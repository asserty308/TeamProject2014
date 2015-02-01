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

		float getLength();
		void normalize();

		//a: Vector to be projected, b: Vector to be projected upon
		static Vector2 projectVector(Vector2 a, Vector2 b);
		static float dotProduct(Vector2 a, Vector2 b);

		Vector2 operator+(const Vector2& right) const;
		Vector2& operator+=(const Vector2& right);
		Vector2 operator-(const Vector2& right) const;
		Vector2 operator*(const Vector2& right) const;
		Vector2& operator*=(const Vector2& right);
		Vector2 operator*(const float& right) const;
		bool operator==(const Vector2& right) const{
			return(right.getX() == x && right.getY() == y);
		}
};