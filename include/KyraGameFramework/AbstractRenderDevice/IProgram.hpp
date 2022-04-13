#ifndef KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP
#define KYRAGAMEFRAMEWORK_ABSTRACTRENDERDEVICE_IPROGRAM_HPP

#include <string>

namespace kyra {
	
	class IProgram {
		
		public:
		
		virtual bool linkFromMemory(const std::string& vertexShader, const std::string& fragmentShader) = 0;
		virtual void use() = 0;
				
	};
	
}

#endif