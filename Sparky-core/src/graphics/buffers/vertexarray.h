#pragma once
#include <vector>
#include <GL\glew.h>
#include "buffer.h"

namespace sparky {	namespace graphics {
	
	class VertexArray
	{
	private:
		GLuint m_ArrayID;
		std::vector<Buffer*>m_Buffers;
		/* Bufferen bliver håndteret af VertexArray, man kan derfor ikke bruge denne buffer i andre arrays */

	public:
		VertexArray();
		~VertexArray();
		void addBuffer(Buffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;

	};

}	}
