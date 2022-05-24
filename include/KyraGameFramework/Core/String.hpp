#ifndef KYRAGAMEFRAMEWORK_CORE_STRING_HPP
#define KYRAGAMEFRAMEWORK_CORE_STRING_HPP

#include <vector>
#include <string>

namespace kyra {
	namespace core {
		class String {
			
			public:
			static std::vector<std::string> split(std::string text, const std::string& limiter) {
				std::vector<std::string> data;
				size_t pos = text.find(limiter);
				while(pos != std::string::npos) {
					data.push_back( text.substr(0, pos) );
					text = text.substr(pos+limiter.size());
					pos = text.find(limiter);
				}
				return data;
			}
			
			static int64_t toInt64(const std::string& text) {
				return atol(text.c_str());
			}
		};
	}
}

#endif