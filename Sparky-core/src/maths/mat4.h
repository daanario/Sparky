#pragma once
#include "vec3.h"
#include "maths_func.h"
#include "vec4.h"

namespace sparky { namespace maths {

	struct mat4
	{
		union 
		{
			float elements[4 * 4];
			vec4 columns[4];
		};

		/* en union bruges, så vi har adgang til data og kan referere til det på samme adresse uden at skulle tildele mere hukommelse. En funktion som f.eks. getColumn() ville allokere en ny blok hukommelse på en ny adresse */

		mat4();
		mat4(float diagonal);

		static mat4 identity();

		mat4& multiply(const mat4& other);
		friend mat4 operator*(mat4 left, const mat4& right);
		mat4& operator*=(const mat4& other);

		static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspective(float fov, float aspectRatio, float near, float far);
		
		static mat4 translation(const vec3& translation);
		static mat4 rotation(float angle, const vec3& axis);
		static mat4 scale(const vec3& scale);

		

	};

} }
