#pragma once

#ifdef KVE_GL
#include <SDL2/SDL.h>
#endif

#include <string>

namespace kve {
	class Window {
#ifdef KVE_GL
	private:
		SDL_Window* sdlWindow;
		SDL_GLContext sdlGlContext;
#endif

	public:
		bool Start(int width, int height, std::string title);
		void End();
		bool Update();
		void Render();
	};
}