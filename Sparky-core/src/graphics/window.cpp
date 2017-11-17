#include "window.h"

namespace sparky {
	namespace graphics {

		void window_resize(GLFWwindow *window, int width, int height);

		Window::Window(const char *title, int width, int height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if(!init())
				glfwTerminate();
		
			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}

		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			/* vindue laves med højde, bredde og titel */
			if (!glfwInit())
			{
				std::cout << "Error: failed to initialize GLFW!" << std::endl;
				return false;
			}
				
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window)
			{
				std::cout << "Failed to Create GLFW window!" << std::endl;
				return false;
			}
			/* Hvis det ikke lykkedes at lave vinduet, bliver der givet besked, og glfw bliver termineret i Window-constructoren */
			
			glfwMakeContextCurrent(m_Window);
			/* OpenGL kontekst gøres aktuel, så vi kan gøre brug af OpenGL API  */
			glfwSetWindowUserPointer(m_Window, this);

			glfwSetWindowSizeCallback(m_Window, window_resize);
			
			
			glfwSetKeyCallback(m_Window, key_callback);
			/* for at vi kan se events (i dette tilfælde keypresses) skal vi sætte en key callback. Metoden medfølger i GLFW-biblioteket */
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			/* det er meget vigtigt at OpenGL Extension Wrangler (GLEW) indlæses EFTER at vinduets OpenGL er blevet sat til aktuel, ellers virker GLEW ikke */
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Error: could not initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			return true;

		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			

			if (keycode >= MAX_KEYS)
			{
				return false;
			}
			/*Vi er nødt til at sikre os, at keycoden er indenfor vores range MAX_KEYS */

			return m_Keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
			{
				return false;
			}
			return m_MouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error: " << error << std::endl;
			}
			glfwPollEvents();
			//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glfwSwapBuffers(m_Window);
			/* double buffer: front buffer gengives på skærmen, back buffer er den, som programmet renderer. Når back buffer er blevet rendered, skal det selvfølgelig gengives på skærmen, så de to buffers bliver byttet rundt efter hver opdatering */



		}
		
		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			/* i init() bliver glfwWindowUserPointer sat til "this", så vi har adgang til Window-classen i eksterne metoder vha. en pointer win */
			
			win->m_Keys[key] = action != GLFW_RELEASE;
			/* Vindue-classens member m_Keys[key] bliver tildelt false, hvis der ikke bliver trykket på en knap, så snart der trykkes på en knap eller den holdes inde, bliver m_Keys[key] tildelt true*/

		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}
	
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

	}
}

