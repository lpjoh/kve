#ifdef KVE_GL

#include "Window.h"
#include <iostream>
#include <algorithm>
#include <GL/glew.h>

using namespace kve;

void Window::GraphicsResize(glm::ivec2 size) {
    glViewport(0, 0, size.x, size.y);
}

void Window::Sleep() {
    int updateTime = SDL_GetTicks() - lastTicks;

    unsigned int waitTime =
        std::max(0, frameTime - updateTime);

    SDL_Delay(waitTime);

    deltaTime = (float)(SDL_GetTicks() - lastTicks) / 1000.0f;
}

float Window::GetDeltaTime() {
    return deltaTime;
}

bool Window::StartGraphics() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL." << std::endl;
        return false;
    }

    int sdlWindowFlags = SDL_WINDOW_OPENGL;

    if (properties.resizeable) {
        sdlWindowFlags |= SDL_WINDOW_RESIZABLE;
    }

    frameTime = (int)(1000.0f / properties.fps);

    sdlWindow = SDL_CreateWindow(
        properties.title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        properties.size.x, properties.size.y, sdlWindowFlags);

    sdlGlContext = SDL_GL_CreateContext(sdlWindow);

    if (sdlGlContext == NULL) {
        std::cerr << "Failed to create SDL GL context." << std::endl;
        return false;
    }

    SDL_GL_SetSwapInterval(0);

    return true;
}

void Window::End() {
    SDL_GL_DeleteContext(sdlGlContext);
    SDL_DestroyWindow(sdlWindow);

    SDL_Quit();
}

bool Window::Update() {
    lastTicks = SDL_GetTicks();

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            return false;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                Resize(glm::ivec2(event.window.data1, event.window.data2));
            }

            break;
        }
    }

    return true;
}

void Window::Render() {
    SDL_GL_SwapWindow(sdlWindow);
}

#endif
