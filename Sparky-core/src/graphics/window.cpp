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
			/* vindue laves med h�jde, bredde og titel */
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
			/* OpenGL kontekst g�res aktuel, s� vi kan g�re brug af OpenGL API  */
			glfwSetWindowUserPointer(m_Window, this);

			glfwSetWindowSizeCallback(m_Window, window_resize);
			
			
			glfwSetKeyCallback(m_Window, key_callback);
			/* for at vi kan se events (i dette tilf�lde keypresses) skal vi s�tte en key callback. Metoden medf�lger i GLFW-biblioteket */
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);

			/* det er meget vigtigt at OpenGL Extension Wrangler (GLEW) indl�ses EFTER at vinduets OpenGL er blevet sat til aktuel, ellers virker GLEW ikke */
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
			/*Vi er n�dt til at sikre os, at keycoden er indenfor vores range MAX_KEYS */

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
			/* double buffer: front buffer gengives p� sk�rmen, back buffer er den, som programmet renderer. N�r back buffer er blevet rendered, skal det selvf�lgelig gengives p� sk�rmen, s� de to buffers bliver byttet rundt efter hver opdatering */



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
			/* i init() bliver glfwWindowUserPointer sat til "this", s� vi har adgang til Window-classen i eksterne metoder vha. en pointer win */
			
			win->m_Keys[key] = action != GLFW_RELEASE;
			/* Vindue-classens member m_Keys[key] bliver tildelt false, hvis der ikke bliver trykket p� en knap, s� snart der trykkes p� en knap eller den holdes inde, bliver m_Keys[key] tildelt true*/

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

