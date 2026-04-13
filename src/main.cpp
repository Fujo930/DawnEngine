#include "dawn/Window.hpp"
#include "dawn/VulkanContext.hpp"
#include <iostream>

int main(int, char*[]) {
    try {
        dawn::Window window("Dawn Engine v0.1", 1280, 720);
        dawn::VulkanContext vulkan(window.handle());

        std::cout << "[Dawn] Engine started. Press ESC to exit.\n";

        while (window.pollEvents()) {
        }

        std::cout << "[Dawn] Shutting down.\n";
    }
    catch (const std::exception& e) {
        std::cerr << "[Dawn] Fatal: " << e.what() << "\n";
        return 1;
    }

    return 0;
}