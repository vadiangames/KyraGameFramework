#include <KyraGameFramework/Core/CmdParameterValue.hpp>
#include <KyraGameFramework/Core/String.hpp>

namespace kyra {
	namespace core {
			
		KYRA_CORE_API CmdParameterValue::CmdParameterValue(const std::string& value) : m_Value(value) {
			
		}
		
		KYRA_CORE_API CmdParameterValue::~CmdParameterValue() {
			
		}
	
		std::string KYRA_CORE_API CmdParameterValue::asString() const {
			return m_Value;
		}
		
		int32_t KYRA_CORE_API CmdParameterValue::asInt32() const {
			return kyra::core::String::toInt32(m_Value);
		}
		
		void KYRA_CORE_API CmdParameterValue::set(const std::string& value) {
			m_Value = value;
		}
	
	}
}