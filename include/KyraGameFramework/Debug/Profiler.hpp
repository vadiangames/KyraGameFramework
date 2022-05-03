#ifndef KYRAGAMEFRAMEWORK_DEBUG_PROFILER_HPP
#define KYRAGAMEFRAMEWORK_DEBUG_PROFILER_HPP

#include <map>
#include <map>

namespace kyra {
	
	typedef struct {
		uint64_t executionCount = 0;
		double   totalExecTime = 0.0f;
		bool isStarted = false;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
	}ProfileSection;
	
	class Profiler {
		
		static std::map<std::string, ProfileSection> m_Data;
		
		public:
		Profiler() {}
		~Profiler() {}
		
		static void startSection(const std::string& sectionName) {
			if(Profiler::m_Data.find(sectionName) == Profiler::m_Data.end()) {
				Profiler::m_Data[sectionName] = ProfileSection();
			}
			Profiler::m_Data[sectionName].executionCount++;
			Profiler::m_Data[sectionName].isStarted = true;
			m_StartTime = std::chrono::high_resolution_clock::now();
		}
		
		static void endSection(const std::string& sectionName) {
			
		}
		
	};
	
	std::map<std::string, ProfileSection> Profiler::m_Data;
	
	#define PROFILE_START_SECTION(x)	kyra::Profiler::startSection(#x);
	#define PROFILE_END_SECTION(x)		kyra::Profiler::endSection(#x);
	
}

#endif