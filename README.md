# Dawn Engine

An open-source 3D engine optimized for Kerbal Space Program-style games.
Built with modern C++ and Vulkan, designed to be fast, modular, and community-driven.

> v0.1 authored by [Fujo](https://github.com/你的用户名) & Claude AI (Anthropic)

---

## Features (v0.1)

- Vulkan rendering backend
- SDL2 window & input system
- Clean C++20 architecture
- Designed for orbital mechanics & large-scale 3D scenes

## Roadmap

- [ ] Swapchain & render loop
- [ ] Basic 3D scene rendering
- [ ] Math library (Vec3 / Quat / Transform)
- [ ] Orbital mechanics module
- [ ] Atmospheric physics
- [ ] Part assembly system
- [ ] Mod / plugin API

---

## Getting Started

### Requirements

| Dependency | Version | Notes |
|---|---|---|
| Vulkan SDK | 1.3+ | [Download](https://vulkan.lunarg.com/sdk/home#windows) |
| CMake | 3.20+ | Make sure it's added to PATH |
| MSVC | 2022 | Via Visual Studio Build Tools |
| SDL2 | 2.28.5 | See setup below |

### SDL2 Setup

1. Download [SDL2-devel-2.28.5-VC.zip](https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-VC.zip)
2. Extract and rename the folder to `SDL2`
3. Place it at `third_party/SDL2/`
4. Confirm `third_party/SDL2/include/SDL.h` exists

### Build

```powershell
git clone https://github.com/你的用户名/DawnEngine.git
cd DawnEngine
mkdir shaders
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

Or open in VS Code and press `Ctrl+Shift+B`.

---

## Contributing

**Everyone is welcome to contribute — all skill levels, all backgrounds.**

Whether it's fixing a bug, adding a feature, improving docs, or just asking questions,
your contribution matters. This engine is built by the community, for the community.

### How to contribute

1. Fork this repository
2. Create a branch: `git checkout -b feature/your-feature-name`
3. Commit your changes: `git commit -m "feat: describe what you did"`
4. Push: `git push origin feature/your-feature-name`
5. Open a Pull Request

### What we need help with

- Vulkan swapchain & render pipeline
- Math library (vectors, quaternions, transforms)
- Orbital mechanics & physics simulation
- Atmospheric model
- Documentation & examples
- Testing on different hardware / OS

No contribution is too small. Even fixing a typo helps.

---

## License

MIT License — free to use, modify, and distribute.

---

*Dawn Engine v0.1 — first version written by Fujo & Claude AI (Anthropic)*
