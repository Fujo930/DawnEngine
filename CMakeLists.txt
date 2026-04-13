cmake_minimum_required(VERSION 3.20)
project(DawnEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Vulkan ────────────────────────────────────────────────────────────────────
find_package(Vulkan REQUIRED)

# ── SDL2 (本地预编译包) ────────────────────────────────────────────────────────
set(SDL2_DIR         "${CMAKE_SOURCE_DIR}/third_party/SDL2")
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
set(SDL2_LIB_DIR     "${SDL2_DIR}/lib/x64")

if(NOT EXISTS "${SDL2_INCLUDE_DIR}/SDL.h")
    message(FATAL_ERROR
        "\n================================================================\n"
        " [Dawn] 找不到 SDL2！请按以下步骤操作：\n"
        "  1. 下载 SDL2-devel-2.28.5-VC.zip\n"
        "     https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-VC.zip\n"
        "  2. 解压，将里面的 SDL2-2.28.5 文件夹重命名为 SDL2\n"
        "  3. 放到项目根目录的 third_party/SDL2 文件夹\n"
        "  4. 确认 third_party/SDL2/include/SDL.h 存在\n"
        "================================================================\n"
    )
endif()

# ── 可执行文件 ─────────────────────────────────────────────────────────────────
add_executable(DawnEngine
    src/main.cpp
    src/VulkanContext.cpp
    src/Window.cpp
)

target_include_directories(DawnEngine PRIVATE
    include
    ${SDL2_INCLUDE_DIR}
    ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries(DawnEngine PRIVATE
    Vulkan::Vulkan
    "${SDL2_LIB_DIR}/SDL2.lib"
    "${SDL2_LIB_DIR}/SDL2main.lib"
)

# 编译后自动拷贝 SDL2.dll
add_custom_command(TARGET DawnEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIB_DIR}/SDL2.dll"
        $<TARGET_FILE_DIR:DawnEngine>
    COMMENT "Copying SDL2.dll..."
)

# 拷贝 shaders
add_custom_command(TARGET DawnEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:DawnEngine>/shaders"
    COMMENT "Copying shaders..."
)
