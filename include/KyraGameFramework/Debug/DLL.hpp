#ifndef KYRAGAMEFRAMEWORK_DEBUG_DLL_HPP
#define KYRAGAMEFRAMEWORK_DEBUG_DLL_HPP

#ifdef KYRA_DEBUG_EXPORTS
  #define KYRA_DEBUG_API __declspec(dllexport)
#else
  #define KYRA_DEBUG_API __declspec(dllimport)
#endif

#endif