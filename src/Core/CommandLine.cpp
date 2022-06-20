#include <KyraGameFramework/Core/CommandLine.hpp>
#include <KyraGameFramework/Core/String.hpp>
#include <iostream>
#include <vector>

namespace kyra {
	namespace core {
	
		KYRA_CORE_API CommandLine::CommandLine() : m_ExecutableName("") {
			
		}


		KYRA_CORE_API CommandLine::~CommandLine() {
				
		}
			
		
		bool KYRA_CORE_API CommandLine::parse(int argc, char** argv) {
			m_ExecutableName = argv[0];
			for(int i = 1; i < argc; i++) {
				std::string value = std::string(argv[i]);
				if(value.starts_with("--") == false) {
					std::cout << "[ERROR] Invalid parameter " << value << std::endl;
					return false;
				}
				std::vector<std::string> parameterArray = kyra::core::String::split(value, "=");
				if(parameterArray.size() == 2) {
					m_Parameters[parameterArray[0].substr(2)] = CmdParameterValue( parameterArray[1] );
				} else {
					m_Parameters[parameterArray[0].substr(2)] = CmdParameterValue();
				}
			}
			return true;
		}
			
		
		bool KYRA_CORE_API CommandLine::isSet(const std::string& value) const {
			return m_Parameters.find(value) != m_Parameters.end();
		}
			
		CmdParameterValue KYRA_CORE_API CommandLine::getValue(const std::string& value) {
			return m_Parameters[value];
		}
			
		std::string KYRA_CORE_API CommandLine::getExecutableName() const {
			return m_ExecutableName;
		}
				
	}
}
