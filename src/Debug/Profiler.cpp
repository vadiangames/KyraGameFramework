#include <KyraGameFramework/Debug/Profiler.hpp>

namespace kyra {

KYRA_DEBUG_API std::string css_style = "*{"
							"box-sizing: border-box;"
							"-webkit-box-sizing: border-box;"
							"-moz-box-sizing: border-box;"
						"}"
						"body{"
							"font-family: Helvetica;"
							"-webkit-font-smoothing: antialiased;"
							"background: rgba( 71, 147, 227, 1);"
						"}"
						"h1 {"
							"text-align: left;"
							"font-size: 48px;"
							"color: white;"
						"}"
						"h2{"
							"text-align: center;"
							"font-size: 18px;"
							"text-transform: uppercase;"
							"letter-spacing: 1px;"
							"color: white;"
							"padding: 30px 0;"
						"}"
						"h3{"
							"text-align: center;"
							"font-size: 12px;"
							"text-transform: uppercase;"
							"letter-spacing: 1px;"
							"color: white;"
							"padding: 30px 0;"
						"}"
						".table-wrapper{"
							"margin: 10px 70px 70px;"
							"box-shadow: 0px 35px 50px rgba( 0, 0, 0, 0.2 );"
						"}"
						".fl-table {"
							"border-radius: 5px;"
							"font-size: 12px;"
							"font-weight: normal;"
							"border: none;"
							"border-collapse: collapse;"
							"width: 100%;"
							"max-width: 100%;"
							"white-space: nowrap;"
							"background-color: white;"
						"}"
						".fl-table td, .fl-table th {"
							"text-align: center;"
							"padding: 8px;"
						"}"
						".fl-table td {"
							"border-right: 1px solid #f8f8f8;"
							"font-size: 12px;"
						"}"
						".fl-table thead th {"
							"color: #ffffff;"
							"background: #4FC3A1;"
						"}"
						".fl-table thead th:nth-child(odd) {"
							"color: #ffffff;"
							"background: #324960;"
						"}"
						".fl-table tr:nth-child(even) {"
							"background: #F8F8F8;"
						"}";


	void KYRA_DEBUG_API Application::calculateStatistics() {
		for(auto& entry : m_SectionData) {
			entry.total = std::accumulate(entry.new_calls.begin(), entry.new_calls.end(),0);
			entry.average = entry.total / entry.new_calls.size();
		}
		for(auto& entry : m_FunctionData) {
			entry.total = std::accumulate(entry.new_calls.begin(), entry.new_calls.end(),0);
			entry.average = entry.total / entry.new_calls.size();
		}
	}
	
	void KYRA_DEBUG_API Application::printTotalRuntime(std::ofstream& file) {
		std::sort(m_FunctionData.begin(), m_FunctionData.end(), [](const FunctionData& v1, const FunctionData& v2) {return v1.total > v2.total;});
		file << "<div class=\"table-wrapper\"><TABLE class=\"fl-table\">" << std::endl;
		file << "<THEAD><TR><TH>Function</TH><TH>Total runtime in ms</TH></TR></THEAD>"<< std::endl;
		for(auto& entry : m_FunctionData) {
			file << "<TR><TD>"<< entry.name << "</TD><TD>" << entry.total << "</TD></TR>" << std::endl;		
		}
		file << "</TABLE></DIV>" << std::endl;
	}
	
	void KYRA_DEBUG_API Application::printAverageRuntime(std::ofstream& file) {
		std::sort(m_SectionData.begin(), m_SectionData.end(), [](const SectionData& v1, const SectionData& v2) {return v1.average > v2.average;});
		file << "<div class=\"table-wrapper\"><TABLE class=\"fl-table\">" << std::endl;
		file << "<THEAD><TR><TH>Function</TH><TH>Average runtime in ms</TH></TR></THEAD>"<< std::endl;
		for(auto& entry : m_SectionData) {
			file << "<TR><TD>"<< entry.name << "</TD><TD>" << entry.average << " milliseconds</TD></TR>" << std::endl;		
		}
		file << "</TABLE></DIV>" << std::endl;
	}
	
