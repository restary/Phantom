
# Setup graphics API
IF(BUILD_OS STREQUAL "Windows")
    SET(GRAPHICS_API "DX11")
ELSE()
    SET(GRAPHICS_API "OpenGL")
ENDIF()

add_subdirectory(GraphicsInterface/${GRAPHICS_API})


add_library(Render
        RenderSystem.cpp
        GraphicsInterface/GraphicsInterface.cpp
        GraphicsInterface/${GRAPHICS_API}/${GL_RHI_SRC}
        )