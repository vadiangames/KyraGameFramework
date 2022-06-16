#ifndef KYRAGAMEFRAMEWORK_CORE_LOG_HPP
#define KYRAGAMEFRAMEWORK_CORE_LOG_HPP

#include <chrono>
#include <filesystem>
#include <iostream>
#include <source_location>
#include <ctime>
#include <map>

namespace kyra {
	
	enum class LogLevel : uint8_t {
		Info = 1,
		Warn = 2,
		Error = 3,
		Fatal = 4
	};
	
	class Log {
			
		LogLevel m_DefaultLevel;
		std::map<LogLevel, std::string> m_LogLevelDesc;
		
		public:
		Log() {
			m_DefaultLevel = LogLevel::Info;
			
			m_LogLevelDesc[LogLevel::Info] = "INFO";
			m_LogLevelDesc[LogLevel::Warn] = "WARN";
			m_LogLevelDesc[LogLevel::Error] = "ERROR";
			m_LogLevelDesc[LogLevel::Fatal] = "FATAL";
			
		}
		
		static Log& getInstance() {
			static Log instance;
			return instance;
		}
		
		void setLogLevel(LogLevel level) {
			m_DefaultLevel = level;
		}
		
		void log( LogLevel level, const std::string& message, std::source_location loc = std::source_location::current()) {
			if(level >= m_DefaultLevel)	{
				const std::time_t tc = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now() );
				std::stringstream str;
				str << std::put_time(std::localtime(&tc), "%c");
				std::cout <<   "[ " << m_LogLevelDesc[level] <<  " ] " <<  str.str()   << " | " << std::filesystem::path(loc.file_name()).filename().string() << ":" << loc.function_name() << ":" << loc.line() << " | " << message << std::endl;
			}		
		}
		
		
	};

}


#endif