	void KYRA_DEBUG_API Application::printCallCount(std::ofstream& file, const std::string& parent = "", int level = 0) {
		std::sort(m_SectionData.begin(), m_SectionData.end(), [](const SectionData& v1, const SectionData& v2) {return v1.new_calls.size() > v2.new_calls.size();});
		file << "<div class=\"table-wrapper\"><TABLE class=\"fl-table\">" << std::endl;
		file << "<THEAD><TR><TH>Function</TH><TH>No. of calls</TH></TR></THEAD>"<< std::endl;
		for(auto& entry : m_SectionData) {
			file << "<TR><TD>"<< entry.name << "</TD><TD>" << entry.new_calls.size() << " calls</TD></TR>" << std::endl;		
		}
		file << "</TABLE></DIV>" << std::endl;
	}
	
	void KYRA_DEBUG_API Application::printCallTreeTotalRuntime(std::ofstream& file, const std::string& parent = "") {

		std::sort(m_SectionData.begin(), m_SectionData.end(), [](const SectionData& v1, const SectionData& v2) {return v1.total > v2.total;});
		
		size_t count = 0;
		for(auto& entry : m_SectionData) {
			if(entry.parent == parent) {
				count++;
			}
		}
	
		if(count > 0) {
			file << "<H3>"<<parent<<"</H3>" << std::endl;
			file << "<div class=\"table-wrapper\"><TABLE class=\"fl-table\">" << std::endl;
			file << "<THEAD><TR><TH>Function</TH><TH>Total runtime in ms</TH></TR></THEAD>"<< std::endl;
			for(auto& entry : m_SectionData) {
				if(entry.parent == parent) {
					file << "<TR><TD>"<< entry.name << "</TD><TD>" << entry.total << " milliseconds</TD></TR>" << std::endl;		
				}
			}
			file << "</TABLE></DIV>" << std::endl;
		}
					
	}

	void KYRA_DEBUG_API Application::printCallTreeAverageRuntime(std::ofstream& file, const std::string& parent = "") {

		std::sort(m_SectionData.begin(), m_SectionData.end(), [](const SectionData& v1, const SectionData& v2) {return v1.average > v2.average;});
		
		size_t count = 0;
		for(auto& entry : m_SectionData) {
			if(entry.parent == parent) {
				count++;
			}
		}
	
		if(count > 0) {
			file << "<H3>"<<parent<<"</H3>" << std::endl;
			file << "<div class=\"table-wrapper\"><TABLE class=\"fl-table\">" << std::endl;
			file << "<THEAD><TR><TH>Function</TH><TH>Average runtime in ms</TH></TR></THEAD>"<< std::endl;
			for(auto& entry : m_SectionData) {
				if(entry.parent == parent) {
					file << "<TR><TD>"<< entry.name << "</TD><TD>" << entry.average << " milliseconds</TD></TR>" << std::endl;		
				}
			}
			file << "</TABLE></DIV>" << std::endl;
		}
					
	}

		
	void KYRA_DEBUG_API Application::printCallTreeCallCount(std::ofstream& file, const std::string& parent = "") {

		size_t count = 0;
		for(auto& entry : m_SectionData) {
			if(entry.parent == parent) {
				count++;
			}
		}
	
		if(count > 0) {
			file << "<H3>"<<parent<<"</H3>" << std::endl;
			file << "<div class=\"table-wrapper\"><TABLE class=\"fl-table\">" << std::endl;
			file << "<THEAD><TR><TH>Function</TH><TH>Calls</TH></TR></THEAD>"<< std::endl;
			for(auto& entry : m_SectionData) {
				if(entry.parent == parent) {
					file << "<TR><TD>"<< entry.name << "</TD><TD>" << entry.new_calls.size() << "Calls</TD></TR>" << std::endl;		
				}
			}
			file << "</TABLE></DIV>" << std::endl;
		}

	}
	
	
	void KYRA_DEBUG_API Application::saveCapture() {
		std::string filename = m_Name + "_profile.html";
		
		calculateStatistics();
		
		std::ofstream file;
		file.open(filename.c_str());
		
		file << "<HTML><HEAD><STYLE>"<< css_style << "</STYLE></HEAD><BODY>" << std::endl;
		file << "<H1>SeasonSimulator</H1>" << std::endl;
		file << "<H2>Total Runtime</H2>" << std::endl;
		printTotalRuntime(file);
		file << "<H2>Average Runtime</H2>" << std::endl;
		printAverageRuntime(file);
		file << "<H2>Call Count</H2>" << std::endl;
		printCallCount(file);
		file << "<H2>Calltree - Total Runtime</H2>" << std::endl;
		for(auto& entry : m_SectionData) {
			printCallTreeTotalRuntime(file, entry.name);
		}
		file << "<H2>Calltree - Average Runtime</H2>" << std::endl;
		for(auto& entry : m_SectionData) {
			printCallTreeAverageRuntime(file, entry.name);
		}
		file << "<H2>Calltree - Call Count</H2>" << std::endl;
		for(auto& entry : m_SectionData) {
			printCallTreeCallCount(file, entry.name);
		}
		file << "</BODY></HTML>" << std::endl;
		file.close();
	}
	
	
	KYRA_DEBUG_API Application::Application() {

	}
	

