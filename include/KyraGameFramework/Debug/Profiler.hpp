#ifndef KYRAGAMEFRAMEWORK_DEBUB_PROFILER_HPP
#define KYRAGAMEFRAMEWORK_DEBUB_PROFILER_HPP

#include <string>
#include <map>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stack>

#include <KyraGameFramework/Debug/DLL.hpp>


namespace kyra {

KYRA_DEBUG_API extern std::string css_style;

typedef struct {
	std::string name;
	size_t calls;
	std::vector<long long int> new_calls;
	long long int total;
	long long int average;
	long long int median;
	std::string parent;
}SectionData;

typedef struct {
	std::string name;
	size_t calls;
	std::vector<long long int> new_calls;
	long long int total;
	long long int average;
	long long int median;
}FunctionData;

class KYRA_DEBUG_API Application {
	
	std::string m_Name;
	std::vector<SectionData> m_SectionData;
	std::vector<FunctionData> m_FunctionData;
	std::stack<std::string> m_Owner;
	
	void calculateStatistics();
	
	void printTotalRuntime(std::ofstream& file);
	
	void printAverageRuntime(std::ofstream& file);
	
	void printCallCount(std::ofstream& file, const std::string& parent, int level);
	
	void printCallTreeTotalRuntime(std::ofstream& file, const std::string& parent);
	
	void printCallTreeAverageRuntime(std::ofstream& file, const std::string& parent);

		
	void printCallTreeCallCount(std::ofstream& file, const std::string& parent);
	
	void saveCapture();
	
	public:
	
	Application();
	
	static Application& getInstance();
	
	
	~Application();
	
	void startCapture(const std::string& name);
	
	void startSection(const std::string& name);
	
	void endSection(const std::string& name, long long int runtime);
	
	
	
};


class KYRA_DEBUG_API Section {
	
	Application* m_Application;
	std::string m_Name;
	std::chrono::time_point<std::chrono::high_resolution_clock>  m_Start;
	
	public:
	Section( Application& app, const std::string& name);

	~Section();
	
};

}

#define KYRA_START_CAPTURE(name)  kyra::Application::getInstance().startCapture(name);kyra::Section section_name(kyra::Application::getInstance(), __PRETTY_FUNCTION__);
#define PROFILER_FUNCTION() kyra::Section section_name(kyra::Application::getInstance(), __PRETTY_FUNCTION__);

#endif