#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"


#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"

#include "src\graphics\renderer2d.h"
#include "src\graphics\simple2drenderer.h"


int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!", 1280, 720);
	//glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	
	Renderable2D sprite(maths::vec3(0, 0, 0), maths::vec2(16, 16), maths::vec4(0.5, 1, 0.5f, 0), shader);
	
	
	shader.setUniform4f("color", vec4(0.2f, 0, 1, 1));
	shader.setUniform2f("light_pos", vec2(-1, -1));

	Simple2DRenderer renderer;
	
	double x=100, y=100;
	
	
	
	double sampleTime = 1;
	double velocity = 50;
	double time = 0;
	double acceleration = 9.82;
	int index = 1;
	float samples = 100 / sampleTime;
	
	
	GLint64 timer = 0;
	unsigned int timerDiff = 1000000000;
	GLint64 timerStart;

	glGetInteger64v(GL_TIMESTAMP, &timer);
	timerStart = timer;
	std::cout << timerStart << std::endl;

	int j = 0;

	while (!window.closed())
	{
		window.clear();

		#if 0
		
		if (window.isKeyPressed(GLFW_KEY_UP))
		{
			y+=1;
			std::cout << "Up is pressed";
		}
		if (window.isKeyPressed(GLFW_KEY_DOWN))
		{
			y-=1;
			std::cout << "Down is pressed";
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT))
		{
			x-=1;
			std::cout << "Left is pressed";
		}

		if (window.isKeyPressed(GLFW_KEY_RIGHT))
		{
			x+=1;
			std::cout << "Right is pressed";
		}
		
		#endif


		glGetInteger64v(GL_TIMESTAMP, &timer);
		//std::cout << timer << std::endl;

		if ((timer - timerStart) >= timerDiff) {
			sampleTime+=1;
			//std::cout << j << std::endl;
			timerStart = timer;

			time = time + sampleTime;
			velocity = velocity - acceleration*sampleTime;
			y = y + velocity*sampleTime;

			x = j*sampleTime;


		}

		

		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 1280.0f), (y * 9.0f / 720.0f)));
		renderer.submit(&sprite);
		renderer.flush();
		window.update();
	}
	return 0;
}