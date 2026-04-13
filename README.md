# Dawn Engine

开源 3D 引擎，专为类坎巴拉太空游戏场景优化。

## 依赖

| 依赖 | 版本 | 说明 |
|------|------|------|
| Vulkan SDK | 1.3+ | [下载](https://vulkan.lunarg.com/sdk/home#windows) |
| CMake | 3.20+ | 构建系统 |
| MSVC | 2022 | C++20 编译器 |
| SDL2 | 2.28 | 自动下载，无需手动安装 |

## 快速开始

```powershell
# 克隆仓库
git clone https://github.com/your-org/DawnEngine.git
cd DawnEngine

# 用 VS Code 打开
code .

# 在 VS Code 中按 Ctrl+Shift+B 构建
# 按 F5 运行
```

## 项目结构

```
DawnEngine/
├── include/dawn/       # 公开头文件（引擎 API）
├── src/                # 实现文件
├── shaders/            # GLSL shader 源文件
├── .vscode/            # VS Code 配置
└── CMakeLists.txt
```

## 路线图

- [x] 窗口系统 (SDL2)
- [x] Vulkan 上下文初始化
- [ ] Swapchain + 渲染循环
- [ ] 基础 3D 场景
- [ ] 数学库 (Vec3 / Quat / Transform)
- [ ] 轨道力学模块
