
add_library(KyraRenderDeviceGL SHARED RenderDeviceGL.cpp
									  Shader.cpp
									  Program.cpp
									  VertexBuffer.cpp
									  Vertexlayout.cpp
									  Texture.cpp
									  Image.cpp
									  Sprite.cpp
									  Text.cpp
									  RectangleShape.cpp)
									  
target_link_libraries(KyraRenderDeviceGL PRIVATE KyraGLExtensionLoader opengl32 gdi32)							  
target_compile_definitions(KyraRenderDeviceGL PRIVATE -DKYRA_RENDERDEVICEGL_EXPORTS)
target_compile_options(KyraRenderDeviceGL PRIVATE -Wall -O3 -Winline)

install(TARGETS KyraRenderDeviceGL RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS KyraRenderDeviceGL ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib)