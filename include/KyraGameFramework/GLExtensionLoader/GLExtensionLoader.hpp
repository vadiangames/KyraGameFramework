#ifndef KYRAGAMEFRAMEWORK_GLEXTENSIONLOADER_GLEXTENSIONLOADER_HPP
#define KYRAGAMEFRAMEWORK_GLEXTENSIONLOADER_GLEXTENSIONLOADER_HPP

#include <KyraGameFramework/GLExtensionLoader/DLL.hpp>

#if _MSC_VER == 1800
	
	#include <Windows.h>
	//DO NOT INCLUDE <GL/gl.h>
	
	#ifndef __PRETTY_FUNCTION__
		#define __PRETTY_FUNCTION__ __FUNCSIG__
	#endif
	
#endif

#include <GL/gl.h>

typedef char GLchar;

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define GL_ARRAY_BUFFER 0x8892
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_STATIC_DRAW 0x88E4
#define GL_LINK_STATUS 0x8B82
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30

#define GL_TEXTURE0 0x84C0
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_COMPILE_STATUS 0x8B81

typedef void(__stdcall *PFNGLGENBUFFERSPROC) (GLsizei n, GLuint* buffers);
typedef void(__stdcall *PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void(__stdcall *PFNGLBUFFERDATAPROC) (GLenum target, ptrdiff_t size, const void* data, GLenum usage);
typedef void(__stdcall *PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint* buffers);
typedef void(__stdcall *PFNGLBUFFERSUBDATAPROC) (GLenum target, ptrdiff_t offset, ptrdiff_t size, const void* data);

typedef void(__stdcall *PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint* arrays);
typedef void (__stdcall *PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void (__stdcall *PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint* arrays);

typedef GLuint(__stdcall *PFNGLCREATESHADERPROC) (GLenum type);
typedef void(__stdcall *PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef void(__stdcall *PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
typedef void(__stdcall *PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint* param);
typedef void(__stdcall *PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void(__stdcall *PFNGLDELETESHADERPROC) (GLuint shader);

typedef GLuint(__stdcall *PFNGLCREATEPROGRAMPROC) (void);
typedef void(__stdcall *PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void(__stdcall *PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void(__stdcall *PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint* param);
typedef void(__stdcall *PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
typedef void(__stdcall *PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void(__stdcall *PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef GLint(__stdcall *PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar* name);
typedef void (__stdcall *PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void(__stdcall *PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void(__stdcall *PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat* value);
typedef void(__stdcall *PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat* value);

typedef void(__stdcall *PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
typedef void(__stdcall *PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void(__stdcall *PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);

typedef void(_stdcall *PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void(_stdcall *PFNGLACTIVETEXTUREPROC) (GLenum texture);

#if defined( _WIN32 ) || defined( _WIN64 ) || defined(__WIN32__) || defined(__WIN64__)
	typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);
#endif

// BUFFER FUNCTIONS
KYRA_GLEXTENSIONLOADER_API extern PFNGLGENBUFFERSPROC glGenBuffers;
KYRA_GLEXTENSIONLOADER_API extern PFNGLBINDBUFFERPROC glBindBuffer;
KYRA_GLEXTENSIONLOADER_API extern PFNGLBUFFERDATAPROC	glBufferData;
KYRA_GLEXTENSIONLOADER_API extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
KYRA_GLEXTENSIONLOADER_API extern PFNGLBUFFERSUBDATAPROC glBufferSubData;

//VERTEXARRAY FUNCTIONS
KYRA_GLEXTENSIONLOADER_API extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
KYRA_GLEXTENSIONLOADER_API extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
KYRA_GLEXTENSIONLOADER_API extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

//SHADER FUNCTIONS
KYRA_GLEXTENSIONLOADER_API extern PFNGLCREATESHADERPROC glCreateShader;
KYRA_GLEXTENSIONLOADER_API extern PFNGLCOMPILESHADERPROC glCompileShader;
KYRA_GLEXTENSIONLOADER_API extern PFNGLSHADERSOURCEPROC	glShaderSource;
KYRA_GLEXTENSIONLOADER_API extern PFNGLGETSHADERIVPROC glGetShaderiv;
KYRA_GLEXTENSIONLOADER_API extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
KYRA_GLEXTENSIONLOADER_API extern PFNGLDELETESHADERPROC glDeleteShader;


//PROGRAM FUNCTIONS
KYRA_GLEXTENSIONLOADER_API extern PFNGLCREATEPROGRAMPROC glCreateProgram;
KYRA_GLEXTENSIONLOADER_API extern PFNGLATTACHSHADERPROC glAttachShader;
KYRA_GLEXTENSIONLOADER_API extern PFNGLLINKPROGRAMPROC glLinkProgram;
KYRA_GLEXTENSIONLOADER_API extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
KYRA_GLEXTENSIONLOADER_API extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
KYRA_GLEXTENSIONLOADER_API extern PFNGLUSEPROGRAMPROC glUseProgram;
KYRA_GLEXTENSIONLOADER_API extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
KYRA_GLEXTENSIONLOADER_API extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
KYRA_GLEXTENSIONLOADER_API extern PFNGLUNIFORM1IPROC glUniform1i;
KYRA_GLEXTENSIONLOADER_API extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
KYRA_GLEXTENSIONLOADER_API extern PFNGLUNIFORM3FVPROC glUniform3fv;
KYRA_GLEXTENSIONLOADER_API extern PFNGLUNIFORM4FVPROC glUniform4fv;

//VERTEXLAYOUT FUNCTIONS
KYRA_GLEXTENSIONLOADER_API extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
KYRA_GLEXTENSIONLOADER_API extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
KYRA_GLEXTENSIONLOADER_API extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

//TEXTURE FUNCTIONS
KYRA_GLEXTENSIONLOADER_API extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
KYRA_GLEXTENSIONLOADER_API extern PFNGLACTIVETEXTUREPROC glActiveTexture;

//WGL EXTENSIONS
#if defined( _WIN32 ) || defined( _WIN64 ) || defined(__WIN32__) || defined(__WIN64__)
	KYRA_GLEXTENSIONLOADER_API extern  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
#endif



#include <iostream>
#define GL_CHECK(x) x; {GLenum err = glGetError(); if(err != GL_NO_ERROR) {std::cout <<"[ERROR] " << __FILE__ << " " << __LINE__ << " " << __PRETTY_FUNCTION__ << " Error in OpenGL-Function: " << #x << " ( " << err << " )" << std::endl;}}

namespace kyra {
		
	class KYRA_GLEXTENSIONLOADER_API GLExtensionLoader {

		public:
		~GLExtensionLoader() = delete;
		
		static bool init();
		
	};
}



#endif