#include "vec2.h"

namespace sparky { namespace maths {
	
	vec2::vec2() //default constructor, hvis der ikke speciferes parametre
	{
		x = 0.0f;
		y = 0.0f;
	}

	vec2::vec2(const float& x, const float& y)
	{
		this->x = x;
		this->y = y;
	}
	
	//funktioner til vektorregning

	vec2& vec2::add(const vec2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2& vec2::subtract(const vec2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vec2& vec2::multiply(const vec2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	vec2& vec2::divide(const vec2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	/* Jeg overloader disse operators, så det er meget nemmere at regne med vektorer, da jeg bare skal bruge normale operators som +, -, *, og / */

	vec2 operator+(vec2 left, const vec2& right)
	{
		return left.add(right);
	}

	vec2 operator-(vec2 left, const vec2& right)
	{
		return left.subtract(right);
	}

	vec2 operator*(vec2 left, const vec2& right)
	{
		return left.multiply(right);
	}

	vec2 operator/(vec2 left, const vec2& right)
	{
		return left.divide(right);
	}

	vec2& vec2::operator+=(const vec2& other)
	{
		return add(other);
	}
	
	vec2& vec2::operator-=(const vec2& other)
	{
		return subtract(other);
	}

	vec2& vec2::operator*=(const vec2& other)
	{
		return multiply(other);
	}

	vec2& vec2::operator/=(const vec2& other)
	{
		return divide(other);
	}

	bool vec2::operator==(const vec2& other)
	{
		return x == other.x && y == other.y;
	}

	bool vec2::operator!=(const vec2& other)
	{
		return !(*this == other);
	}

	/*Jeg overloader <<-operatoren, så det er nemmere at printe vectorer til konsollen*/

	std::ostream& operator<<(std::ostream& stream, const vec2& vector)
	{
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

}	}