# ==============================================================================
# 1. EXECUTABLE TARGET CREATION
# ==============================================================================
# Tells CMake to compile main.cpp and package it into the final executable binary named "app" (app.exe).
add_executable(app main.cpp)

# ==============================================================================
# 2. LINKING THE ENGINE CORE
# ==============================================================================
# Links the "app" executable against the "engine" static library built in src/engine/.
# Because "engine" used PUBLIC for its include paths and dependencies, "app" automatically
# inherits C++20, Vulkan definitions, GLM math, and include directories.
target_link_libraries(app PRIVATE engine)

# ==============================================================================
# 3. BUILD ORDER DEPENDENCY (Shader Guarantee)
# ==============================================================================
# Forces CMake to build the "shaders" target (from CompileShaders.cmake) BEFORE building "app".
# This guarantees that all raw GLSL shaders (.vert, .frag) are fully compiled into SPIR-V (.spv)
# binaries before the executable tries to launch and load them from disk.
add_dependencies(app shaders)

# ==============================================================================
# 4. VISUAL STUDIO DEBUGGER ENVIRONMENT
# ==============================================================================
# Sets the default working directory when pressing 'Play' or debugging (F5) inside Visual Studio.
# By setting this to ${CMAKE_SOURCE_DIR} (your project root), relative paths like "shaders/" 
# or "assets/" will resolve correctly without failing to find files at runtime.
set_target_properties(app PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})