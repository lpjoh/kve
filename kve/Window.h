#pragma once

#ifdef KVE_GL
#include <GLFW/glfw3.h>
#endif

#include <string>

namespace kve {
	class Window {
#ifdef KVE_GL
	private:
		GLFWwindow* glfwWindow;
#endif

	public:
		bool Start(int width, int height, std::string title);
		void End();
		bool Update();
		void Render();
	};
}