#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP

#include <string>
#include <filesystem>

namespace kyra {
	
	class IProgram {
		
		public:
		
		virtual bool linkFromMemory(const std::string& vertexShader, const std::string& fragmentShader) = 0;
		virtual bool linkFromFile(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader) = 0;
		virtual void use() = 0;
				
	};
	
}

#endif