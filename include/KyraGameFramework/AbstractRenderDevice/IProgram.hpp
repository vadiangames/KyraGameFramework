#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP

#include <string>
#include <filesystem>
#include <memory>

#include <glm/glm.hpp>

namespace kyra {

	/// A program consists of a vertex shader and a fragment shader. 
	/// Geometry shaders are currently not supported. 
	/// Uniforms can also be accessed through the class.

	/// Internal shader programs are managed separately from the rest of the shaders. 
	/// There are currently internal shaders for text and sprite rendering.
	
	/// \brief Type of the internal shader program
	enum class InternalProgramType{
		TEXT,
		SPRITE
	};
	
	//! Abstract class for shader program classes
	class IProgram {
		
		public:
		
		typedef std::shared_ptr<IProgram> Ptr;
		
		/// \brief Sets the uniform to an integer value
		///	\param id The id of the uniform
		///	\param value The new value of the uniform
		virtual void setInteger(const std::string& id, int value) = 0;
		
		/// Sets the uniform to an matrix4 value
		///	\param id The id of the uniform
		///	\param matrix4 The new value of the uniform 
		virtual void setMatrix4(const std::string& id, const glm::mat4& matrix) = 0;
		
		/// \brief Sets the uniform-vector3 id to the value of vec
		///	\param id The id of the uniform
		///	\param matrix4 The new value of the uniform 
		virtual void setVector3(const std::string& id, const glm::vec3& vec) = 0;
		
		/// \brief Links the program - getting the shaders by string 
		///	\param vertexShader The source code of the vertex shader
		///	\param fragmentShader The source code of the fragment shader 
		///	\return true if the shaders could compile succesfully or false if there was an error 
		virtual bool linkFromMemory(const std::string& vertexShader, const std::string& fragmentShader) = 0;
		
		/// Links the program - getting the shaders from file 
		///	\param vertexShader The file with the source code of the vertex shader
		///	\param fragmentShader The file with source code of the fragment shader 
		///	\return true if the shaders could compile succesfully or false if there was an error 
		virtual bool linkFromFile(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader) = 0;
		
		/// \brief Activates the program 
		virtual void use() = 0;
				
	};
	
}

#endif