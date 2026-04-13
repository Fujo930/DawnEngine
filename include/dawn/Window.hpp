#pragma once
#include <string>
#include <SDL.h>

namespace dawn {

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;

    bool        isOpen()  const { return m_open; }
    SDL_Window* handle()  const { return m_window; }
    int         width()   const { return m_width; }
    int         height()  const { return m_height; }

    bool pollEvents();

private:
    SDL_Window* m_window = nullptr;
    int         m_width;
    int         m_height;
    bool        m_open = true;
};

} // namespace dawn