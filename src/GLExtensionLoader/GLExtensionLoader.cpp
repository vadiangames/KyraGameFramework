
#include <KyraGameFramework/GLExtensionLoader/GLExtensionLoader.hpp>
#include <iostream>

//BUFFER FUNCTION

KYRA_GLEXTENSIONLOADER_API PFNGLGENBUFFERSPROC glGenBuffers = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLBINDBUFFERPROC glBindBuffer = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLBUFFERDATAPROC	glBufferData = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;

//VERTEXARRAY FUNCTIONS
KYRA_GLEXTENSIONLOADER_API PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;

//SHADER FUNCTIONS

KYRA_GLEXTENSIONLOADER_API PFNGLCREATESHADERPROC glCreateShader = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLCOMPILESHADERPROC glCompileShader = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLSHADERSOURCEPROC	glShaderSource = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLDELETESHADERPROC glDeleteShader = NULL;

//PROGRAM FUNCTIONS

KYRA_GLEXTENSIONLOADER_API PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLATTACHSHADERPROC glAttachShader = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLUSEPROGRAMPROC glUseProgram = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLUNIFORM1IPROC glUniform1i = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLUNIFORM4FVPROC glUniform4fv = NULL;

KYRA_GLEXTENSIONLOADER_API PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;

KYRA_GLEXTENSIONLOADER_API PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;
KYRA_GLEXTENSIONLOADER_API PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;

KYRA_GLEXTENSIONLOADER_API PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;


namespace kyra {
		
	#define INIT_GL_FUNC(x,y) x = (y)wglGetProcAddress(#x); if(x == NULL) { std::cout <<"[ERROR] Can not load GL-Function: " << #x << " " << glGetError() << std::endl; return false;}
	
	bool KYRA_GLEXTENSIONLOADER_API GLExtensionLoader::init()  {
		
		INIT_GL_FUNC(glGenBuffers, PFNGLGENBUFFERSPROC);
		INIT_GL_FUNC(glBindBuffer, PFNGLBINDBUFFERPROC);
		INIT_GL_FUNC(glBufferData, PFNGLBUFFERDATAPROC);
		INIT_GL_FUNC(glDeleteBuffers, PFNGLDELETEBUFFERSPROC);
		INIT_GL_FUNC(glBufferSubData,PFNGLBUFFERSUBDATAPROC);

		INIT_GL_FUNC(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC);
		INIT_GL_FUNC(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC);
		INIT_GL_FUNC(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC);

		INIT_GL_FUNC(glCreateShader, PFNGLCREATESHADERPROC);
		INIT_GL_FUNC(glCompileShader, PFNGLCOMPILESHADERPROC);
		INIT_GL_FUNC(glShaderSource, PFNGLSHADERSOURCEPROC);
		INIT_GL_FUNC(glGetShaderiv, PFNGLGETSHADERIVPROC);
		INIT_GL_FUNC(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC);
		INIT_GL_FUNC(glDeleteShader, PFNGLDELETESHADERPROC);
		
		INIT_GL_FUNC(glCreateProgram, PFNGLCREATEPROGRAMPROC);
		INIT_GL_FUNC(glAttachShader, PFNGLATTACHSHADERPROC);
		INIT_GL_FUNC(glLinkProgram, PFNGLLINKPROGRAMPROC);
		INIT_GL_FUNC(glGetProgramiv, PFNGLGETPROGRAMIVPROC);
		INIT_GL_FUNC(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC);
		INIT_GL_FUNC(glUseProgram, PFNGLUSEPROGRAMPROC);
		INIT_GL_FUNC(glDeleteProgram, PFNGLDELETEPROGRAMPROC);
		INIT_GL_FUNC(glGetUniformLocation,PFNGLGETUNIFORMLOCATIONPROC);
		INIT_GL_FUNC(glUniform1i, PFNGLUNIFORM1IPROC);
		INIT_GL_FUNC(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC);
		INIT_GL_FUNC(glUniform3fv, PFNGLUNIFORM3FVPROC);
		INIT_GL_FUNC(glUniform4fv, PFNGLUNIFORM4FVPROC);

		INIT_GL_FUNC(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC);
		INIT_GL_FUNC(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC);
		INIT_GL_FUNC(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC);
		
		INIT_GL_FUNC(glGenerateMipmap, PFNGLGENERATEMIPMAPPROC);
		INIT_GL_FUNC(glActiveTexture, PFNGLACTIVETEXTUREPROC);
		
		INIT_GL_FUNC(wglCreateContextAttribsARB, PFNWGLCREATECONTEXTATTRIBSARBPROC );
		return true;
	}
	
}