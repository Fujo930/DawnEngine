#include "dawn/Window.hpp"
#include <stdexcept>
#include <SDL.h>

namespace dawn {

Window::Window(const std::string& title, int width, int height)
    : m_width(width), m_height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());

    m_window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!m_window)
        throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
}

Window::~Window() {
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::pollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_open = false;
        }
        if (event.type == SDL_KEYDOWN &&
            event.key.keysym.sym == SDLK_ESCAPE) {
            m_open = false;
        }
    }
    return m_open;
}

} // namespace dawn
