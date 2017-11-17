#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW\glfw3.h>


namespace sparky { 
	namespace graphics {

		#define MAX_KEYS 1024
		#define MAX_BUTTONS 32

		/* der laves en class til spilmotorens vindue (alle members til class'en noteres med m_Stortbegyndelsesbogstav for at skelne dem fra andre variable) */
		class Window 
		{
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow* m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS]; //boolsk array til keycodes
			bool m_MouseButtons[MAX_BUTTONS]; //boolsk array til museknapperne
			double mx, my; //double værdier for cursorens placering på vinduet
		public:
			Window(const char *title, int width, int height); //window contructor
			~Window(); //window destructor
			void clear() const;
			void update(); //funktion til at opdatere vinduet
			bool closed() const; //funktion til at lukke vinduet

			inline int getWidth() const { return m_Width; };
			inline int getHeight() const { return m_Height; };

			bool isKeyPressed(unsigned int keycode) const;
			/*Da keycodes altid er positive kan keycode være unsigned, så vi kan tildele den større tal */

			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;

		private:
			bool init(); //funktion til at initialisere vinduet
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			/* metoden key_callback gøres til friend, så den har adgang til alle private variabler til klassen*/
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}


}
