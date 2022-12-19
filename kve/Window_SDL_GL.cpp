#ifdef KVE_GL

#include "Window.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace kve;

int Window::GetWidth() {
    return properties.width;
}

int Window::GetHeight() {
    return properties.height;
}

void Window::Resize(int width, int height) {
    properties.width = width;
    properties.height = height;

    glViewport(0, 0, width, height);
}

glm::mat4 Window::GetOrthoTransform() {
    return glm::ortho(0.0f, float(GetWidth()), float(GetHeight()), 0.0f, -1.0f, 1.0f);
}

bool Window::Start(WindowProperties properties) {
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

    sdlWindow = SDL_CreateWindow(
        properties.title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        properties.width, properties.height, sdlWindowFlags);

    sdlGlContext = SDL_GL_CreateContext(sdlWindow);

    if (sdlGlContext == NULL) {
        std::cerr << "Failed to create SDL GL context." << std::endl;
        return false;
    }

    if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        std::cerr << "Failed to initialize vsync." << std::endl;
        return false;
    }

    this->properties = properties;

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
        switch (event.type) {
        case SDL_QUIT:
            return false;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                Resize(event.window.data1, event.window.data2);
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
