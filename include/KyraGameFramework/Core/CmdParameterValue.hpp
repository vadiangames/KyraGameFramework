#ifndef KYRAGAMEFRAMEWORK_CORE_CMDPARAMTERVALUE_HPP
#define KYRAGAMEFRAMEWORK_CORE_CMDPARAMTERVALUE_HPP

#include <KyraGameFramework/Core/DLL.hpp>
#include <string>
#include <cstdint>

namespace kyra {
	namespace core {
		
		/// Represents a value of a commandline-parameter, provides functions to convert the value to different types 
		class KYRA_CORE_API CmdParameterValue {
			
			std::string m_Value;	//!< The value of the parameter
			
			public:
			
			/// Default constructor, sets the value to ""
			CmdParameterValue(const std::string& value="");
			
			/// Default destructor
			~CmdParameterValue();
			
			/// Returns the value of the parameter as string
			std::string asString() const;
			
			int32_t asInt32() const;
			
			/// Sets the value
			void set(const std::string& value);
		};
		
	}
}

#endif