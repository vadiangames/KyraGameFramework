#ifndef KYRAGAMEFRAMEWORK_DEBUG_PROFILER_HPP
#define KYRAGAMEFRAMEWORK_DEBUG_PROFILER_HPP

#include <map>
#include <chrono>
#include <cstdint>
#include <string>
#include <ostream>


using namespace std::literals;

namespace kyra {
	
	typedef struct {
		uint64_t executionCount = 0;
		double   totalExecTime = 0.0f;
		bool isStarted = false;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		std::string parent;
	}ProfileSection;
	
	class Profiler {
		
		static std::map<std::string, ProfileSection> m_Data;
		static std::string m_ActiveSection;
		
		public:
		
		static void startSection(const std::string& sectionName) {
			if(Profiler::m_Data.find(sectionName) == Profiler::m_Data.end()) {
				Profiler::m_Data[sectionName] = ProfileSection();
			}
			Profiler::m_Data[sectionName].isStarted = true;
			Profiler::m_Data[sectionName].startTime = std::chrono::high_resolution_clock::now();
			if(Profiler::m_ActiveSection != "") {
				Profiler::m_Data[sectionName].parent = m_ActiveSection;
			}
			Profiler::m_ActiveSection = sectionName;
		}
		
		static void endSection(const std::string& sectionName) {
			std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
			if(Profiler::m_Data[sectionName].isStarted) {
				Profiler::m_Data[sectionName].executionCount++;
				Profiler::m_Data[sectionName].isStarted = false;
				Profiler::m_Data[sectionName].totalExecTime += (endTime - Profiler::m_Data[sectionName].startTime) / 1ms;
			}
			Profiler::m_ActiveSection = Profiler::m_Data[sectionName].parent;
		}
		
		static void print(std::ostream& stream) {
			stream << "PROFILING STATISTICS" << std::endl;
			for(auto& entry : Profiler::m_Data) {
				double execTimePerSample = (entry.second.totalExecTime / entry.second.executionCount);
				if(entry.second.totalExecTime == 0 && entry.second.executionCount == 0) {
					execTimePerSample = 0;
				}
				stream << entry.first << " " << entry.second.parent << " " << entry.second.executionCount << " " << entry.second.totalExecTime << " " << (entry.second.totalExecTime / entry.second.executionCount) << std::endl;
			}
		}
		
	};
	
	std::map<std::string, ProfileSection> Profiler::m_Data;
	std::string Profiler::m_ActiveSection = "";

	#define PROFILE_START_SECTION(x)	kyra::Profiler::startSection(#x);
	#define PROFILE_END_SECTION(x)		kyra::Profiler::endSection(#x);
	#define PROFILE_PRINT(x)			kyra::Profiler::print(x);
	#define PROFILE_START_FUNCTION()	kyra::Profiler::startSection(__PRETTY_FUNCTION__);
	#define PROFILE_END_FUNCTION()		kyra::Profiler::endSection(__PRETTY_FUNCTION__);
}

#endif