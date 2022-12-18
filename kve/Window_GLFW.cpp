#ifdef KVE_GL

#include "Window.h"
#include <iostream>

using namespace kve;

bool Window::Start(int width, int height, std::string title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (glfwWindow == NULL) {
        std::cerr << "Failed to init GLFW." << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(glfwWindow);

    return true;
}

void Window::End() {
    glfwTerminate();
}

bool Window::Update() {
    if (glfwWindowShouldClose(glfwWindow)) {
        return false;
    }

    glfwPollEvents();

    return true;
}

void Window::Render() {
    glfwSwapBuffers(glfwWindow);
}

#endif
