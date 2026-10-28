# 3D Rendering Engine

A real-time 3D renderer written from scratch in C++20 and Vulkan 1.3. I am building it to learn graphics and engine programming properly, and to document the process in public.

<!-- Add a screenshot or GIF here as soon as something renders:
![vk-renderer](docs/media/hero.png) -->

## Status

Early development. The project builds and opens a window; the Vulkan renderer itself is in progress.

| Area | State |
| --- | --- |
| Build system (CMake and vcpkg) | Done |
| Window creation | Done |
| Instance, device, swap chain | In progress |
| First triangle with clean validation layers | Next |

Progress notes and measurements are in the [devlog](docs/devlog/) and [benchmarks](docs/Benchmarks.md). The full plan is in the [roadmap](docs/RoadMap.md).

## Goals

- Learn modern Vulkan (dynamic rendering, synchronization2, descriptor indexing) by writing my own thin abstraction layer instead of using a ready-made one.
- Measure performance and report it with hardware, scene and frame times.
- Explain design decisions in the devlog, including the mistakes.

## Planned features

**Foundation:** instance, device and swapchain; frames in flight; shader compilation; GPU memory and staging uploads; depth buffering; free camera; textures; glTF loading; bindless textures; physically based shading with image-based lighting; shadow maps; ImGui debug UI; CPU and GPU profiling.

**Core:** HDR, tone mapping and bloom; MSAA and SSAO; cascaded shadow maps; indirect rendering with CPU culling and LODs; skeletal animation; asynchronous asset loading and a job system; texture compression.

**Stretch:** GPU-driven culling with Hi-Z, clustered forward lighting, a render graph, temporal anti-aliasing, a custom job scheduler, animation blending and morph targets, ray queries.

## Dependencies

Installed automatically by vcpkg from `vcpkg.json`:

| Library | Used for |
| --- | --- |
| GLFW | Window, input and Vulkan surface |
| volk | Loading Vulkan functions |
| VulkanMemoryAllocator | GPU memory allocation |
| GLM | Math |
| spdlog | Logging |
| stb | Image decoding |

Shaders are compiled with `glslc`, which ships with the Vulkan SDK.

**Planned additions:** Dear ImGui, Tracy, fastgltf, meshoptimizer, Taskflow, KTX-Software. A move from GLSL to Slang is planned for the PBR stage.

## Building

Windows 10 or 11 (x64) only for now.

**Requirements**

- Visual Studio 2022 with the "Desktop development with C++" workload
- CMake 3.21 or newer
- Vulkan SDK 1.3 or newer (sets the `VULKAN_SDK` environment variable)
- Git, and vcpkg with the `VCPKG_ROOT` environment variable set
- A GPU and driver with Vulkan 1.3 support

**One-time vcpkg setup**

```powershell
git clone https://github.com/microsoft/vcpkg.git D:\dev\vcpkg
C:\dev\vcpkg\bootstrap-vcpkg.bat -disableMetrics
setx VCPKG_ROOT "D:\dev\vcpkg"
```

Reopen the terminal after `setx`.

**Build and run**

```powershell
git clone https://github.com/ArvindKumar29/3DRenderinEngine.git
cd vk-renderer
cmake --preset default
cmake --build --preset debug
.\build\bin\Debug\app.exe
```

The first configure takes several minutes while vcpkg builds the dependencies.

## Project structure

```
vk-renderer/
  cmake/        Build helper scripts (shader compilation)
  src/engine/   The renderer library; all engine code lives here
  src/app/      The executable that opens a window and runs the renderer
  shaders/      GLSL shaders, compiled to SPIR-V at build time
  assets/       Models and textures
  docs/         Devlog, benchmarks and roadmap
```

## Benchmarks

Test machine: NVIDIA GeForce RTX 3050 Laptop GPU, Windows 11. Results are published in [docs/BENCHMARKS.md](docs/Benchmarks.md) as they are measured.

## References and credits

I use these as references while writing my own code. Where an approach follows a reference closely, the devlog says so.

- *3D Graphics Rendering Cookbook* by Sergey Kosarevsky and Viktor Latypov
- *Game Engine Architecture* by Jason Gregory
- [vkguide.dev](https://vkguide.dev)
- Test scenes from the [Khronos glTF Sample Assets](https://github.com/KhronosGroup/glTF-Sample-Assets); each asset keeps its own license

## License

MIT. See `LICENSE`.

## Author

Arvind Kumar: [Portfolio](https://arvind-kumar-portfolio.bolt.host), [LinkedIn](https://linkedin.com/in/arvind-kumar-59b609178), [GitHub](https://github.com/ArvindKumar29)