	Application& KYRA_DEBUG_API Application::getInstance() {
		static Application instance;
		return instance;
	}
	
	
	KYRA_DEBUG_API Application::~Application() {
		saveCapture();
	}
	
	void KYRA_DEBUG_API Application::startCapture(const std::string& name) {
		m_Name = name;
	}
	
	void KYRA_DEBUG_API Application::startSection(const std::string& name) {
		std::vector<SectionData>::iterator it = std::find_if(m_SectionData.begin(), m_SectionData.end(), [&](const SectionData& data){ return data.name == name; } );
		if(it == m_SectionData.end()) {
			SectionData tmp;
			tmp.name = name;
			tmp.calls = 0;
			tmp.total = 0;
			tmp.average = 0;
			tmp.median = 0;
			if(m_Owner.size() > 0) {
				tmp.parent = m_Owner.top();
			}
			m_SectionData.push_back(tmp);
		}
		
		std::vector<FunctionData>::iterator func_it = std::find_if(m_FunctionData.begin(), m_FunctionData.end(), [&](const FunctionData& data){ return data.name == name; } );
		if(func_it == m_FunctionData.end()) {
			FunctionData tmp;
			tmp.name = name;
			tmp.calls = 0;
			tmp.total = 0;
			tmp.average = 0;
			tmp.median = 0;
			m_FunctionData.push_back(tmp);
		}
				
		m_Owner.push(name);
	}
	
	void KYRA_DEBUG_API Application::endSection(const std::string& name, long long int runtime) {
		if(m_Owner.size() > 0) {
			m_Owner.pop();
		}
		std::string ownerStr = (m_Owner.size() == 0) ? "" : m_Owner.top();
		
		std::vector<SectionData>::iterator it = std::find_if(m_SectionData.begin(), m_SectionData.end(), [&](const SectionData& data){ return (data.name == name) && (data.parent == ownerStr); } );
		if(it != m_SectionData.end()) {
			it->new_calls.push_back(runtime);
		}
		
		std::vector<FunctionData>::iterator func_it = std::find_if(m_FunctionData.begin(), m_FunctionData.end(), [&](const FunctionData& data){ return data.name == name; } );
		if(func_it != m_FunctionData.end()) {
			func_it->new_calls.push_back(runtime);
		}
	}
	

	KYRA_DEBUG_API Section::Section( Application& app, const std::string& name) : m_Application(&app), m_Name(name), m_Start(std::chrono::high_resolution_clock::now()) {
		m_Application->startSection(m_Name);
	}

	KYRA_DEBUG_API Section::~Section() {
		std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
		m_Application->endSection(m_Name, (end - m_Start).count() / 1000000 );
	}

}