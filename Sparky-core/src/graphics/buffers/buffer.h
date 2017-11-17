#pragma once
#include <GL\glew.h>

namespace sparky {	namespace graphics {
	
	class Buffer
	{
	private:
		GLuint m_BufferID; 
		GLuint m_ComponentCount;
		/*med m_ComponentCount specificerer vi, hvordan input data skal forstås. Om der er tale om 2d-vektor, 3dvektor, 4dvektor osv. */
	public:
		Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

		void bind() const;
		void unbind() const;

		inline GLuint getComponentCount() const { return m_ComponentCount; }

	};



}	}

