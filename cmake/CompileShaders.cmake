# Declares a custom, reusable CMake function.
# We pass in a name for the task (TARGET_NAME), where your raw shaders are (SHADER_DIR), 
# and where the compiled binaries should go (OUT_DIR).
function(add_shader_target TARGET_NAME SHADER_DIR OUT_DIR)

  # GLOB scans the SHADER_DIR folder and finds every file ending in .vert, .frag, and .comp.
  # CONFIGURE_DEPENDS is crucial: It tells CMake to automatically re-configure the project 
  # if you create a brand new shader file in that folder.
  file(GLOB SHADER_SOURCES CONFIGURE_DEPENDS
       ${SHADER_DIR}/*.vert
       ${SHADER_DIR}/*.frag
       ${SHADER_DIR}/*.comp)

  # Create an empty list to keep track of all the compiled .spv (SPIR-V) files we are about to generate.
  set(SPV_FILES "")

  # Loop through every single raw shader file found by the GLOB command above.
  foreach(SHADER ${SHADER_SOURCES})
    
    # Extracts just the file name (e.g., "triangle.vert") from the full file path.
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    
    # Defines the exact output path for the compiled binary (e.g., "build/shaders/triangle.vert.spv").
    set(SPV ${OUT_DIR}/${SHADER_NAME}.spv)
    
    # This is the core magic. It tells CMake exactly HOW to turn the raw text file into a GPU binary.
    add_custom_command(
      OUTPUT ${SPV}                                           # The file this command will produce.
      COMMAND ${CMAKE_COMMAND} -E make_directory ${OUT_DIR}   # Ensures the output folder actually exists before writing to it.
      
      # Calls the Vulkan SDK's shader compiler (glslc).
      # -o sets the output file.
      # --target-env=vulkan1.3 ensures the shader has access to modern Vulkan 1.3 features.
      # -g includes debug information so you can debug shaders in tools like RenderDoc.
      COMMAND Vulkan::glslc ${SHADER} -o ${SPV} --target-env=vulkan1.3 -g
      
      # CMake will watch the raw ${SHADER} file. 
      # It will ONLY run this heavy compilation step if you actually edited and saved the shader.
      DEPENDS ${SHADER}
      
      COMMENT "Compiling shader ${SHADER_NAME}"               # The message printed in the terminal during the build.
      VERBATIM)
      
    # Add the path of the newly compiled binary to our tracking list.
    list(APPEND SPV_FILES ${SPV})
  endforeach()

  # Groups all of those individual shader compilation tasks into one master target (e.g., "shaders").
  # By making your main C++ executable depend on this target, CMake guarantees all shaders 
  # are fully compiled BEFORE it finishes building your engine.
  add_custom_target(${TARGET_NAME} DEPENDS ${SPV_FILES})
  
endfunction()