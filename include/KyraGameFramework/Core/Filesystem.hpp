#ifndef KYRAGAMEFRAMEWORK_CORE_FILESYSTEM_HPP
#define KYRAGAMEFRAMEWORK_CORE_FILESYSTEM_HPP

#include <filesystem>

#ifdef _MSC_VER

namespace std {
	namespace filesystem = std::tr2::sys;
}

#endif



#endif