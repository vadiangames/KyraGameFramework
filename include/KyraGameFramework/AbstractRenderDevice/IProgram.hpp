#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP

#include <string>
#include <filesystem>
#include <memory>

#include <glm/glm.hpp>

namespace kyra {
	
	class IProgram {
		
		public:
		
		typedef std::shared_ptr<IProgram> Ptr;
		
		virtual void setInteger(const std::string& id, int value) = 0;
		virtual void setMatrix4(const std::string& id, const glm::mat4& matrix) = 0;
		virtual void setVector3(const std::string& id, const glm::vec3& vec) = 0;
		
		virtual bool linkFromMemory(const std::string& vertexShader, const std::string& fragmentShader) = 0;
		virtual bool linkFromFile(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader) = 0;
		virtual void use() = 0;
				
	};
	
}

#endif