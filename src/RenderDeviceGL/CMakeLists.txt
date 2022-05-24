
add_library(KyraRenderDeviceGL SHARED RenderDeviceGL.cpp
									  Shader.cpp
									  Program.cpp
									  VertexBuffer.cpp
									  Vertexlayout.cpp
									  Texture.cpp
									  Image.cpp
									  Sprite.cpp
									  Text.cpp
									  RectangleShape.cpp
									  IndexBuffer.cpp)
									  
target_link_libraries(KyraRenderDeviceGL PRIVATE KyraGLExtensionLoader opengl32 gdi32 freetype)							  
target_compile_definitions(KyraRenderDeviceGL PRIVATE -DKYRA_RENDERDEVICEGL_EXPORTS)

if(${KYRA_COMPILER_IS_GCC} EQUAL true)
	target_compile_options(KyraRenderDeviceGL PRIVATE -Wall -O3 -Winline)
endif()


install(TARGETS KyraRenderDeviceGL RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraRenderDeviceGL ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)