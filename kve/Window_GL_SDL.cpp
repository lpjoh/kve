#ifdef KVE_GL

#include "Window.h"
#include <iostream>

using namespace kve;

bool Window::Start(int width, int height, std::string title) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL." << std::endl;
        return false;
    }

    sdlWindow = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, SDL_WINDOW_OPENGL);

    sdlGlContext = SDL_GL_CreateContext(sdlWindow);

    if (sdlGlContext == NULL) {
        std::cerr << "Failed to create SDL GL context." << std::endl;
        return false;
    }

    if( SDL_GL_SetSwapInterval( 1 ) < 0 )
    {
        std::cerr << "Failed to initialize vsync." << std::endl;
        return false;
    }

    return true;
}

void Window::End() {
    SDL_GL_DeleteContext(sdlGlContext);
    SDL_DestroyWindow(sdlWindow);

    SDL_Quit();
}

bool Window::Update() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
    }

    return true;
}

void Window::Render() {
    SDL_GL_SwapWindow(sdlWindow);
}

#endif
