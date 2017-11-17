#pragma once
#include <iostream>

namespace sparky { namespace maths {

	struct vec2
	{
		float x, y;
		
		vec2(); //default constructor
		vec2(const float& x, const float& y);

		vec2& add(const vec2& other);
		vec2& subtract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		/*Selvom objekter i structs normalt er public, vil jeg sikre mig at jeg har adgang til disse overloadede operators, s� jeg g�r dem til friends */

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);

		bool operator==(const vec2& other);
		bool operator!=(const vec2& other);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);
	};

} }
